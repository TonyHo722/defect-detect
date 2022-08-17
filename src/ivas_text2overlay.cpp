/*
 * Copyright 2021 Xilinx, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <ivas/ivas_kernel.h>
#include <gst/ivas/gstinferencemeta.h>

//Willy debug - s
#include <list>
//Willy debug - e

int log_level;
using namespace cv;
using namespace std;

#define DEFAULT_DEFECT_THRESHOLD  0.16

enum
{
  LOG_LEVEL_ERROR,
  LOG_LEVEL_WARNING,
  LOG_LEVEL_INFO,
  LOG_LEVEL_DEBUG
};

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define LOG_MESSAGE(level, ...) {\
  do {\
    char *str; \
    if (level == LOG_LEVEL_ERROR)\
      str = (char*)"ERROR";\
    else if (level == LOG_LEVEL_WARNING)\
      str = (char*)"WARNING";\
    else if (level == LOG_LEVEL_INFO)\
      str = (char*)"INFO";\
    else if (level == LOG_LEVEL_DEBUG)\
      str = (char*)"DEBUG";\
    if (level <= log_level) {\
      printf("[%s %s:%d] %s: ",__FILENAME__, __func__, __LINE__, str);\
      printf(__VA_ARGS__);\
      printf("\n");\
    }\
  } while (0); \
}


struct overlayframe_info
{
  IVASFrame *inframe;
  Mat lumaImg;
};

struct ivas_xoverlaypriv
{
  float font_size;
  float defect_threshold;
  unsigned int is_acc_result;
  unsigned int font;
  unsigned int y_offset;
  unsigned int x_offset;
  unsigned int total_defect;
  struct overlayframe_info frameinfo;
};


//Willy debug - s

typedef struct

{
	int x;
	int y;
	int width;
	int height;
} icObject;

typedef struct

{
	int x;
	int y;
	int width;
	int height;
	int size;
	int centroids_x;
	int centroids_y;
} ccObject;



// comparison, not case sensitive.
bool list_compare(const ccObject& first, const ccObject& second)
{
	return (first.size < second.size);
}


int DetermineDirection(Mat img)
{
	int width = img.size().width;
	int height = img.size().height;

	Mat img_binary_ic;
	threshold(img, img_binary_ic, 0, 255, THRESH_BINARY | THRESH_OTSU);

	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));

	Mat img_dilate;
	dilate(img_binary_ic, img_dilate, element, Point(-1, -1), 4);

	Mat img_target = img_dilate;

	//imshow("img_ic", img_target);
	Mat labels, stats, centroids;

	int nccomps = cv::connectedComponentsWithStats(
		img_target,
		labels,
		stats,
		centroids
	);




	int cc_size, cc_centroids_x, cc_centroids_y, cc_x, cc_y, cc_width, cc_height;
	double ratio, pxielpercent;

	std::list<ccObject> ccObjectList;

	ccObject ccObjecttmp;

	for (int index = 1; index < nccomps; index++) {
		cc_centroids_x = (int)centroids.at<double>(index, 0);
		cc_centroids_y = (int)centroids.at<double>(index, 1);
		cc_x = stats.at<int>(index, 0);
		cc_y = stats.at<int>(index, 1);
		cc_width = stats.at<int>(index, 2);
		cc_height = stats.at<int>(index, 3);
		cc_size = stats.at<int>(index, 4);

		ratio = (double)cc_height / (double)cc_width;
		pxielpercent = (double)cc_size / (double)(cc_height * cc_width);

		if ((cc_width >= 20) &&
			(cc_width <= 120) &&
			(cc_height >= 20) &&
			(cc_height <= 120) &&
			(ratio >= 0.7) &&
			(ratio <= 1.5) &&
			(pxielpercent >= 0.5)
			)
		{
			//Record the CC objects
			ccObjecttmp.x = cc_x;
			ccObjecttmp.y = cc_y;
			ccObjecttmp.width = cc_width;
			ccObjecttmp.height = cc_height;
			ccObjecttmp.centroids_x = cc_centroids_x;
			ccObjecttmp.centroids_y = cc_centroids_y;
			ccObjecttmp.size = cc_size;

			ccObjectList.push_back(ccObjecttmp);
		}
	}



	//Check IC must have a CC object in the center, if not, determine it is empty.
	//We check the max size cc object does it in the center.

	ccObjectList.sort(list_compare);
	ccObjectList.reverse();

	ccObject ccObjecttmp2;
	int x_diff, y_diff;
	if (ccObjectList.size() == 2)
	{
		ccObjecttmp = ccObjectList.front();
		cc_centroids_x = ccObjecttmp.centroids_x;
		cc_centroids_y = ccObjecttmp.centroids_y;

		if ((cc_centroids_x < (double)width * 0.3) ||
			(cc_centroids_x >(double)width * 0.7) ||
			(cc_centroids_y < (double)height * 0.3) ||
			(cc_centroids_y >(double)height * 0.7)
			)
		{
			return 0;
		}

		ccObjecttmp2 = ccObjectList.back();
		x_diff = ccObjecttmp2.x - ccObjecttmp.x;
		y_diff = ccObjecttmp2.y - ccObjecttmp.y;
		if ((x_diff <= 0) && (y_diff <= 0))
		{
			return 1;
		}
		else if ((x_diff >= 0) && (y_diff <= 0))
		{
			return 2;
		}
		else if ((x_diff <= 0) && (y_diff >= 0))
		{
			return 3;
		}
		else
		{
			return 4;
		}

	}
	else
	{
		return 0;
	}

}

//Willy debug - e



extern "C"
{
  int32_t xlnx_kernel_init (IVASKernel * handle)
  {
    LOG_MESSAGE (LOG_LEVEL_DEBUG, "enter");

    ivas_xoverlaypriv *kpriv =
        (ivas_xoverlaypriv *) malloc (sizeof (ivas_xoverlaypriv));
    memset (kpriv, 0, sizeof (ivas_xoverlaypriv));

    json_t *jconfig = handle->kernel_config;
    json_t *val;

    /* Initialize config params with default values */
    kpriv->total_defect = 0;

    val = json_object_get (jconfig, "debug_level");
    if (!val || !json_is_integer (val))
        log_level = LOG_LEVEL_WARNING;
    else
        log_level = json_integer_value (val);
    LOG_MESSAGE (LOG_LEVEL_DEBUG, "log level %u", log_level);

    val = json_object_get (jconfig, "font_size");
    if (!val || !json_is_number (val))
        kpriv->font_size = 0.5;
    else
        kpriv->font_size = json_number_value (val);
    LOG_MESSAGE (LOG_LEVEL_DEBUG, "font size %lf", kpriv->font_size);

    val = json_object_get (jconfig, "font");
    if (!val || !json_is_integer (val))
        kpriv->font = 0;
    else
        kpriv->font = json_integer_value (val);
    LOG_MESSAGE (LOG_LEVEL_DEBUG, "font type %u", kpriv->font);

    val = json_object_get(jconfig, "defect_threshold");
    if (!val || !json_is_number(val))
        kpriv->defect_threshold = DEFAULT_DEFECT_THRESHOLD;
    else
        kpriv->defect_threshold = json_number_value(val);
    LOG_MESSAGE (LOG_LEVEL_DEBUG, "defect threshold %lf", kpriv->defect_threshold);

    val = json_object_get(jconfig, "is_acc_result");
    if (!val || !json_is_integer(val))
        kpriv->is_acc_result = 1;
    else
        kpriv->is_acc_result = json_integer_value(val);
    LOG_MESSAGE (LOG_LEVEL_DEBUG, "Is accumulated result %d", kpriv->is_acc_result);

    val = json_object_get (jconfig, "y_offset");
    if (!val || !json_is_integer (val))
        kpriv->y_offset = 30;
    else
        kpriv->y_offset = json_integer_value (val);
    LOG_MESSAGE (LOG_LEVEL_DEBUG, "Y Offset %u", kpriv->y_offset);

    val = json_object_get (jconfig, "x_offset");
    if (!val || !json_is_integer (val))
        kpriv->x_offset = 800;
    else
        kpriv->x_offset = json_integer_value (val);
    LOG_MESSAGE (LOG_LEVEL_DEBUG, "X Offset %u", kpriv->x_offset);

    handle->kernel_priv = (void *) kpriv;
    return 0;
  }

  uint32_t xlnx_kernel_deinit (IVASKernel * handle)
  {
    LOG_MESSAGE (LOG_LEVEL_DEBUG, "enter");
    ivas_xoverlaypriv *kpriv = (ivas_xoverlaypriv *) handle->kernel_priv;

    if (kpriv)
        free (kpriv);

    return 0;
  }



  uint32_t xlnx_kernel_start (IVASKernel * handle, int start,
      IVASFrame * input[MAX_NUM_OBJECT], IVASFrame * output[MAX_NUM_OBJECT])
  {
    ivas_xoverlaypriv *kpriv = (ivas_xoverlaypriv *) handle->kernel_priv;
    struct overlayframe_info *frameinfo = &(kpriv->frameinfo);
    frameinfo->inframe = input[0];

	LOG_MESSAGE(LOG_LEVEL_INFO, "input[0]=%p", input[0]);
	LOG_MESSAGE(LOG_LEVEL_INFO, "output[0]=%p", output[0]);
	
    char *lumaBuf = (char *) frameinfo->inframe->vaddr[0];

    frameinfo->lumaImg.create (input[0]->props.height, input[0]->props.stride, CV_8U);
    frameinfo->lumaImg.data = (unsigned char *) lumaBuf;
	
	//Willy debug - s
	char text_buffer[512] = { 0, };
	int y_point = kpriv->y_offset;


	//The origirnal input (lumaImg is gray already)
	Mat img_gray = frameinfo->lumaImg.clone();
	//cvtColor(frameinfo->lumaImg, img_gray, COLOR_BGR2GRAY);

	Mat img_binary;
	threshold(img_gray, img_binary, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);


	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
	Mat img_dilate, img_erode;

	dilate(img_binary, img_dilate, element, Point(-1, -1), 1);

	erode(img_dilate, img_erode, element, Point(-1, -1), 1);


	Mat img_target = img_dilate;

	Mat labels, stats, centroids;

	int nccomps = cv::connectedComponentsWithStats(
		img_target,
		labels,
		stats,
		centroids
	);

	LOG_MESSAGE(LOG_LEVEL_INFO, "CC objects: %d", nccomps);
	sprintf(text_buffer, "CC objects: %d", nccomps);
	putText(frameinfo->lumaImg, text_buffer, cv::Point(kpriv->x_offset, y_point), kpriv->font,
		kpriv->font_size, Scalar(255.0, 255.0, 255.0), 1, 1);
	y_point += 30;


	int cc_size, cc_centroids_x, cc_centroids_y, cc_x, cc_y, cc_width, cc_height;


	bool ic_found = false;
	icObject icObjects[4];

	for (int index = 1; index < nccomps; index++) {
		cc_centroids_x = (int)centroids.at<double>(index, 0);
		cc_centroids_y = (int)centroids.at<double>(index, 1);
		cc_x = stats.at<int>(index, 0);
		cc_y = stats.at<int>(index, 1);
		cc_width = stats.at<int>(index, 2);
		cc_height = stats.at<int>(index, 3);
		cc_size = stats.at<int>(index, 4);

		if ((cc_width >= 250) &&
			(cc_width <= 350) &&
			(cc_height >= 250) &&
			(cc_height <= 350)
			)
		{
			ic_found = true;

			// Print the circle and rectangle for the CCs
			cv::rectangle(frameinfo->lumaImg,
				cv::Point(cc_x, cc_y),
				cv::Point(cc_x + cc_width, cc_y + cc_height),
				cv::Scalar(255, 255, 255),
				2, 8, 0);


			// Print the line for the 4 IC traps
			cv::line(frameinfo->lumaImg,
				cv::Point(cc_centroids_x, cc_y),
				cv::Point(cc_centroids_x, cc_y + cc_height),
				cv::Scalar(255, 255, 255),
				2);
			cv::line(frameinfo->lumaImg,
				cv::Point(cc_x, cc_centroids_y),
				cv::Point(cc_x + cc_width, cc_centroids_y),
				cv::Scalar(255, 255, 255),
				2);

			// Seperate 4 IC blocks
			// Top Left
			icObjects[0].x = cc_x;
			icObjects[0].y = cc_y;
			icObjects[0].width = cc_width / 2;
			icObjects[0].height = cc_height / 2;

			// Top Right
			icObjects[1].x = cc_x + cc_width / 2;
			icObjects[1].y = cc_y;
			icObjects[1].width = cc_width / 2;
			icObjects[1].height = cc_height / 2;


			// Button Left
			icObjects[2].x = cc_x;
			icObjects[2].y = cc_y + cc_height / 2;
			icObjects[2].width = cc_width / 2;
			icObjects[2].height = cc_height / 2;

			// Button Right
			icObjects[3].x = cc_x + cc_width / 2;
			icObjects[3].y = cc_y + cc_height / 2;
			icObjects[3].width = cc_width / 2;
			icObjects[3].height = cc_height / 2;
			break;
		}
	}


	if (ic_found)
	{

		LOG_MESSAGE(LOG_LEVEL_INFO, "IC trap is found");
		sprintf(text_buffer, "IC trap is found");
		/* Draw label text on the filled rectanngle */
		putText(frameinfo->lumaImg, text_buffer, cv::Point(kpriv->x_offset, y_point), kpriv->font,
		kpriv->font_size, Scalar(255.0, 255.0, 255.0), 1, 1);

		for (int index = 0; index < 4; index++)
		{
			int x = icObjects[index].x;
			int y = icObjects[index].y;
			int width = icObjects[index].width;
			int height = icObjects[index].height;
			int central_x = (width / 2) + x;
			int central_y = (height / 2) + y;

			Rect rect_ic(x, y, width, height);
			Mat img_ic = Mat(img_gray, rect_ic);

			int result = DetermineDirection(img_ic);


			if (result == 0)
			{
				cv::line(frameinfo->lumaImg,
					cv::Point(x, y),
					cv::Point(x + width, y + height),
					cv::Scalar(255, 255, 255),
					2);
				cv::line(frameinfo->lumaImg,
					cv::Point(x, y + height),
					cv::Point(x + width, y),
					cv::Scalar(255, 255, 255),
					2);
			}
			else if (result == 1)
			{
				cv::arrowedLine(frameinfo->lumaImg,
					cv::Point(central_x, central_y),
					cv::Point(x, y),
					cv::Scalar(255, 255, 255),
					2, 0, 0, 0.2);
			}
			else if (result == 2)
			{
				cv::arrowedLine(frameinfo->lumaImg,
					cv::Point(central_x, central_y),
					cv::Point(x + width, y),
					cv::Scalar(255, 255, 255),
					2, 0, 0, 0.2);
			}
			else if (result == 3)
			{
				cv::arrowedLine(frameinfo->lumaImg,
					cv::Point(central_x, central_y),
					cv::Point(x, y + height),
					cv::Scalar(255, 255, 255),
					2, 0, 0, 0.2);
			}
			else if (result == 4)
			{
				cv::arrowedLine(frameinfo->lumaImg,
					cv::Point(central_x, central_y),
					cv::Point(x + width, y + height),
					cv::Scalar(255, 255, 255),
					2, 0, 0, 0.2);
			}

		}
	}
	else
	{
		LOG_MESSAGE(LOG_LEVEL_INFO, "IC trap is not found");
		sprintf(text_buffer, "IC trap is not found");
		/* Draw label text on the filled rectanngle */
		putText(frameinfo->lumaImg, text_buffer, cv::Point(kpriv->x_offset, y_point), kpriv->font,
			kpriv->font_size, Scalar(255.0, 255.0, 255.0), 1, 1);
	}

	//Willy debug - e

    return 0;
  }


  int32_t xlnx_kernel_done (IVASKernel * handle)
  {
      return 0;
  }
}

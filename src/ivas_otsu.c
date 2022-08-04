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

#include <ivas/ivaslogs.h>
#include <ivas/ivas_kernel.h>
#include <gst/ivas/gstinferencemeta.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _kern_priv
{
    int log_level;
    IVASFrame *mem;
} PreProcessingKernelPriv;

int32_t  xlnx_kernel_start(IVASKernel *handle, int start, IVASFrame *input[MAX_NUM_OBJECT], IVASFrame *output[MAX_NUM_OBJECT]);
int32_t  xlnx_kernel_done(IVASKernel *handle);
int32_t  xlnx_kernel_init(IVASKernel *handle);
uint32_t xlnx_kernel_deinit(IVASKernel *handle);

uint32_t xlnx_kernel_deinit(IVASKernel *handle)
{
    PreProcessingKernelPriv *kernel_priv;
    kernel_priv = (PreProcessingKernelPriv *)handle->kernel_priv;
    if (kernel_priv->mem)
        ivas_free_buffer (handle, kernel_priv->mem);
    free(kernel_priv);
    return 0;
}

int32_t xlnx_kernel_init(IVASKernel *handle)
{
    json_t *jconfig = handle->kernel_config;
    json_t *val; /* kernel config from app */
    PreProcessingKernelPriv *kernel_priv;

    kernel_priv = (PreProcessingKernelPriv *)calloc(1, sizeof(PreProcessingKernelPriv));
    if (!kernel_priv) {
        printf("Error: Unable to allocate PPE kernel memory\n");
    }
    kernel_priv->mem = ivas_alloc_buffer (handle, 1*(sizeof(uint32_t)), IVAS_INTERNAL_MEMORY, NULL);

    /* parse config */
    val = json_object_get (jconfig, "debug_level");
    if (!val || !json_is_integer (val))
	    kernel_priv->log_level = LOG_LEVEL_WARNING;
    else
	    kernel_priv->log_level = json_integer_value (val);
    LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "IVAS PPE: debug_level %d", kernel_priv->log_level);

    handle->kernel_priv = (void *)kernel_priv;
    handle->is_multiprocess = 1;
    return 0;
}

int32_t xlnx_kernel_start(IVASKernel *handle, int start, IVASFrame *input[MAX_NUM_OBJECT], IVASFrame *output[MAX_NUM_OBJECT])
{
    PreProcessingKernelPriv *kernel_priv;
    int ret;
    uint32_t *thr;
    float sigma = 0.0;
    GstInferenceMeta *infer_meta = NULL;
    IVASFrame *outframe = output[0];
    kernel_priv = (PreProcessingKernelPriv *)handle->kernel_priv;

    LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "MAX_NUM_OBJECT = %d", MAX_NUM_OBJECT);

    ivas_register_write(handle, &(input[0]->paddr[0]), sizeof(uint64_t),         0x10);      /* Input buffer */
    ivas_register_write(handle, &(input[0]->props.height), sizeof(uint32_t),     0x28);      /* Rows */
    ivas_register_write(handle, &(input[0]->props.width), sizeof(uint32_t),      0x30);      /* Columns */
    ivas_register_write(handle, &(sigma), sizeof(float),                         0x38);      /* Sigma */
    ivas_register_write(handle, &(output[0]->paddr[0]), sizeof(uint64_t),        0x1C);      /* Output buffer */
    ivas_register_write(handle, &(kernel_priv->mem->paddr[0]), sizeof(uint32_t), 0x40);      /* OTSU threashold */

    ret = ivas_kernel_start (handle);
    if (ret < 0) {
        LOG_MESSAGE (LOG_LEVEL_ERROR, kernel_priv->log_level, "Failed to issue execute command");
        return FALSE;
    }

    /* wait for kernel completion */
    ret = ivas_kernel_done (handle, 1000);
    if (ret < 0) {
        LOG_MESSAGE (LOG_LEVEL_ERROR, kernel_priv->log_level, "Failed to receive response from kernel");
        return FALSE;
    }


    thr =  kernel_priv->mem->vaddr[0]; 

    {
	    FILE *demo;

    		LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "fopen checkpoint 1");
	    demo=fopen("demo_file.txt", "w+");
    		LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "fopen checkpoint 2");
	    fprintf(demo, "%s %s %s", "Welcome",      "to", "GeeksforGeeks");
    		LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "fopen checkpoint 3");
	    fclose(demo);
    		LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "fopen checkpoint 4");


    }

    LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "be outframe->app_priv = %p", outframe->app_priv);
    LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "be &outframe->app_priv = %p", &outframe->app_priv);
    LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "infer_meta = %p", infer_meta);
    LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "&infer_meta = %p", &infer_meta);

    infer_meta = (GstInferenceMeta *) gst_buffer_add_meta ((GstBuffer *)outframe->app_priv,
                                                     gst_inference_meta_get_info (), NULL);

    LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "af outframe->app_priv = %p", outframe->app_priv);
    LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "af &outframe->app_priv = %p", &outframe->app_priv);
    LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "infer_meta = %p", infer_meta);
    LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "&infer_meta = %p", &infer_meta);

    if (infer_meta == NULL) {
        LOG_MESSAGE (LOG_LEVEL_ERROR, kernel_priv->log_level, "Meta data is not available");
        return FALSE;
    }

    LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "Tony_debug");

    if (NULL == infer_meta->prediction) {
        LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "Allocating prediction");
        infer_meta->prediction = gst_inference_prediction_new ();
    } else {
        LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "Already allocated prediction");
    }

    GstInferencePrediction *predict;
    GstInferenceClassification *a = NULL;
    
    LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "predict = %p", predict);
    LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "&predict = %p", &predict);

    LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "execution gst_inference_prediction_new");
    predict = gst_inference_prediction_new ();

    LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "predict = %p", predict);
    LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "&predict = %p", &predict);
    LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "predict->predictions = %p", predict->predictions);
    if (predict->predictions) {
    	LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "predict->predictions->data = %p", predict->predictions->data);
    	LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "predict->predictions->next = %p", predict->predictions->next);
    	LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "predict->predictions->prev = %p", predict->predictions->prev);
    	LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "predict->predictions->parent = %p", predict->predictions->parent);
    	LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "predict->predictions->children = %p", predict->predictions->children);
    	LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "predict->classifications = %p", predict->classifications);
    }

    LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "exectuin gst_inference_classification_new_fullp");

    a = gst_inference_classification_new_full (-1, 0.0, "OTSU THRSHOLD", 0, NULL, NULL, NULL);
    predict->reserved_1 = (void *)thr;

    gst_inference_prediction_append_classification (predict, a);

    if (predict->predictions) {
    	LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "predict->predictions->data = %p", predict->predictions->data);
    	LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "predict->predictions->next = %p", predict->predictions->next);
    	LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "predict->predictions->prev = %p", predict->predictions->prev);
    	LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "predict->predictions->parent = %p", predict->predictions->parent);
    	LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "predict->predictions->children = %p", predict->predictions->children);
    	LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "predict->classifications = %p", predict->classifications);
	if (predict->predictions->children) {
		GNode *child = predict->predictions->children;
    		LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "child->data = %p", child->data);
	    	LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "child->next = %p", child->next);
    		LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "child->prev = %p", child->prev);
	    	LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "child->parent = %p", child->parent);
    		LOG_MESSAGE (LOG_LEVEL_INFO, kernel_priv->log_level, "child->children = %p", child->children);

	}

    }

    gst_inference_prediction_append (infer_meta->prediction, predict);

    return TRUE;
}

int32_t xlnx_kernel_done(IVASKernel *handle)
{
    /* dummy */
    return 0;
}

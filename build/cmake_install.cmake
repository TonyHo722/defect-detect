# Install script for directory: /home/willychiang/tony-workspace/defect-detect

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/willychiang/petalinux/2021.1/xilinx-k26-starterkit-2021.1/images/linux/sdk/sysroots/cortexa72-cortexa53-xilinx-linux")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/home/willychiang/petalinux/2021.1/xilinx-k26-starterkit-2021.1/images/linux/sdk/sysroots/x86_64-petalinux-linux/usr/bin/aarch64-xilinx-linux/aarch64-xilinx-linux-objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/lib/libivas_cca.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/lib/libivas_cca.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/lib/libivas_cca.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/opt/xilinx/lib" TYPE SHARED_LIBRARY FILES "/home/willychiang/tony-workspace/defect-detect/build/libivas_cca.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/lib/libivas_cca.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/lib/libivas_cca.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/home/willychiang/petalinux/2021.1/xilinx-k26-starterkit-2021.1/images/linux/sdk/sysroots/x86_64-petalinux-linux/usr/bin/aarch64-xilinx-linux/aarch64-xilinx-linux-strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/lib/libivas_cca.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/lib/libivas_otsu.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/lib/libivas_otsu.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/lib/libivas_otsu.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/opt/xilinx/lib" TYPE SHARED_LIBRARY FILES "/home/willychiang/tony-workspace/defect-detect/build/libivas_otsu.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/lib/libivas_otsu.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/lib/libivas_otsu.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/home/willychiang/petalinux/2021.1/xilinx-k26-starterkit-2021.1/images/linux/sdk/sysroots/x86_64-petalinux-linux/usr/bin/aarch64-xilinx-linux/aarch64-xilinx-linux-strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/lib/libivas_otsu.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/lib/libivas_text2overlay.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/lib/libivas_text2overlay.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/lib/libivas_text2overlay.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/opt/xilinx/lib" TYPE SHARED_LIBRARY FILES "/home/willychiang/tony-workspace/defect-detect/build/libivas_text2overlay.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/lib/libivas_text2overlay.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/lib/libivas_text2overlay.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/home/willychiang/petalinux/2021.1/xilinx-k26-starterkit-2021.1/images/linux/sdk/sysroots/x86_64-petalinux-linux/usr/bin/aarch64-xilinx-linux/aarch64-xilinx-linux-strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/lib/libivas_text2overlay.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/lib/libivas_preprocess.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/lib/libivas_preprocess.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/lib/libivas_preprocess.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/opt/xilinx/lib" TYPE SHARED_LIBRARY FILES "/home/willychiang/tony-workspace/defect-detect/build/libivas_preprocess.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/lib/libivas_preprocess.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/lib/libivas_preprocess.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/home/willychiang/petalinux/2021.1/xilinx-k26-starterkit-2021.1/images/linux/sdk/sysroots/x86_64-petalinux-linux/usr/bin/aarch64-xilinx-linux/aarch64-xilinx-linux-strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/lib/libivas_preprocess.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/bin/defect-detect" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/bin/defect-detect")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/bin/defect-detect"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/opt/xilinx/bin" TYPE EXECUTABLE FILES "/home/willychiang/tony-workspace/defect-detect/build/defect-detect")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/bin/defect-detect" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/bin/defect-detect")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/home/willychiang/petalinux/2021.1/xilinx-k26-starterkit-2021.1/images/linux/sdk/sysroots/x86_64-petalinux-linux/usr/bin/aarch64-xilinx-linux/aarch64-xilinx-linux-strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/bin/defect-detect")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/bin/defect-test" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/bin/defect-test")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/bin/defect-test"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/opt/xilinx/bin" TYPE EXECUTABLE FILES "/home/willychiang/tony-workspace/defect-detect/build/defect-test")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/bin/defect-test" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/bin/defect-test")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/home/willychiang/petalinux/2021.1/xilinx-k26-starterkit-2021.1/images/linux/sdk/sysroots/x86_64-petalinux-linux/usr/bin/aarch64-xilinx-linux/aarch64-xilinx-linux-strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/bin/defect-test")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/bin/defect-test2" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/bin/defect-test2")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/bin/defect-test2"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/opt/xilinx/bin" TYPE EXECUTABLE FILES "/home/willychiang/tony-workspace/defect-detect/build/defect-test2")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/bin/defect-test2" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/bin/defect-test2")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/home/willychiang/petalinux/2021.1/xilinx-k26-starterkit-2021.1/images/linux/sdk/sysroots/x86_64-petalinux-linux/usr/bin/aarch64-xilinx-linux/aarch64-xilinx-linux-strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/opt/xilinx/bin/defect-test2")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/opt/xilinx" TYPE FILE RENAME "README_DEFECT_DETECT" FILES "/home/willychiang/tony-workspace/defect-detect/README")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/opt/xilinx/bin" TYPE PROGRAM FILES
    "/home/willychiang/tony-workspace/defect-detect/script/defect-detect-install.py"
    "/home/willychiang/tony-workspace/defect-detect/script/ar0144-sensor-calib.sh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/opt/xilinx/share/ivas/defect-detect" TYPE FILE FILES
    "/home/willychiang/tony-workspace/defect-detect/config/otsu-accelarator.json"
    "/home/willychiang/tony-workspace/defect-detect/config/text2overlay.json"
    "/home/willychiang/tony-workspace/defect-detect/config/cca-accelarator.json"
    "/home/willychiang/tony-workspace/defect-detect/config/preprocess-accelarator.json"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/opt/xilinx/share/notebooks/defect-detect" TYPE DIRECTORY FILES "/home/willychiang/tony-workspace/defect-detect/notebook/")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/willychiang/tony-workspace/defect-detect/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")

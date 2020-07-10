cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(tools /usr/local/cross-compile/aarch64-cc/)
set(CMAKE_C_COMPILER ${tools}/bin/aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER ${tools}/bin/aarch64-linux-gnu-g++)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)


project(mpp_test)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "-O0 -g")

include_directories(
	/usr/include/aarch64-linux-gnu
	/env/platforms/aarch64/include
	${CMAKE_CURRENT_LIST_DIR}/ffm_inc
	${CMAKE_CURRENT_LIST_DIR}/rockchip
)

link_directories(
	/env/platforms/aarch64/so
	/env/platforms/aarch64/static
	/usr/local/lib
	${CMAKE_CURRENT_LIST_DIR}/firefly_mpplib
	${CMAKE_CURRENT_LIST_DIR}/ffm_lib
	
)


add_executable(mpp_test MppDecode.cpp MppDecode.h main.cpp)

target_link_libraries(mpp_test
        rockchip_mpp
        utils
        avformat
        avcodec
		avutil
		opencv_core
		opencv_highgui
		opencv_imgproc
		opencv_imgcodecs
		m
)

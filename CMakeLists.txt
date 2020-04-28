cmake_minimum_required(VERSION 3.9)
project(ffpro)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        /usr/include/aarch64-linux-gnu
        /home/firefly/zlatan/mpp/mpp/base/inc
        /home/firefly/zlatan/mpp/utils
        /home/firefly/zlatan/mpp/mpp/inc
        /home/firefly/zlatan/mpp/inc
        /home/firefly/zlatan/mpp/osal/inc
)


add_executable(ffpro MppDecode.c MppDecode.h main.c)

target_link_libraries(ffpro
        /home/firefly/zlatan/mpp/mpp/librockchip_mpp.so
        /home/firefly/zlatan/mpp/utils/libutils.a
        /usr/lib/aarch64-linux-gnu/libavformat.so.57
        /usr/lib/aarch64-linux-gnu/libavcodec.so.57
        /usr/lib/aarch64-linux-gnu/libavutil.so.55
)
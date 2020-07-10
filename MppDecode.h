//
// Created by LX on 2020/4/25.
//

#ifndef LIVERTSPCLIENT_MPPDECODE_H
#define LIVERTSPCLIENT_MPPDECODE_H

#define MODULE_TAG "mpi_dec_test"

#include <string.h>

#include "utils.h"
#include "rk_mpi.h"
#include "mpp_log.h"
#include "mpp_mem.h"
#include "mpp_env.h"
#include "mpp_time.h"
#include "mpp_common.h"

#include "mpp_frame.h"
#include "mpp_buffer_impl.h"
#include "mpp_frame_impl.h"
#include <libavformat/avformat.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


#define MPI_DEC_STREAM_SIZE         (SZ_4K)
#define MPI_DEC_LOOP_COUNT          4
#define MAX_FILE_NAME_LENGTH        256

typedef struct
{
    MppCtx          ctx;
    MppApi          *mpi;
    RK_U32          eos;
    char            *buf;

    MppBufferGroup  frm_grp;
    MppBufferGroup  pkt_grp;
    MppPacket       packet;
    size_t          packet_size;
    MppFrame        frame;

    FILE            *fp_input;
    FILE            *fp_output;
    RK_S32          frame_count;
    RK_S32          frame_num;
    size_t          max_usage;
} MpiDecLoopData;

typedef struct
{
    char            file_input[MAX_FILE_NAME_LENGTH];
    char            file_output[MAX_FILE_NAME_LENGTH];
    MppCodingType   type;
    MppFrameFormat  format;
    RK_U32          width;
    RK_U32          height;
    RK_U32          debug;

    RK_U32          have_input;
    RK_U32          have_output;

    RK_U32          simple;
    RK_S32          timeout;
    RK_S32          frame_num;
    size_t          max_usage;
} MpiDecTestCmd;



size_t mpp_frame_get_buf_size(const MppFrame s);
void dump_mpp_frame_to_file(MppFrame frame, FILE *fp);
size_t mpp_buffer_group_usage(MppBufferGroup group);

int decode_simple(MpiDecLoopData *data, AVPacket* av_packet);

void YUV420SP2Mat(MppFrame  frames, cv::Mat rgbImg );

#endif //LIVERTSPCLIENT_MPPDECODE_H

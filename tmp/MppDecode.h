

#pragma once



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

#include "Callback.h"

#define ROK 0
#define RERR -1

#define MAX_DEC_ERROR_NUM (30) // 错误帧数超过当前值则重新初始化MPP
#define MAX_DEC_ERROR_TRY_NUM (5) // 超过当前次数未能成功发送，则丢弃当前帧


class MppDecode {
 public:
	MppDecode()
			: ctx(NULL),
				mpi(NULL),
				eos(0),
				packet(NULL),
				frame(NULL),
				param(NULL),
				need_split(1),
				type(MPP_VIDEO_CodingAVC),
				frm_grp(NULL),
				pkt_grp(NULL),
				mpi_cmd(MPP_CMD_BASE),
				frame_count(1),
				frame_num(0),
				max_usage(0),
				fp_output(NULL),
				m_nDecPutErrNum(0) {}
	~MppDecode() { deInitMpp(); }

	/**
	 * set type for h264 or h265 decode
	 * MPP_VIDEO_CodingAVC  ---> h264
	 * MPP_VIDEO_CodingHEVC ---> h265
	 */
	void setMppDecodeType(MppCodingType t) { type = t; }
	void setMppFp(FILE* fp) { fp_output = fp; }

	int initMpp();

	int decode(AVPacket* av_packet, cv::Mat& image);

	//转码, 将yuv转码为rgb的格式
	void YUV420SP2Mat(cv::Mat& image);

	void deInitMpp();
	// void setDataCallback(const rtsp_data_callback_t& cb) { cb_ = cb; }

 private:
	MppCtx ctx;
	MppApi* mpi;
	RK_U32 eos;
	MppBufferGroup frm_grp;
	MppBufferGroup pkt_grp;
	MppPacket packet;
	MppFrame frame;
	MppParam param;
	RK_U32 need_split;
	MpiCmd mpi_cmd;
	RK_S32 frame_count;
	RK_S32 frame_num;
	size_t max_usage;
	MppCodingType type;
	FILE* fp_output;

	// rtsp_data_callback_t cb_;

	int m_nDecPutErrNum;

 public:
	cv::Mat rgbImg;
};

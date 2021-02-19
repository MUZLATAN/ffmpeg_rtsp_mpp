

#pragma once


extern "C" {
#include <libavformat/avformat.h>
};

#include <memory>
#include <opencv2/core/core.hpp>

#include "MppDecode.h"
// #include "Callback.h"



class RtspImpl {
 public:
	RtspImpl(const std::string &rtsp_addr) : rtsp_addr_(rtsp_addr) {}
	virtual ~RtspImpl() {}
	virtual int init() {}
	virtual bool read(cv::Mat &image) {}
	virtual bool open(const std::string &rtsp_addr) {}
	virtual void release(){};
	virtual void set(int option, int value) {}
	virtual bool isOpened() {}
	// virtual void setDataCallback(const rtsp_data_callback_t &cb) {}

 protected:
	std::string rtsp_addr_;
	bool opened_;
};

class RtspMppImpl : public RtspImpl {
 public:
	RtspMppImpl(const std::string &rtsp_addr)
			: RtspImpl(rtsp_addr),
			    inited_(false),
				pFormatCtx_(NULL),
				options_(NULL),
				packet_(NULL),
				videoindex_(-1),
				codec_id_(AV_CODEC_ID_NONE),
				mppdec_(std::make_shared<MppDecode>()) {
		av_register_all();
		avformat_network_init();
	}

	~RtspMppImpl() {
		av_free(packet_);
		avformat_close_input(&pFormatCtx_);
	}

	int init();
	bool open(const std::string &rtsp_addr) {}

	void reopen() {}

	bool read(cv::Mat &image);
	void set(int option, int value) {}
	bool isOpened() {}
	void release() {}

	int getFrame(cv::Mat &image);

	// void setDataCallback(const rtsp_data_callback_t &cb) {
	// 	mppdec_->setDataCallback(cb);
	// }
	void restart();

 private:
    int inited_;
	AVFormatContext *pFormatCtx_;
	AVDictionary *options_;
	int videoindex_;
	AVPacket *packet_;
	enum AVCodecID codec_id_;
	std::shared_ptr<MppDecode> mppdec_;
    int64_t last_decode_time_;
	const int mpp_exception_decode_time_window_ = 5 * 60 * 1000;
	const int decode_gop_time_window_ = 60 * 1000;
};


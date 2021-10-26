# ffmpeg_rtsp_mpp
ffmpeg 拉取rtsp h264流， 使用mpp解码， 目前在firefly 板子上跑通了

保存的yuv文件可以用yuvplayer.exe文件打开， 设置文件大小， 就可以正常显示了
![](./yuv.jpg)


# change log
重新添加了一个整的YUV420SP2Mat()函数, 修改了内存泄露的bug， 根据release 版本的mpp精简了一点代码


# reference
mpp 硬编码, 从文件中读取yuv一帧图片, 硬编码

该接口也可以直接传入yuv的void*  内存地址, 编码成h264的文件, 具体地址如下
https://github.com/MUZLATAN/MPP_ENCODE

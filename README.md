# ffmpeg_rtsp_mpp
ffmpeg 拉取rtsp h264流， 使用mpp解码， 目前在firefly 板子上跑通了

保存的yuv文件可以用yuvplayer.exe文件打开， 设置文件大小， 就可以正常显示了
![](./yuv.jpg)


# change log
重新添加了一个整的YUV420SP2Mat()函数, 修改了内存泄露的bug， 根据release 版本的mpp精简了一点代码

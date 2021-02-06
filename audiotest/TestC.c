//
//  TestC.c
//  audiotest
//
//  Created by Tung Lam Chan on 6/2/2021.
//

/*
            FFmpeg解码流程图(参考雷神的备忘)
 
            av_register_all()
                    ↓
            avformat_open_input()
                    ↓
            avformat_find_stream_info()
                    ↓
            avcodec_find_decoder()
                    ↓
            avcodec_open2()
                    |-------------------------------------------←--------
                    ↓                                                   |
            av_read_frame()                                             |
                    ↓                                                   |
                get packet?----------YES--------------                  |
                    |                                ↓                  |
                    NO                            AVPacket              ↑
                    |                                ↓                  |
                    |                       avcodec_decode_video2()     |
                    ↓                                ↓                  |
                  close                           AVFrame               |
                                                     ↓                  |
                                              show on screen..          |
                                                     ↓                  |
                                                     |__________________|
 */

#include "TestC.h"

void printHello(void) {
    printf("Hello C.\n");
}

void ffmpegTest(void) {
    avdevice_register_all();
    AVInputFormat *iformat = av_find_input_format("avfoundation");
    
    AVFormatContext *fmt_ctx = NULL;
    char *deviceName = ":0";
    AVDictionary *options = NULL;
    char errors[1024];
    int ret = avformat_open_input(&fmt_ctx, deviceName, iformat, &options);
    if (ret < 0) {
        av_strerror(ret, errors, 1024);
        printf(stderr, "Faild to open audio device, [%d]%s/n", ret, errors);
        return;
    }
    printf("Hello C.\n");
    
    int count = 0;
    AVPacket pkt;
    av_init_packet(&pkt);
    while ((ret = av_read_frame(fmt_ctx, &pkt)) >= 0) {
        printf("pkt.size=%d/n", pkt.size);
    }
    av_packet_unref(&pkt);
    char readFrameError[1024];
    if (ret < 0) {
        printf("%s\n", av_err2str(ret));
//        av_strerror(ret, readFrameError, 1024);
//        printf(stderr, "Faild to read audio frame, [%d]%s/n", ret, readFrameError);
    }
    
    av_log_set_level(AV_LOG_DEBUG);
    av_log(NULL, AV_LOG_DEBUG, "Hello, av log!\n");
}

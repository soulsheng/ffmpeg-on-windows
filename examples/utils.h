
#ifndef UTILIS_H__
#define UTILIS_H__

#include "../inc/libavformat/avformat.h"
#include "../inc/libswscale/swscale.h"


void extra_exit(int value);

void uninit_opts(SwsContext *sws_opts,
	AVDictionary *format_opts, AVDictionary *codec_opts, AVDictionary *resample_opts);

void print_error(const char *filename, int err);

int check_stream_specifier(AVFormatContext *s, AVStream *st, const char *spec);

AVDictionary *filter_codec_opts(AVDictionary *opts, enum AVCodecID codec_id,
	AVFormatContext *s, AVStream *st, AVCodec *codec);

AVDictionary **setup_find_stream_info_opts(AVFormatContext *s,
	AVDictionary *codec_opts);
	

#endif
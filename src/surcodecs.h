#ifndef _SUR_CODECS_H
#define _SUR_CODECS_H

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

#include <string>
#include "surqueue.h"


namespace Sur {

  struct File {
    AVFormatContext *formatContext = NULL;
    AVCodecContext *codecContext = NULL;
    AVCodec *codec = NULL;
    AVFrame *frame = NULL;
    int audioStream = -1;
    std::string filename = "";
  };


  extern bool codecsInitialized;

  void InitializeCodecs();

  int OpenFile (Sur::File *file, std::string fn);

  int GetContext(Sur::File *file);

  int GetCodec(Sur::File *file);

  int ReadFrame(Sur::File *file, Sur::Queue *q);

  void EndCodecs(Sur::File *file);
}

#endif

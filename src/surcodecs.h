#ifndef _SUR_CODECS_H
#define _SUR_CODECS_H

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

namespace Sur {

  int codecsInitialized = false;
  inline void InitializeCodecs() {
    if(!codecsInitialized) {
      av_register_all();
    }
  };
}

#endif

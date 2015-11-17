#include "surcodecs.h"

bool Sur::codecsInitialized = false;

void Sur::InitializeCodecs() {
  if(!Sur::codecsInitialized) {
    av_register_all();
    Sur::codecsInitialized = true;
  }
  else {
    // TODO: PUT GENERAL PANIC HERE
  }
}

void Sur::EndCodecs(Sur::File *file) {
  if(file->codecContext != NULL) {
    avcodec_close(file->codecContext);
  }
  if(file->formatContext != NULL) {
    avformat_close_input(&file->formatContext);
  }
}

int Sur::OpenFile(Sur::File *file, std::string fn) {
  if(avformat_open_input(&file->formatContext, fn.c_str(), NULL, NULL) != 0) {
    return -1;
  }
  file->filename = fn;
  av_dump_format(file->formatContext, 0, fn.c_str(),0);
  return 1;
}

int Sur::GetContext(Sur::File *file) {
  int audioStream = -1;
  AVFormatContext *pContext = file->formatContext;
  if(pContext == NULL) {
    return -1;
  }
  for (unsigned int i = 0; i < pContext->nb_streams; i++) {
    if(pContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO &&
       audioStream < 0) {
      audioStream = i;
    }
  }
  if(audioStream >= 0) {
    file->codecContext = file->formatContext->streams[audioStream]->codec;
    file->audioStream = audioStream;
    return audioStream;
  }
  else {
    return -1;
  }
}


int Sur::GetCodec(Sur::File *file) {
  AVCodecContext *codecCtx = file->codecContext;
  if(codecCtx == NULL) {
    return -1;
  }


  AVCodec *aCodec;
  aCodec = avcodec_find_decoder(codecCtx->codec_id);
  if(!aCodec) {
    return -1;
  }
  codecCtx = avcodec_alloc_context3(aCodec);

  avcodec_open2(codecCtx, aCodec, NULL);

  file->codec = aCodec;
  return 1;
}

int Sur::ReadFrame(Sur::File *file, Sur::Queue *q) {
  if(file->codecContext == NULL) {
    return -2;
  }

  if(file->codec == NULL) {
    return -1;
  }

  AVPacket packet;

  if(av_read_frame(file->formatContext, &packet) >= 0 )  {
    if(packet.stream_index == file->audioStream) {
      Sur::InsertIntoSurQueue(q, &packet);
    }
    else {
      av_free_packet(&packet);
    }
  }
}

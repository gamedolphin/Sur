#ifndef _SUR_QUEUE_H
#define _SUR_QUEUE_H

#include <thread>
#include <queue>
#include <mutex>

extern "C" {
#include <libavcodec/avcodec.h>
}

namespace Sur {
  struct Queue {
    std::queue<AVPacket*> packetList;
    std::mutex lockQueue;
  };


  void insert_into_surQueue (Sur::Queue* q, AVPacket* packet);
  void retrieve_from_surQueue(Sur::Queue* q);

  void insertToQueue_thread(Sur::Queue* q, AVPacket* packet);
  void retrieveFromQueue_thread(Sur::Queue* q);
}

#endif

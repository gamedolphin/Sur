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
    std::deque<AVPacket*> packetList;
    std::mutex lockQueue;
  };

  enum queue_modify {
    INSERT, REMOVE, DELETEALL
  };

  void changeQueue_thread(Queue* q, AVPacket* packet, queue_modify m);

  void insert_into_surQueue (Sur::Queue* q, AVPacket* packet);
  void retrieve_from_surQueue(Sur::Queue* q, AVPacket* packet);

  bool isQueueEmpty (Sur::Queue* q);

  void EndQueue(Sur::Queue *q);
}

#endif

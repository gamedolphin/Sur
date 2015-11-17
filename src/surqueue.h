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

  void thread_ChangeQueue(Queue* q, AVPacket* packet, queue_modify m);

  void InsertIntoSurQueue (Sur::Queue* q, AVPacket* packet);
  void RetrieveFromSurQueue(Sur::Queue* q, AVPacket* packet);

  void EndQueue(Sur::Queue *q);
}

#endif

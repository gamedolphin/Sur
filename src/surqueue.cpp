#include "surqueue.h"
#include <iostream>

int num = 0;

void Sur::changeQueue_thread(Sur::Queue *q, AVPacket *packet, Sur::queue_modify state) {
  std::lock_guard<std::mutex> guard(q->lockQueue);
  switch(state) {
  case Sur::INSERT:
    q->packetList.push_back(packet);
    break;
  case Sur::REMOVE:
    if(q->packetList.empty()) {
      break;
    }
    packet = q->packetList.front();
    q->packetList.pop_front();
    break;
  case Sur::DELETEALL:
    if(q->packetList.empty()) {
      break;
    }
    for (auto s: q->packetList) {
      av_free_packet(s);
    }
    q->packetList.clear();
    break;
  default: return;
  }
}

void Sur::insert_into_surQueue(Sur::Queue* q, AVPacket* p) {
  std::thread t(Sur::changeQueue_thread, q, p, Sur::INSERT);
  t.join();
}

void Sur::retrieve_from_surQueue(Sur::Queue *q, AVPacket *p) {
  std::thread t(Sur::changeQueue_thread, q, p, Sur::REMOVE);
  t.join();
}

bool Sur::isQueueEmpty(Sur::Queue *q) {
  return q->packetList.empty();
}

void Sur::EndQueue(Sur::Queue *q) {
  AVPacket *p;
  std::thread t(Sur::changeQueue_thread, q, p, Sur::DELETEALL);
  t.join();
}

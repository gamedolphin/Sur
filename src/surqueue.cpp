#include "surqueue.h"

int num = 0;

void Sur::thread_ChangeQueue(Sur::Queue *q, AVPacket *packet, Sur::queue_modify state) {
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
      if(!s)
        continue;
      av_free_packet(s);
    }
    q->packetList.clear();
    break;
  default: return;
  }
}

void Sur::InsertIntoSurQueue(Sur::Queue* q, AVPacket* p) {
  std::thread t(Sur::thread_ChangeQueue, q, p, Sur::INSERT);
  t.join();
}

void Sur::RetrieveFromSurQueue(Sur::Queue *q, AVPacket *p) {
  std::thread t(Sur::thread_ChangeQueue, q, p, Sur::REMOVE);
  t.join();
}

void Sur::EndQueue(Sur::Queue *q) {
  AVPacket *p;
  std::thread t(Sur::thread_ChangeQueue, q, p, Sur::DELETEALL);
  t.join();
}

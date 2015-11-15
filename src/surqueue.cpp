#include "surqueue.h"
#include <iostream>

int num = 0;
void Sur::insertToQueue_thread(Sur::Queue *q, AVPacket *packet) {
  std::lock_guard<std::mutex> guard(q->lockQueue);
  // do stuff;
}

void Sur::retrieveFromQueue_thread(Sur::Queue *q) {
  if(q->packetList.empty()) {
    return;
  }
  std::lock_guard<std::mutex> guard(q->lockQueue);
  std::cout<<"HELLO IN THREAD "<<num++<<std::endl;
  // do stuff
}

void Sur::insert_into_surQueue(Sur::Queue* q, AVPacket* p) {
  std::thread t(Sur::insertToQueue_thread, q, p);
  t.join();
}

void Sur::retrieve_from_surQueue(Sur::Queue *q) {
  std::thread t(Sur::retrieveFromQueue_thread, q);
  t.join();
}

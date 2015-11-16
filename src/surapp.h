#ifndef _SUR_APP_H
#define _SUR_APP_H

#include "surqueue.h"
#include "sursound.h"
#include "surcodecs.h"

namespace Sur {
  struct WindowInfo {
  };

  struct App {
    bool isRunning = false;
    WindowInfo window;
    Audio audio;
    File file;
    Queue audioQueue;
  };
}

#endif

#ifndef _SUR_H_
#define _SUR_H_

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

  bool Initialize(App* app);

  void UpdateAndRender(App *app);

  void End(App* app);
}

#endif

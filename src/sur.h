#ifndef _SUR_H_
#define _SUR_H_

#include "sursound.h"


namespace Sur {

  struct WindowInfo {
  };

  struct App {
    bool isRunning;
    WindowInfo window;
    Audio audio;
  };

  void UpdateAndRender(App *app);

  bool Initialize(App* app);

  void End(App* app);
}

#endif

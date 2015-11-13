#ifndef _SUR_H_
#define _SUR_H_

#include <soundio/soundio.h>

namespace Sur {

  struct WindowInfo {
  };

  struct Audio {
    SoundIo *soundIo;
    SoundIoOutStream *outStream;
    int deviceIndex;
    SoundIoDevice *device;
  };


  struct App {
    bool isRunning;
    WindowInfo window;
    Audio audio;
  };

  void UpdateAndRender(App *app);

  bool Initialize(App* app);
  SoundIoError InitializeAudio(Audio *audio);

  static void write_callback(SoundIoOutStream *outStream,
                             int frame_count_min, int frame_count_max);

  void End(App* app);
  void EndAudio(Audio *audio);
}

#endif

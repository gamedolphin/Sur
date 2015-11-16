#ifndef _SUR_SOUND_H
#define _SUR_SOUND_H

#include <soundio/soundio.h>

namespace Sur {

  struct Audio {
    SoundIo *soundIo = nullptr;
    SoundIoOutStream *outStream = nullptr;
    int deviceIndex = -1;
    SoundIoDevice *device = nullptr;
  };


  SoundIoError InitializeAudio(Audio *audio);

  void EndAudio(Audio *audio);

  void write_callback(SoundIoOutStream *outStream,
                      int frame_count_min, int frame_count_max);

  inline void sound_events(SoundIo *sound) {
    soundio_wait_events(sound);
  }
}

#endif

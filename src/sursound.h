#ifndef _SUR_SOUND_H
#define _SUR_SOUND_H

#include <soundio/soundio.h>

namespace Sur {
  struct Audio {
    SoundIo *soundIo;
    SoundIoOutStream *outStream;
    int deviceIndex;
    SoundIoDevice *device;
  };

  SoundIoError InitializeAudio(Audio *audio);

  void EndAudio(Audio *audio);

  static void write_callback(SoundIoOutStream *outStream,
                             int frame_count_min, int frame_count_max);

  inline void sound_events(SoundIo *sound) {
    soundio_wait_events(sound);
  }
}

#endif

#include <soundio/soundio.h>
#include "sur.h"

static void Sur::write_callback(SoundIoOutStream *outStream,
                                int frame_count_min, int frame_count_max) {
}

SoundIoError Sur::InitializeAudio(Sur::Audio *audio) {
  int err;

  SoundIo *soundIo = soundio_create();
  if(!soundIo) {
    return SoundIoErrorNoMem;
  }

  audio->soundIo = soundIo;

  if((err = soundio_connect(soundIo))) {
    return SoundIoErrorNoMem;
  }

  soundio_flush_events(soundIo);

  int default_out_device_index = soundio_default_output_device_index(soundIo);
  if (default_out_device_index < 0) {
    return SoundIoErrorNoMem;
  }

  audio->deviceIndex = default_out_device_index;

  struct SoundIoDevice *device = soundio_get_output_device(soundIo, default_out_device_index);
  if (!device) {
    return SoundIoErrorNoMem;
  }

  audio->device = device;

  struct SoundIoOutStream *outstream = soundio_outstream_create(device);
  outstream->format = SoundIoFormatFloat32NE;
  outstream->write_callback = write_callback;

  audio->outStream = outstream;

  if ((err = soundio_outstream_open(outstream))) {
    return SoundIoErrorNoMem;
  }

  if (outstream->layout_error)
    return SoundIoErrorNoMem;

  if ((err = soundio_outstream_start(outstream))) {
    return SoundIoErrorNoMem;
  }
  return SoundIoErrorNone;
}

bool Sur::Initialize(App *app) {

  if(app->isRunning == true) {
    return false;
  }
  app->isRunning = true;

  InitializeAudio(&app->audio);
  return true;
}

void Sur::EndAudio(Audio *audio) {
  soundio_outstream_destroy(audio->outStream);
  soundio_device_unref(audio->device);
  soundio_destroy(audio->soundIo);
}

void Sur::End(App *app) {
  EndAudio(&app->audio);
}

#include <soundio/soundio.h>
#include "sur.h"
#include <math.h>

static const float PI = 3.14159f;
static float seconds_offset = 0.0f;

static void Sur::write_callback(SoundIoOutStream *outstream,
                                int frame_count_min, int frame_count_max) {

  const struct SoundIoChannelLayout *layout = &outstream->layout;
  float float_sample_rate = outstream->sample_rate;
  float seconds_per_frame = 1.0f / float_sample_rate;
  struct SoundIoChannelArea *areas;
  int frames_left = frame_count_max;
  int err;

  while (frames_left > 0) {
    int frame_count = frames_left;

    if ((err = soundio_outstream_begin_write(outstream, &areas, &frame_count))) {
    }

    if (!frame_count)
      break;

    float pitch = 440.0f;
    float radians_per_second = pitch * 2.0f * PI;
    for (int frame = 0; frame < frame_count; frame += 1) {
      float sample = sinf((seconds_offset + frame * seconds_per_frame) * radians_per_second);
      for (int channel = 0; channel < layout->channel_count; channel += 1) {
        float *ptr = (float*)(areas[channel].ptr + areas[channel].step * frame);
        *ptr = sample;
      }
    }
    seconds_offset += seconds_per_frame * frame_count;

    if ((err = soundio_outstream_end_write(outstream))) {
    }

    frames_left -= frame_count;
  }
}

void Sur::UpdateAndRender(App *app) {
  for (;;) {
    soundio_wait_events(app->audio.soundIo);
  }
}

SoundIoError Sur::InitializeAudio(Audio *audio) {
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

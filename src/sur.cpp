#include <soundio/soundio.h>

#include "sur.h"
#include "sursound.h"
#include "surcodecs.h"

void Sur::UpdateAndRender(App *app) {
  for (;;) {
    Sur::sound_events(app->audio.soundIo);
  }
}

bool Sur::Initialize(App *app) {

  if(app->isRunning == true) {
    return false;
  }
  app->isRunning = true;

  Sur::InitializeAudio(&app->audio);
  Sur::InitializeCodecs();

  return true;
}

void Sur::End(App *app) {
  Sur::EndAudio(&app->audio);
}

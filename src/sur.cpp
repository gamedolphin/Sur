#include "sur.h"

void Sur::UpdateAndRender(App *app) {
  //  while(true)
  int j = Sur::ReadFrame(&app->file, &app->audioQueue);
}

bool Sur::Initialize(App *app) {

  if(app->isRunning == true) {
    return false;
  }
  app->isRunning = true;

  Sur::InitializeAudio(&app->audio);
  // very important to set the user data as app
  // no other way to access this rest of app in callback
  app->audio.outStream->userdata = (Sur::App*)app;

  Sur::InitializeCodecs();

  int k = Sur::OpenFile(&app->file, "../sample.mp3");
  int j = Sur::GetContext(&app->file);
  int l = Sur::GetCodec(&app->file);

  Sur::EndQueue(&app->audioQueue);
  return true;
}

void Sur::End(App *app) {
  Sur::EndAudio(&app->audio);
  Sur::EndCodecs(&app->file);
  Sur::EndQueue(&app->audioQueue);
}

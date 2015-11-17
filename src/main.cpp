#include <iostream>
#include "sur.h"


int main(int argc, char **argv) {

  Sur::App app;

  Sur::Initialize(&app);

  Sur::UpdateAndRender(&app);

  Sur::End(&app);
}

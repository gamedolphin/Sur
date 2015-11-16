#include <iostream>
#include "sur.h"


int main(int argc, char **argv) {

  Sur::App app;

  std::cout<<Sur::Initialize(&app)<<"HELLO"<<std::endl;

  Sur::UpdateAndRender(&app);

  Sur::End(&app);
}

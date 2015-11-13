#include <iostream>
#include <soundio/soundio.h>
#include "sur.h"


int main(int argc, char **argv) {

  Sur::App app = {0};

  std::cout<<Sur::Initialize(&app)<<"HELLO"<<std::endl;

  Sur::End(&app);
}

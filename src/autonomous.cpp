#include "main.h"

void redFront(){
  moveForward(24);
}

void blueFront(){
  moveForward(45);
}

void autonomous() {

  switch (autonIndex) {
  case 0:
    redFront();
    break;
  case 1:
    blueFront();
    break;
  }
}

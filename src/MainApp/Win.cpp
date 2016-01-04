#include "Win.h"
#include <iostream>
#include <stdio.h>

Win::Win() : image(*this){
  set_size(430,380);
  set_title("MyEye configuration");
  show();
} 
Win::~Win(){	
  close_window();
}

#include "Win.h"
#include <iostream>
#include <stdio.h>
#include <list>
#include <string.h>

#include <dlib/dlib/array.h>


Win::Win() : image(*this), cameras(*this){
  Settings* settings = Settings::getInstance();
  set_size(1280,760);
  set_title("MyEye configuration");
  dlib::array<std::string> l;
  for (int i = 0; i < settings->getCameraCount();  i++){
    auto str = std::to_string(i);
    std::cout << str << std::endl; 
    l.push_back(str);
  }
  cameras.load(l);
  image.set_pos(200,10);
  cameras.set_size(50,20);
  dlib::list_box_style_default s;
  cameras.set_style(s);
  cameras.set_click_handler(*this,&Win::on_camera_select);
  show();
} 

void Win::on_camera_select(unsigned long i){
  Settings* settings = Settings::getInstance();
  settings->setCamera(i);
}

Win::~Win(){	
  close_window();
}



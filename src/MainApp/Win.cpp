#include "Win.h"
#include <iostream>
#include <stdio.h>
#include <list>
#include <string.h>

#include <dlib/dlib/array.h>


Win::Win() : image(*this), cameras(*this), off(*this){
  Settings* settings = Settings::getInstance();
  set_size(1280,760);
  set_title("MyEye configuration");
  dlib::array<std::string> l;
  for (int i = 0; i < settings->getCameraCount();  i++){
    auto str = std::to_string(i);
    std::cout << str << std::endl; 
    l.push_back(str);
  }
  
  dlib::list_box_style_default s;
  cameras.load(l);
  cameras.set_style(s);
  cameras.set_size(50,20);
  cameras.set_click_handler(*this,&Win::on_camera_select);
  

  image.set_pos(200,10);

  off.set_click_handler(*this,&Win::on_off_clicked);
  off.set_pos(100,10);
  off.set_name("off");

  show();
} 

void Win::on_camera_select(unsigned long i){
  Settings* settings = Settings::getInstance();
  if (i != settings->getCamera()) {
    settings->setCamera(i);
  }
}

void Win::on_off_clicked(){
  Settings* settings = Settings::getInstance();
  if (settings->toggleTrackingState()) {
    off.set_name("off");
  } else {
    off.set_name("on");
  }
}

Win::~Win(){	
  close_window();
}



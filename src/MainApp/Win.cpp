#include "Win.h"
#include <iostream>
#include <stdio.h>
#include <list>
#include <string.h>

#include <dlib/dlib/array.h>


Win::Win() : image(*this), cameras(*this), off(*this), grid(*this, 1,2), detection_label(*this), flip_frame(*this){
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
 
  detection_label.set_pos(10, 260);
  detection_label.set_text("No Detection"); 

  grid.set_pos(10,50);
  grid.set_size(200,200);
  grid.construct_grid();
   

  image.set_pos(220,10);

  off.set_click_handler(*this,&Win::on_off_clicked);
  off.set_pos(50,10);
  off.set_name("off");

  flip_frame.set_click_handler(*this,&Win::on_flip_clicked);
  flip_frame.set_pos(100,10);
  flip_frame.set_name("flip");
 
  show();
} 

void Win::on_camera_select(unsigned long i){
  Settings* settings = Settings::getInstance();
  if (i != settings->getCamera()) {
    settings->setCamera(i);
  }
}
void Win::on_flip_clicked(){
  Settings* settings = Settings::getInstance();
  if (settings->toggleFlipFrame()) {
    off.set_name("flip");
  } else {
    off.set_name("unflip");
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

std::string directionName(Direction d);

void Win::set_focus(Direction d){
  switch (d){
    case Left : {grid.set_focus(0,0);
    detection_label.set_text(directionName(d));
    break;
    };
    case Right : {grid.set_focus(1,0);
    detection_label.set_text(directionName(d));
    break;
    };
    case Middle :{};
    case Unknown : {};
  } 
}

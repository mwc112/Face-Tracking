#include "grid_widget.h"
#include <dlib/dlib/pixel.h>

using namespace dlib;

grid_widget::grid_widget(dlib::drawable_window& win, int rows, int cols) : image_display(win), rows(rows), cols(cols){
   
}


void grid_widget::construct_grid(){
  int w = (width()-5)/cols;
  int h = (height()-5)/rows;
  
  dlib::matrix<int> blank(width()-5,height()-5);
  blank = 0;
  set_image(blank);
  std::vector<overlay_rect> rects; 
  
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){
      int l = j*w;
      int t = i*h; 
      int r = l + w;
      int b = t + h;
      rects.push_back(overlay_rect(dlib::rectangle(l,t,r,b), (dlib::rgb_alpha_pixel)lowlightColor));    
    }
  }
  
  add_overlay(rects);
}


void grid_widget::set_focus(int x, int y){
  int w = (width()-5)/cols;
  int h = (height()-5)/rows;
  clear_overlay();
  std::cout << x << y << std::endl;
  std::vector<overlay_rect> rects; 
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){
      int l = j*w;
      int t = i*h; 
      int r = l + w;
      int b = t + h;
      std::cout << x << j << y << i << std::endl;
 
      if (j == x && y == i){
        rects.push_back(overlay_rect(dlib::rectangle(l,t,r,b), (dlib::rgb_alpha_pixel)hilightColor));
        std::cout << "red" << l << t << r << b << std::endl;
      } else {
        rects.push_back(overlay_rect(dlib::rectangle(l,t,r,b), (dlib::rgb_alpha_pixel)lowlightColor));    
        std::cout << "white" << l << t << r << b << std::endl;
      }
      
    }
  }
  add_overlay(rects);
  
}


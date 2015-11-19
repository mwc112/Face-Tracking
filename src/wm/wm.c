#include <stdlib.h>
#include <stdio.h>
#include <X11/Xlib.h>
#include "main.h"

Status get_root_windows(Display *d, Window **children_windows_ret,
                                         int *num_children_ret){
  Window root_window = XDefaultRootWindow(d);
  Window root, parent;
  if ((XQueryTree(d, root_window, &root, &parent,
                                children_windows_ret, num_children_ret))==0){
    return 0;
  }
}

Status get_windows_attr(Display *d, Window *children_windows,
                           int num_children, XWindowAttributes *attrs_ret){
  for(int i = 0; i < num_children; i++){
    if(XGetWindowAttributes(d, children_windows[i], attrs_ret+i)==0){
      return 0;
    }
  }
}

void print_attr(Display* d, Window *children_windows, XWindowAttributes *attrs,
                                            int num_children){
  char* name;

  for(int i = 0; i < num_children; i++){
    XFetchName(d, children_windows[i], &name);
    printf("Name: %s\nx: %i  y: %ze: %i, %i\n\n", name, attrs[i].x,
                                   attrs[i].y, attrs[i].width, attrs[i].height);
  }
}

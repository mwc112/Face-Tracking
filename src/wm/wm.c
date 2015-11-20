#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <X11/Xlib.h>
#include "wm.h"

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

void set_focus_to(Display* d, int x, int y){
	bool got_pointer = false;
	Window *c_wins;
	int num_child;
	Window r_win, c_win;
	int root_x, root_y, win_x, win_y;
	unsigned int mask;

	get_root_windows(d, &c_wins, &num_child);
	
	for(int i = 0; i < num_child; i++){
		got_pointer = XQueryPointer(d, c_wins[i], &r_win, &c_win, 
																				&root_x, &root_y, &win_x, &win_y,
																				&mask);
		if(got_pointer){
			printf("Got pointer\n");
			break;
		}
	}

	int move_x = x - root_x;
	int move_y = y - root_y;
	printf("%i  %i\n", move_x, move_y);

	XWarpPointer(d, None, None, 0, 0, 0, 0, move_x, move_y);
	XFlush(d);
	XSetInputFocus(d, PointerRoot, RevertToNone, CurrentTime);
}

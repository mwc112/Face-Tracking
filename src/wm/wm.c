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
    printf("Name: %s\nx: %i  y: %i  size: %i, %i\n\n", name, attrs[i].x,
                                   attrs[i].y, attrs[i].width, attrs[i].height);
  }
}


void set_focus_to(Display* d, int x, int y){

	long *windows;
	unsigned long length;

	get_client_window_list(d, &windows, &length);

	int i;
	for(i = 1; i < length; i++){
		bool in = pointInPolygon(windows+(i*5)+1, x, y);
		if(in){
			break;
		}
	}

	printf("%i\n", i);

	int root_x, root_y;
	get_pointer_location(d, &root_x, &root_y);

	int move_x = x - root_x;
	int move_y = y - root_y;

	XWarpPointer(d, None, None, 0, 0, 0, 0, move_x, move_y);
	XFlush(d);
	
	XSetInputFocus(d, windows[i*5], RevertToNone, CurrentTime);
	XFlush(d);
}

void get_pointer_location(Display *d, int *x_ret, int *y_ret){
	bool got_pointer = false;
  Window *c_wins;
  int num_child;
  Window r_win, c_win;
  int win_x, win_y;
  unsigned int mask;

  get_root_windows(d, &c_wins, &num_child);

  for(int i = 0; i < num_child; i++){
    got_pointer = XQueryPointer(d, c_wins[i], &r_win, &c_win,
                                        x_ret, y_ret, &win_x, &win_y,
                                        &mask);
  }
}

bool pointInPolygon(long* window, int x, int y) {

	bool in = false;

	if(x > window[0] && x < window[1] && y > window[2] && y < window[3]){
		in = true;
	}
	

  return in;
}

void get_client_window_list(Display* d, long **windows, unsigned long* length){
	Atom a = XInternAtom(d, "_NET_CLIENT_LIST" , true);
  Atom actualType;
  int format;
  unsigned long bytesAfter;
  unsigned char *data;
  int status = XGetWindowProperty(d,
                XDefaultRootWindow(d),
                a,
                0L,
                (~0L),
                false,
                AnyPropertyType,
                &actualType,
                &format,
                length,
                &bytesAfter,
                &data);

  long* array;

	*windows = malloc(*length * sizeof(long) * 5);
  if (status >= Success && *length)
  {
     array = (long*)data;
     for (int k = 0; k < *length; k++)
     {
				Window root;
				Window parent;
				Window* children;
				unsigned int nchildren;
				XQueryTree(d, array[k], &root, &parent, &children, &nchildren);
				XWindowAttributes attr;
				XGetWindowAttributes(d, parent, &attr);

        (*windows)[k*5] = array[k];
				(*windows)[(k*5)+1] = (long)attr.x;
				(*windows)[(k*5)+2] = (long)(attr.x + attr.width);
				(*windows)[(k*5)+3] = (long)attr.y;
				(*windows)[(k*5)+4] = (long)(attr.y+attr.height);
     }
  }
}






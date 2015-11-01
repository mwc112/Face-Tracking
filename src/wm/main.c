#include <stdlib.h>
#include <stdio.h>
#include <X11/Xlib.h>

int main(void){
	Display *d;
	if((d = XOpenDisplay(NULL)) == NULL){
		printf("ERROR: failed to get screen\n");
	}

	Window root_window = XDefaultRootWindow(d);
	Window root_window_ret, parent_window_ret;
	Window *children_windows_ret;
	unsigned int num_children;
	if ((XQueryTree(d, root_window, &root_window_ret, &parent_window_ret,
																&children_windows_ret, &num_children))==0){
		printf("ERROR: Failed to get tree of windows\n");
		XCloseDisplay(d);
	}
	

	XWindowAttributes *attrs = calloc(num_children, sizeof(XWindowAttributes));

	for(int i = 0; i < num_children; i++){
		XWindowAttributes *attr = attrs+i;
		if((XGetWindowAttributes(d, children_windows_ret[i], attr))==0){
			printf("ERROR: Failed to get attributes for child %i\n", 1);
		}
	}




	for(int i = 0; i < num_children; i++){
			printf("x: %i  y: %i\n", attrs[i].x, attrs[i].y);
	}

	XCloseDisplay(d);
	free(attrs);

}

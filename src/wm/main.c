#include <stdlib.h>
#include <stdio.h>
#include <X11/Xlib.h>
#include "wm.h"

int main(void){
	Display *d;
	if((d = XOpenDisplay(NULL)) == NULL){
		printf("Failed to get display");
	}

	set_focus_to(d, 20, 20);
}

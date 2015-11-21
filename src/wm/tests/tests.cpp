#include "gtest/gtest.h"
#include "X11/Xlib.h"

extern "C" void set_focus_to(Display*, int, int);

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(window_manager, changes_focus){
	Display *d = XOpenDisplay(NULL);
	int set_x = 100;
	int set_y = 100;

	set_focus_to(d, set_x, set_y);
	
}

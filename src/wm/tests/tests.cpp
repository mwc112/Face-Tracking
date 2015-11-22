#include "gtest/gtest.h"
#include "X11/Xlib.h"

extern "C" void set_focus_to(Display*, int, int);
extern "C" void get_pointer_location(Display*, int*, int*);

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(window_manager, changes_focus){
	Display *d = XOpenDisplay(NULL);
	int set_x = 100;
	int set_y = 100;
	int ret_x;
	int ret_y;

	set_focus_to(d, set_x, set_y);
	get_pointer_location(d, &ret_x, &ret_y);

	ASSERT_EQ(set_x, ret_x) << "Pointer x location was not set correctly. Set: " << set_x << " Actual: " << ret_x << "\n";
	ASSERT_EQ(set_y, ret_y) << "Pointer y location was not set correctly. Set: " << set_y << " Actual: " << ret_y << "\n";	

}

#include "main.h"
#include "chassis.h"

const int LOOKAHEAD_DISTANCE = 6.0;

ASSET(precision_test_txt)
void precision_test() {
	chassis.setPose(-48.0, 24.0, 90.0);
	lemlib_tarball::Decoder precision_test_decoder(precision_test_txt);
	// Arc from (-48, 24) to (-48, -24)
	chassis.follow(precision_test_decoder["Path 1"], LOOKAHEAD_DISTANCE, 10000, true, false);
	// Arc backwards from (-48, -24) to (-48, 24)
	chassis.follow(precision_test_decoder["Path 2"], LOOKAHEAD_DISTANCE, 10000, false, false);
}

ASSET(accuracy_test_txt)
void accuracy_test() {
	chassis.setPose(-48.0, 24.0, 90.0);
	lemlib_tarball::Decoder accuracy_test_decoder(accuracy_test_txt);
	// Drive to (0, 36)
	chassis.follow(accuracy_test_decoder["Path 1"], LOOKAHEAD_DISTANCE, 10000, true, false);
	// Drive around field 5 times
	for (int i = 0; i < 5; i++) {
		// Drive full circle around field, returning to starting position
		chassis.follow(accuracy_test_decoder["Path 2"], LOOKAHEAD_DISTANCE, 10000, true, false);
	}
}
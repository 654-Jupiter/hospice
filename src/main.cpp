#include "main.h"
#include "chassis.h"
#include "autons.h"

using namespace pros;

Controller controller(pros::E_CONTROLLER_MASTER);

// Robodash UI
rd::Selector auton_selector("Autonomous Selector", {
	{"Precision Test", precision_test, "", 120},
	{"Accuracy Test", accuracy_test, "", 240}
});

void initialize() {}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	auton_selector.run_auton();
}

void opcontrol() {
	while (true) {
		float throttle = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		float turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		chassis.arcade(throttle, turn);

		pros::delay(20);
	}
}
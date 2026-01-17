#include "main.h"
#include "chassis.h"
#include "autons.h"
#include "subsystems.h"

using namespace pros;

Controller controller(pros::E_CONTROLLER_MASTER);

// Robodash UI
rd::Selector auton_selector("Autonomous Selector", {
	{"Red Right", red_right, "", 0},
	{"Red Left", red_left, "", 0},
	{"Blue Right", blue_right, "", 240},
	{"Blue Left", blue_left, "", 240},
});

void initialize() {
	chassis.calibrate();
}

void disabled() {}

void competition_initialize() {
	lemlib::Pose pose = chassis.getPose();

	while (true) {
		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
			chassis.calibrate();
			chassis.setPose(pose);
		}

		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
			pose = chassis.getPose();
		}

		pros::delay(20);
	}
}

void autonomous() {
	auton_selector.run_auton();
}

void opcontrol() {


	while (true) {
		bool r1_pressed = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
		bool r2_pressed = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2);

		bool l1_pressed = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
		bool l2_pressed = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2);

		bool middle = r1_pressed && l2_pressed;

		int32_t intake_voltage = 
			r1_pressed * 127 - 
			r2_pressed * 127 +
			l1_pressed * 127;
		
		intake.move(intake_voltage, middle);

		if (r1_pressed) {
			
		}

		float throttle = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		float turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		chassis.arcade(throttle, turn);

		pros::delay(20);
	}
}
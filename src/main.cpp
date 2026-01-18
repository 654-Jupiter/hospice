#include "main.h"
#include "chassis.h"
#include "autons.h"
#include "subsystems.h"

using namespace pros;

Controller controller(pros::E_CONTROLLER_MASTER);

// Robodash UI
rd::Selector auton_selector("Autonomous Selector", {
	{"Drive", red_right, "", 120},
	//{"Red Left", red_left, "", 0},
	{"Right", blue_right, "", 0},
	{"Left", blue_left, "", 240},
	{"Left Elims", blue_left_elims, "", 240},
	{"Skills", skills, "", 120},
	{"Wiggle", skills_wiggle, "", 120},
});

void initialize() {
	chassis.calibrate();
	auton_selector.on_select([](std::optional<rd::Selector::routine_t> auton) { if (auton) {
		if (auton->name == "Right") {
			chassis.setPose(48, 24 - 6.75, 270);
			lift.set_value(false);
		} else if (auton->name == "Left") {
			chassis.setPose(48, -24 + 6.75, 270);
			lift.set_value(false);
		} else if (auton->name == "Skills") {
			chassis.setPose(48, -24 + 6.75, 270);
			lift.set_value(false);
		}
	}});
}

void disabled() {}

void competition_initialize() {
	
}

lemlib::Pose pose = chassis.getPose();

void autonomous() {
	chassis.setPose(pose);
	auton_selector.run_auton();
}

void opcontrol() {
	lift.set_value(true);

	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);

	int32_t r1_pressed_duration = 0;
	int32_t l1_pressed_duration = 0;

	while (true) {
		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
			chassis.calibrate();
			chassis.setPose(pose);
		}

		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
			pose = chassis.getPose();
		}

		bool r1_pressed = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
		if (r1_pressed) { r1_pressed_duration += 20; } else { r1_pressed_duration = 0; }
		bool r2_pressed = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2);

		if (r1_pressed_duration > 50) {
			wing.set_state(true);
		}

		bool l1_pressed = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
		if (l1_pressed) { l1_pressed_duration += 20; } else { l1_pressed_duration = 0; }
		bool l2_pressed = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2);

		if (l1_pressed_duration > 50) {
			wing.set_state(false);
		}

		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
			wing.toggle();
		}

		bool middle = r1_pressed && l1_pressed;

		if (middle) {
			wing.set_state(true);
		}

		int32_t intake_voltage = 
			r1_pressed * 127 - 
			r2_pressed * 127 +
			l1_pressed * 127;
		
		if (intake_voltage > 127) { intake_voltage = 127; }
		if (intake_voltage < -127) { intake_voltage = -127; }
		
		intake.move(intake_voltage, middle);

		bool right_pressed = controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT);

		if (right_pressed) {
			intake.move(50, true);
		}
		
		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
			scraper.toggle();
		}

		float throttle = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		float turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		chassis.arcade(throttle, turn);

		pros::delay(20);
	}
}
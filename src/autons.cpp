#include "main.h"
#include "chassis.h"
#include "subsystems.h"

void red_right() {
	chassis.arcade(30, 0);
	pros::delay(250);
	chassis.arcade(0, 0);
}

void red_left() {

}

void blue_right() {
	intake.move(127);

	wing.set_state(true);

	chassis.moveToPose(24, 24, 270, 1500, {}, false);

	scraper.set_state(true);

	pros::delay(400);

	chassis.moveToPoint(40, 47, 2000, {.maxSpeed = 90}, false);
	chassis.turnToHeading(90, 750, {.minSpeed = 10, .earlyExitRange = 3}, false);

	chassis.arcade(40, 0);

	intake.move(127);

	pros::delay(1300);

	intake.move(127);

	chassis.moveToPose(24, 47, 90, 1500, {.forwards = false}, false);

	intake.move(127);

	chassis.arcade(-40, 0);

	wing.set_state(false);

	intake.move(127, true);

	pros::delay(200);

	intake.move(127);

	pros::delay(800);

	intake.move(0);

	chassis.moveToPose(36, 48, 90, 1000, {.minSpeed = 10, .earlyExitRange = 2}, false);

	chassis.moveToPose(24, 38, 60, 1500, {.forwards = false, .minSpeed = 10, .earlyExitRange = 2}, false);

	chassis.moveToPose(-2, 38, 90, 1500, {.forwards = false}, false);

	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
}

void blue_left() {
	intake.move(127);

	wing.set_state(true);

	chassis.moveToPose(24, -24, 270, 1500, {}, false);

	scraper.set_state(true);

	pros::delay(400);

	chassis.moveToPose(12, -14, 135, 2000, {.forwards = false, .maxSpeed = 60}, false);

	chassis.arcade(-20, 0);

	wing.set_state(false);

	intake.move(-60);

	pros::delay(500);

	intake.move(127, true);

	pros::delay(1500);

	intake.move(0);

	scraper.set_state(true);

	wing.set_state(true);

	chassis.moveToPoint(48, -49, 2000, {.maxSpeed = 90}, false);
	chassis.turnToHeading(90, 750, {.minSpeed = 10, .earlyExitRange = 1}, false);

	chassis.arcade(40, 0);

	intake.move(127);

	pros::delay(1300);

	intake.move(127);

	chassis.moveToPose(28, -49, 90, 2000, {.forwards = false, .maxSpeed = 100}, false);

	chassis.arcade(-40, 0);

	wing.set_state(false);

	intake.move(127, true);

	pros::delay(100);

	intake.move(-127);

	pros::delay(100);

	intake.move(127);

	pros::delay(800);

	intake.move(0);

	scraper.set_state(false);

	chassis.moveToPose(44, -49, 90, 1000, {.minSpeed = 10, .earlyExitRange = 2}, false);

	chassis.moveToPose(28, -60, 90, 1500, {.forwards = false }, false);

	chassis.moveToPoint(9, -56, 1500, {.forwards = false, .maxSpeed = 60}, false);

	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
}

void blue_left_elims() {
	intake.move(127);

	wing.set_state(true);

	chassis.moveToPose(24, -24, 270, 1500, {}, false);

	scraper.set_state(true);

	pros::delay(400);

	chassis.moveToPoint(48, -49, 2000, {.maxSpeed = 90}, false);
	chassis.turnToHeading(90, 750, {.minSpeed = 10, .earlyExitRange = 1}, false);

	chassis.arcade(40, 0);

	intake.move(127);

	pros::delay(1300);

	intake.move(127);

	chassis.moveToPose(28, -49, 90, 2000, {.forwards = false, .maxSpeed = 100}, false);

	chassis.arcade(-40, 0);

	wing.set_state(false);

	intake.move(127, true);

	pros::delay(100);

	intake.move(-127);

	pros::delay(100);

	intake.move(127);

	pros::delay(800);

	intake.move(0);

	scraper.set_state(false);

	chassis.moveToPose(44, -49, 90, 1000, {.minSpeed = 10, .earlyExitRange = 2}, false);

	chassis.moveToPose(28, -60, 90, 1500, {.forwards = false }, false);

	chassis.moveToPoint(9, -56, 1500, {.forwards = false, .maxSpeed = 50}, false);

	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
}

void skills_wiggle() {
	int j = 127;
	for (float i = 0.0; i < 2500.0; i += 20.0) {
		chassis.arcade(j, sin(i / 100.0) * 80);

		j--;
		pros::delay(20);
	}

	chassis.arcade(0, 0);
}

void skills() {
	intake.move(127);

	wing.set_state(true);

	chassis.moveToPose(24, -24, 270, 1500, {}, false);

	scraper.set_state(true);

	pros::delay(400);

	chassis.moveToPose(12, -14, 135, 2000, {.forwards = false, .maxSpeed = 60}, false);

	chassis.arcade(-20, 0);

	wing.set_state(false);

	intake.move(-60);

	pros::delay(500);

	intake.move(127, true);

	pros::delay(1500);

	intake.move(0);

	scraper.set_state(true);

	wing.set_state(true);

	chassis.moveToPoint(48, -50, 2000, {.maxSpeed = 90}, false);
	chassis.turnToHeading(90, 750, {.minSpeed = 10, .earlyExitRange = 6}, false);

	chassis.arcade(40, 0);

	intake.move(127);

	pros::delay(2500);

	intake.move(127);

	chassis.moveToPose(32, -50, 90, 1500, {.forwards = false}, false);

	wing.set_state(false);

	chassis.arcade(-40, 0);

	intake.move(127, true);

	pros::delay(200);

	intake.move(-127);

	pros::delay(200);

	intake.move(127);

	pros::delay(2000);

	intake.move(0);

	chassis.arcade(40, 0);

	pros::delay(500);

	scraper.set_state(false);

	chassis.moveToPose(48, 6, 90, 10000, {.minSpeed = 30, .earlyExitRange = 2}, false);

	wing.set_state(false);

	intake.move(127);

	lift.set_value(true);

	skills_wiggle();
}

void skills_41() {
	intake.move(127);

	wing.set_state(true);
	
	scraper.set_state(true);

	chassis.moveToPose(48, -48, 90, 2000, {.maxSpeed = 90}, false);
	chassis.turnToHeading(90, 750, {.minSpeed = 10, .earlyExitRange = 3}, false);

	chassis.arcade(30, 0);

	intake.move(127);

	pros::delay(1800);

	intake.move(127);

	chassis.moveToPose(32, -48, 90, 1500, {.forwards = false}, false);

	intake.move(127);

	chassis.arcade(-40, 0);

	wing.set_state(false);

	intake.move(127, true);

	pros::delay(200);

	intake.move(127);

	pros::delay(800);

	wing.set_state(true);

	chassis.arcade(60, 0);

	pros::delay(400);

	scraper.set_state(false);

	chassis.moveToPose(2, -24, 270, 1500, {}, false);

	scraper.set_state(true);

	pros::delay(600);

	chassis.moveToPose(32, -48, 90, 1500, {.forwards = false}, false);

	intake.move(127);

	chassis.arcade(-40, 0);

	wing.set_state(false);

	intake.move(127, true);

	pros::delay(200);

	intake.move(127);

	pros::delay(800);
}
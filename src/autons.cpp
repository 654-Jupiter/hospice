#include "main.h"
#include "chassis.h"
#include "subsystems.h"

void red_right() {

}

void red_left() {

}

void blue_right() {

}

void blue_left() {
	intake.move(127);

	wing.set_state(true);

	chassis.moveToPose(24, -24, 270, 1500, {.minSpeed = 20, .earlyExitRange = 3}, false);

	scraper.set_state(true);

	chassis.moveToPose(5, -44.5, 180, 2000, {}, true);

	chassis.waitUntil(14.0);

	scraper.set_state(false);

	// chassis.waitUntil(24.0);

	// scraper.set_value(true);

	chassis.waitUntilDone();

	pros::delay(200);

	scraper.set_state(true);

	chassis.arcade(-40, 0);

	pros::delay(500);

	scraper.set_state(false);

	chassis.moveToPose(10, -10, 135, 1500, {.forwards = false}, false);

	wing.set_state(false);

	intake.move(127, true);

	pros::delay(1000);

	intake.move(127);

	scraper.set_state(true);

	chassis.moveToPoint(48, -48, 1500, {.maxSpeed = 40, .minSpeed = 10, .earlyExitRange = 2}, false);
	chassis.moveToPose(56, -48, 90, 1000, {}, false);

	chassis.arcade(60, 0);

	pros::delay(1000);

	chassis.moveToPose(30, -48, 90, 10000, {.forwards = false}, false);

	chassis.arcade(-60, 0);

	wing.set_state(false);

	pros::delay(1000);
}
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
	chassis.setPose(48, -24 + 6.75, 270);

	intake.move(127);

	wing.set_value(true);

	chassis.moveToPose(24, -24, 270, 1500, {.minSpeed = 20, .earlyExitRange = 3}, false);

	scraper.set_value(true);

	chassis.moveToPose(5, -44.5, 180, 2000, {}, true);

	chassis.waitUntil(14.0);

	scraper.set_value(false);

	// chassis.waitUntil(24.0);

	// scraper.set_value(true);

	chassis.waitUntilDone();

	pros::delay(200);

	scraper.set_value(true);

	chassis.arcade(-40, 0);

	pros::delay(500);

	scraper.set_value(false);

	chassis.moveToPose(10, -10, 135, 1500, {.forwards = false}, false);

	scraper.set_value(true);

	chassis.moveToPoint(48, -43.5, 1500, {.maxSpeed = 40, .minSpeed = 10, .earlyExitRange = 2}, false);
	chassis.moveToPose(56, -43.5, 90, 750, {}, false);

	chassis.arcade(60, 0);

	pros::delay(750);

	chassis.moveToPose(30, -43.5, 90, 10000, {.forwards = false}, false);

	chassis.arcade(-60, 0);

	wing.set_value(false);

	pros::delay(1000);
}
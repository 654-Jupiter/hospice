#include "main.h"

pros::MotorGroup drive_left({1, 2, 3}, pros::MotorGears::blue);
pros::MotorGroup drive_right({4, 5, 6}, pros::MotorGears::blue);

lemlib::Drivetrain drivetrain(
	&drive_left,
	&drive_right,
	12.0,	// track width in inches
	3.25,	// wheel diameter in inches
	450.0,	// rpm
	8.0	// horizontal drift
);

lemlib::ControllerSettings linear_settings(
	10.0,	// kP
	0.0,	// kI
	3.0,	// kD
	0.0,	// antiWindup
	1.0,	// smallError
	100.0,	// smallErrorTimeout
	3.0,	// largeError
	500.0,	// largeErrorTimeout
	5.0	// slew
);

lemlib::ControllerSettings angular_settings(
	3.0,	// kP
	0.0,	// kI
	10.0,	// kD
	0.0,	// antiWindup
	5.0,	// smallError
	100.0,	// smallErrorTimeout
	15.0,	// largeError
	500.0,	// largeErrorTimeout
	10.0	// slew
);

lemlib::OdomSensors sensors(
	nullptr,			// vertical1
	nullptr,			// vertical2
	nullptr,			// horizontal1
	nullptr,			// horizontal2
	nullptr				// imu
);

lemlib::Chassis chassis(
	drivetrain,
	linear_settings,
	angular_settings,
	sensors
);
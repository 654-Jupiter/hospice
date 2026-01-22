#include "main.h"

pros::MotorGroup drive_left({-11, -12, -13}, pros::MotorGears::blue);
pros::MotorGroup drive_right({17, 18, 19}, pros::MotorGears::blue);

lemlib::Drivetrain drivetrain(
	&drive_left,
	&drive_right,
	10.5,	// track width in inches
	3.25,	// wheel diameter in inches
	450.0,	// rpm
	4.0	// horizontal drift
);

lemlib::ControllerSettings linear_settings(
	20.0,	// kP
	0.1,	// kI
	64.0,	// kD
	0.0,	// antiWindup
	1.0,	// smallError
	100.0,	// smallErrorTimeout
	3.0,	// largeError
	500.0,	// largeErrorTimeout
	0.0	// slew
);

lemlib::ControllerSettings angular_settings(
	3,	// kP
	0.01,	// kI
	25,	// kD
	0,	// antiWindup
	3.0,	// smallError
	100.0,	// smallErrorTimeout
	5.0,	// largeError
	500.0,	// largeErrorTimeout
	0.0	// slew
);

pros::Rotation horizontal_rotation(7);
lemlib::TrackingWheel horizontal_tracker(&horizontal_rotation, -lemlib::Omniwheel::NEW_275, 0.375);
pros::Imu imu(20);
 
lemlib::OdomSensors sensors(
	nullptr,			// vertical1
	nullptr,			// vertical2
	&horizontal_tracker,			// horizontal1
	nullptr,			// horizontal2
	&imu				// imu
);

lemlib::Chassis chassis(
	drivetrain,
	linear_settings,
	angular_settings,
	sensors
);
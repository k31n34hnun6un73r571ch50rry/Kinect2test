#pragma once
#include <Kinect.h>
#include <Kinect.VisualGestureBuilder.h>

#include "Buffer.h"
#include "Eigen/Dense"

#include "GestureRecognition.h"
#include "MotionParameters.h"
#include "Person.h"

class ControlWidget {
public: virtual void pickModel(float x, float y) {};
};

class StateMachine {
public:
	enum State {
		IDLE,
		CAMERA_TRANSLATE,
		CAMERA_ROTATE,
		OBJECT_MANIPULATE
	};
	
	void setState(State newState);
	State getState();

	void setMotionParameters(MotionParameters motionParameters);
	MotionParameters getMotionParameters();

	void setMaster(Person newMaster);
	Person getMaster();

	void bufferGestureConfidence();
	void compute();
	void switchState();

	void assignWidget(ControlWidget *_widget);

	StateMachine();
private:
	State state;
	GestureRecognition gestureRecognition;
	MotionParameters motionParameters;
	Person master;

	const float smoothingFactor[9] = { 1, 2, 4, 8, 16, 32, 64, 128, 256 };
	const float smoothingSum = 511.0f; //Summe obiger Eintr�ge

	const float rotationSmoothingFactor[10] = { 1.f, 1.5f, 2.25f, 3.375f, 5.0625f, 7.6f, 11.39f, 17.086f, 25.63f, 38.44f };
	const float rotationSmoothingSum = 113.3335f; //Summe obiger Eintr�ge

	CameraSpacePoint smoothSpeed(Buffer<CameraSpacePoint>* buffer);
	Eigen::Quaternionf smoothRotation(Buffer<Eigen::Quaternionf> *buffer);

	ControlWidget *widget;
};
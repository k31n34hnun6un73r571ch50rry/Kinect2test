#pragma once
#include "Buffer.h"

class GestureRecognition {
public:
	enum Gesture {
		UNKNOWN,
		TRANSLATE_GESTURE,
		ROTATE_GESTURE,
		GRAB_GESTURE,
		FLY_GESTURE
	};

	struct GestureConfidence {
		float unknownConfidence;
		float translateCameraConfidence;
		float rotateCameraConfidence;
		float grabConfidence;
		float flyConfidence;
	};

	enum ControlHand {
		HAND_LEFT = 0,
		HAND_RIGHT = 1
	};

	Gesture getRecognizedGesture();
	void setRecognizedGesture(Gesture gesture);

	Buffer<GestureConfidence> *getConfidenceBuffer();
	void evaluateBuffer();

	GestureRecognition();
private:
	Gesture recognizedGesture;
	const int GESTURE_BUFFER_SIZE = 10;
	Buffer<GestureConfidence> *confidenceBuffer;
	
	float gestureSmooth[10] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 };
	float gestureSmoothSum = 1023;
};

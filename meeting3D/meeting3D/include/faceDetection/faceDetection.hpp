#pragma once

#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>
#include "faceDetectionInput.hpp"


class FaceDetection {
private:

	// Input variables
	faceDetectionInput faceDetectionData;

	// Output variables
	double xCoordinate;
	double yCoordinate;
	double framesPerSecond;
	bool faceDetected;

public:
	FaceDetection(faceDetectionInput input);

	void solve();

	int getXCoordinate();

	int getYCoordinate();

	double getFramesPerSecond();

	bool getFaceDetected();

};
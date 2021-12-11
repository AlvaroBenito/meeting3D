#pragma once

struct faceDetectionOutput{
	double xCoordinate;
	double yCoordinate;
	double framesPerSecond;
	bool faceDetected;

	std::mutex mutex;
	std::condition_variable condition;
	bool frameProcessed;

	faceDetectionOutput(double xCoordinate, double yCoordinate, double framesPerSecond, bool faceDetected) :
		xCoordinate(xCoordinate), yCoordinate(yCoordinate), framesPerSecond(framesPerSecond), faceDetected(faceDetected) {}
};

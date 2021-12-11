#pragma once

#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>
#include "cascadeFaceDetectionInput.hpp"
#include "faceDetectionOutput.hpp"

enum class faceDetectionType {
	CASCADE_CLASSIFIER = 0,
	DNN_CLASSIFIER
};

/// <summary>
/// Class that implements a face detection algorithm based on Viola-Jones method for real time video applications
/// </summary>
class faceDetection {

private:

	// Input variable
	cv::VideoCapture camera;

	// Output variables
	double xCoordinate = 0.0;
	double yCoordinate = 0.0;
	double framesPerSecond = 0.0;
	bool faceDetected = false;

public:
	explicit faceDetection(const cv::VideoCapture& camera);

	virtual ~faceDetection() = default;

	void solve(faceDetectionOutput* output);

	virtual bool findFace(cv::Mat image, cv::Rect& lastContour) = 0;

	virtual faceDetectionType getType() = 0;

	cv::VideoCapture getCamera() const;

	double getXCoordinate() const;

	double getYCoordinate() const;

	double getFramesPerSecond() const;

	bool getFaceDetected() const;

	void setxCoordinate(double x);
	
	void setyCoordinate(double y);
};
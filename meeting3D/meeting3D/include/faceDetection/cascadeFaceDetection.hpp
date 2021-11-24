#pragma once

#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>
#include "faceDetectionInput.hpp"

/// <summary>
/// Enum for the possible errors for face detection algorithm
/// </summary>
enum class errorCode {
	
	NO_ERROR = 0,
	XML_ERROR,
	CAM_ERROR,
	CLASSIFIER_ERROR,
	SCALE_FACTOR_ERROR,
	MIN_NEIGHBOURS_ERROR
};

/// <summary>
/// Class that implements a face detection algorithm based on Viola-Jones method for real time video applications
/// </summary>
class cascadeFaceDetection {

private:

	// Input variables
	faceDetectionInput faceDetectionData;

	// Status variables
	errorCode error;

	// Output variables
	double xCoordinate = 0.0;
	double yCoordinate = 0.0;
	double framesPerSecond = 0.0;
	bool faceDetected = false;

public:
	explicit cascadeFaceDetection(faceDetectionInput const& input);

	void solve();

	bool detectFace(cv::Mat image, std::vector<cv::Rect> faces, cv::Rect& lastContour);

	double getXCoordinate() const;

	double getYCoordinate() const;

	double getFramesPerSecond() const;

	bool getFaceDetected() const;

};
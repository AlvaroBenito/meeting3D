#pragma once

#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>
#include "faceDetectionInput.hpp"


class FaceDetection {
private:

	// Input variables
	faceDetectionInput faceDetectionData;

	// Output variables
	double xCoordinate = 0.0;
	double yCoordinate = 0.0;
	double framesPerSecond = 0.0;
	bool faceDetected = false;

public:
	explicit FaceDetection(faceDetectionInput const& input);

	void solve();

	void detectFace(std::shared_ptr<float> timing, cv::Mat image, std::vector<cv::Rect> faces);

	double getXCoordinate() const;

	double getYCoordinate() const;

	double getFramesPerSecond() const;

	bool getFaceDetected() const;

};
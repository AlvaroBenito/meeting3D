#pragma once

#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>



class FaceDetection {
private:

	// Input variables
	cv::VideoCapture camera;
	cv::CascadeClassifier faceCascade;
	cv::String haarCascadeXmlPath;

	// Output variables
	int xCoordinate;
	int yCoordinate;
	double framesPerSecond;
	bool faceDetected;

public:
	FaceDetection(cv::VideoCapture camera, cv::CascadeClassifier cascadeClassifier, cv::String haarCascadeXmlPath);

	void solve();

	int getXCoordinate();

	int getYCoordinate();

	double getFramesPerSecond();

	bool getFaceDetected();

};
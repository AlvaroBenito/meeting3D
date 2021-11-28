#include <faceDetection/faceDetection.hpp>
#include <iostream>
#include <utils/basicGeometry.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include <utils/timer.hpp>
#include <utils/vector2D.hpp>
#include <memory>
#include <fstream>

faceDetection::faceDetection(cv::VideoCapture camera) : camera(camera) {}


[[ noreturn ]]  void faceDetection::solve() {
	
	// Variable where the cam info will be stored
	cv::Mat image;

	// Vector of Rect objects where the possible faces from the cascade classifier are stored
	

	// File initialization for experimental data retrieval
	std::ofstream myfile;
	myfile.open("example.csv");

	// Auxiliary variables for dynamic cropping of the image (improves performance)
	bool lastDetection = false;
	cv::Rect lastContour;
	cv::Mat croppedImage;
	cv::Point2i faceCenter;

	// Infinite loop for face detection
	while (true) {

		auto timing = std::make_shared<float>();

		camera.read(image);

		if (lastDetection) {
			Timer timer(timing.get());
			croppedImage = cropFaceSurrounding(image, faceCenter, lastContour.size());
			lastDetection = getFace(croppedImage, lastContour);
			cv::Point2i croppedFaceCenter = getCenterPoint(lastContour.tl(), lastContour.br());
			cv::Point2i faceCenterMove(croppedFaceCenter.x - (croppedImage.cols / 2), croppedFaceCenter.y - croppedImage.rows / 2);
			faceCenter = faceCenter + faceCenterMove;
		}
		else {
			Timer timer(timing.get());
			croppedImage = image;
			lastDetection = getFace(croppedImage, lastContour);
			faceCenter = getCenterPoint(lastContour.tl(), lastContour.br());
		}
		
		if (*timing != 0.0) {
			framesPerSecond = 1.0f / *timing;
			std::cout << framesPerSecond << std::endl;
		}
		cv::imshow("Image", image);
		cv::waitKey(2);
		
	}
}

cv::VideoCapture faceDetection::getCamera() const { return camera; }

double faceDetection::getXCoordinate() const { return xCoordinate; }

double faceDetection::getYCoordinate() const { return yCoordinate; }

double faceDetection::getFramesPerSecond() const { return framesPerSecond; }

bool faceDetection::getFaceDetected() const { return faceDetected; }

void faceDetection::setxCoordinate(double x) { xCoordinate = x; }

void faceDetection::setyCoordinate(double y) { yCoordinate = y; }
#include "FaceDetection.h"
#include <iostream>
#include "utils/BasicGeometry.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include "utils/Timer.hpp"


#include <fstream>

FaceDetection::FaceDetection(cv::VideoCapture camera, cv::CascadeClassifier cascadeClassifier, cv::String haarCascadeXmlPath) {
	this->camera = camera;
	this->faceCascade = cascadeClassifier;
	this->haarCascadeXmlPath = haarCascadeXmlPath;

	faceCascade.load(haarCascadeXmlPath);
}


void FaceDetection::solve() {
	
	// Check if XML was not loaded
	if (faceCascade.empty()) {
		std::cout << "XML file not found" << std::endl;
		return;
	}
	
	// Generate local image variables
	cv::Mat image;
	cv::Mat resizedImgage;
	std::vector<cv::Rect> faces;
	Vector2d<int> center;

	//Get camera resolution for resizing

	camera.read(image);
	
	

	std::ofstream myfile;
	myfile.open("example.csv");

	while (true) {
		float* timing = new float;
		{
			Timer timer(timing);
			camera.read(image);

			faces.clear();

			faceCascade.detectMultiScale(image, faces, 1.2, 10);

			cv::Point2i center;
			for (int i = 0; i < faces.size(); i++) {

				rectangle(image, faces[i].tl(), faces[i].br(), cv::Scalar(255, 0, 255), 3);

				center = getCenterPoint(faces[i].tl(), faces[i].br());

			}

			if (faces.size() > 0) {
				faceDetected = true;
				std::cout << "Detected" << std::endl;
			}
			else {
				faceDetected = false;
				std::cout << "NotDetected" << std::endl;
			}
		}
		framesPerSecond = 1.0f / *timing;
		std::cout << framesPerSecond << std::endl;
		
	}
}

int FaceDetection::getXCoordinate() { return xCoordinate; }

int FaceDetection::getYCoordinate() { return yCoordinate; }

double FaceDetection::getFramesPerSecond() { return framesPerSecond; }

bool FaceDetection::getFaceDetected() { return faceDetected; }
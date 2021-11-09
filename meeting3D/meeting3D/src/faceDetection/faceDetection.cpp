#include "faceDetection\faceDetection.hpp"
#include <iostream>
#include "utils/basicGeometry.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include "utils/timer.hpp"
#include "utils/vector2D.hpp"



#include <fstream>

FaceDetection::FaceDetection(faceDetectionInput input) : faceDetectionData(input), xCoordinate(0.0), yCoordinate(0.0), framesPerSecond(0.0), faceDetected(false) {

	this->faceDetectionData.faceCascade.load(input.haarCascadeXmlPath);
}


void FaceDetection::solve() {
	
	// Check if XML was not loaded
	if (faceDetectionData.faceCascade.empty()) {
		std::cout << "XML file not found" << std::endl;
		return;
	}
	
	// Generate local image variables
	cv::Mat image;
	cv::Mat resizedImgage;
	std::vector<cv::Rect> faces;
	Vector2d<int> center;

	//Get camera resolution for resizing

	faceDetectionData.camera.read(image);
	
	

	std::ofstream myfile;
	myfile.open("example.csv");

	while (true) {
		float* timing = new float;
		{
			Timer timer(timing);
			faceDetectionData.camera.read(image);

			faces.clear();

			faceDetectionData.faceCascade.detectMultiScale(image, faces, faceDetectionData.scaleFactor, faceDetectionData.minNeighbors);

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
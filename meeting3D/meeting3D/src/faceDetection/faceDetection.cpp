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

FaceDetection::FaceDetection(faceDetectionInput const& input) : faceDetectionData(input) {

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

	//Get camera resolution for resizing

	faceDetectionData.camera.read(image);

	std::ofstream myfile;
	myfile.open("example.csv");

	while (true) {

		auto timing = std::make_shared<float>();
		
		detectFace(timing, image, faces);

		if (*timing != 0.0) {
			framesPerSecond = 1.0f / *timing;
			std::cout << framesPerSecond << "\n" << std::endl;
		}

		cv::imshow("image", image);
		cv::waitKey(1);
		
	}
}

void FaceDetection::detectFace(std::shared_ptr<float> timing, cv::Mat image, std::vector<cv::Rect> faces) {
	Timer timer(timing.get());
	faceDetectionData.camera.read(image);

	faces.clear();

	faceDetectionData.faceCascade.detectMultiScale(image, faces, faceDetectionData.scaleFactor, faceDetectionData.minNeighbors, 0, cv::Size(faceDetectionData.minSize, faceDetectionData.minSize));

	if (faces.empty()) return;

	auto f = [=](std::vector<cv::Rect> rects) {
		cv::Rect biggest = rects[0];
		for (auto r : rects) {
			if (r.width > biggest.width)
				biggest = r;
		}
		return biggest;
	};

	cv::Rect biggestRect = f(faces);

	rectangle(image, biggestRect.tl(), biggestRect.br(), cv::Scalar(255, 0, 255), 3);

	cv::Point2i center = getCenterPoint(biggestRect.tl(), biggestRect.br());
	xCoordinate = center.x;
	yCoordinate = center.y;


	if (!faces.empty()) {
		faceDetected = true;
		std::cout << "Detected" << std::endl;
	}
	else {
		faceDetected = false;
		std::cout << "NotDetected" << std::endl;
	}
}

double FaceDetection::getXCoordinate() const { return xCoordinate; }

double FaceDetection::getYCoordinate() const { return yCoordinate; }

double FaceDetection::getFramesPerSecond() const { return framesPerSecond; }

bool FaceDetection::getFaceDetected() const { return faceDetected; }
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

/// <summary>
/// cascadeFaceDetection constructor from faceDetectionInput variable and checks for possible errors
/// </summary>
/// <param name="input"></param>
faceDetection::faceDetection(faceDetectionInput const& input) : faceDetectionData(input) {
	
	// Loads parameters and sets error to NO_ERROR status
	this->faceDetectionData.faceCascade.load(input.haarCascadeXmlPath);
	this->error = errorCode::NO_ERROR;

	// Checks different errors during object creation
	if (!this->faceDetectionData.camera.isOpened()) {
		this->error = errorCode::CAM_ERROR;
		throw std::invalid_argument("Could not find any camera connected to the specified port");
	}
	if (this->faceDetectionData.faceCascade.empty()) {
		this->error = errorCode::XML_ERROR;
		throw std::invalid_argument("Could not find haarCascadeXml");
	}
	if (this->faceDetectionData.faceCascade.empty()) {
		this->error = errorCode::CLASSIFIER_ERROR;
		throw std::invalid_argument("Face detection classifier not initialized correctly");
	}
	if (this->faceDetectionData.scaleFactor <= 1) {
		this->error = errorCode::SCALE_FACTOR_ERROR;
		throw std::out_of_range("Scale factor out of bounds (has to be higher than 1.0)");
	}
	if (this->faceDetectionData.minNeighbors <= 1) {
		this->error = errorCode::MIN_NEIGHBOURS_ERROR;
		throw std::out_of_range("Min neighbors out of bounds (has to be higher than 1)");
	}
}


[[ noreturn ]]  void faceDetection::solve() {
	
	// Variable where the cam info will be stored
	cv::Mat image;

	// Vector of Rect objects where the possible faces from the cascade classifier are stored
	std::vector<cv::Rect> faces;

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

		faceDetectionData.camera.read(image);

		if (lastDetection) {
			Timer timer(timing.get());
			croppedImage = cropFaceSurrounding(image, faceCenter, lastContour.size());
			lastDetection = detectFace(croppedImage, faces, lastContour);
			cv::Point2i croppedFaceCenter = getCenterPoint(lastContour.tl(), lastContour.br());
			cv::Point2i faceCenterMove(croppedFaceCenter.x - (croppedImage.cols / 2), croppedFaceCenter.y - croppedImage.rows / 2);
			faceCenter = faceCenter + faceCenterMove;
		}
		else {
			Timer timer(timing.get());
			croppedImage = image;
			lastDetection = detectFace(croppedImage, faces, lastContour);
			faceCenter = getCenterPoint(lastContour.tl(), lastContour.br());
		}
		
		if (*timing != 0.0) {
			framesPerSecond = 1.0f / *timing;
			std::cout << framesPerSecond << "\n" << std::endl;
		}
		cv::imshow("Image", image);
		cv::waitKey(2);
		
	}
}

bool faceDetection::detectFace(cv::Mat image, std::vector<cv::Rect> faces, cv::Rect& lastContour) {

	faces.clear();

	faceDetectionData.faceCascade.detectMultiScale(image, faces, faceDetectionData.scaleFactor, faceDetectionData.minNeighbors, 0, cv::Size(faceDetectionData.minSize, faceDetectionData.minSize));

	if (faces.empty()) return false;

	auto f = [=](std::vector<cv::Rect> rects) {
		cv::Rect biggest = rects[0];
		for (auto r : rects) {
			if (r.width > biggest.width)
				biggest = r;
		}
		return biggest;
	};

	cv::Rect biggestRect = f(faces);

	lastContour = biggestRect;

	rectangle(image, biggestRect.tl(), biggestRect.br(), cv::Scalar(255, 0, 255), 3);

	cv::Point2i center = getCenterPoint(biggestRect.tl(), biggestRect.br());
	xCoordinate = center.x;
	yCoordinate = center.y;

	return true;
}

double faceDetection::getXCoordinate() const { return xCoordinate; }

double faceDetection::getYCoordinate() const { return yCoordinate; }

double faceDetection::getFramesPerSecond() const { return framesPerSecond; }

bool faceDetection::getFaceDetected() const { return faceDetected; }
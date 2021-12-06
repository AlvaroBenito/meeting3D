#include "faceDetection/dnnFaceDetection.hpp"
#include <iostream>
#include <utils/basicGeometry.hpp>

dnnFaceDetecion::dnnFaceDetecion(dnnFaceDetectionInput const& input, cv::VideoCapture const& camera) : faceDetection(camera), faceDetectionData(input){
	this->net = cv::dnn::readNet(faceDetectionData.configFile, faceDetectionData.weightFile);
	this->error = errorCodeDnn::NO_ERROR;
}

bool dnnFaceDetecion::findFace(cv::Mat image, cv::Rect& lastContour) {


	int frameWidth = image.cols;
	int frameHeight = image.rows;
	auto meanVal = cv::Scalar(127.5, 127.5, 127.5);
	auto size = cv::Size(300, 300);

	// Establish mode of operation
	if (net.empty()) {
		std::cout << "Network weights not loaded" << std::endl;
	}

	net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
	net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);

	// Pass the image to blob 
	cv::Mat inputBlob = cv::dnn::blobFromImage(image, 1.0, size, meanVal, true, false);
	net.setInput(inputBlob, "data");

	// Pass the image to the network
	cv::Mat output = net.forward("detection_out");
	
	// Matrix with the detections
	cv::Mat results(output.size[2], output.size[3], CV_32F, output.ptr<float>());

	// Run through predictions and get biggest face
	for (int i = 0; i < results.rows; i++) {
		float confidence = results.at<float>(i, 2);

		// Check if the detection is over the min threshold and draw box
		if (confidence > this->faceDetectionData.confidenceThreshold) {
			
			auto x1 = static_cast<int>(results.at<float>(i, 3) * (float)frameWidth);
			auto y1 = static_cast<int>(results.at<float>(i, 4) * (float)frameHeight);
			auto x2 = static_cast<int>(results.at<float>(i, 5) * (float)frameWidth);
			auto y2 = static_cast<int>(results.at<float>(i, 6) * (float)frameHeight);
			lastContour = cv::Rect(cv::Point(x1, y1), cv::Point(x2, y2));

			cv::Point2i center = getCenterPoint(lastContour.tl(), lastContour.br());
			this->setxCoordinate(center.x);
			this->setyCoordinate(center.y);

			cv::rectangle(image, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(255, 0, 255), 2, 4);
			std::cout << center << std::endl;
			return true;
		}
	}
	
	return false;
}

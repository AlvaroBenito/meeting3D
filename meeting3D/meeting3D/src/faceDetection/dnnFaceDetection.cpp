#include "faceDetection/dnnFaceDetection.hpp"
#include <iostream>
#include <utils/basicGeometry.hpp>

dnnFaceDetecion::dnnFaceDetecion(dnnFaceDetectionInput const& input, cv::VideoCapture const& camera) : faceDetection(camera), faceDetectionData(input) {
	this->net = cv::dnn::readNet(faceDetectionData.configFile, faceDetectionData.weightFile);

	if (net.empty()) {
		this->error = errorCodeDnn::EMPTY_NET;
		throw std::invalid_argument("Could not load DNN parameter files");
	}
	else
		this->error = errorCodeDnn::NO_ERROR;

	// Establish mode of operation
	net.setPreferableBackend(cv::dnn::DNN_BACKEND_DEFAULT);
	net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
}

bool dnnFaceDetecion::findFace(cv::Mat image, cv::Rect& lastContour) {

	// Pass the image to blob 
	cv::Mat inputBlob = cv::dnn::blobFromImage(image, 1.0, cv::Size(300, 300), cv::Scalar(127.5, 127.5, 127.5), false, false);
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
			
			auto x1 = static_cast<int>(results.at<float>(i, 3) * (float)image.cols);
			auto y1 = static_cast<int>(results.at<float>(i, 4) * (float)image.rows);
			auto x2 = static_cast<int>(results.at<float>(i, 5) * (float)image.cols);
			auto y2 = static_cast<int>(results.at<float>(i, 6) * (float)image.rows);
			lastContour = cv::Rect(cv::Point(x1, y1), cv::Point(x2, y2));

			cv::Point2i center = getCenterPoint(lastContour.tl(), lastContour.br());
			this->setxCoordinate(center.x);
			this->setyCoordinate(center.y);

			cv::rectangle(image, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(255, 0, 255), 2, 4);
			return true;
		}
	}
	
	return false;
}

faceDetectionType dnnFaceDetecion::getType() {
	return faceDetectionType::DNN_CLASSIFIER;
}

#pragma once

#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>

struct faceDetectionInput {
	cv::VideoCapture camera;
	cv::CascadeClassifier faceCascade;
	cv::String haarCascadeXmlPath;
	double scaleFactor;
	int minNeighbors;

	faceDetectionInput(cv::VideoCapture cam, cv::CascadeClassifier classifier, cv::String xmlPath, double scale, int neighbors) {
		this->camera = cam;
		this->faceCascade = classifier;
		this->haarCascadeXmlPath = xmlPath;
		this->scaleFactor = scale;
		this->minNeighbors = neighbors;
	}

};
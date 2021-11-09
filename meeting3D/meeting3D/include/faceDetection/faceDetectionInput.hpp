#pragma once

#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>

struct faceDetectionInput {
	cv::VideoCapture camera;
	cv::CascadeClassifier faceCascade;
	cv::String haarCascadeXmlPath;
	double scaleFactor;
	int minNeighbors;
	int minSize;

	faceDetectionInput(cv::VideoCapture const& cam, cv::CascadeClassifier classifier, cv::String const& xmlPath, double scale, int neighbors, int size) :
	camera(cam), faceCascade(classifier), haarCascadeXmlPath(xmlPath), scaleFactor(scale), minNeighbors(neighbors), minSize(size){}
};
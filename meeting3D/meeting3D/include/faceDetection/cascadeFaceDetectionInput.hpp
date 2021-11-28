#pragma once

#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>

/// <summary>
/// Structure that contains all of the necessary inputs for the cascadeFaceDetection class
/// </summary>
struct cascadeFaceDetectionInput {
	cv::CascadeClassifier faceCascade;
	cv::String haarCascadeXmlPath;
	double scaleFactor;
	int minNeighbors;
	int minSize;
	int frameRateLimit;

	cascadeFaceDetectionInput(cv::CascadeClassifier classifier, cv::String const& xmlPath, double scale, int neighbors, int size, int frameRateLimit) :
	faceCascade(classifier), haarCascadeXmlPath(xmlPath), scaleFactor(scale), minNeighbors(neighbors), minSize(size), frameRateLimit(frameRateLimit){}
};
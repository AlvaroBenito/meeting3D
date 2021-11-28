#pragma once
#include "faceDetection/faceDetection.hpp"
#include <opencv2/imgproc.hpp>

/// <summary>
/// Enum for the possible errors for face detection algorithm
/// </summary>
enum class errorCode {

	NO_ERROR = 0,
	XML_ERROR,
	CAM_ERROR,
	CLASSIFIER_ERROR,
	SCALE_FACTOR_ERROR,
	MIN_NEIGHBOURS_ERROR
};

class cascadeFaceDetection : public faceDetection{

private:

	// Input variables
	cascadeFaceDetectionInput faceDetectionData;

	// Status variables
	errorCode error;

public:

	explicit cascadeFaceDetection(cascadeFaceDetectionInput const& input, cv::VideoCapture camera);

	bool getFace(cv::Mat image, cv::Rect& lastContour) override;
	
};
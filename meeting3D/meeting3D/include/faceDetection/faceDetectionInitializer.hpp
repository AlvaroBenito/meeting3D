#pragma once
#include <opencv2/highgui.hpp>
#include "faceDetection/dnnFaceDetection.hpp"
#include "faceDetection/cascadeFaceDetection.hpp"

cascadeFaceDetectionInput initializeCascadeFaceDetector();
void callCascadeFaceDetection(cascadeFaceDetectionInput faceInput, cv::VideoCapture const& camera);
dnnFaceDetectionInput initializeDnnFaceDetector();
void callDnnFaceDetection(const dnnFaceDetectionInput& faceInput, cv::VideoCapture const& camera);

	
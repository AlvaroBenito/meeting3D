#pragma once
#include <opencv2/highgui.hpp>
#include "faceDetection/dnnFaceDetection.hpp"

dnnFaceDetectionInput initializeDnnFaceDetector();
void callDnnFaceDetection(const dnnFaceDetectionInput& faceInput, cv::VideoCapture const& camera);
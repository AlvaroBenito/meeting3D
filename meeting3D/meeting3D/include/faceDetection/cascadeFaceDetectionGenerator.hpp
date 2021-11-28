#pragma once
#include <opencv2/highgui.hpp>
#include "faceDetection/cascadeFaceDetection.hpp"

cascadeFaceDetectionInput initializeCascadeFaceDetector();
void callCascadeFaceDetection(cascadeFaceDetectionInput faceInput, cv::VideoCapture const& camera);
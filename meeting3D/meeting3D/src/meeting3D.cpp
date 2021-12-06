// meeting3D.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.

#include <iostream>
#include <thread>
#include <opencv2/highgui.hpp>
#include "opencv2/core/utils/logger.hpp"
#include "faceDetection/cascadeFaceDetectionGenerator.hpp"
#include "faceDetection/dnnFaceDetectionGenerator.hpp"

#define DNN

/// <summary>
/// Main function of the program. The program flow is contained in this function.
/// </summary>
/// <returns></returns>
int main() {

    // Disable opencv logging to
    cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);

    // Declare camera port
    cv::VideoCapture camera(1);

#ifdef DNN
	dnnFaceDetectionInput faceInput = initializeDnnFaceDetector();
    callDnnFaceDetection(faceInput, camera);
#else
	cascadeFaceDetectionInput faceInput = initializeCascadeFaceDetector();
	callCascadeFaceDetection(faceInput, camera);
#endif

    return 0;
}


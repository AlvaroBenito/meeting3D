// meeting3D.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.

#include <iostream>
#include <thread>
#include <opencv2/highgui.hpp>
#include "opencv2/core/utils/logger.hpp"
#include "faceDetection/faceDetectionInitializer.hpp"
#define DNN


void cascadeFaceDetectionReader(faceDetectionOutput* output) {
	cv::VideoCapture camera(1);
	cascadeFaceDetectionInput faceInput = initializeCascadeFaceDetector();
    callCascadeFaceDetection(faceInput, camera, output);
}

void dnnFaceDetectionReader(faceDetectionOutput* output) {
    cv::VideoCapture camera(1);
	dnnFaceDetectionInput faceInput = initializeDnnFaceDetector();
	callDnnFaceDetection(faceInput, camera, output);
}

// EXAMPLE CLASS FOR MUTEX HANDLING WITH FACE DETECTION OUTPUT
void readFramesPerSecond(faceDetectionOutput* output) {
    while (true) {
        std::unique_lock locked(output->mutex);
        output->condition.wait( locked, [&output] { return output->frameProcessed; });
        output->frameProcessed = false;
        locked.unlock();
        
        std::cout << "Awaken" << std::endl;
    }
}




/// <summary>
/// Main function of the program. The program flow is contained in this function.
/// </summary>
/// <returns></returns>
int main() {

    // Disable opencv logging to
    cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);

    // Declare camera port
    cv::VideoCapture camera(1);
    faceDetectionOutput output(0.0, 0.0, 0.0, false);

#ifdef DNN
	std::jthread faceDetectionThread(dnnFaceDetectionReader, &output);
#else
    std::jthread faceDetectionThread(cascadeFaceDetectionReader, &faceDetectionOutput);
#endif
    
}


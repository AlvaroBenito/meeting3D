// meeting3D.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.

#include <iostream>
#include <thread>
#include <opencv2/highgui.hpp>
#include "opencv2/core/utils/logger.hpp"
#include "faceDetection/faceDetection.hpp"
using namespace cv;
using namespace std;

void callFaceDetector(faceDetectionInput faceInput);

/// <summary>
/// Main function of the program. The program flow is contained in this function.
/// </summary>
/// <returns></returns>
int main() {

    // Disable opencv logging to
    cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);

    // Creation of all the necessary variables for the face detection algorithm
    VideoCapture camera(1);
    CascadeClassifier faceCascade;
    String haarCascadeXmlPath = "resources/haarcascade_frontalface_default.xml";
    double scaleFactor = 1.05;
    int minNeighbors = 6;
    int minSize = 100;
    int frameRateLimit = 60;
    // Generation of the face detection algorithm and call
    faceDetectionInput faceInput(camera, faceCascade, haarCascadeXmlPath, scaleFactor, minNeighbors, minSize, frameRateLimit);

    try {
        std::jthread faceDetection(callFaceDetector, faceInput);
    }
    catch(const invalid_argument& e) {
        cout << "\\\\\\\\\\\\\\\\\\ ERROR IN HAAR CASCADE CLASSIFIER \\\\\\\\\\\\\\\\\\" << endl;
        cout << "\\\\\\\\\\\\\\\\\\ " << e.what() << " \\\\\\\\\\\\\\\\\\" << endl;
        cout << "\\\\\\\\\\\\\\\\\\ ERROR IN HAAR CASCADE CLASSIFIER \\\\\\\\\\\\\\\\\\" << endl;
        return -1;
    }
    return 0;
}

void callFaceDetector(faceDetectionInput faceInput){
    try {
        faceDetection detect(faceInput);
        detect.solve();
    }
	catch (const std::out_of_range& e) {
		cout << e.what() << endl;
		if (faceInput.scaleFactor <= 1) {
			faceInput.scaleFactor = 1.1;
			cout << "Scale factor changed to 1.1" << endl;
            cout << "Press enter to continue" << endl;
            cin.get();
            callFaceDetector(faceInput);
		}
        if (faceInput.minNeighbors <= 1) {
            faceInput.minNeighbors = 3;
            cout << "Min neighbors changed to 3" << endl;
            cout << "Press enter to continue" << endl;
            cin.get();
            callFaceDetector(faceInput);
        }
	}
}
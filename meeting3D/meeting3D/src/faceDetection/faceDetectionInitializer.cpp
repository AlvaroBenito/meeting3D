#pragma once
#include  "faceDetection/faceDetectionInitializer.hpp"

#include <iostream>


// Activate or not Caffe model vs Tf model
#define CAFFE

/**
 * This file provides the API to create a cascade classifier for face detection in real time using computers web cam
 */

 /**
  * The parameters of the classifier are contained in the initialize function and can be tweaked according to the program requirements.
  *
  * Recommended values for scale factor goes from 1.05 (high accuracy and slow performance) up to 1.4 (low accuracy and fast performance)
  * Recommended values for min neighbors goes from 2 (more detections but with less quality) to 8 (less detections but with more quality)
  * Frame rate limit is yet to be implemented if a performance improvement is needed in other parts of the project.
  * \return
  */
cascadeFaceDetectionInput initializeCascadeFaceDetector() {
	// Creation of all the necessary variables for the face detection algorithm

	cv::CascadeClassifier faceCascade;
	cv::String haarCascadeXmlPath = "resources/haarcascade_frontalface_default.xml";
	double scaleFactor = 1.05;
	int minNeighbors = 6;
	int minSize = 100;
	int frameRateLimit = 60;
	return cascadeFaceDetectionInput(faceCascade, haarCascadeXmlPath, scaleFactor, minNeighbors, minSize, frameRateLimit);
}

/**
 * This function calls a cascade classifier face detection with the initialized inputs and calls a while loop that constantly
 * gets the face coordinates. If the numerical inputs of the algorithm are out of their valid ranges, a recommended value will be used
 *
 * \param faceInput : parameters of the face detection algorithm
 * \param camera : camera object from opencv library
 */
void callCascadeFaceDetection(cascadeFaceDetectionInput faceInput, cv::VideoCapture const& camera, faceDetectionOutput* output) {

	try {
		cascadeFaceDetection detect(faceInput, camera);
		detect.solve(output);
	}
	catch (const std::out_of_range& e) {
		std::cout << e.what() << std::endl;
		if (faceInput.scaleFactor <= 1) {
			faceInput.scaleFactor = 1.1;
			std::cout << "Scale factor changed to 1.1" << std::endl;
			std::cout << "Press enter to continue" << std::endl;
			std::cin.get();
			callCascadeFaceDetection(faceInput, camera, output);
		}
		if (faceInput.minNeighbors <= 1) {
			faceInput.minNeighbors = 3;
			std::cout << "Min neighbors changed to 3" << std::endl;
			std::cout << "Press enter to continue" << std::endl;
			std::cin.get();
			callCascadeFaceDetection(faceInput, camera, output);
		}
	}
	catch (const std::invalid_argument& e) {
		std::cout << "\\\\\\\\\\\\\\\\\\ ERROR IN HAAR CASCADE CLASSIFIER \\\\\\\\\\\\\\\\\\" << std::endl;
		std::cout << "\\\\\\\\\\\\\\\\\\ " << e.what() << " \\\\\\\\\\\\\\\\\\" << std::endl;
		std::cout << "\\\\\\\\\\\\\\\\\\ ERROR IN HAAR CASCADE CLASSIFIER \\\\\\\\\\\\\\\\\\" << std::endl;
		exit(-1);
	}
}



/**
 * This file provides the API to create a cascade classifier for face detection in real time using computers web cam
 */

 /**
  * The parameters of the classifier are contained in the initialize function and can be tweaked according to the program requirements.
  *
  * Recommended values for scale factor goes from 1.05 (high accuracy and slow performance) up to 1.4 (low accuracy and fast performance)
  * Recommended values for min neighbors goes from 2 (more detections but with less quality) to 8 (less detections but with more quality)
  * Frame rate limit is yet to be implemented if a performance improvement is needed in other parts of the project.
  * \return
  */
dnnFaceDetectionInput initializeDnnFaceDetector() {
	// Creation of all the necessary variables for the face detection algorithm

#ifdef CAFFE
	cv::String configFile = "resources/deploy.prototxt.txt";
	cv::String weightFile = "resources/res10_300x300_ssd_iter_140000.caffemodel";
#else
	cv::String configFile = "resources/opencv_face_detector.pbtxt";
	cv::String weightFile = "resources/opencv_face_detector_uint8.pb";
#endif
	return dnnFaceDetectionInput(configFile, weightFile, (float)0.6, 60);
}

/**
 * This function calls a cascade classifier face detection with the initialized inputs and calls a while loop that constantly
 * gets the face coordinates. If the numerical inputs of the algorithm are out of their valid ranges, a recommended value will be used
 *
 * \param faceInput : parameters of the face detection algorithm
 * \param camera : camera object from opencv library
 */
void callDnnFaceDetection(const dnnFaceDetectionInput& faceInput, cv::VideoCapture const& camera, faceDetectionOutput* output) {


	dnnFaceDetecion detect(faceInput, camera);

	detect.solve(output);

}
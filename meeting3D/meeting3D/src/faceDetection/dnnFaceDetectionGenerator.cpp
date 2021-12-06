#pragma once
#include  "faceDetection/dnnFaceDetectionGenerator.hpp"
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
dnnFaceDetectionInput initializeDnnFaceDetector() {
	// Creation of all the necessary variables for the face detection algorithm
	
#ifdef CAFFE
	cv::String configFile = "resources/deploy.prototxt.txt";
	cv::String weightFile = "resources/res10_300x300_ssd_iter_140000.caffemodel";
#else
	cv::String configFile = "resources/opencv_face_detector.pbtxt";
	cv::String weightFile = "resources/opencv_face_detector_uint8.pb";
#endif
	return dnnFaceDetectionInput(configFile, weightFile, (float)0.8, 60);
}

/**
 * This function calls a cascade classifier face detection with the initialized inputs and calls a while loop that constantly
 * gets the face coordinates. If the numerical inputs of the algorithm are out of their valid ranges, a recommended value will be used
 *
 * \param faceInput : parameters of the face detection algorithm
 * \param camera : camera object from opencv library
 */
void callDnnFaceDetection(const dnnFaceDetectionInput& faceInput, cv::VideoCapture const& camera) {

	dnnFaceDetecion detect(faceInput, camera);

	detect.solve();

}
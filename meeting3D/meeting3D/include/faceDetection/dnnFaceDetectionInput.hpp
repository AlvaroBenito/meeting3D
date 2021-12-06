#pragma once

#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>

/// <summary>
/// Structure that contains all of the necessary inputs for the cascadeFaceDetection class
/// </summary>
struct dnnFaceDetectionInput {
	std::string configFile;
	std::string weightFile;
	float confidenceThreshold;
	int frameRateLimit;

	dnnFaceDetectionInput(const std::string& config, const std::string& weight, float confidence, int frameRate) : 
		configFile(config), weightFile(weight), confidenceThreshold(confidence), frameRateLimit(frameRate) {}
};
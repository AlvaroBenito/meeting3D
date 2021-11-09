#pragma once
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>


cv::Point2i getCenterPoint(cv::Point2i upperRight, cv::Point2i downLeft) {
	
	cv::Point2i result;
	result.x = (upperRight.x + downLeft.x) / 2;
	result.y = (upperRight.y + downLeft.y) / 2;
	return result;
}



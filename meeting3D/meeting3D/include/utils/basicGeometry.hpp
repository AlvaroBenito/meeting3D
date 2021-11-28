#pragma once
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>


cv::Point2i getCenterPoint(cv::Point2i firstCorner, cv::Point2i secondCorner);
cv::Mat cropFaceSurrounding(cv::Mat const& image, cv::Point2i faceCenter, cv::Size faceSize);
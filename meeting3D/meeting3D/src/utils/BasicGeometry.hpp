#pragma once
#include "Vector2D.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>


Point2i getCenterPoint(Point2i upperRight, Point2i downLeft) {
	
	Point2i result;
	result.x = (upperRight.x + downLeft.x) / 2;
	result.y = (upperRight.y + downLeft.y) / 2;
	return result;
}



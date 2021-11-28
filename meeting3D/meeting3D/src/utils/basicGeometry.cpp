#pragma once
#include <utils/basicGeometry.hpp>


/// <summary>
/// Method that gets the center point from two corners of a rectangle
/// </summary>
/// <param name="upperRight"></param>
/// <param name="downLeft"></param>
/// <returns></returns>
cv::Point2i getCenterPoint(cv::Point2i firstCorner, cv::Point2i secondCorner) {
	cv::Point2i result;
	result.x = (firstCorner.x + secondCorner.x) / 2;
	result.y = (firstCorner.y + secondCorner.y) / 2;
	return result;
}


/// <summary>
/// Function that receives an image with a face detected and returns the image cropped around the face
/// </summary>
/// <param name="image"></param> Full size image
/// <param name="faceCenter"></param> Center point of the face (in pixels)
/// <param name="faceSize"></param> Size of the face (in pixels)
/// <returns></returns>
cv::Mat cropFaceSurrounding(cv::Mat const& image, cv::Point2i faceCenter, cv::Size faceSize) {

	// expand region of interest
	int inflationSize = 50;
	cv::Point2i topLeft(faceCenter.x - faceSize.width / 2, faceCenter.y - faceSize.height / 2);
	cv::Point2i bottomRight(faceCenter.x + faceSize.width / 2, faceCenter.y + faceSize.height / 2);
	cv::Rect contour(topLeft, bottomRight);

	contour += cv::Point(-inflationSize / 2, -inflationSize / 2);
	contour += cv::Size(inflationSize, inflationSize);

	cv::Rect roi = contour & cv::Rect(0, 0, image.cols, image.rows);
	return image(roi);
}


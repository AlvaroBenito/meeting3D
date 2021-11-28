#include <faceDetection/cascadeFaceDetection.hpp>
#include <utils/basicGeometry.hpp>


/// <summary>
/// cascadeFaceDetection constructor from faceDetectionInput variable and checks for possible errors
/// </summary>
/// <param name="input"></param>
cascadeFaceDetection::cascadeFaceDetection(cascadeFaceDetectionInput const& input, cv::VideoCapture camera) :  faceDetection(camera), faceDetectionData(input) {

	// Loads parameters and sets error to NO_ERROR status
	this->faceDetectionData.faceCascade.load(input.haarCascadeXmlPath);
	this->error = errorCode::NO_ERROR;

	// Checks different errors during object creation
	if (!this->getCamera().isOpened()) {
		this->error = errorCode::CAM_ERROR;
		throw std::invalid_argument("Could not find any camera connected to the specified port");
	}
	if (this->faceDetectionData.faceCascade.empty()) {
		this->error = errorCode::XML_ERROR;
		throw std::invalid_argument("Could not find haarCascadeXml");
	}
	if (this->faceDetectionData.faceCascade.empty()) {
		this->error = errorCode::CLASSIFIER_ERROR;
		throw std::invalid_argument("Face detection classifier not initialized correctly");
	}
	if (this->faceDetectionData.scaleFactor <= 1) {
		this->error = errorCode::SCALE_FACTOR_ERROR;
		throw std::out_of_range("Scale factor out of bounds (has to be higher than 1.0)");
	}
	if (this->faceDetectionData.minNeighbors <= 1) {
		this->error = errorCode::MIN_NEIGHBOURS_ERROR;
		throw std::out_of_range("Min neighbors out of bounds (has to be higher than 1)");
	}
}


bool cascadeFaceDetection::getFace(cv::Mat image, cv::Rect& lastContour) {
	std::vector<cv::Rect> faces;
	faces.clear();

	faceDetectionData.faceCascade.detectMultiScale(
		image,
		faces, faceDetectionData.scaleFactor,
		faceDetectionData.minNeighbors,
		0,
		cv::Size(faceDetectionData.minSize,
			faceDetectionData.minSize));

	if (faces.empty()) return false;

	auto f = [=](std::vector<cv::Rect> rects) {
		cv::Rect biggest = rects[0];
		for (auto r : rects) {
			if (r.width > biggest.width)
				biggest = r;
		}
		return biggest;
	};

	cv::Rect biggestRect = f(faces);

	lastContour = biggestRect;

	rectangle(image, biggestRect.tl(), biggestRect.br(), cv::Scalar(255, 0, 255), 3);

	cv::Point2i center = getCenterPoint(biggestRect.tl(), biggestRect.br());
	this->setxCoordinate(center.x);
	this->setyCoordinate(center.y);

	return true;
}
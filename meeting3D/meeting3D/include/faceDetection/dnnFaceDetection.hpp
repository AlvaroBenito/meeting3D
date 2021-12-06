
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "faceDetection.hpp"
#include "dnnFaceDetectionInput.hpp"



/// <summary>
/// Enum for the possible errors for face detection algorithm
/// </summary>
enum class errorCodeDnn {

	NO_ERROR = 0
	
};


class dnnFaceDetecion : public faceDetection {

private:

	// Input variables
	dnnFaceDetectionInput faceDetectionData;

	// Network
	cv::dnn::Net net;

	// Status variables
	errorCodeDnn error;

public:

	explicit dnnFaceDetecion(dnnFaceDetectionInput const& input, cv::VideoCapture const& camera);

	bool findFace(cv::Mat image, cv::Rect& lastContour) override;


};

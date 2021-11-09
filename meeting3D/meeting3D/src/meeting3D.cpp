// meeting3D.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>

#include "faceDetection\faceDetection.hpp"


using namespace cv;
using namespace std;


int main() {

    VideoCapture camera(1);
    CascadeClassifier faceCascade;
    String haarCascadeXmlPath = "resources/haarcascade_frontalface_default.xml";
    double scaleFactor = 1.1;
    int minNeighbors = 3;

    faceDetectionInput faceInput(camera, faceCascade, haarCascadeXmlPath, scaleFactor, minNeighbors);
    FaceDetection faceDetection(faceInput);

    faceDetection.solve();    

    return 0;
}


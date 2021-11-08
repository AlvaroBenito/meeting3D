// meeting3D.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>

#include "FaceDetection.h"


using namespace cv;
using namespace std;


void main() {

    VideoCapture camera(1);
    CascadeClassifier faceCascade;
    String haarCascadeXmlPath = "resources/haarcascade_frontalface_default.xml";

    FaceDetection faceDetection(camera, faceCascade, haarCascadeXmlPath);

    faceDetection.solve();    


}


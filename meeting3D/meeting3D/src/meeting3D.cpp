// meeting3D.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <faceDetection/cascadeFaceDetection.hpp>


using namespace cv;
using namespace std;

/// <summary>
/// Main function of the program
/// </summary>
/// <returns></returns>
int main() {

    // Creation of all the necessary variables for the face detection algorithm
    VideoCapture camera(1);
    CascadeClassifier faceCascade;
    String haarCascadeXmlPath = "resources/haarcascade_frontalface_default.xml";
    double scaleFactor = 1.1;
    int minNeighbors = 3;
    int minSize = 100;

    // Generation of the face detection algorithm and call
    faceDetectionInput faceInput(camera, faceCascade, haarCascadeXmlPath, scaleFactor, minNeighbors, minSize);
    cascadeFaceDetection detect(faceInput);
    detect.solve();    

    return 0;
}


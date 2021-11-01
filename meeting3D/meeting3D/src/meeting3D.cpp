// meeting3D.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>

using namespace cv;
using namespace std;


/*
    VideoCapture cam(1);
    Mat img;

    while (true) {
        cam.read(img);

        imshow("Image", img);
        waitKey(100);
    }
    */

void main() {

    /*string path = "resources/P1070056.JPG";
    Mat img = imread(path);
    Mat imgSmall;

    resize(img, imgSmall, Size(), 0.3, 0.3)*/;

    VideoCapture cam(1);
    Mat img;
    Mat greyImg;
    Mat smallImg;
    CascadeClassifier faceCascade;
    faceCascade.load("resources/haarcascade_frontalface_default.xml");

    if (faceCascade.empty()) { cout << "XML file not found" << endl; }

    vector<Rect> faces;

    while (true) {
        cam.read(img);
        
        resize(img, smallImg, Size(), 0.5, 0.5);
        cvtColor(smallImg, greyImg, COLOR_BGR2GRAY);
        faceCascade.detectMultiScale(greyImg, faces, 1.1, 10);
        for (int i = 0; i < faces.size(); i++) {
            rectangle(greyImg, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3);
        }

        imshow("Image", greyImg);
        waitKey(10);
    }
    
    
    


}


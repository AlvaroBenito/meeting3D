// OpenCV_Test.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


using namespace cv;
using namespace std;

void main() {

    Mat poio = imread("FotoCarnet.png");
    Mat grey;
    imshow("Prueba", poio);
    cvtColor(poio, grey, COLOR_BGR2GRAY);
    imshow("gris", grey);
    waitKey(0);
}


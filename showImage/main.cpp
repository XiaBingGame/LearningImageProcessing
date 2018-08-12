#include <QCoreApplication>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "example.h"
#include "showui.h"
#include <QFont>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    // return read_and_write_image(argc, argv);
    //return read_and_write_video(argc, argv);
    showui(argc, argv);

    return 0;
}

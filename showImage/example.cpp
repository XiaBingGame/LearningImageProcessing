#include "example.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int read_and_write_image(int argc, char *argv[])
{
    Mat in_image, out_image;

    if(argc < 3)
        return 0;
    in_image = imread(argv[1], IMREAD_UNCHANGED);

    if(in_image.empty())
    {
        cout << "Error! Input image cannot be read...\n";
        return -1;
    }

    namedWindow(argv[1], WINDOW_AUTOSIZE);
    namedWindow(argv[2], WINDOW_AUTOSIZE);

    imshow(argv[1], in_image);
    cvtColor(in_image, out_image, COLOR_BGR2GRAY);
    imshow(argv[2], out_image);
    cout << "Press any key to exit...\n";
    waitKey();
    imwrite(argv[2], out_image);
    return 0;
}

int read_and_write_video(int argc, char* argv[])
{
    Mat in_frame, out_frame;
    const char win1[] = "Grabbing...", win2[] = "Recording...";
    double fps = 30;
    char file_out[] = "recorded.avi";

    VideoCapture inVid(0);
    if(!inVid.isOpened())
    {
        cout << "Error! Camera not ready...\n";
        return -1;
    }

    int width = (int)inVid.get(CAP_PROP_FRAME_WIDTH);
    int height = (int)inVid.get(CAP_PROP_FRAME_HEIGHT);
    VideoWriter recVid(file_out,
                       VideoWriter::fourcc('M', 'S', 'V', 'C'),
                       fps, Size(width, height));
    if(!recVid.isOpened()) {
        cout << "Error! Video file not opened...\n";
        return -1;
    }

    namedWindow(win1);
    namedWindow(win2);
    while(true)
    {
        inVid >> in_frame;
        cvtColor(in_frame, out_frame, COLOR_BGR2GRAY);
        recVid << out_frame;
        imshow(win1, in_frame);
        imshow(win2, out_frame);
        if(waitKey(1000/fps) >= 0)
            break;
    }
    inVid.release();
    return 0;
}

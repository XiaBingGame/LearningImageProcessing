#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char *argv[])
{
    Mat image = imread("fruits.jpg");
    if(image.empty())
        return 0;

    uchar M[256];
    for(int i = 0; i < 256; i++)
    {
        if(i > 128)
            M[i] = 255;
        else
            M[i] = 0;
    }
    Mat lut(1, 256, CV_8UC1, M);
    Mat dst;
    LUT(image, lut, dst);

    imshow("origin", image);
    imshow("lut", dst);

    waitKey();

    return 0;
}

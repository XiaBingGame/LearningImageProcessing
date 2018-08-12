#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    Mat src;
    src = imread("checkerboard.jpg");
    namedWindow("original", WINDOW_AUTOSIZE);
    imshow("original", src);

    Mat dst, dst2, dst3;
    inRange(src, Scalar(0, 0, 100), Scalar(40, 30, 255), dst);
    // 可以获取图像里类似结构的物体.
    // getStructuringElement
    Mat element = getStructuringElement(MORPH_ELLIPSE, Size(15, 15));
    dilate(dst, dst2, element);
    erode(dst2, dst3, element);

    namedWindow("segmented", WINDOW_AUTOSIZE);
    imshow("segmented", dst);
    namedWindow("dilation", WINDOW_AUTOSIZE);
    imshow("dilation", dst2);
    namedWindow("erosion", WINDOW_AUTOSIZE);
    imshow("erosion", dst3);

    waitKey(0);
    return 0;
}

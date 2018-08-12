#include "opencv2/opencv.hpp"

using namespace cv;

int main(int argc, char *argv[])
{
    Mat src;
    if(argc == 1)
        return 0;
    src = imread(argv[1]);

    Mat dst, dst2;
    Sobel(src, dst, -1, 1, 1);
    Laplacian(src, dst2, -1);

    namedWindow("original", WINDOW_AUTOSIZE);
    imshow("original", src);
    namedWindow("sobel", WINDOW_AUTOSIZE);
    imshow("sobel", dst);
    namedWindow("laplacian", WINDOW_AUTOSIZE);
    imshow("laplacian", dst2);

    waitKey(0);
   
    return 0;
}

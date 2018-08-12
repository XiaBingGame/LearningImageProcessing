#include <QCoreApplication>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void histogramcalculation(const Mat& Image, Mat& histoImage)
{
    int histSize = 255;

    float range[] = {0, 256};
    const float* histRange = {range};

    bool uniform = true; bool accumulate = false;
    Mat b_hist, g_hist, r_hist;
    vector<Mat> bgr_planes;
    split(Image, bgr_planes);

    // 计算各个直方图
    calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound((double)hist_w/histSize);
    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

    // 结果归一化为 [0, histImage.rows]
    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

    // 为每个通道进行绘制
    for(int i = 1; i < histSize; i++) {
        line(histImage, Point(bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1))), Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))),
             Scalar(255, 0, 0), 2, 8, 0);
        line(histImage, Point(bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1))), Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))),
             Scalar(0, 255, 0), 2, 8, 0);
        line(histImage, Point(bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1))), Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))),
             Scalar(0, 0, 255), 2, 8, 0);
    }
    histoImage = histImage;
}

int main(int argc, char *argv[])
{
    Mat src, imageq;
    Mat histImage;
    // 读取原始图像
    src = imread("fruits.jpg");
    if(!src.data)
    {
        cout << "Error image" << endl;
        return -1;
    }

    // 图像划为三个部分
    vector<Mat> bgr_planes;
    split(src, bgr_planes);
    imshow("Source image", src);

    // 计算直方图
    histogramcalculation(src, histImage);
    imshow("Colour Image Histogram", histImage);

    // 均衡化
    equalizeHist(bgr_planes[0], bgr_planes[0]);
    equalizeHist(bgr_planes[1], bgr_planes[1]);
    equalizeHist(bgr_planes[2], bgr_planes[2]);
    merge(bgr_planes, imageq);
    imshow("Equalized Image ", imageq);

    // 重计算
    histogramcalculation(imageq, histImage);
    imshow("Equalized Colour Image Histogram", histImage);

    waitKey();
    return 0;
}

#include <QCoreApplication>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

void histogram2Dcalculation(const Mat& src, Mat& histo2D)
{
    Mat hsv;
    // BGR 转 HSV
    cvtColor(src, hsv, CV_BGR2HSV);

    int hbins = 255;
    int sbins = 255;
    int histSize[] = {hbins, sbins};

    float hranges[] = {0, 180};
    float sranges[] = {0, 256};

    const float* ranges[] = {hranges, sranges};

    MatND hist, hist2;
    int channels[] = {0, 1};

    calcHist(&hsv, 1, channels, Mat(), hist, 2, histSize, ranges, true, false);
    double maxVal = 0;
    minMaxLoc(hist, 0, &maxVal, 0, 0);

    int scale = 1;
    Mat histImg = Mat::zeros(sbins*scale, hbins*scale, CV_8UC3);

    for(int h = 0; h < hbins; h++)
        for(int s = 0; s < sbins; s++)
        {
            float binVal = hist.at<float>(h, s);
            int intensity = cvRound(binVal*255/maxVal);
            rectangle(histImg, Point(h*scale, s*scale), Point((h+1)*scale-1, (s+1)*scale-1),
                Scalar::all(intensity),
                CV_FILLED);
        }
    histo2D = histImg;
}

void histogramRGcalculation(const Mat &src, Mat &histoRG)
{
    int r_bins = 50; int g_bins = 60;
    int histSize[] = {r_bins, g_bins};

    float r_ranges[] = {0, 255};
    float g_ranges[] = {0, 255};

    const float* ranges[] = { r_ranges, g_ranges };

    int channels[] = {0, 1};

    MatND hist_base;

    calcHist(&src, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false);
    normalize(hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat());

    histoRG = hist_base;
}

int main(int argc, char *argv[])
{
    Mat src, imageq;
    Mat histImg, histImgeq;
    Mat histHSorg, histHSeq;

    src = imread("fruits.jpg");
    if(!src.data)
    {
        cout << "Error image" << endl;
    }

    vector<Mat> bgr_planes;
    split(src, bgr_planes);

    namedWindow("Source image", 0);
    imshow("Source image", src);

    // 生成和显示 HS 直方图.
    histogram2Dcalculation(src, histImg);
    imshow("H-S Histogram", histImg);

    equalizeHist(bgr_planes[0], bgr_planes[0]);
    equalizeHist(bgr_planes[1], bgr_planes[1]);
    equalizeHist(bgr_planes[2], bgr_planes[2]);

    merge(bgr_planes, imageq);

    namedWindow("Equalized Image", 0);
    imshow("Equalized Image", imageq);

    histogram2Dcalculation(imageq, histImgeq);
    imshow("H-S Histogram Equalized", histImgeq);

    histogramRGcalculation(src, histHSorg);
    histogramRGcalculation(imageq, histHSeq);

    for(int i = 0; i < 4; i++)
    {
        int compare_method = i;
        double orig_orig = compareHist(histHSorg, histHSorg, compare_method);
        double orig_equ = compareHist(histHSorg, histHSeq, compare_method);

        printf("Method [%d] Original-Original, Original-Equalized: %f, %f\n",
               i, orig_orig, orig_equ);
    }
    printf("Done.\n");

    cvWaitKey();
    return 0;
}

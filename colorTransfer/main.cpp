#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
using namespace cv;

int main(int argc, char *argv[])
{
    Mat src = imread("../clock_tower.jpg");
    Mat tar = imread("../big_ben.jpg");

    Mat src_lab, tar_lab;

    cvtColor(src, src_lab, COLOR_BGR2Lab);
    cvtColor(tar, tar_lab, COLOR_BGR2Lab);

    src_lab.convertTo(src_lab, CV_32FC1);
    tar_lab.convertTo(tar_lab, CV_32FC1);

    Mat mean_src, mean_tar, stdd_src, stdd_tar;
    meanStdDev(src_lab, mean_src, stdd_src);
    meanStdDev(tar_lab, mean_tar, stdd_tar);

    std::vector<Mat> src_chan, tar_chan;

    split(src_lab, src_chan);
    split(tar_lab, tar_chan);

    for(int i = 0; i < 3; i++) {
        tar_chan[i] -= mean_tar.at<double>(i);
        tar_chan[i] *= (stdd_src.at<double>(i) / stdd_tar.at<double>(i));
        tar_chan[i] += mean_tar.at<double>(i);
    }

    Mat output;
    merge(tar_chan, output);

    output.convertTo(output, CV_8UC1);
    cvtColor(output, output, COLOR_Lab2BGR);

    imshow("source image", src);
    imshow("target image", tar);
    imshow("result image", output);

    waitKey();

    return 0;
}

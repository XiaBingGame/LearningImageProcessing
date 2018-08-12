#include "showui.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 回调函数声明
void cbMouse(int event, int x, int y, int flags, void*);
void tb1_Callback(int value, void *);
void tb2_Callback(int value, void *);
void checkboxCallback(int state, void *);
void ratioboxCallback(int state, void *id);
void pushbuttonCallBack(int, void* font);

Mat orig_img, tmp_img;
const char main_win[] = "main_win";
char msg[50];

int showui(int argc, char* argv[])
{
    const char track1[] = "TrackBar 1";
    const char track2[] = "TrackBar 2";
    const char checkbox[] = "Check Box";
    const char radiobox1[] = "Radio Box1";
    const char radiobox2[] = "Radio Box2";
    const char pushbutton[] = "Push Button";
    int tb1_value = 50;
    int tb2_value = 25;

    orig_img = imread(argv[1]);
    if(orig_img.empty())
    {
        cout << "Error!!! Image cannot be loaded..." << endl;
        return -1;
    }
    namedWindow(main_win);

    QtFont font = fontQt("Arial", 20, Scalar(255, 0, 0, 0),
                         QT_FONT_BLACK, QT_STYLE_NORMAL);

    setMouseCallback(main_win, cbMouse, NULL);
    createTrackbar(track1, main_win, &tb1_value, 100, tb1_Callback);
    createButton(checkbox, checkboxCallback, 0, QT_CHECKBOX);
    createButton(pushbutton, pushbuttonCallBack, (void*)&font, QT_PUSH_BUTTON);
    createTrackbar(track2, main_win, &tb2_value, 50, tb2_Callback);
    createButton(radiobox1, ratioboxCallback, (void*)radiobox1, QT_RADIOBOX);
    createButton(radiobox2, ratioboxCallback, (void*)radiobox2, QT_RADIOBOX);

    imshow(main_win, orig_img);
    cout << "Press any key to exit..." << endl;
    waitKey();
    return 0;
}

void tb1_Callback(int value, void *)
{
    sprintf(msg, "Trackbar 1 changed, New value=%d", value);
    displayOverlay(main_win, msg);
    return;
}

void tb2_Callback(int value, void *)
{
    sprintf(msg, "Trackbar 2 changed, New value=%d", value);
    displayStatusBar(main_win, msg, 1000);
    return;
}

void checkboxCallback(int state, void *)
{
    sprintf(msg, "Check box changed, New state=%d", state);
    displayStatusBar(main_win, msg);
    return;
}

void ratioboxCallback(int state, void *id)
{
    sprintf(msg, "%s changed. New state=%d", (char*)id, state);
    displayStatusBar(main_win, msg);
    return;
}

void pushbuttonCallBack(int, void* font)
{
    addText(orig_img, "Push button clicked", Point(50, 50), *((QtFont*)font));
    imshow(main_win, orig_img);
    return;
}

void cbMouse(int event, int x, int y, int flags, void*)
{
    static Point p1, p2;
    static bool p2set = false;

    if(event == EVENT_LBUTTONDOWN)
    {
        p1 = Point(x, y);
        p2set = false;
    } else if(event == EVENT_MOUSEMOVE && flags == EVENT_FLAG_LBUTTON)
    {
        if(x > orig_img.size().width)
            x = orig_img.size().width;
        else if(x < 0)
            x = 0;

        if(y > orig_img.size().height)
            y = orig_img.size().height;
        else if(y < 0)
            y = 0;
        p2 = Point(x, y);
        p2set = true;
        orig_img.copyTo(tmp_img);
        rectangle(tmp_img, p1, p2, Scalar(0, 0, 255));
        imshow(main_win, tmp_img);
    } else if(event == EVENT_LBUTTONUP && p2set)
    {
        Mat submat = orig_img(Rect(p1, p2));

        // 处理

        rectangle(orig_img, p1, p2, Scalar(0, 0, 255), 2);
        imshow("main_win", orig_img);
    }
    return;
}

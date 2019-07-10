// camera_cap.h

#pragma once
#ifndef CAMERA_CAP_H
#define CAMERA_CAP_H

#include <opencv2/opencv.hpp>

class CamCap {
public:
    enum State { kCapCrop };

    CamCap(State s);
    ~CamCap();

    void run();
private:
    State _state;
    cv::VideoCapture _cap;
};

#endif // CAMERA_CAP_H
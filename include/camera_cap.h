// camera_cap.h

#pragma once
#ifndef CAMERA_CAP_H
#define CAMERA_CAP_H

#include <opencv2/opencv.hpp>

class CamCap {
public:
    enum State { kCapCrop };

    CamCap(State);
    ~CamCap();

    void run();
};

#endif // CAMERA_CAP_H
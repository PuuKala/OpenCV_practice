// camera_cap.cpp
#include "camera_cap.h"

CamCap::CamCap(State s) : _state(s) { _cap.open(0); }

CamCap::~CamCap() { _cap.release(); }

void CamCap::run() {
  cv::Mat frame;

  // In case of crop
  _cap >> frame;
  cv::Rect myROI(frame.size() / 4, frame.size() * 3 / 4);
  cv::Mat crop;

  char key;
  while (true) {
    _cap >> frame;
    switch (_state) {
      case kCapCrop:
        crop = frame(myROI);
        cv::imshow("Cropped middle portion of the full image. Press q to quit.",
                   crop);
        break;

      default:
        break;
    }
    key = cv::waitKey(33);
    if (key == 'q') {
      break;
    }
  }
  frame.release();
  crop.release();
}
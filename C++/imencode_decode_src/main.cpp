#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

int main() {
  // Define camera cap
  cv::VideoCapture cap(0);
  if (!cap.isOpened()) {
    std::cout << "Could not open camera!" << std::endl;
    return 0;
  }

  // Capture an image
  cv::Mat img;
  cap >> img;

  // Encode the image
  std::vector<uchar> enc_img;
  if (!cv::imencode(".webp", img, enc_img)) {
    std::cout << "Could not encode!" << std::endl;
  }

  // Decode the image and check the differences between decoded and original
  cv::Mat dec_img = cv::imdecode(enc_img, cv::IMREAD_COLOR);
  if (img.size != dec_img.size) {
    std::cout << "Mat sizes are different!" << std::endl;
    return 0;
  } else {
    cv::Mat diff;
    cv::subtract(img, dec_img, diff);
    std::vector<cv::Mat> arr;
    cv::split(diff, arr);
    if (cv::countNonZero(arr[0]) > 0) {
      std::cout << "Differences found in pixel values!" << std::endl;
      return 0;
    } else if (cv::countNonZero(arr[1]) > 0) {
      std::cout << "Differences found in pixel values!" << std::endl;
      return 0;
    } else if (cv::countNonZero(arr[2]) > 0) {
      std::cout << "Differences found in pixel values!" << std::endl;
      return 0;
    }
  }

  // Show the images just to be sure they're the same
  std::cout << "The raw image is the same as decoded image" << std::endl;
  cv::imshow("Raw image", img);
  cv::waitKey();
  cv::imshow("Decoded image", dec_img);
  cv::waitKey();
  return 0;
}
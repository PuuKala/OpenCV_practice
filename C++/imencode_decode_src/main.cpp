// A program just to make sure the imencode(".png", ...) is lossless and measure
// its execution time

#include <chrono>
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


  std::cout << "Image type before and after conversion: " << img.type() << "(before) ";
  int color_format = CV_BGR2YUV_YV12;
  cv::cvtColor(img, img, color_format);
  std::cout << img.type() << "(after)" << std::endl;

  // Encode the image
  std::vector<uchar> enc_img;
  auto t1 = std::chrono::high_resolution_clock::now();
  cv::imencode(".png", img, enc_img);
  auto t2 = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);

  std::cout << "Took " << duration.count() << " microseconds in encoding"
            << std::endl;

  cv::Mat resized_img;
  t1 = std::chrono::high_resolution_clock::now();
  cv::resize(img, resized_img, cv::Size(img.cols / 2.5, img.rows / 2.5));
  t2 = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
  std::cout << "For comparison, took " << duration.count()
            << " microseconds in resizing" << std::endl
            << std::endl;

  unsigned int enc_size = sizeof(uchar) * enc_img.size();
  unsigned int img_size = img.total() * img.elemSize();
  unsigned int resized_size = resized_img.total() * resized_img.elemSize();

  std::cout << "Raw image size: " << img_size << " bytes" << std::endl
            << "Encoded image size: " << enc_size << " bytes" << std::endl
            << "Size difference: " << (img_size - enc_size) << " bytes"
            << std::endl
            << std::endl
            << "Resized image size: " << resized_size << " bytes" << std::endl
            << "Size difference to raw image: " << (img_size - resized_size)
            << " bytes" << std::endl
            << "Size difference to encoded image: " << (enc_size - resized_size)
            << " bytes" << std::endl
            << std::endl;

  // Decode the image and check the differences between decoded and original
  cv::Mat dec_img = cv::imdecode(enc_img, cv::IMREAD_ANYCOLOR);
  cv::resize(resized_img, resized_img, img.size());
  if (img.size != dec_img.size) {
    std::cout << "Mat sizes are different!" << std::endl;
  } else {
    cv::Mat diff;
    cv::subtract(img, dec_img, diff);

    if (color_format == CV_BGR2GRAY) {  // Grayscale image checking
      if (cv::countNonZero(diff) > 0) {
        std::cout << "Differences found in pixel values!" << std::endl;
      } else {
        std::cout << "The raw image is the same as decoded image" << std::endl;
      }
    } else if (color_format == CV_BGR2RGB) {  // RGB image checking
      std::vector<cv::Mat> arr;
      cv::split(diff, arr);
      if (cv::countNonZero(arr[0]) > 0) {
        std::cout << "Differences found in pixel values!" << std::endl;
      } else if (cv::countNonZero(arr[1]) > 0) {
        std::cout << "Differences found in pixel values!" << std::endl;
      } else if (cv::countNonZero(arr[2]) > 0) {
        std::cout << "Differences found in pixel values!" << std::endl;
      } else {
        std::cout << "The raw image is the same as decoded image" << std::endl;
      }
    } else if (color_format == CV_BGR2YUV) {
      std::cout << "YUV checking not yet implemented" << std::endl;
    } else if (color_format == CV_BGR2YUV_YV12) {
      std::cout << "YUV_YV12 checking not yet implemented" << std::endl;
      std::cout << "Image channels: " << img.channels() << std::endl;
      cv::cvtColor(img, img, CV_YUV2BGR_YV12);
      cv::cvtColor(dec_img, dec_img, CV_YUV2BGR_YV12);
      cv::cvtColor(resized_img, resized_img, CV_YUV2BGR_YV12);
    }
  }

  // Show the images
  cv::imshow("Raw image", img);
  cv::imshow("Decoded image", dec_img);
  cv::imshow("Resized image", resized_img);
  cv::waitKey();
  return 0;
}
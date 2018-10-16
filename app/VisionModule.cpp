/******************************************************************************
 *  MIT License
 *
 *  Copyright (c) 2018 Saimouli Katragadda, Adarsh Jagan Sathyamoorthy
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *******************************************************************************/

/**
 * @file      VisionModule.cpp
 * @author    Saimouli Katragadda (saimouli)
 * @copyright MIT License
 * @brief     Implements VisionModule class methods
 */
#include "VisionModule.h"

VisionModule::VisionModule()
    : headingAngle(0) {

}

VisionModule::~VisionModule() {

}

cv::Mat VisionModule::returnCameraMatrix() {
  return cameraMatrix;
}

cv::Mat VisionModule::returnDistortionCoeff() {
  return distortionCoeff;
}

void VisionModule::unDistortImage(const cv::Mat& frame) {
  undistortedFrame.release();
  undistort(frame, undistortedFrame, cameraMatrix, distortionCoeff);
}

void VisionModule::smoothenImage() {
  cv::GaussianBlur(undistortedFrame, undistortedFrame, cv::Size(3, 3), 0, 0);
}

cv::Mat VisionModule::returnUndistortedFrame() {
  return undistortedFrame;
}

void VisionModule::computePerspectiveMatrices() {
  cv::Mat M;
  cv::Mat Minv;
  M = getPerspectiveTransform(srcPoints, dstPoints);
  Minv = getPerspectiveTransform(dstPoints, srcPoints);
  perspectiveMatrices.push_back(M);
  perspectiveMatrices.push_back(Minv);
}

std::vector<cv::Mat> VisionModule::returnPerspectiveMatrices() {
  return perspectiveMatrices;
}

cv::Mat VisionModule::getTopView(const cv::Mat& frame) {
  cv::Mat topView;
  warpPerspective(frame, topView, perspectiveMatrices[0], topView.size());
  return topView;
}

void VisionModule::createMask(const cv::Mat& topView) {
  cv::Mat yellowMask;
  cv::Mat whiteMask;
  cv::Mat topViewHSV;
  cvtColor(topView, topViewHSV, CV_BGR2HSV);
  // Thresholding for the lanes
  inRange(topViewHSV, cv::Scalar(0, 65, 104), cv::Scalar(87, 255, 255),
          yellowMask);
  inRange(topViewHSV, cv::Scalar(0, 0, 200, 0), cv::Scalar(180, 255, 255, 0),
          whiteMask);
  bitwise_or(whiteMask, yellowMask, mask);
}

std::vector<cv::Vec4i> VisionModule::houghLinesDetect(cv::Mat& processFrames) {
  std::vector<cv::Vec4i> lines;
  return lines;
}

void VisionModule::getHistogramPeaks() {
  cv::Point leftPeak;
  cv::Point rightPeak;
  double minVal, maxVal;
  cv::Point minLoc;
  cv::Mat leftHalf = mask(cv::Range(0, mask.rows),
                          cv::Range(0, mask.cols / 2 - 1));
  cv::Mat rightHalf = mask(cv::Range(0, mask.rows),
                           cv::Range(mask.cols / 2, mask.cols - 1));

  // Histogram calculation for left and right halves
  cv::Mat histLeft, histRight;
  reduce(leftHalf, histLeft, 0, CV_REDUCE_SUM, CV_32S);
  reduce(rightHalf, histRight, 0, CV_REDUCE_SUM, CV_32S);

  minMaxLoc(histLeft, &minVal, &maxVal, &minLoc, &leftPeak);
  minMaxLoc(histRight, &minVal, &maxVal, &minLoc, &rightPeak);
  rightPeak.x += mask.cols / 2;
  peaks.push_back(leftPeak);
  peaks.push_back(rightPeak);
}

std::vector<cv::Point> VisionModule::returnPeaks() {
  return peaks;
}

std::vector<cv::Point> VisionModule::isolateLane(cv::Point peak,
                                                 const cv::Mat& topView) {
   std::vector<cv::Point> boxCentroid;
  boxCentroid.clear();
  for (int i = 0; i < numBoxes; i++) {
    int boxHeight = mask.rows / numBoxes;
    int bottomY = mask.rows - i * boxHeight;
    int topY = mask.rows - (i + 1) * boxHeight;

    // Draw the rectangles
    cv::rectangle(topView, cv::Point(peak.x - boxMargin, topY),
                  cv::Point(peak.x + boxMargin, bottomY),
                  cv::Scalar(0, 255, 255), 3);

    // Adjust the base according to number of white pixels
    cv::Mat ROI = mask(cv::Range(topY, bottomY),
                       cv::Range(peak.x - boxMargin, peak.x + boxMargin));

    // Find number of white pixels
    cv::Mat whitePixelsLoc;
    findNonZero(ROI, whitePixelsLoc);

    // check if number of white pixels is greater than 100 for left line
    if (whitePixelsLoc.rows > 100) {
      // Find average of x locations
      pixelLocSum = 0;
      for (int j = 0; j < whitePixelsLoc.rows; j++) {
        whitePixelsLoc.at<cv::Point>(j).x += (peak.x - boxMargin);
        pixelLocSum += whitePixelsLoc.at<cv::Point>(j).x;
      }
      int average;
      average = static_cast<int>(pixelLocSum / whitePixelsLoc.rows);
      peak.x = average;
    }
    // Store the left and right box centroids
    boxCentroid.push_back(cv::Point(peak.x, (topY + bottomY) / 2));
  }
  imshow("top view", topView);
  return boxCentroid;
}

void VisionModule::computeHeadingAngle(
    std::vector<cv::Point> boxCentroidLeft,
    std::vector<cv::Point> boxCentroidRight) {

}

double VisionModule::returnHeadingAngle() {
  return headingAngle;
}

cv::Mat VisionModule::laneDetection(cv::Mat& frame) {

  return undistortedFrame;
}

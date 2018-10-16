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

}

void VisionModule::edgeFilter(cv::Mat& processFrame) {

}


std::vector<cv::Vec4i> VisionModule::houghLinesDetect(cv::Mat& processFrames) {
  std::vector<cv::Vec4i> lines;
  return lines;
}

void VisionModule::getHistogramPeaks() {

}

std::vector<cv::Point> VisionModule::returnPeaks() {
  return peaks;
}

std::vector<cv::Point> VisionModule::isolateLane(cv::Point peak,
                                                 const cv::Mat& topView) {
  std::vector<cv::Point> boxCentroid;
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

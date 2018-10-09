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
 * @file      VisionModule.h
 * @author    Saimouli Katragadda (saimouli)
 * @copyright MIT License
 * @brief     VisionModule Class declaration
 * @detail    Declared functions Class to denoise frames, apply homography,
 *            find hough lines, and find heading angle
 */

#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#ifndef INCLUDE_VISIONMODULE_H_
#define INCLUDE_VISIONMODULE_H_

using cv::Mat;
using cv::Vec4i;
using std::vector;

/**
 * @brief Class VisionModule
 * The following class VisionModule gets the frames from FrameParser class
 * and is responsible for filtering and detecting hough lines on to an image.
 */

class VisionModule {
 private:
  /**
   * @brief Container to store hough lines
   */
  std::vector<cv::Vec4i> lines;
  /**
   * @brief Container to store heading angle
   */
  double headingAngle;
  /**
   * @brief Container to store frames as they are being processed by functions
   */
  cv::Mat processFrame;

 public:
  /**
   * @brief constructor VisionModule
   * @param none
   * @return none
   */
  VisionModule();
  /**
   * @brief destructor VisionModule
   * @param none
   * @return none
   */
  ~VisionModule();
  /**
   * @brief Function unDistortImage
   * @param processFrame of type cv::Mat
   * @return none
   * The following function will undistort the given image using the
   * datasets given calibration matrix
   */
  void unDistrortImage(&cv::Mat processFrame);
  /**
   * @brief Function preProcess
   * @param processFrame of type cv::Mat
   * @return none
   * The following function will denoise the image by applying gaussian filter
   * and crop at ROI of the image
   */
  void preProcess(&cv::Mat processFrame);
  /**
   * @brief Function perspectiveTransform
   * @param processFrame of type cv::Mat
   * @return none
   * The following function will apply homography to the image
   * to get the birds eye
   */
  void perspectiveTransform(&cv::Mat processFrame);
  /**
   * @brief Function edgeFilter
   * @param processFrame of type cv::Mat
   * @return none
   * The following function will apply edge filter to the processed image
   */
  void edgeFilter(&cv::Mat processFrame);
  /**
   * @brief Function getHistogram
   * @param processFrame of type cv::Mat
   * @return none
   * The following function will apply a histogram and finds a region where the white
   * threshold values are high
   */
  void getHistogram(&cv::Mat processFrame);
  /**
   * @brief Function houghLinesDetect
   * @param processFrame of type cv::Mat
   * @return lines of type vector<cv::4i>
   * The following function will detect hough lines on a
   * processed image
   */
  vector<cv::Vec4i> houghLinesDetect(&cv::Mat processFrames);
  /**
   * @brief Function computeHeadingAngle
   * @param lines of type vector<cv::Vec4i>
   * @return angle of type double
   * The following function will compute cars heading angle based on
   * detected hough lines
   */
  double computeHeadingAngle(vector<cv::Vec4i> lines);
  /**
   * @brief Function laneDetection
   * @param image of type cv::Mat
   * @return finalImage of type cv::Mat
   * The following function will augment the hough lines
   * display text on the passed image using vector of hough lines
   * and heading angle variables
   */
  cv::Mat laneDetection(&cv::Mat);
};

#endif /* INCLUDE_VISIONMODULE_H_ */

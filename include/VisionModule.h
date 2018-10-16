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
 * @author    Adarsh Jagan Sathyamoorthy
 * @copyright MIT License
 * @brief     VisionModule Class declaration
 * @detail    Declared functions Class to denoise frames, apply homography,
 *            apply histogram, and find heading angle
 */

#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#ifndef INCLUDE_VISIONMODULE_H_
#define INCLUDE_VISIONMODULE_H_

/**
 * @brief Class VisionModule
 * The following class VisionModule gets the frames from FrameParser class
 * and is responsible for filtering and detecting hough lines on to an image.
 */

class VisionModule {
 private:
  /**
   * @brief Stores distortion parameters
   */
  cv::Mat distortionCoeff =
      (cv::Mat_<double>(1, 5) << -2.42565104e-01, -4.77893070e-02, -1.31388084e-03, -8.79107779e-05, 2.20573263e-02);
  /**
   * @brief Stores camera matrix parameters
   */
  cv::Mat cameraMatrix =
      (cv::Mat_<double>(3, 3) << 1.15422732e+03, 0.00000000e+00, 6.71627794e+02, 0.00000000e+00, 1.14818221e+03, 3.86046312e+02, 0, 0, 1);
  /**
   * @brief Container to store undistored frames
   */
  cv::Mat undistortedFrame;
  /**
   * @brief Container to store masked frames
   */
  cv::Mat mask;
  /**
   * @brief Container to store histogram peak values
   */
  std::vector<cv::Point> peaks;
  /**
   * @brief Stores histogram box numbers
   */
  int numBoxes = 9;
  /**
   * @brief Stores histogram box margins numbers
   */
  int boxMargin = 100;
  /**
   * @brief variable to all the pixel sum in the histogram
   */
  int pixelLocSum = 0;
  /**
   * @brief variable to store vector of source points used for cropping
   */
  std::vector<cv::Point2f> srcPoints = { cv::Point2f(581, 477), cv::Point2f(
      699, 477), cv::Point2f(896, 675), cv::Point2f(384, 675) };
  /**
   * @brief variable to store vector of distance points used for cropping
   */
  std::vector<cv::Point2f> dstPoints = { cv::Point2f(384, 0), cv::Point2f(896,
                                                                          0),
      cv::Point2f(896, 720), cv::Point2f(384, 720) };
  /**
   * @brief container to store the matrix for perspective transform
   */
  std::vector<cv::Mat> perspectiveMatrices;
  /**
   * @brief Container to store heading angle
   */
  double headingAngle;


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
   * @brief Function returnCameraMatrix
   * @param none
   * @return cameraMatrix of type cv::Mat
   * The following function will return the cameraMatrix private variable
   */
  cv::Mat returnCameraMatrix();

  /**
   * @brief Function returnDistortionCoeff
   * @param none
   * @return distortionCoeff of type cv::Mat
   * The following function will return the distortionCoeff private variable
   */
  cv::Mat returnDistortionCoeff();

  /**
   * @brief Function unDistortImage
   * @param processFrame of type cv::Mat
   * @return none
   * The following function will undistort the given image using the
   * datasets given calibration matrix
   */
  void unDistortImage(const cv::Mat& frame);

  /**
   * @brief Function smoothenImage
   * @param none
   * @return none
   * The following function will denoise the image by applying gaussian filter
   */
  void smoothenImage();

  /**
   * @brief Function returnUndistortedFrame
   * @param none
   * @return undistortedFrame of type cv::Mat
   * The following function returns the undistorted image stored as private data member
   */
  cv::Mat returnUndistortedFrame();

  /**
   * @brief Function computePerspectiveMatrices
   * @param none
   * @return none
   * The following function will apply homography to the image
   * to get the birds eye
   */
  void computePerspectiveMatrices();

  /**
   * @brief Function returnPerspectiveMatrices
   * @param none
   * @return perspectiveMatrices of type std::vector<cv::Mat>
   * The following function returns the computed perspective matrices private data member
   */
  std::vector<cv::Mat> returnPerspectiveMatrices();

  /**
   * @brief Function getTopView
   * @param Frame of type cv::Mat
   * @return frame of type cv::Mat
   * The following function will get the birds view of the image
   */
  cv::Mat getTopView(const cv::Mat& frame);

  /**
   * @brief Function createMask
   * @param frame of type cv::Mat
   * @return none
   * The following function will create a mask from the image
   */
  void createMask(const cv::Mat& frame);

  /**
   * @brief Function edgeFilter
   * @param frame of type cv::Mat
   * @return none
   * The following function will detect edges in images
   */

  void edgeFilter(&cv::Mat processFrame);

  /**
   * @brief Function houghLinesDetect
   * @param processFrame of type cv::Mat
   * @return lines of type vector<cv::4i>
   * The following function will detect hough lines on a
   * processed image
   */
  vector<cv::Vec4i> houghLinesDetect(&cv::Mat processFrames);

  /**
   * @brief Function getHistogramPeaks
   * @param none
   * @return none
   * The following function will apply a histogram and finds a region where the white
   * threshold values are high
   */
  void getHistogramPeaks();

  /**
   * @brief Function returnPeaks
   * @param none
   * @return peaks of type std::vector<cv::Point>
   * The following function returns the peaks in the histogram
   */
  std::vector<cv::Point> returnPeaks();

  /**
   * @brief Function isolateLane
   * @param peak of type cv::Point
   * @param topView of type const cv::Mat&
   * @return point of type std::vector
   * The following function draws boxes on the road lanes and returns centroid points of the boxes.
   */
  std::vector<cv::Point> isolateLane(cv::Point peak, const cv::Mat& topView);

  /**
   * @brief Function computeHeadingAngle
   * @param boxCentroidLeft of type :vector<cv::Point>
   * @param boxCentroidRight of type :vector<cv::Point>
   * @return none
   * The following function will compute cars heading angle based on
   * detected centroid points and connecting lines
   */
  void computeHeadingAngle(std::vector<cv::Point> boxCentroidLeft,
                           std::vector<cv::Point> boxCentroidRight);

  /**
   * @brief Function returnHeadingAngle
   * @param none
   * @return angle of type double
   * The following function returns the calculated heading angle
   */
  double returnHeadingAngle();

  /**
   * @brief Function laneDetection
   * @param image of type cv::Mat
   * @return finalImage of type cv::Mat
   * The following function will augment the hough lines
   * display text on the passed image using vector of hough lines
   * and heading angle variables
   */
  cv::Mat laneDetection(cv::Mat&);

};

#endif /* INCLUDE_VISIONMODULE_H_ */

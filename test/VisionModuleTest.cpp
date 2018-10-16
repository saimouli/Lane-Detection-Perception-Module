******************************************************************************
* MIT License
*
* Copyright (c) 2018 Saimouli Katragadda, Adarsh Jagan Sathyamoorthy
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
 *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*******************************************************************************/

/**
 * @file      main.cpp
 * @author    Saimouli Katragadda (saimouli)
 * @author    Adarsh Jagan Sathyamoorthy
 * @copyright MIT License
 * Copyright (c) 2018 Saimouli Katragadda, Adarsh Jagan Sathyamoorthy
 * @brief     Test for VisionModule class methods
 */
#include<gtest/gtest.h>
#include<gmock/gmock.h>
#include<vector>
#include<VisionModule.h>
#include<cmath>
#include<iostream>

TEST(cameraMatrixCheck, testcameraMatrixSize) {
  VisionModule v;
  cv::Mat matrix;
  matrix = v.returnCameraMatrix();
  ASSERT_EQ(matrix.cols, 3);
  ASSERT_EQ(matrix.rows, 3);
}

TEST(distortionCoeffCheck, testdistortionCoeffSize) {
  VisionModule v;
  cv::Mat distortionCoeff;
  distortionCoeff = v.returnDistortionCoeff();
  ASSERT_EQ(distortionCoeff.cols, 5);
  ASSERT_EQ(distortionCoeff.rows, 1);
}

TEST(undistortFrameCheck, testUndistortedFrameSize) {
  VisionModule v;
  cv::Mat testImage;
  testImage = cv::imread("../data/test.png");
  v.unDistortImage(testImage);
  cv::Mat result;
  result = v.returnUndistortedFrame();
  ASSERT_EQ(result.cols, testImage.cols);
  ASSERT_EQ(result.rows, testImage.rows);
}

TEST(smoothenFrameCheck, testNonAggressiveSmoothing) {
  VisionModule v;
  cv::Mat testImage;
  testImage = cv::imread("../data/test.png");
  v.unDistortImage(testImage);
  cv::Mat result1;
  result1 = v.returnUndistortedFrame();
  v.smoothenImage();
  cv::Mat result2;
  result2 = v.returnUndistortedFrame();
  ASSERT_EQ(result1.cols, testImage.cols);
  ASSERT_EQ(result1.rows, testImage.rows);
  ASSERT_EQ(result2.cols, testImage.cols);
  ASSERT_EQ(result2.rows, testImage.rows);
  inRange(result1, cv::Scalar(0, 0, 200, 0), cv::Scalar(180, 255, 255, 0),
          result1);
  inRange(result2, cv::Scalar(0, 0, 200, 0), cv::Scalar(180, 255, 255, 0),
          result2);
  cv::Mat diff;
  cv::bitwise_xor(result1, result2, diff);
  ASSERT_EQ(cv::countNonZero(diff), 0);
}

TEST(persMatrixCheck, testMatrixSizeandInverse) {
  VisionModule v;
  v.computePerspectiveMatrices();
  std::vector<cv::Mat> matrices;
  matrices = v.returnPerspectiveMatrices();

  // Check appropriate matrix dimensions
  ASSERT_EQ(matrices[0].cols, 3);
  ASSERT_EQ(matrices[0].rows, 3);
  ASSERT_EQ(matrices[1].cols, 3);
  ASSERT_EQ(matrices[1].rows, 3);
  cv::Mat product;
  product = abs(matrices[1] * matrices[0]);
  std::cout << product << std::endl;

  // Check Diagonal elements are almost the same
  EXPECT_NEAR(product.at<double>(0, 0), product.at<double>(1, 1), 0.00000001);
  EXPECT_NEAR(product.at<double>(0, 0), product.at<double>(2, 2), 0.00000001);

  // Check Other elements are almost zero
  std::vector<int> otherElements = { static_cast<int>(product.at<double>(0, 1)),
      static_cast<int>(product.at<double>(0, 2)), static_cast<int>(product
          .at<double>(1, 0)), static_cast<int>(product.at<double>(1, 2)),
      static_cast<int>(product.at<double>(2, 1)), static_cast<int>(product
          .at<double>(2, 0)) };
  std::vector<int> zeroes = { 0, 0, 0, 0, 0, 0 };
  EXPECT_EQ(otherElements, zeroes);
}






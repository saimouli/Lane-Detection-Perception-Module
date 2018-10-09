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
#include <VisionModule.h>

VisionModule::VisionModule()
    : headingAngle(0) {

}

VisionModule::~VisionModule() {

}

void VisionModule::unDistrortImage(&cv::Mat processFrame) {

}

void VisionModule::preProcess(&cv::Mat processFrame) {

}

void VisionModule::perspectiveTransform(&cv::Mat processFrame) {

}

void VisionModule::edgeFilter(&cv::Mat processFrame) {

}

void VisionModule::getHistogram(&cv::Mat processFrame) {

}

vector<cv::Vec4i> VisionModule::houghLinesDetect(&cv::Mat processFrames) {

}

double VisionModule::computeHeadingAngle(vector<cv::Vec4i> lines) {

  return 0.0;
}

cv::Mat VisionModule::laneDetection(&cv::Mat) {

}
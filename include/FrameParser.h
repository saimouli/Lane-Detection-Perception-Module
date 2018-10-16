/*******************************************************************************
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
 * @file      FrameParser.h
 * @author    Saimouli Katragadda (saimouli)
 * @author    Adarsh Jagan Sathyamoorthy
 * @copyright MIT License
 * @brief     FrameParser Class declaration
 * @detail    Declared functions Class to extract frames from the video input, and
 *            process frames
 */

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "UserInterface.h"

#ifndef INCLUDE_FRAMEPARSER_H_
#define INCLUDE_FRAMEPARSER_H_

/**
 * @brief Class FrameParser
 * The following class FrameParser aids UserInterface class by parsing the
 * frames in a video and calling the VisionModule and UserInterface class for 
 * further image processing using OpenCV
 */

class FrameParser {
 private:
  /**
   * @brief Container to store images
   */
  cv::Mat frame;

  /**
   * @brief Container to store camera output
   */
  cv::VideoCapture cap;

 public:
  /**
   * @brief constructor FrameParser
   * @param none
   * @return none
   */
  FrameParser();
  /**
   * @brief destructor FrameParser
   * @param none
   * @return none
   */
  ~FrameParser();

  /**
   * @brief Function extractFrames
   * @param interface of type UserInterface
   * @return 0 if the program is sucessful else -1
   * The following function will extract frames from the video input
   * and using the frames calls VisionModule and userInterface class
   */
  int extractFrame(UserInterface interface);
};

#endif /* INCLUDE_FRAMEPARSER_H_ */


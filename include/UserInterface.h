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
 * @file      UserInterface.h
 * @author    Saimouli Katragadda (saimouli)
 * @copyright MIT License
 * @brief     UserInterface Class declaration
 * @detail    Declared functions Class to interact with user about the input format
 *            and to diaplay the output on the video
 */

#include <iostream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#ifndef INCLUDE_USERINTERFACE_H_
#define INCLUDE_USERINTERFACE_H_

using std::string;
using cv::Mat;

/**
 * @brief Class UserInterface
 * The following class UserInterface gets the user input and interacts with the
 * VisionModule class. It augments the output from VisionModule class onto the user
 * input.
 */

class UserInterface {
 private:
  /**
   * @brief Container to store user input choice
   */
  int userChoice;
  /**
   * @brief Container for input path that will be processed
   */
  std::string fileLocation;
  /**
   * @brief Container for the final frames containing hough lines
   */
  cv::Mat finalFrames;

 public:
  /**
   * @brief constructor UserInterface
   * @param none
   * @return none
   */
  UserInterface();
  /**
   * @brief destructor UserIntefrace
   * @param none
   * @return none
   */
  ~UserInterface();
  /**
   * @brief Function getUserChoice
   * @param none
   * @return none
   * The following function will get the user input choice
   * and stores into the private variable userChoice
   */
  void getUserChoice();
  /**
   * @brief Function returnUserChoice
   * @param none
   * @return userChoice
   * The following function will access and return the private varible
   * userChoice, which contains the user input.
   */
  int returnUserChoice();
  /**
   * @brief Function getInputLocation
   * @param none
   * @return none
   * The following function will get the user input file
   * location and stores into the private variable fileLocation.
   */
  void getInputLocation();
  /**
   * @brief Function returnInputLocation
   * @param none
   * @return fileLocation
   * The following function will access and return the private varible
   * fileLocation, which contains the user input file location.
   */
  std::string returnInputLocation();
  /**
   * @brief Function displayLanes
   * @param none
   * @return none
   * The following function displays the final result
   * to the user.
   */
  void displayLanes();
};

#endif /* INCLUDE_USERINTERFACE_H_ */

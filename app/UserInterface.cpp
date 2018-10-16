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
 * @file      main.cpp
 * @author    Saimouli Katragadda (saimouli)
 * @author    Adarsh Jagan Sathyamoorthy
 * @copyright MIT License
 * @brief     Implements UserInterface class methods
 */
#include <UserInterface.h>

UserInterface::UserInterface()
    : userChoice(1),
      fileLocation("../data/project_video.mp4"),
      cameraID(0),
      defaultChoice("n") {
}

UserInterface::UserInterface(int userChoicePassed,
                             const std::string& fileLocationPassed,
                             int camerIDPassed,
                             const std::string& defaultChoicePassed)
    : fileLocation(fileLocationPassed),
      defaultChoice(defaultChoicePassed) {
  userChoice = userChoicePassed;
  cameraID = camerIDPassed;
}

UserInterface::~UserInterface() {
}

std::string UserInterface::returnDefaultChoice() {
  if (defaultChoice == "n" || defaultChoice == "N") {
    std::cout << "Do you want to test for default case? (enter y/n)"
              << std::endl;
    std::cin >> defaultChoice;
  }
  return defaultChoice;
}

void UserInterface::getUserChoice() {
  std::cout << "Enter 0- image input, 1- video file, 2- live stream"
            << std::endl;
  std::cin >> userChoice;
}

int UserInterface::returnUserChoice() {
  return userChoice;
}

void UserInterface::getInputLocation() {
  if (userChoice == 0 || userChoice == 1) {
    std::cout << "Enter the location of the file (ex:../data/project_video.mp4)"
              << std::endl;
    std::cin >> fileLocation;
  } else {
    std::cout << "Enter the camera ID number (Ex: 0)" << std::endl;
    std::cin >> cameraID;
  }
}

std::string UserInterface::returnInputLocation() {
  return fileLocation;
}

int UserInterface::returnCameraID() {
  return cameraID;
}

void UserInterface::displayLanes(cv::Mat frame) {

}


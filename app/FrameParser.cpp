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
 * @file      FrameParser.cpp
 * @author    Saimouli Katragadda (saimouli)
 * @author    Adarsh Jagan Sathyamoorthy
 * @copyright MIT License
 * @brief     Implements FrameParser class methods
 */
#include <FrameParser.h>
#include <VisionModule.h>
#include <UserInterface.h>

FrameParser::FrameParser() {
}

FrameParser::~FrameParser() {
}

int FrameParser::extractFrame(UserInterface interface) {
  VisionModule process;
  std::string defaultChoice;
  defaultChoice = interface.returnDefaultChoice();
  if (defaultChoice == "n" || defaultChoice == "N") {
    interface.getUserChoice();
    interface.getInputLocation();
  }

  int choice;
  choice = interface.returnUserChoice();

  std::string fileName;
  int cID;

  // image input format
  if (choice == 0) {
    fileName = interface.returnInputLocation();
    frame = cv::imread(fileName);
    // check for vaild input
    if (!frame.data) {
      std::cout << "Could not open or find the image" << std::endl;
      return -1;
    }
    frame = process.laneDetection(frame);
    interface.displayLanes(frame);

    std::cout << "To quit press any keystroke in the window" << std::endl;
    // Wait for a keystroke in the window
    cv::waitKey(0);
    std::cout << "Thanks for using Vision Module app! " << std::endl;
    return 0;

  } else if (choice == 1) {
    // video input format
    fileName = interface.returnInputLocation();
    cap = cv::VideoCapture(fileName);
  } else if (choice == 2) {
    cID = interface.returnCameraID();
    cap = cv::VideoCapture(cID);
  }
  if (!cap.isOpened()) {
    std::cout << "Error opening video stream or file" << std::endl;
    return -1;
  }
  while (cap.read(frame)) {
    if (frame.empty()) {
      break;
    }
    frame = process.laneDetection(frame);
    interface.displayLanes(frame);

    // Press  ESC on keyboard to exit
    char c = static_cast<char>(cv::waitKey(25));
    if (c == 27)
      break;
  }
  std::cout << "Thanks for using Vision Module app! " << std::endl;
  cap.release();
  cv::destroyAllWindows();
  return 0;
  }






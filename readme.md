# C++ Boilerplate
[![Build Status](https://travis-ci.org/saimouli/Lane-Detection-Perception-Module.svg?branch=master)](https://travis-ci.org/saimouli/Lane-Detection-Perception-Module)
[![Coverage Status](https://coveralls.io/repos/github/saimouli/Lane-Detection-Perception-Module/badge.svg?branch=master)](https://coveralls.io/github/saimouli/Lane-Detection-Perception-Module?branch=master)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
---

## Overview
This repository contains the implementation of a perception module capable of detecting and tracking traffic lanes. We assume that the camera is attached at the center of a moving vehicle. The input to this module can be any of the following formats: an image, a video or a live stream. The developed module is capable of detecting and augmenting lines on the input format while updating the heading angle of the car to the controller. Further details about the module are discussed in the algorithm overview.

<p align="center">
  <img src="https://github.com/saimouli/Lane-Detection-Perception-Module/blob/master/images/gif.gif?raw=true" alt="Lane detection and heading angle calculation"/>
</p>

The whole demo video can be found [here](https://www.youtube.com/watch?v=-Mf2Tt2DLRo&feature=youtu.be)

## Important note
The coveralls website was unresponsive since mid of tuesday(10/16/2018), so the coverage output of make code_coverage is stored in the results folder.


## Algorithm Overview

The overall workflow:

1. Each frame in the video is extracted and undistorted using the camera matrix and and distortion coefficients.

2. The undistorted image is then smoothened using a Gaussian blur.

3. The perspective transformation matrices are calculated using user-defined points in the straight view and their desired locations in the top view of the road.

4. Using the transformation matrices, the top view of the road is obtained (as shown below).
 
<p align="center">
  <img src="https://github.com/saimouli/Lane-Detection-Perception-Module/blob/master/images/topView.png" alt="Top view angle "/>
</p>

5. The top view of the frame is then thresholded for white and yellow colors and a binary image is created.

6. A histogram of the number of white pixels is calculated along the width of the binarized top view.

7. The maximum values in this histogram is treated as the peak of the histogram. There will be one peak per lane. So in out case, there will be a peak on the left half and right half of the image.

8. Using the peak location as reference rectangular boxes are drawn, stacked on top of each other.

9. If the number of white pixels in a particular rectangular box is greater than a given threshold, the box is moved along the x direction based on the mean of all white pixel x locations.

10. The centroid of these "self-adjusting" boxes are taken and a line is plotted through the centroids in the middle (say 2nd and 6th box), avoiding the extreme centroids. (Extreme centroids may be inconsistent due to the lack of a white region to self adjust.)

11. The end points of the lines drawn (coordinates of the 2nd and 6th boxes' centroids), are taken and an inverse perspective transform is applied to get the straight view. A polygon is drawn using these transformed points, as shown below.

<p align="center">
  <img src="https://github.com/saimouli/Lane-Detection-Perception-Module/blob/master/images/laneDetection.png?raw=true" alt="Lane detection and heading angle calculation"/>
</p>

12. The average line (plotted between the average of the end points of the two lines) between the two lines drawn is taken and the slope of this line is calculated. The angle of this line with the horizontal (x axis) will be the inverse tan of the slope. This angle is converted to degrees and subtracted from 90 to get the angle with respect to the vertical/ straight direction.

## Advantages
This implementation is able to handle random lines / blemishes on the road. For example, the bridge in the dataset is drastically different from the other parts of the road. But the algorithm is able to handle this.

## Limitation
The thresholding in this implementation may not work under some lighting conditions. 

## Dependencies
To build this module, the following dependecies should be met:

- CMake version at least 3.2
- OpenCV 3.1 or higher: Installation instructions can be found [here](https://www.learnopencv.com/install-opencv3-on-ubuntu/)
- Google Test: Unit test requires gtest framework by Google

## Product Backlog and Sprint Schedule

Please visit the link [here](https://docs.google.com/spreadsheets/d/1zOa9ZJuQaPj7fCO_8nVtLgBPcMP1-hMzZ2huXdk1TFU/edit?usp=sharing)

Adarsh Jagan Sathyamoorthy and Saimouli Katragadda worked together on this implementation and alternate commits were made. The commits are made by the driver while the other person acted as navigator. 

## License 
```
MIT License

Copyright (c) 2018 Saimouli Katragadda, Adarsh Jagan Sathyamoorthy

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
## Build package
```
git clone --recursive https://github.com/saimouli/Lane-Detection-Perception-Module.git
cd <path to repository>
mkdir build
cd build
cmake ..
make
```
## Run module/demo 
```
cd <path to repository>
cd build
Run program: ./app/vision-app
```
Follow the instructions displayed on the terminal. 

If you want to run the demo, run the program as given above, the following will be displayed:

```
Do you want to test for default case? (enter y/n)
``` 

Press y and the implementation on the dataset will run, along with the heading angle on the top left corner.

If you press n:
```
Enter 0- image input, 1- video file, 2- live stream
```
will be displayed. Enter your choice, 0 for Image input, 1 for video file, 2 for live stream.
If 0 or 1 is given, a file location is asked:

```
Enter the location of the file (ex:../data/project_video.mp4)
```
To run a simple test, enter ../data/test.png for an image.
For video, ../data/project_video.mp4 can be used.

In case of live feed, you will be prompted to enter the cameraID. 
```
Enter the camera ID number (Ex: 0)
```
Enter a valid camera ID and the live stream will be displayed. If there are valid lanes within the frame with appropriate lighting conditions, the lane will be tracked.


## Running tests
```
Run tests: ./test/cpp-test
```
## Building for code coverage 
```
sudo apt-get install lcov
cmake -D COVERAGE=ON -D CMAKE_BUILD_TYPE=Debug ../
make
make code_coverage
```
This generates a index.html page in the build/coverage sub-directory that can be viewed locally in a web browser.

## Doxygen
To install Doxygen
```
sudo apt install doxygen
```
To generate the Doxygen documentation 
```
doxygen ./Doxygen
```

## Working with Eclipse IDE ##

## Installation

In your Eclipse workspace directory (or create a new one), checkout the repo (and submodules)
```
mkdir -p ~/workspace
cd ~/workspace
git clone --recursive https://github.com/saimouli/Lane-Detection-Perception-Module.git
```

In your work directory, use cmake to create an Eclipse project for an [out-of-source build] of cpp-boilerplate

```
cd ~/workspace
mkdir -p LaneVision-eclipse
cd LaneVision-eclipse
cmake -G "Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug -D CMAKE_ECLIPSE_VERSION=4.7.0 -D CMAKE_CXX_COMPILER_ARG1=-std=c++14 ../Lane-Detection-Perception-Module/
```
## Import

Open Eclipse, go to File -> Import -> General -> Existing Projects into Workspace -> 
Select "LaneVision-eclipse" directory created previously as root directory -> Finish

# Edit

Source files may be edited under the "[Source Directory]" label in the Project Explorer.


## Build

To build the project, in Eclipse, unfold boilerplate-eclipse project in Project Explorer,
unfold Build Targets, double click on "all" to build all projects.

## Run

1. In Eclipse, right click on the boilerplate-eclipse in Project Explorer,
select Run As -> Local C/C++ Application

2. Choose the binaries to run (vision-app for application, cpp-test for unit testing)

# C++ Boilerplate
[![Build Status](https://travis-ci.org/saimouli/Lane-Detection-Perception-Module.svg?branch=master)](https://travis-ci.org/saimouli/Lane-Detection-Perception-Module)
[![Coverage Status](https://coveralls.io/repos/github/saimouli/Lane-Detection-Perception-Module/badge.svg?branch=master)](https://coveralls.io/github/saimouli/Lane-Detection-Perception-Module?branch=master)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
---

## Overview
This repository contains the implementation of a perception module capable of detecting and tracking traffic lanes. The camera is attached at the center of a moving vehicle. The input to this module can be any of the following formats: an image, a video or a live stream. The developed module is capable of detecting and augmenting lines on the input format while updating the heading angle of the car to the controller. Further details about the module are discussed in the algorithm overview.

<p align="center">
  <img src="https://github.com/saimouli/Lane-Detection-Perception-Module/blob/master/images/gif.gif?raw=true" alt="Lane detection and heading angle calculation"/>
</p>

The whole demo video can be found [here](https://www.youtube.com/watch?v=-Mf2Tt2DLRo&feature=youtu.be)

## Algorithm Overview 
<p align="center">
  <img src="https://github.com/saimouli/Lane-Detection-Perception-Module/blob/master/images/topView.png" alt="Top view angle "/>
</p>

<p align="center">
  <img src="https://github.com/saimouli/Lane-Detection-Perception-Module/blob/master/images/laneDetection.png?raw=true" alt="Lane detection and heading angle calculation"/>
</p>

## Dependencies
To build this module, the following dependecies should be met:

- CMake version at least 3.2
- OpenCV 3.1 or higher: Installation instructions can be found [here](https://www.learnopencv.com/install-opencv3-on-ubuntu/)
- Google Test: Unit test requires gtest framework by Google

## Product Backlog and Sprint Schedule

Please visit the link at:
https://docs.google.com/spreadsheets/d/1zOa9ZJuQaPj7fCO_8nVtLgBPcMP1-hMzZ2huXdk1TFU/edit?usp=sharing

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
Run program: ./app/vision-app
```
Follow the instructions displayed on the terminal. 

Press "y" if you would like to run a default test case. 

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

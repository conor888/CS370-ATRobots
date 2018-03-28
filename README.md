# ATRobots - Team Cerebral
CS370 - SUNY Polytechnic, Spring 2018.

Porting the classic competitive robot game, ATRobots, to modern operating systems with a more advanced and evolved interface.

## Table of Contents
1. [Compiling](https://github.com/conorahern7/CS370-ATRobots#compiling)
   1. [Install Qt & Qt Creator](https://github.com/conorahern7/CS370-ATRobots#1-install-qt--qt-creator)
   1. [Opening ATR2 in Qt Creator](https://github.com/conorahern7/CS370-ATRobots#2-opening-atr2-in-qt-creator)
   1. [Building & Running ATR2 in Qt Creator](https://github.com/conorahern7/CS370-ATRobots#3-building--running-atr2-in-qt-creator


## Compiling
Follow these steps if you want to compile ATR2 from the source code yourself.

#### 1. Install Qt & Qt Creator (Windows)

1. Go to https://www.qt.io/download, and select "Go open source".
    1. Click "Accept" on the pop-up window.
    1. Make sure the correct operating system is detected and click "Download"
1. Run the downloaded installer.
    1. Click "Next" on the initial welcome screen.
    1. Click "Skip" on the account Qt Account screen.
    1. Click "Next" again on the second welcome screen. The installer will retrieve meta information from Qt servers, this may take up to 10 minutes.
1. Choose a directory for Qt to be installed to (you need approximately 5GB of free storage), and optionally check the "associate common file types with Qt Creator".
1. Close the "Preview" section of components and expand the "Qt" section.
1. At the time of writing, our ATR2 port uses and has been tested with **Qt 5.10.1**. Expand this section.
1. Select **MinGW 5.3.0 32-bit** as a component to install.\
![Image of how to select Qt 5.10.1](https://i.imgur.com/fSn9js6.png)
1. Scroll to the bottom of the parent "Qt" section and expand the "Tools" subsection.
1. Select **MinGW 5.3.0**.\
![Image of how to select Qt Tools](https://i.imgur.com/6wgBMMb.png)
1. Click next and wait for the components to download and install. This can take anywhere from 20 minutes to 1 hour.

#### 2. Opening ATR2 in Qt Creator
To obtain the ATR2 source code, there are two main options:
1. Download a .zip of the master branch for a one-time download. OR:
1. Download a Git program and be able to pull commits as they are made and the program is changed.

      ##### Download .zip
      At the top of this page, look for the "Clone or download" button and click "Download ZIP". Extract the .zip file to a folder.\
      ![Image of how to download repository as .zip](https://i.imgur.com/BjsbWPf.png)
      
      ##### Download & Install GitHub Desktop (Windows & macOS Only)
      GitHub Desktop provides an easy-to-use graphical interface for using git commands.
      1. [Download GitHub Desktop](https://desktop.github.com/) and install it.
      1. Sign in to your GitHub account
      1. On the Welcome screen of GitHub Desktop, you'll see 3 columns. Click on the "Clone repository" button in the column on the right.
      1. Click the URL tab of the pop-up window and type ```conorahern7/CS370-ATRobots``` as the Repository URL. Choose a directory that you want the repo to be cloned to.\
      ![Image of how to clone repo](https://i.imgur.com/9udqq0z.png)
      1. Click Clone. All contents of this repository will be downloaded into the folder you selected.
      
1. Open the folder of the CS370-ATRobots repository.
1. Open the ATR2.pro file. It should open automatically in Qt Creator. If it does not, select Qt Creator as the program to open the file with.
1. Select "Configure project" in Qt Creator to configure the project for your system.
      
#### 3. Building & Running ATR2 in Qt Creator
1. In Qt Creator's menu bar, select the Build tab, and click Build Project "ATR2".\
![Image of where to find Build Project "ATR2"](https://i.imgur.com/TmlKUk5.png)
1. Building will take up to one minute, depending on your system. Look for a solid green progress bar at the bottom right corner of the window. If you see this, the build has completed successfully.\
![Image of successful build](https://i.imgur.com/NaEF8PF.png)
1. Now that the build has completed, the run-time options must be set. On the left side of Qt Creator, select the Projects tab.\
![Projects tab in Qt Creator](https://i.imgur.com/EwGVxdR.png)
1. Enter robot file names and program parameters in the "Command line arguments" field.\
![Run configuration](https://i.imgur.com/qUw2qhR.png)
   1. See Program arguments for more information on options for running ATR2.
   1. **Robot files must be located in the Working Directory.** Place the robot files (.AT2 or .ATL) in the default working directory created by Qt, or choose your own directory with the Working Directory field.
1. Go to the Build menu, and click Run.\
![Run ATR2](https://i.imgur.com/yH6XIS7.png)
1. If everything worked, you should see the ATR2 arena begin playing. Congratulations!\
![Running instance of ATR2](https://i.imgur.com/bQHs6iv.png)

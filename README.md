# ATRobots - Team Cerebral
CS370 - SUNY Polytechnic, Spring 2018.

Porting the classic competitive robot game, ATRobots, to modern operating systems with a more advanced and evolved interface.

## Compiling

### Windows

#### 1. Install Qt & Qt Creator

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
1. Select **MinGW 5.3.0 32-bit** as a component to install.
    ![Image of how to select Qt 5.10.1](https://i.imgur.com/fSn9js6.png)
1. Scroll to the bottom of the parent "Qt" section and expand the "Tools" subsection.
1. Select **MinGW 5.3.0**.
    ![Image of how to select Qt Tools](https://i.imgur.com/6wgBMMb.png)
1. Click next and wait for the components to download and install. This can take anywhere from 20 minutes to 1 hour.

#### 2. Opening ATR2 and Building in Qt Creator
(to do)

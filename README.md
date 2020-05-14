# GlassPlotter - Simple Glass Map Viewer

![MDI](image/Screenshot_MDI.png)

[日本語はこちら](README_ja.md)

## Overview
GlassPlotter is an open source, desktop glass map viewer.  This application is capable of visualizing abbe diagram, other glass maps, plotting property curves and showing datasheets, enabling to search and compare optical glasses easily.  It aims to be useful for daily work of diverse optical engineers.


## Key Features
- No specific programming environment are required to use
- Multi Document Interface for flexible viewing
- Good looking plots with intaractive mouse control
  
## Getting Started

0. Download  
Executable binaries for Windows/Mac can be downloaded in [Release page](https://github.com/heterophyllus/glassplotter/releases).

1. Load AGF  
 What to do first after launching is to load AGF files. Go to "File->load AGF" and then select desired AGF files.

2. Plot  
 Clicking an action in "Tools" menu creates a subwindow to plot maps or graphs.
 User defined curve in glass maps is plotted using the following cubic function.  
   <img src="https://latex.codecogs.com/gif.latex?y=C_{0}&plus;C_{1}x&plus;C_{2}x^2&plus;C_{3}x^3" />


## Resources
This application extracts glass data from Zemax AGF files.  Each of AGF files is available on the respective supplyer's web site. If Zemax has been installed to the computer, they might be contained in the folder like Documents/Zemax/Glasscat.

Note that the AGF files included in this repository are not always up to date.

## Development
This application is built with:
- [Qt and QtCreator](https://www.qt.io) : GUI library and IDE
- [QCustomPlot](https://www.qcustomplot.com) : Graph plotting library
- [spline](https://github.com/ttk592/spline) : Cubic spline interpolation library
  
## License
This project is licensed under the GPLv3 License - see the [LICENSE](LICENSE.md) for details.

## Contribution
Contributions and feedbacks are greatly appreciated.


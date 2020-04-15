# GlassPlotter

![MDI](image/Screenshot_MDI.png)

## Overview
GlassPlotter is an open source, simple desktop glass catalog manager.  This application is capable of plotting glass maps, dispersion graphs and internal transmittance curves.  GlassPlotter aims to be useful for diverse optical engineers, including those who are not familiar with programming.


## Key Features
- Multi Document Interface allows flexible viewing
- Good looking plots with intaractive mouse control
- Support several glass maps, dispersion plot and internal transmittance plot

## Getting Started

0. Download  
Windows binaries (portable zip) can be downloaded in [Release page](https://github.com/heterophyllus/glassplotter/releases).

1. Load AGF  
 What to do first after launching is to load AGF files. Go to "File->load AGF" and then select desirable AGF files.

2. Plotting  
 Clicking an action in "Tools" menu creates a subwindow to view and control plotting.  
 User defined curve is plotted using the following formula.  
   <img src="https://latex.codecogs.com/gif.latex?y=C_{0}&plus;C_{1}x&plus;C_{2}x^2&plus;C_{3}x^3" />

See also [image/demo.gif](image/demo.gif)

## Resources
This application extracts glass data from Zemax AGF file.  Each of AGF files is available on the supplyer's web site. If Zemax has been installed to the computer, AGF files might be contained in the folder like Documents/Zemax/Glasscat.

Note that the AGF files included in this repository are not always up to date.

## Development
This application is built with:
- [Qt and QtCreator](https://www.qt.io) : GUI library and IDE
- [QCustomPlot](https://www.qcustomplot.com) : Graph plotting library
- [spline](https://github.com/ttk592/spline) : Cubic spline interpolation library
  
## License
This project is licensed under the GPL License - see the [LICENSE](LICENSE.md) for details.

## Contribution
Contributions and feedbacks are always welcome.


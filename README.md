# GlassPlotter - Simple Glassmap Viewer

![MDI](image/Screenshot_MDI.png)

## Overview
GlassPlotter is an open source, desktop glass map viewer which is capable of visualizing Abbe diagram, plotting property curves and showing datasheets, etc. It aims to be useful for daily work of diverse optical designers.


## Key Features
- Interactive exploring of glassmaps
  - Optical designers eager to find the best material to satisfy the target function.  This application helps with exploring various optical glasses from different suppliers.
- Support user defined curve
  - Each of the suppliers defines its own "normal line", which confuses us a lot in  comparing multiple glasses.  This application displays properties on tha same basis by plotting user defined curve.  In addition, a polynomial fitting curve can be calculated from multiple samples. 
- Easy to use
  - This application serves reasonable GUI, and no specific environment is needed.
  
## Getting Started 
Executable binaries for Windows/Mac can be downloaded from [Release page](https://github.com/heterophyllus/glassplotter/releases/latest).

See also [Wiki](https://github.com/heterophyllus/glassplotter/wiki) to get how to use and other information.

## Resources
This application extracts glass data from Zemax AGF files.  Each of AGF files is available on the respective supplier's web site. If Zemax has been installed to the computer, they might be contained in the folder like Documents/Zemax/Glasscat.

Note that the AGF files included in this repository are not always up to date.

## Development
This application is built with:
- [Qt and QtCreator](https://www.qt.io) : GUI library and IDE
- [QCustomPlot](https://www.qcustomplot.com) : Graph plotting library
- [spline](https://github.com/ttk592/spline) : Cubic spline interpolation library
- [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page) : Template library for linear algebra
  
## License
This project is licensed under the GPL v3 License - see the [LICENSE](LICENSE.md) for details.

## Contribution
Contributions and feedbacks are greatly appreciated.
Please read [CONTRIBUTING](CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests to us.

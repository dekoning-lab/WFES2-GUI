# WFES-GUI

This repository is an implementation of a GUI for [wfes2](https://github.com/dekoning-lab/wfes2).

Wright-Fisher Exact Solver (`WFES`) implements a variety of exact calculations with the Wright-Fisher model. Unlike other approaches, `WFES` does not use simulations or strong simplifying assumptions. `WFES` benefits from high-performance linear algebra techniques, making it possible to compute exact quantities for biologically realistic population sizes. The following document details the usage of the `WFES` code.

## Installation

Download the last version for your OS in the [releases](https://github.com/dekoning-lab/wfes-gui/releases) page and follow the installer instructions.

### Microsoft Windows
WFES-GUI for Microsoft Windows may requires Visual C++ Redistributable 2015-2019 and it is installed automatically in your computer.

### Mac
WFES-GUI for Mac is automatically installed in your Applications folder.

### Linux
WFES-GUI for Mac has been tested in Ubuntu 20.04. Testing pending in other Linux distributions.
If the installer is not working properly, you may need to install ```ocl-icd-opencl``` and ```libxcb-xinerama0```:

```
sudo apt update
sudo apt install ocl-icd-opencl-dev
sudo apt install libxcb-xinerama0
```

## Usage

Consult the manual of the application in the [wiki](https://github.com/dekoning-lab/wfes-gui/wiki) of this repository.

## Third party libraries:

* [Qt Libraries](https://www.qt.io/) ([GPL and LGPL Licenses](https://www.qt.io/licensing/))
* [Intel MKL](https://software.intel.com/content/www/us/en/develop/tools/math-kernel-library.html) ([ISSL License](https://software.intel.com/content/www/us/en/develop/articles/end-user-license-agreement.html))
* [Eigen](http://eigen.tuxfamily.org/) ([MPL2 License](https://www.mozilla.org/en-US/MPL/2.0/))
* [ViennaCL](https://github.com/viennacl/viennacl-dev) ([Custom License](https://github.com/viennacl/viennacl-dev/blob/master/LICENSE))
* [Font Awesome](https://fontawesome.com/) ([MIT License](https://opensource.org/licenses/mit-license.html), [SIL OFL 1.1 License](https://scripts.sil.org/cms/scripts/page.php?site_id=nrsi&id=OFL))
* [Tenderness Font](https://fontlibrary.org/en/font/tenderness) ([CC-0](https://creativecommons.org/share-your-work/public-domain/cc0/))
* [Boost Libraries](https://www.boost.org/) ([Boost License](https://www.boost.org/users/license.html))
* [Open CL Khronos Headers](https://github.com/KhronosGroup/OpenCL-Headers) ([Apache License](https://github.com/KhronosGroup/OpenCL-Headers/blob/master/LICENSE))

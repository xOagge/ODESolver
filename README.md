# ODESolver

## Overview
ODESolver is a C++ application designed to numerically solve Ordinary Differential Equations. The project separates core mathematical solving logic from output generation, providing an organized approach to calculating and visualizing ODEs.

## Repository Structure
The project is modularized into source files, main execution, and build instructions.

| Directory / File | Description |
| :--- | :--- |
| **`src/ODEpoint.h` & `.cpp`** | Defines the data structure representing a coordinate or state point in the ODE system. |
| **`src/ODEsolver.h` & `.cpp`** | Contains the core numerical methods and algorithms used to solve the differential equations. |
| **`src/PlotsMaker.h` & `.cpp`** | Handles data output and generates visual plots of the solved equations. |
| **`main/main.cpp`** | The main entry point for the application, linking the solver and plotting modules. |
| **`Makefile`** | Contains the instructions for compiling and building the project executable. |

## Getting Started

### Prerequisites
* A standard C++ compiler (e.g., GCC or Clang)
* `make` (to utilize the included build system)

### Building the Project
To compile the solver, open your terminal, navigate to the root directory of this repository, and run the following command:
```bash
make
```

### Running the Application
After building the project, you can run the executable (update `[ExecutableName]` with the actual output name defined in your Makefile):
```bash
./[ExecutableName]
```

## Contributing
Feel free to submit issues and enhancement requests.

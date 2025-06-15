# Engine Just For Fun (EJFF for short)
EJFF is an engine created for educational purposes, aimed at mastering the fundamental principles of 2D and 3D engine development

# Minimum requirements
- **C++17 compiler**  
  A modern C++ compiler with full support for the C++17 standard.  
  Recommended compilers:
  - GCC 9 or newer
  - Clang 10 or newer
  - MSVC 2019 (version 16.0) or newer
  
- **CMake 3.24 or higher**  
  Used as the build system generator. Make sure your system has at least version 3.24, as earlier versions may not support features used in this project.

- **Git**  
  Required to clone the repository and manage submodules (if any). Git is also useful for version control and contributing to the project.

# Dependencies
- SDL3
- SDL3_image

# Building
```bash
git clone https://github.com/alx2qndr/EJFF.git
cd EJFF
mkdir build && cd build
cmake ..
cmake --build .
```

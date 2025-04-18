# Installation and Usage Instructions

## Environment

- VS2019

- CMake 3.20 +

## Installation

- Download the source code, choose one of the following two methods
    - git: `git clone https://github.com/shimakaze09/MyGM`
    - https://github.com/shimakaze09/MyGM/archive/main.zip (extract)
- Open CMake-GUI
    - In the `Where is the source code` field, enter `<your-path-to-MyGM>`
    - In the `Where to build the binaries` field, enter `<your-path-to-MyGM>/build`
    - Click Configure, during which it will download [MyCMake](https://github.com/shimakaze09/MyCMake)
      and [MyTemplate](https://github.com/shimakaze09/MyTemplate) to the directory `build/_deps/` (if the download
      fails,
      try several more times or use a VPN until it succeeds without errors)
    - In the middle configuration box of CMake-GUI
        - Find `CMAKE_INSTALL_PREFIX` (installation location), change it to another location (not C drive, because
          installing to C drive requires administrator privileges, which can be troublesome), such as
          `D:/Program_Files/My` (make sure it ends with `My`), referred to as `<install-path>`
        - You can also configure other options
            - `BUILD_TEST_MyCMake` (enabled by default): Example of the dependent library CMake, can be skipped
            - `BUILD_TEST_MyGM` (enabled by default): Example of MyGM, recommended to build
            - `BUILD_TEST_MyTemplate` (enabled by default): Example of MyTemplate, can be skipped
            - `SMKZ_USE_SIMD` (enabled by default): Ensure your CPU supports SSE 2
            - `SMKZ_USE_SSE_4_1` (enabled by default): Ensure your CPU supports SSE 4.1
    - Click Generate
    - Click Open Project, this will **open VS2019**
- After opening VS2019
    - In the Solution Explorer, find `CMakePredefinedTargets/INSTALL`, right-click -> Build, you can see some files (
      MyCMake, MyTemplate
      and MyGM) installed to `<install-path>` in the output window
    - Additionally, you can run the examples (e.g., in the Solution Explorer, find `MyGM/test/MyGM_test_00_val`,
      right-click -> Set as StartUp Project, then in
      the VS2019 toolbar, click "Local Windows Debugger" to run the example)

## Usage

- Configure environment variables

    - Add `<install-path>` to the system environment variable `Path` (or create a new environment variable `MyGM_DIR`
      and set its value to `<install-path>`
      ), so that CMake's `find_package` can correctly find `MyGM`
    - Delete `<your-path-to-MyGM>/build`, otherwise CMake's `find_package` will prioritize locating here, which may
      cause errors

- Project setup example (code can be found in [demo/](demo/))

  ```c++
  // main.cpp
  #include <MyGM/MyGM.h>
  #include <iostream>
  using namespace Smkz;
  int main(){
      pointf3 p{0, 1, 2};
      pointf3 q{2, 1, 0};
      std::cout << p - q << std::endl;
  }
  ```

  ```CMake
  # CMakeLists.txt
  cmake_minimum_required(VERSION 3.14)
  project(demo_project VERSION 1.0.0)
  
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED True)
  
  find_package(MyGM REQUIRED)
  
  add_executable(demo main.cpp)
  
  target_link_libraries(demo PUBLIC My::MyGM_core)
  ```

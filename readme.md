# evr-internals-api

## Where to put the files for wrapping and testing.
* source/
  The private source files
* include/
  The private include files
* public_include/
  The public include files which will be wrapped with swig
* test/cpp
  The GoogleTest files. Please see `TestCurlExample.h` and `TestCurlExample.cpp` for an example on how to use googletest.
* test/python/Darwin
  The python test files. 

## Setup environment
* For MacOS, Run `./bin/setup_mac.sh`
* For Linux, Run `./bin/setup_linux.h`
* For Windows, TODO

## How to setup the build envrionment and build
* For all Platforms, Run `./bin/run_cmake_and_build.sh`
* For MacOS, Run `./bin/macOS.sh`
* For Linux, Run `./bin/linux.sh`
* For Windows32, Run `./bin/windows32.sh`
* For Windows64, Run `./bin/windows64.sh`

## Testing
### ScriptRunner Target
* For python: Run the target `_evr-internals-api-python-swig_ScriptRunner`
** The script runner will run the `main.py` file that is located in `test/python/Darwin`
### Google Test Target
* Run the target `testStaticLibrary`
[Google Test/Mock Tutorial](https://chromium.googlesource.com/external/github.com/google/googletest/+/HEAD/googlemock/README.md)
### Run Script in terminal
* For python in MacOS: Run `./test/python/Darwin/run.sh`
# swig_general

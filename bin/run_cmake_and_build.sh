#!/bin/bash

PLATFORM=$1

# CONFIGURATION=Debug
CONFIGURATION=Release

INSTALL_PREFIX=install

cd ../

if [ "${PLATFORM}" != "android" ]
then
  BUILD_DIR=build_$PLATFORM

  rm -rf $BUILD_DIR
  mkdir -p $BUILD_DIR
  cd $BUILD_DIR
fi

if [ "${PLATFORM}" == "emscripten" ]
then
  # export CC=/usr/bin/cc
  # export CXX=/usr/bin/c++

  # export EMSCRIPTEN_VERSION=1.37.9
  export EMSCRIPTEN_VERSION=1.38.10
  export EMSCRIPTEN_LOCATION=/Users/jamesfolk/Work/tools/emsdk/emscripten/${EMSCRIPTEN_VERSION}
  export EMSCRIPTEN_INCLUDE_LOCATION=${EMSCRIPTEN_LOCATION}/system/include

  emcmake cmake .. \
    -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX} \
    -G "Ninja"

elif [ "${PLATFORM}" == "windows64" ]
then

  cmake .. \
    -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX} \
    -G "Visual Studio 14 2015 Win64"

elif [ "${PLATFORM}" == "windows32" ]
then

  cmake .. \
    -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX} \
    -G "Visual Studio 14 2015"

elif [ "${PLATFORM}" == "macOS" ]
then
    export OPENSSL_ROOT_DIR="/usr/local/opt/openssl@1.1/"

  cmake .. \
    -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX} \
    -G "Xcode"

elif [ "${PLATFORM}" == "linux" ]
then
  export CC=/usr/bin/cc
  export CXX=/usr/bin/c++

  cmake .. \
    -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX} \
    -G "Unix Makefiles"

elif [ "${PLATFORM}" == "ios" ]
then

  cmake .. \
    -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX} \
    -G "Xcode" \
    -DIOS:BOOL=TRUE

elif [ "${PLATFORM}" == "appletv" ]
then

  cmake .. \
    -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX} \
    -G "Xcode" \
    -DTVOS:BOOL=TRUE

elif [ "${PLATFORM}" == "android" ]
then

  rm -rf android/app/.externalNativeBuild

  cd android
  ./gradlew clean
  ./gradlew assemble${CONFIGURATION}

else
  cmake .. -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX}
fi

# cmake --build . --target clean
# cmake --build . --config ${CONFIGURATION} --target install

cd ../bin


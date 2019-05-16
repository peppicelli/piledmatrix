#!/usr/bin/env bash
set -e

UNAMEOUT="$(uname -s)"
case "${UNAMEOUT}" in
    Linux*)     MACHINE="Linux";;
    Darwin*)    MACHINE="Mac";;
    CYGWIN*)    MACHINE="Cygwin";;
    MINGW*)     MACHINE="MinGw";;
    *)          MACHINE="UNKNOWN:${UNAMEOUT}"
esac

# Cleanup (should be moved to a trap function)
cleanup() {
  echo "Cleaning up"
  cd $ORIGINAL_DIR
}
trap cleanup 0

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
ORIGINAL_DIR=$(pwd)
echo "Building in $(pwd) as $(whoami)"

mkdir -p $SCRIPT_DIR/../build

docker run -u$(id -u) --rm -v$SCRIPT_DIR/..:/data dpeppicelli/raspbian-rt-cross-compilation:0.1 /bin/bash -c "cd /data/build && cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=/opt/raspberry/pi.cmake ../ && make"

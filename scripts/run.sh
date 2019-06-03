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
  cd $ORIGINAL_DIR
}
trap cleanup 0

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
ORIGINAL_DIR=$(pwd)
echo "Running in $(pwd) as $(whoami)"

scp $SCRIPT_DIR/../build/piledmatrix*.deb pi@$1:/home/pi
ssh pi@$1 << EOF
  cd /home/pi
  sudo dpkg --purge piledmatrix
  sudo apt -y install ./piledmatrix*.deb
  rm -rf piledmatrix*.deb
  sudo piledmatrix
EOF
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

echo "Cleaning up last results"
rm -rf $SCRIPT_DIR/../build/coverage
find $SCRIPT_DIR/../build/ -name "*.gcda" -type f -delete

echo "Transfering build to raspberry."
scp $SCRIPT_DIR/../build/piledmatrix*.deb pi@$1:/home/pi

echo "Running the test on the target."
ssh pi@$1 << EOF
  cd /home/pi
  sudo dpkg --purge piledmatrix
  sudo apt -y install ./piledmatrix*.deb
  rm -rf piledmatrix*.deb
  export GCOV_PREFIX=/home/pi
  sudo pkill -9 piledmatrix
  piledmatrix_tests
EOF

# Get the coverage back
echo "Getting the coverage data back."
scp -r pi@$1:/home/pi/data/build/* $SCRIPT_DIR/../build/

docker run -u$(id -u) --rm -v$SCRIPT_DIR/..:/data dpeppicelli/raspbian-rt-cross-compilation:0.3 /bin/bash -c "
mkdir -p /data/build/coverage &&
lcov -c --directory /data/build/CMakeFiles/piledmatrix_tests.dir/src --output-file /data/build/coverage/main_coverage.info &&
lcov --remove /data/build/coverage/main_coverage.info '/data/build/spdlog/*' '/opt/*' -o /data/build/coverage/main_coverage.info &&
genhtml --legend /data/build/coverage/main_coverage.info --output-directory /data/build/coverage"

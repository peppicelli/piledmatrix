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
  sudo umount $DOCKER_DIR/rootfs/tmp_mount
  cd $ORIGINAL_DIR
}
trap cleanup 0

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
ORIGINAL_DIR=$(pwd)
DOCKER_DIR=$SCRIPT_DIR/../docker
cd $DOCKER_DIR
echo "Building in $(pwd) as $(whoami)"

# Unfortunately, it's impossible to mount an img file with docker build (
# see https://unix.stackexchange.com/questions/305430/build-docker-image-in-privileged-mode)
# Instead, we are extracting here, on the host, the parts of the raspberry filesystem
# that will be needed for cross compilation.
# We do that only if not already done.

if [ ! -d $DOCKER_DIR/rootfs/lib ]; then
  mkdir -p $DOCKER_DIR/rootfs
  if [ ! -f $DOCKER_DIR/rootfs/2018-06-12_2018-04-18-realtimepi-stretch-lite-0.3.zip ]; then
    curl -SL http://unofficialpi.org/Distros/RealtimePi/2018-06-12_2018-04-18-realtimepi-stretch-lite-0.3.zip --output $DOCKER_DIR/rootfs/2018-06-12_2018-04-18-realtimepi-stretch-lite-0.3.zip
  fi
  if [ ! -f $DOCKER_DIR/rootfs/2018-04-18-realtimepi-stretch-lite-0.3.img ]; then
    unzip $DOCKER_DIR/rootfs/2018-06-12_2018-04-18-realtimepi-stretch-lite-0.3.zip -d $DOCKER_DIR/rootfs
  fi
  mkdir -p $DOCKER_DIR/rootfs/tmp_mount

  # Use "fdisk -l" to find the offset of the rootfs partition. Do not forget to multiply 
  # the value by 512
  OFFSET=50331648 # 98304 * 512
  sudo mount -v -o offset=50331648 -t ext4 $DOCKER_DIR/rootfs/2018-04-18-realtimepi-stretch-lite-0.3.img $DOCKER_DIR/rootfs/tmp_mount
  cp -R $DOCKER_DIR/rootfs/tmp_mount/lib $DOCKER_DIR/rootfs
  cp -R $DOCKER_DIR/rootfs/tmp_mount/usr $DOCKER_DIR/rootfs
  sudo umount $DOCKER_DIR/rootfs/tmp_mount

  # Cleanup (So that the docker context is kept small)
  rm -rf $DOCKER_DIR/rootfs/*.zip
  rm -rf $DOCKER_DIR/rootfs/*.img
  rm -rf $DOCKER_DIR/rootfs/tmp_mount
fi

# Build the image
docker build --build-arg UID=$(id -u) --build-arg GID=$(id -g) ../docker -t dpeppicelli/raspbian-rt-cross-compilation:0.3

# pi-led-matrix

## Build

This project can be built using a `docker` container.
In order to build the container image:

```
cd script
./build-docker.sh
```

The script `scripts/build.sh` will automatically use the docker image to build the project.
If the image is not built, the one from [Dockerhub](https://hub.docker.com/r/dpeppicelli/raspbian-rt-cross-compilation)
will be automatically used.

## Dependencies

This project uses:
- [wiringPi](http://wiringpi.com/)
- [spdlog](https://github.com/gabime/spdlog).
- [google tests and mock](https://github.com/google/googletest)
All these dependencies are built automatically with the help of `ExternalProject_Add` in CMake.
# pi-led-matrix

## Build

This project is to be built using a `docker` container.
In order to build the container image (if not built locally, image will get pulled from 
dockerhub):

```
cd script
./build-docker.sh
```

The script `scripts/build.sh` will automatically use the docker image to build the project.
If the image is not built, the one from [Dockerhub](https://hub.docker.com/r/dpeppicelli/raspbian-rt-cross-compilation)
will be automatically used.

## Test

Running the test is as easy as calling `scripts/test.sh IP_OF_RASPBERRY_HERE`. Make sure that
your machine can ssh in the raspberry without password (using `ssh-copy-id`). 

The tests will run, then the coverage files will be retrieved and the docker container will
generate the coverage report in `build/coverage`

## Documentation

The documentation is automatically generated and can be found in `build/html`.

## Dependencies

This project uses:
- [wiringPi](http://wiringpi.com/)
- [spdlog](https://github.com/gabime/spdlog).
- [google tests and mock](https://github.com/google/googletest)
All these dependencies are built automatically with the help of `ExternalProject_Add` in CMake.
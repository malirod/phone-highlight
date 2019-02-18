# Phone highlight

For given phone and search pattern returns structures of indexes which should be highlighted. Allows to calculate highlights for visualization of search as it's done by phone. Some special characters are ignored during calculation (e.g. "(", ")", " " and some other)

E.g. for number "(123) 55 35" and search string "35" result will be "3-3;6-6;9-10". For more cases see unit tests.

## Platform

Ubuntu 18.10: Clang 7.0, GCC 8.2, Cmake 3.12, Conan

C++14 Standard is used.

WebKit [style](https://webkit.org/code-style-guidelines/) is used.

See `tools/Dockerfile` for details how to setup development environment

## Setup

Assuming all further commands are executed from project root.

### Setup git hook

Run `tools/install_hooks.py`

This will allow to perform some code checks locally before posting changes to server.

### Dependencies

Libs: Boost 1.69

Project uses [Conan Package Manager](https://github.com/conan-io/conan)

Install conan with

`sudo -H pip install conan`

CMake will try to automatically setup dependencies.

Add additional repositories to conan:

`conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan`
`conan remote add catchorg https://api.bintray.com/conan/catchorg/Catch2`

Cmake will automatically check required dependencies and setup them taking into account current compiler (clang or gcc).

Conan misses gcc 8.2 in default config at the moment. The one can use pre-defined config file.

`conan config install ./tools/conan/cfg`

### Draw deps with cmake

```bash
cmake --graphviz=graph ..
dot graph -T png -o graph.png
```

## Install doxygen

`sudo apt install -y doxygen graphviz`

## Build

### Build commands

By default used clang compiler and debug mode.

Run in project root to build debug version with clang

`mkdir build-clang-debug && cd build-clang-debug && cmake .. && make -j$(nproc)`

To build release version with gcc run the following command

`RUN mkdir build-gcc-release && cd build-gcc-release && CXX=g++ cmake -DCMAKE_BUILD_TYPE=Release .. && make -j$(nproc)`

### Build with sanitizers (clang)

You can enable sanitizers with `SANITIZE_ADDRESS`, `SANITIZE_MEMORY`, `SANITIZE_THREAD` or `SANITIZE_UNDEFINED` options in your CMake configuration. You can do this by passing e.g. `-DSANITIZE_ADDRESS=On` in your command line.

## Run

Run from build directory

`ctest`

or

`bin/testrunner`

## Coverage report

To enable coverage support in general, you have to enable `ENABLE_COVERAGE` option in your CMake configuration. You can do this by passing `-DENABLE_COVERAGE=On` on your command line or with your graphical interface.

If coverage is supported by your compiler, the specified targets will be build with coverage support. If your compiler has no coverage capabilities (I assume Intel compiler doesn't) you'll get a warning but CMake will continue processing and coverage will simply just be ignored.

Collect coverage in Debug mode. Tested with gcc 5.0 and clang 5.0 compiler.

### Sample commands to get coverage html report

```bash
CXX=g++ cmake -DENABLE_COVERAGE=On -DCMAKE_BUILD_TYPE=Debug ..
make -j$(nproc)
make test
make lcov-capture
make lcov-genhtml
xdg-open lcov/html/selected_targets/index.html

```

## Integration

### Create docker image

**Dockerfile**: image, which contains basic environment setup (compiler, build tools)

`docker build -t phone-highlight -f tools/Dockerfile .`

### Clang static analyzer

Sample command to run analyzer. By default report is stored in `/tmp/scan-build*`

```bash
mkdir build-debug
cd build-debug
scan-build --use-analyzer=/usr/bin/clang++ cmake ..
scan-build --use-analyzer=/usr/bin/clang++ make -j$(nproc)
```

or

```bash
cmake ..
make clang-static-analyzer
```

### Clang-tidy

Setting are stored in `.clang-tidy`.

Run

```bash
mkdir build
cd build
cmake ..
make clang-tidy
```

### Documentation

Code contains doxygen. To generate html documentation run command `make doc`. Output will be in `<build dir>\doc\html`
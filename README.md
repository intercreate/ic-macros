# Intercreate Macros

This header-only macro library provides common GCC utility macros.

# Include in Your Project

* Add the fetch file to your repo: `wget https://github.com/intercreate/ic-macros/releases/latest/download/fetch_ic_macros.cmake`
* Include and link in your CMakeLists.txt:
  ```cmake
  include(fetch_ic_macros.cmake)
  #...
  target_link_libraries(my_cmake_project PRIVATE ic_macros)
  ```
* Include in your source code: 
  ```c
  #include <ic_macros.h>
  ```

# Contributions

* Fork this repository: https://github.com/intercreate/ic-macros/fork
* Clone your fork: `git clone git@github.com:<YOUR_FORK>/ic-macros.git`
  * then change directory to your cloned fork: `cd ic-macros`
* Enable the githook: `git config core.hooksPath .githooks`

# Development Guide

## Activate the Environment

`. ./envr.ps1`

## Run Tests

`test`

## Run Linters

`lint`

## Setup Toolchains for Testing

The following assumes that you are on an x86 machine and would like to run tests in QEMU after cross-compiling.

### Install QEMU

* `sudo apt install qemu-user qemu-user-static`

### GNU arm-none-eabi (Arm 32-bit)

#### Install the xPack GNU Arm Embedded GCC

* [Install `xpm`](https://xpack.github.io/xpm/install/): `npm install --global xpm@latest`
* [Install the Arm GNU toolchain](https://xpack.github.io/dev-tools/arm-none-eabi-gcc/install/): `xpm install @xpack-dev-tools/arm-none-eabi-gcc@13.2.1-1.1.1`

Add to your `envr-local` if the path and/or version is different from the one specified in `envr-default`:

```
[VARIABLES]
TOOLCHAIN_GNU_ARM_NONE_EABI_PATH=$HOME/my_path_to/the_toolchain/bin
```

Run the tests: `test arm-none-eabi-gcc`

### GNU arm-zephyr-eabi (AKA Zephyr SDK) (Arm 32-bit)

#### Install the Zephyr SDK

Reference: https://docs.zephyrproject.org/latest/develop/getting_started/index.html#install-zephyr-sdk

```
cd ~
wget https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.16.3/zephyr-sdk-0.16.3_linux-x86_64.tar.xz
wget -O - https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.16.3/sha256.sum | shasum --check --ignore-missing
tar xf zephyr-sdk-0.16.3_linux-x86_64.tar.xz
rm zephyr-sdk-0.16.3_linux-x86_64.tar.xz
cd zephyr-sdk-0.16.3
./setup.sh -t arm-zephyr-eabi

cd ~/<back to this repository>
```

Run the tests: `test arm-zephyr-eabi-gcc`

Add to your `envr-local` if the path and/or version is different from the one specified in `envr-default`:

```
[VARIABLES]
TOOLCHAIN_GNU_ARM_ZEPHYR_EABI_PATH=$HOME/my_path_to/the_toolchain/bin
```

### aarch64-linux-gnu (Arm 64-bit)

```
sudo apt install gcc-aarch64-linux-gnu g++-aarch64-linux-gnu binutils-aarch64-linux-gnu
```

Run the tests: `test aarch64-linux-gnu-gcc`

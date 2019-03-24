<div align=center>
<img src="https://www.onvif.org/wp-content/themes/onvif-public/images/logo.png" width = "65%" height = "65%" alt="onvif logo"/>
</div>

# 0. BUILDING AND INSTALLATION (Briefly)

## CMake (General)

```cmake
# Enable build WS-Discovery module.
OVF_BUILD_WSDD:BOOL=ON

# Enable build test code.
OVF_BUILD_TEST:BOOL=ON

# Enable using glog library. Make sure to enable -DHAVE_USING_GLOG as well.
OVF_USING_GLOG:BOOL=ON
```

## CMake (Windows)

```shell
$ md build && cd build
$ cmake -G "Visual Studio 12" .. # Or whatever generator you want to use cmake --help for a list.
$ start libevent.sln
```

## CMake (Unix)

```shell
$ mkdir build && cd build
$ cmake .. # Default to Unix Makefiles.
$ make
```
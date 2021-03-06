# /bin/sh

libonvif_dir=$(pwd)
rm -fr lib
mkdir lib

git submodule init
git submodule update

## build 3rdparty libs
# glog
cd ./3rdparty/glog
rm -fr build
mkdir build
cd ./build
# echo $libonvif_dir/modlules/common/glog
cmake .. -DBUILD_SHARED_LIBS=ON
make -j8
cp -r ./glog $libonvif_dir/modules/common
cp ../src/glog/log_severity.h $libonvif_dir/modules/common/glog
cp libglog.so* $libonvif_dir/lib
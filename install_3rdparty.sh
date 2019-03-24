# /bin/sh

libonvif_dir=$(pwd)

## build 3rdparty libs
# glog
cd ./3rdparty/glog
rm -r build
mkdir build
cd ./build
echo $libonvif_dir/modlules/common/glog
cmake .. -DBUILD_SHARED_LIBS=ON
make -j8
cp -r ./glog $libonvif_dir/modules/common/glog
cp ../src/glog/log_severity.h $libonvif_dir/modules/common/glog
cp libglog.so $libonvif_dir/lib

# cd $libonvif_dir
# rm -r build
# mkdir build
# cd build
# cmake ..
# make -j8 & make install
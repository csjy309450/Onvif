source install_3rdparty.sh

cd $libonvif_dir
rm -fr build
mkdir build
cd build
cmake ..
make -j8 & make install
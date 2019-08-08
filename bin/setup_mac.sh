brew install swig
brew install cmake
brew install go
# brew install lua
# brew install python
brew install octave

cver=3.11.0
wd=/tmp
wget -nc -P $wd https://cmake.org/files/v${cver:0:4}/cmake-$cver.tar.gz
cd $wd
tar -xf cmake-$cver.tar.gz
cd cmake-$cver
./configure
make -j8
sudo make install
cd ..
rm -rf cmake-$cver



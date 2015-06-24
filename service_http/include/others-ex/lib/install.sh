#!/bin/sh
# You can excute the install script under any directory
# It will find the latest version to compile and install
# make distclean comes first, the we get fresh source code
# the parameters of configure specify to build a static library and install the package under 'expat' directory
cd `dirname $0`
dir=`pwd`

rm -rf $dir/include $dir/lib $dir/bin $dir/build-1 apr-util apr log4cxx jsoncpp

tar -zxvf apr-1.3.8.tar.gz
latest_version='apr-1.3.8'
cd $latest_version
echo $latest_version
if [ -f "[Mm]akefile" ]; then
	make distclean
	echo "make distclean"
fi
./configure --enable-shared=no --prefix="$dir/$latest_version"
echo "./configure --enable-shared=no --prefix=$dir/$latest_version"
make  ; make install

cd $dir
rm -rf $dir/include $dir/lib

tar -zxvf apr-util-1.3.9.tar.gz 
latest_version='apr-util-1.3.9'
cd $latest_version
echo $latest_version
if [ -f "[Mm]akefile" ]; then
	make distclean
	echo "make distclean"
fi
./configure --enable-shared=no --prefix="$dir/$latest_version" --with-apr="$dir/apr-1.3.8/"
echo "./configure --enable-shared=no --prefix=$dir "
make ; make install

cd $dir
tar zvxf apache-log4cxx-0.10.0.tar.gz
/bin/rm -rf $dir/include $dir/lib
cd apache-log4cxx-0.10.0
./configure  --prefix="$dir/apache-log4cxx-0.10.0" --with-charset=utf-8 --with-logchar=utf-8 --enable-shared=no --with-apr="$dir/apr-1.3.8/" --with-apr-util="$dir/apr-util-1.3.9/"
make ; make install


cd $dir
mv apache-log4cxx-0.10.0/ log4cxx
mv apr-1.3.8/ apr
mv apr-util-1.3.9 apr-util
rm -rf $dir/include $dir/lib $dir/bin $dir/build-1 share/

tar -zxvf jsoncpp-src-0.5.0.tar.gz
cd $dir/jsoncpp-src-0.5.0
make release 

cd $dir
mv jsoncpp-src-0.5.0 jsoncpp

cd $dir
tar zvxf libiconv-1.9.2.tar.gz
cd $dir/libiconv-1.9.2
CFLAGS="-fPIC" ./configure  --prefix="$dir/libiconv-1.9.2" --enable-shared=no

make && make install
cd $dir
mv libiconv-1.9.2 libiconv

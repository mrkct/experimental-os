. ./config.sh

mkdir -p $(pwd)/sysroot/usr/include
mkdir -p $(pwd)/sysroot/usr/boot

# The folder where all .o files will be stored
mkdir -p $OBJF/
cd ./src
cp --preserve=timestamps --parents `find ./ -name \*.h` $SYSROOT$INCLUDEDIR
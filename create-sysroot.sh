. ./config.sh

mkdir -p $(pwd)/sysroot/usr/include
mkdir -p $(pwd)/sysroot/usr/boot

# The folder where all .o files will be stored
mkdir -p $OBJF/

for PROJECT in $PROJECTS; do
    ( cd $PROJECT && cp --preserve=timestamps -R include/. $SYSROOT$INCLUDEDIR )
done
# This scripts sets some variables and most importantly creates the sysroot
# The folder 'sysroot' is where gcc will lookup all the headers
# Here we copy all the headers from the folders defined in PROJECTS into sysroot
# and setup the default CC to call gcc and look for the headers in this folder
# this way we will be able to also implement our libc in the future


# A list of folders (space separated) that need to have their headers copied to sysroot
# All folders need to have an 'include' subfolder, that contains the headers
export PROJECTS="kern"

export CC=$TARGET-gcc
export AS=$TARGET-as
export AR=$TARGET-ar

export SYSROOT=$(pwd)/sysroot
export INCLUDEDIR=/usr/include

mkdir -p $(pwd)/sysroot/usr/include
mkdir -p $(pwd)/sysroot/usr/boot

for PROJECT in $PROJECTS; do
    ( cd $PROJECT && cp --preserve=timestamps -R include/. $SYSROOT$INCLUDEDIR )
done

echo $(pwd)

export CC="$CC --sysroot=$SYSROOT -isystem=$INCLUDEDIR"

make run
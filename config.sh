# This scripts sets some variables, mostly about the sysroot and
# where the .o files will be created.
# The folder 'sysroot' is where gcc will lookup all the headers

if [ -z "$TARGET" ]; then 
    echo "WARNING: You have not set the \$TARGET path variable";
    echo "Using default of i686-elf";
    export TARGET=i686-elf 
else 
    echo "Using $TARGET as TARGET"; 
fi

export CC=$TARGET-gcc
export AS=$TARGET-as
export AR=$TARGET-ar

# The sysroot and the include directory (inside the sysroot)
export SYSROOT=$(pwd)/sysroot
export INCLUDEDIR=/usr/include

export CC="$CC --sysroot=$SYSROOT -isystem=$INCLUDEDIR"
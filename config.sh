# This scripts sets some variables, mostly about the sysroot and
# where the .o files will be created.
# The folder 'sysroot' is where gcc will lookup all the headers


# A list of folders (space separated) that need to have their headers copied to sysroot
# All folders need to have an 'include' subfolder, that contains the headers
export PROJECTS="kern"

export CC=$TARGET-gcc
export AS=$TARGET-as
export AR=$TARGET-ar

# This is the folder where all .o files will be stored
# Note: this is also redefined in the Makefiles
export OBJF=out

# The sysroot and the include directory (inside the sysroot)
export SYSROOT=$(pwd)/sysroot
export INCLUDEDIR=/usr/include

export CC="$CC --sysroot=$SYSROOT -isystem=$INCLUDEDIR"
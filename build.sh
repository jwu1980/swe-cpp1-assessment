#!/usr/bin/env bash

ROOT="${BASEDIR:=$(dirname $0)}"
echo "ROOT: $ROOT"

CODEGEN_DIR=$ROOT/_build
LIBS=""
SRC_DIRS="src"

CPPFLAGS="-O3 -std=c++17 -c -fPIC"
ALL_OBJS=""

if [[ "$OSTYPE" == "darwin"* ]]; then
    # Mac OSX
    CPPFLAGS="${CPPFLAGS} -stdlib=libc++"
fi

# cc files in SRC_DIRS
for src_d in $SRC_DIRS
do
    dst_dir=$CODEGEN_DIR/$src_d
    mkdir -p $dst_dir
    for f in $src_d/*.cc
    do
        echo "Compiling cc $f"
        filename=$(basename -- "$f")
        filename="${filename%.*}"
        obj_path=$dst_dir/$filename.o
        g++ $CPPFLAGS -o $obj_path -I$CODEGEN_DIR -I. -I$ROOT $f
        ALL_OBJS="$ALL_OBJS $obj_path"
    done
done

#!/bin/bash

# CMake prebuild script
# Usage:
#   ./PrebuildScript_Linux.sh [c]
#   c: clean build (Clean cache and recompile)

BUILD_DIR="build"
CMAKE_COMPILER="-DCMAKE_CXX_COMPILER=g++"  # Adjust as you need

if [ "$1" == "c" ]; then
	if [ -d "$BUILD_DIR" ]; then
		echo "[INFO] Cleaning CMake cache in $BUILD_DIR..."
		rm -f "$BUILD_DIR/CMakeCache.txt"
		echo "[INFO] (Re)creating build structure in $BUILD_DIR..."
		cmake -B "$BUILD_DIR" -S . $CMAKE_COMPILER
		echo "[INFO] Compiling project..."
		make -C "$BUILD_DIR"
	else
		echo "[INFO] Directory $BUILD_DIR does not exists. Creating and setting..."
		mkdir "$BUILD_DIR"
		cmake -B "$BUILD_DIR" -S . $CMAKE_COMPILER
		echo "[INFO] Compiling project..."
		make -C "$BUILD_DIR"
	fi
elif [ -d "$BUILD_DIR" ]; then
	echo "[INFO] Directory $BUILD_DIR exists. Executing make..."
	make -C "$BUILD_DIR"
else
	echo "[INFO] Directory $BUILD_DIR does not exists. Creating and setting..."
	mkdir "$BUILD_DIR"
	cmake -B "$BUILD_DIR" -S . $CMAKE_COMPILER
	echo "[INFO] Compiling project..."
	make -C "$BUILD_DIR"
fi

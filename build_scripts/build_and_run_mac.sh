#!/bin/bash
set -e

cd ..

if ! xcode-select -p &>/dev/null; then
    echo "Installing Xcode Command Line Tools..."
    xcode-select --install
    exit 0
fi

if ! command -v brew &>/dev/null; then
    echo "Installing Homebrew..."
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
fi

if ! command -v cmake &>/dev/null; then
    echo "Installing CMake..."
    brew install cmake
fi

if [ -d "build" ]; then
    echo "Removing previous build..."
    rm -rf "build"
fi
mkdir -p "build"
cd "build"

echo "Configuring project..."
cmake .. -DCMAKE_BUILD_TYPE=Release

echo "Building project..."
cmake --build . --config Release

echo "Launching game..."
./bin/Game2048

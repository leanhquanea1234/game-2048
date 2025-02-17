# Game 2048

A simple game 2048 implemented using C++ with SFML v2.6. A project purely for the sake of educational purpose. [Github page](https://github.com/leanhquanea1234/game-2048)

*by Le Anh Quan - 24120217*


## Demo

- Video with build and run showcase 

[![Watch the video](https://img.youtube.com/vi/2ak-EIfmCLA/hqdefault.jpg)](https://youtu.be/2ak-EIfmCLA)

- A quick look

[![Watch the video](https://img.youtube.com/vi/ejB1lSIpuds/hqdefault.jpg)](https://youtu.be/ejB1lSIpuds)


## How to build 

### Windows

1. If you don't have Cmake, the first step is installing Cmake. Download 'Windows x64 Installer' from [here](https://cmake.org/download/) and follow the wizard.
2. Install 'Visual Studio 2022 Build Tools' from [here](https://visualstudio.microsoft.com/visual-cpp-build-tools/) and **make sure** to install with `Desktop development with C++` option.
4. Download .zip file and exact it from [here](https://github.com/leanhquanea1234/game-2048/archive/refs/heads/main.zip).
3. Locate the project file, click and run `build_and_run.bat` in `/build_scipts`.

### Mac (NOT TESTED)

I did make a bash script in `/build_scipts` called `build_and_run_mac.sh` (learn how to run bash script from [here](https://stackoverflow.com/questions/733824/how-to-run-a-shell-script-on-a-unix-console-or-mac-terminal)). Not sure if it works though. If it doesn't work, please follow the manual method below.

1. Install 'Xcode Command Line Tools'. Type this in the terminal:
```
xcode-select --install
```
2. Install 'Homebrew'. For more info, please prefer to [here](https://github.com/Homebrew/install):
```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
3. Install Cmake via brew:
```
brew install cmake
```
4. Download .zip file and exact it from [here](https://github.com/leanhquanea1234/game-2048/archive/refs/heads/main.zip).
5. Locate the project file. I'm assuming after extraction, it'll be /Downloads/game-2048-main:
```
cd ~/Downloads/game-2048-main # please change it to your file location if you put it somewhere else
```
6. Make build directory and cd into it:
```
mkdir -p build
cd build
```
7. Configure project:
```
cmake .. -DCMAKE_BUILD_TYPE=Release
```
8. Build project:
```
cmake --build . --config Release
```
9. Run the game!
```
./bin/Game2048
```

## Self-review
Completion: 100%
- [x] Have Undo/Redo
- [x] Have a save game feature
- [x] Saving game using binary file
- [x] Using only pointers, not using <vector> or <stack> lib
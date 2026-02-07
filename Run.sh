ARG=$0
if (ARG == "--clean") then
    rm -rf ./builds
fi

cmake -S . -B ./builds
cmake --build ./builds
./builds/Physics-Engine

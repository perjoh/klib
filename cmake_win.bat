mkdir _build
pushd _build
rem Note: Run 'vcpkg integrate install' to find path to vcpkg.cmake.
rem set CMAKE_TOOLCHAIN_FILE=C:/bin/vcpkg/scripts/buildsystems/vcpkg.cmake
echo %CMAKE_TOOLCHAIN_FILE%
cmake -DCMAKE_TOOLCHAIN_FILE=%CMAKE_TOOLCHAIN_FILE% -DCMAKE_GENERATOR_PLATFORM=x64 ..\
popd

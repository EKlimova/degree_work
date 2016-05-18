$ mkdir build.debug
$ cd build.debug
$ conan install ../src -s compiler="Visual Studio" -s compiler.version=14 -s arch=x86 -s build_type=Debug -s compiler.runtime=MDd
$ cmake ../src -G "Visual Studio 14"


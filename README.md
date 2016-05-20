       
## *The destination of the document*
This document is devoted to how to install libraries. Make sure, that Conan and CMake have been already installed in your computer, and CMakeLists have been written. Whereupon, you have to clone a repository from the official library site. Below in the text there are the code what you have to print on the command line.

### *Note*
The code below was written for Debug (Visual Studio 15 32bit).

## *The code for the command line*

     $ mkdir build.debug

     $ cd build.debug

     $ conan install ../src -s compiler="Visual Studio" -s compiler.version=14 -s arch=x86 -s build_type=Debug -s compiler.runtime=MDd

     $ cmake ../src -G "Visual Studio 14"
     
### *Comments to the code*

1. Creat a build.debug directory.
2. Go to the directory.
3. Conan installs the library for your development environment.
4. CMake build the library.





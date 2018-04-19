# Jeplu
A framework for Plugin management.

 # Installing on windows #

 * Download CMake >= 3.10;
 * Download MSVC 2015;
 * Download Qt v5.10;
 * Download debugger from windows sdk (optional);
 * Install everything. Make sure to install Qt for MSVC 2015.

 ## Configuring ##

 * Run `vcvarsall.bat`;

## Building ##

 * Build using cmake and make (or MSBuild for windows).

```
mkdir build
cd build
cmake ..
make
```

or for windows:
```
MSBuild ALL_BUILD.vcxproj
```

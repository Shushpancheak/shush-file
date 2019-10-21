# shush::file
A file manager for my projects. Takes advantage of shush::dump's exceptions for better error handling.

cmake .. # "-UBUILD_TESTS -DBUILD_TESTS=ON" to build tests, "-ULIBRARY_TYPE -DLIBRARY_TYPE=SHARED" for building shared library
make
```

## Usage
Download the repository and place it into your project directory. In your project's CMakeLists.txt file, insert the following lines:
```cmake
...
add_subdirectory(shush-file)
...
target_link_libraries(${PROJECT_NAME} shush-file)
...
```

## Build documentation
```shell
doxygen
```
Documentation will be generated in the directory named `docs`.
# About this project

Make a new copy of this folder in the sketch group (the folder containing this one, called `99-My-Sketches`).

In CMakeLists.txt, there is a line as follows
```cmake
# This is the name of the executable
set(EXECUTABLE_NAME 99_99_Template)
```

In the new copy, assign a unique value to `EXECUTABLE_NAME`. No two sketches can have the same executable name; otherwise CMake will throw an error.

Happy hacking!
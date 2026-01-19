#
cmake_minimum_required (VERSION 3.8)

disable_if_opencv_not_found()

# This is the name of the executable
set(EXECUTABLE_NAME 03_00_08_Video)

# Add source to this project's executable.
add_executable (${EXECUTABLE_NAME} "main.cpp")

# Add tests and install targets if needed.
TARGET_LINK_LIBRARIES (${EXECUTABLE_NAME} ${OpenCV_LIBS})

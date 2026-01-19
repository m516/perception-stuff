# This macro finds all the libraries required by the projects. 
# 
# It has one parameter: the path to the folder containing all the 
# libraries that are stored locally in this project.

cmake_minimum_required(VERSION 3.6)


macro (get_3rd_party_libraries)

###########################################################################################################
#                                         Argument Checking                                               #
###########################################################################################################
# The first parameter is the path to the external library, relative to where the macro was called
if(${ARGC} GREATER 0)
    set(EXTERNAL_LIBRARY_DIRECTORY ${ARGV0}) # used by external_dependencies to locate the external packages
else()
    message("Error from get_external_dependencies macro: External library directory not set!")
endif()

###########################################################################################################
#                                         External Libraries                                              #
###########################################################################################################
message("Searching for external libraries...")

# OpenCV
message("Finding OpenCV")
option(USE_OPENCV "Attempt to use OpenCV. If disabled, projects that require OpenCV can't build. Enabled by default" ON)
if(USE_OPENCV)
    find_package(OpenCV)
    include_directories(${OpenCV_INCLUDE_DIRS})
    if(OpenCV_FOUND)
        message("OpenCV found.")
    else()
        message("OpenCV wasn't found.")
    endif()

else()
    message("OpenCV was disabled.")
endif()

###########################################################################################################
#                                         Internal Libraries                                              #
###########################################################################################################
message("Importing local libraries...")
include_directories(${EXTERNAL_LIBRARY_DIRECTORY})

# That's all the libraries
message("Library search complete!")

endmacro()
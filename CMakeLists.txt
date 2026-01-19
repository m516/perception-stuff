# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#

cmake_minimum_required (VERSION 3.10)
project ("CV-Sandbox" C CXX)


###########################################################################################################
#                                         Auto Configuration                                              #
###########################################################################################################


# Set the macro/helper directory 
set(MACRO_DIRECTORY "${CMAKE_HOME_DIRECTORY}/CMake/macros")
# Add some macros
include("${MACRO_DIRECTORY}/colors.cmake")
include("${MACRO_DIRECTORY}/get_3rd_party_libraries.cmake")
include("${MACRO_DIRECTORY}/libhelpers.cmake")

#Manually place all binaries into a folder under bin/
set(BUILD_FULL_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin/)
message("Output directory: ${BUILD_FULL_DIRECTORY}")
# First for the generic no-config case (e.g. with mingw)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${BUILD_FULL_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${BUILD_FULL_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${BUILD_FULL_DIRECTORY})
# Second, for multi-config builds (e.g. msvc)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${BUILD_FULL_DIRECTORY})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${BUILD_FULL_DIRECTORY})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${BUILD_FULL_DIRECTORY})
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

# Manually define a compile-time definition for the media/ directory
set(MEDIA_DIR "${CMAKE_SOURCE_DIR}/media/")
if(CMAKE_VERSION VERSION_GREATER 3.12)
    add_compile_definitions(MEDIA_DIRECTORY="${MEDIA_DIR}")
else()
    add_definitions("-DMEDIA_DIRECTORY=\"${MEDIA_DIR}\"")
endif()
message("Media directory: ${MEDIA_DIR}")










###########################################################################################################
#                                        Check compiler options                                           #
###########################################################################################################

############################################## Threads ####################################################
message("Finding Threads")
option(USE_THREADS "Attempt to use pthread library. If disabled, some projects will use a single thread or refuse to build. Enabled by default" ON)
if(USE_THREADS)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    include(FindThreads)
    if(CMAKE_USE_PTHREADS_INIT)
        message("Threads library found.")
        #Add compiler definition to tell code it can use threads. The value of the definition is the number of cores.
        if(CMAKE_VERSION VERSION_GREATER 3.12)
            include(ProcessorCount)
            ProcessorCount(N_PROCESSORS)
            if(N_PROCESSORS EQUAL 0)
                set(N_PROCESSORS 2)
                message("Unable to count processors")
            endif()
            message("Max supported thread count estimated to be ${N_PROCESSORS}")
            add_compile_definitions(THREAD_SUPPORT=${N_PROCESSORS})
        else()
            add_definitions("-DTHREAD_SUPPORT=\"${N_PROCESSORS}\"")
        endif()
    else()
        if(Threads_FOUND)
            message("A threading library was found, but it isn't pthread.")
        else()
            message("Threads library wasn't found.")
        endif()
    endif()
else()
    message("Threads library was disabled.")
endif()

############################################## OpenMP ####################################################
message("Checking OpenMP support")
include(FindOpenMP)
if(OpenMP_FOUND)
    if(OpenMP_C_FOUND)
        message("-- C version: ${OpenMP_C_VERSION}")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    endif()
    if(OpenMP_CXX_FOUND)
        message("-- C++ version: ${OpenMP_CXX_VERSION}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    endif()
endif()

############################################## CUDA ####################################################
message("Checking if CUDA files can be compiled")
option(USE_CUDA "Attempt to use CUDA. If disaled, projects that require CUDA can't build. Enabled by default" ON)
#https://cliutils.gitlab.io/modern-cmake/chapters/packages/CUDA.html
if(USE_CUDA)
    include(CheckLanguage)
    check_language(CUDA)
    if(CMAKE_CUDA_COMPILER)
        message("CUDA exists")
        enable_language(CUDA)
        include_directories(${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})
        if(NOT DEFINED CMAKE_CUDA_STANDARD)
            set(CMAKE_CUDA_STANDARD 11)
            set(CMAKE_CUDA_STANDARD_REQUIRED ON)
        endif()
    else()
        message("Failed to find CUDA. Some projects can't be run.")
    endif()
else()
    message("CUDA was disabled.")
endif()



###########################################################################################################
#                                           3rd Party Libraries                                           #
###########################################################################################################
get_3rd_party_libraries("extern")


###########################################################################################################
#                                           Project Source code                                           #
###########################################################################################################
add_subdirectory ("src")

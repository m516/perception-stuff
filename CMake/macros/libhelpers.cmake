macro (disable_if_cuda_not_found)
    #Check if CUDA is unavailable
    if(NOT CMAKE_CUDA_COMPILER)
        message("             Project can't be built without CUDA")
        return()
    endif()
endmacro()

macro (disable_if_opencv_not_found)
    #Check if opencv is unavailable
    if(NOT OpenCV_FOUND)
        message("             Project can't be built without OpenCV")
        return()
    endif()
endmacro()

macro (disable_if_pthread_not_found)
    #Check if thread library is unavailable
    if(NOT Threads_FOUND)
        message("             Project can't be built without Pthreads")
        return()
    endif()
endmacro()

macro (enforce_unix)
    #Check if this system isn't UNIX
    if (NOT UNIX)
        message("             Project can only be built for UNIX systems")
        return()
    endif ()
endmacro()

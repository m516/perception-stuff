# Every project is its own standalone application in a subfolder, 
# and they likely contain CMake scripts.
#
# This script uses a macro to automatically find and build all the algorithms 
# with CMakeLists.txtunder this folder.

include(${MACRO_DIRECTORY}/subdirlist.cmake)

SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})
FOREACH(subdir ${SUBDIRS})
    message("  Tool: ${subdir}")
    ADD_SUBDIRECTORY(${subdir})
ENDFOREACH()

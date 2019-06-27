#------------------------------------------------------------------------------
# Usage: find_package(SDL2 [REQUIRED] [COMPONENTS main])
#
# Sets variables:
#     SDL2_INCLUDE_DIRS
#     SDL2_LIBS
#     SDL2_DLLS
#------------------------------------------------------------------------------

include(FindPackageHandleStandardArgs)

# Check if "main" was specified as a component
set(_SDL2_use_main FALSE)

foreach(_SDL2_component ${SDL2_FIND_COMPONENTS})
    if(_SDL2_component STREQUAL "main")
        set(_SDL2_use_main TRUE)
    else()
        message(WARNING "Unrecognized component \"${_SDL2_component}\"")
    endif()
endforeach()

set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/../Extern/SDL2/include")

if(WIN32)
    find_path(SDL2_ROOT "include/SDL.h" PATHS "${CMAKE_CURRENT_LIST_DIR}/../Extern/SDL2" NO_DEFAULT_PATH)
    # Search for SDL2 Debug CMake build in Extern/SDL2/build
    if(SDL2_ROOT)
        if("${CMAKE_GENERATOR}" MATCHES "Win64")
            set(SDL2_LIBS "${SDL2_ROOT}/lib/x64/SDL2.lib")
            set(SDL2_DLLS "${SDL2_ROOT}/lib/x64/SDL2.dll")
            if(_SDL2_use_main)
                list(APPEND SDL2_LIBS "${SDL2_ROOT}/lib/x64/SDL2main.lib")
            endif()
        else()
            set(SDL2_LIBS "${SDL2_ROOT}/lib/x86/SDL2.lib")
            set(SDL2_DLLS "${SDL2_ROOT}/lib/x86/SDL2.dll")
            if(_SDL2_use_main)
                list(APPEND SDL2_LIBS "${SDL2_ROOT}/lib/x86/SDL2main.lib")
            endif()
        endif()
    endif()

    mark_as_advanced(SDL2_ROOT)
    find_package_handle_standard_args(SDL2 DEFAULT_MSG SDL2_INCLUDE_DIRS SDL2_LIBS SDL2_DLLS)
else()
#    find_path(SDL2_INCLUDE_DIRS SDL.h PATH_SUFFIXES SDL2)
    find_library(_SDL2_LIB SDL2)
    set(SDL2_LIBS ${SDL2})
    if(_SDL2_use_main)
        find_library(_SDL2main_LIB SDL2)
        list(APPEND SDL2_LIBS ${_SDL2main_LIB})
    endif()

    mark_as_advanced(SDL2_INCLUDE_DIRS _SDL2_LIB _SDL2main_LIB)
    find_package_handle_standard_args(SDL2 DEFAULT_MSG SDL2_INCLUDE_DIRS SDL2_LIBS)
endif()
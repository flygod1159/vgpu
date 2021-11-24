# CMake version
cmake_minimum_required (VERSION 3.14)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
	message(FATAL_ERROR "In-source builds are not supported. Please choose a different binary directory.")
	return()
endif()

# Use solution folders to organize projects
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Configure CMake global variables
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Project declaration
project (vgpu)

# Build version
set (VGPU_VERSION_MAJOR 0)
set (VGPU_VERSION_MINOR 1)
set (VGPU_VERSION_PATCH 0)
set (VGPU_VERSION ${VGPU_VERSION_MAJOR}.${VGPU_VERSION_MINOR}.${VGPU_VERSION_PATCH})
set (VGPU_VERSION_ALIAS "WIP")

execute_process(COMMAND git rev-list --count HEAD
    OUTPUT_VARIABLE VGPU_REVISION_ID
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

if ("${VGPU_REVISION_ID}" STREQUAL "")
    # We don't have any source control so just hard-code all of this information to empty
    set (VGPU_REVISION_ID 0)
    set (VGPU_SHORT_CHANGE_SET 0)
    set (VGPU_CHANGE_SET 0)
    set (VGPU_CHANGE_SET_DATE "")
else ()
    execute_process(COMMAND git rev-parse --short HEAD
        OUTPUT_VARIABLE VGPU_SHORT_CHANGE_SET
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    execute_process(COMMAND git rev-parse HEAD
        OUTPUT_VARIABLE VGPU_CHANGE_SET
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    execute_process(COMMAND git log -1 --abbrev=12 --date=format:%Y-%m-%d --pretty=format:%cd
        OUTPUT_VARIABLE VGPU_CHANGE_SET_DATE
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
endif ()

# Options
option(VGPU_BUILD_SHARED "Build vgpu as a shared library" ON)
option(VGPU_SAMPLES "Build samples" ON)

if (VGPU_BUILD_SHARED)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEV "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# Detect target platform
set(PLATFORM_WIN32 FALSE CACHE INTERNAL "")
set(PLATFORM_UWP FALSE CACHE INTERNAL "")
set(PLATFORM_ANDROID FALSE CACHE INTERNAL "")
set(PLATFORM_LINUX FALSE CACHE INTERNAL "")
set(PLATFORM_MACOS FALSE CACHE INTERNAL "")
set(PLATFORM_IOS FALSE CACHE INTERNAL "")
set(PLATFORM_TVOS FALSE CACHE INTERNAL "")
set(PLATFORM_EMSCRIPTEN FALSE CACHE INTERNAL "")

if(WIN32)
    if(${CMAKE_SYSTEM_NAME} STREQUAL "WindowsStore")
        set(PLATFORM_UWP TRUE CACHE INTERNAL "Target platform: Windows Store")
        set(PLATFORM_NAME "UWP" CACHE STRING "" FORCE)
        message(STATUS "Target platform: Universal Windows. SDK Version: " ${CMAKE_SYSTEM_VERSION})
    else ()
        set(PLATFORM_WIN32 TRUE CACHE INTERNAL "Target platform: Win32")
        set(PLATFORM_NAME "Win32"  CACHE STRING "" FORCE)
        message(STATUS "Target platform: Win32. SDK Version: " ${CMAKE_SYSTEM_VERSION})
    endif()
else()
    if(${CMAKE_SYSTEM_NAME} STREQUAL "Android")
        set(PLATFORM_ANDROID TRUE CACHE INTERNAL "Target platform: Android")
        set(PLATFORM_NAME "Android" CACHE STRING "" FORCE)
        message(STATUS "Target platform: Android")
    elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
        set(PLATFORM_LINUX TRUE CACHE INTERNAL "Target platform: Linux")
        set(PLATFORM_NAME "Linux" CACHE STRING "" FORCE)
        message(STATUS "Target Platform: Linux")
    elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
        if(IOS)
            set(PLATFORM_IOS TRUE CACHE INTERNAL "Target platform: iOS")
            set(PLATFORM_NAME "iOS" CACHE STRING "" FORCE)
            message(STATUS "Target Platform: iOS")
        else()
            set(PLATFORM_MACOS TRUE CACHE INTERNAL "Target platform: MacOS")
            set(PLATFORM_NAME "MacOS" CACHE STRING "" FORCE)
            message(STATUS "Target Platform: MacOS")
        endif()
    elseif(${CMAKE_SYSTEM_NAME} STREQUAL "iOS")
        set(PLATFORM_IOS TRUE CACHE INTERNAL "Target platform: iOS")
        set(PLATFORM_NAME "iOS" CACHE STRING "" FORCE)
        message(STATUS "Target Platform: iOS")
    elseif(${CMAKE_SYSTEM_NAME} STREQUAL "tvOS")
        set(PLATFORM_TVOS TRUE CACHE INTERNAL "Target platform: tvOS")
        set(PLATFORM_NAME "tvOS" CACHE STRING "" FORCE)
        message(STATUS "Target Platform: tvOS")
    elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
        set(PLATFORM_EMSCRIPTEN TRUE CACHE INTERNAL "Target platform: Emscripten")
        set(PLATFORM_NAME "Web" CACHE STRING "" FORCE)
        message(STATUS "Target Platform: Emscripten")
    else()
        message(FATAL_ERROR "Unsupported platform")
    endif()
endif()

# Define standard configurations
if( CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_CONFIGURATION_TYPES MATCHES "Debug;Dev;Release" )
	set(CMAKE_CONFIGURATION_TYPES "Debug;Dev;Release" CACHE STRING "List of supported configurations." FORCE)

    set(CMAKE_BUILD_TYPE Dev CACHE STRING "The default build type")
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES})

    # Copy settings
    set(CMAKE_EXE_LINKER_FLAGS_DEV ${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO} CACHE STRING "" FORCE)
	set(CMAKE_SHARED_LINKER_FLAGS_DEV ${CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO} CACHE STRING "" FORCE)
	set(CMAKE_STATIC_LINKER_FLAGS_DEV ${CMAKE_STATIC_LINKER_FLAGS_RELWITHDEBINFO} CACHE STRING "" FORCE)
	set(CMAKE_MODULE_LINKER_FLAGS_DEV ${CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO} CACHE STRING "" FORCE)
	set(CMAKE_CXX_FLAGS_DEV ${CMAKE_CXX_FLAGS_RELWITHDEBINFO} CACHE STRING "" FORCE)
	set(CMAKE_C_FLAGS_DEV ${CMAKE_C_FLAGS_RELWITHDEBINFO} CACHE STRING "" FORCE)
	set(CMAKE_CSharp_FLAGS_DEV ${CMAKE_CSharp_FLAGS_RELWITHDEBINFO} CACHE STRING "" FORCE)
	set(CMAKE_RC_FLAGS_DEV ${CMAKE_RC_FLAGS_RELWITHDEBINFO} CACHE STRING "" FORCE)

	mark_as_advanced(FORCE CMAKE_EXE_LINKER_FLAGS_DEV)
	mark_as_advanced(FORCE CMAKE_SHARED_LINKER_FLAGS_DEV)
	mark_as_advanced(FORCE CMAKE_STATIC_LINKER_FLAGS_DEV)
	mark_as_advanced(FORCE CMAKE_MODULE_LINKER_FLAGS_DEV)
	mark_as_advanced(FORCE CMAKE_CXX_FLAGS_DEV)
	mark_as_advanced(FORCE CMAKE_C_FLAGS_DEV)
	mark_as_advanced(FORCE CMAKE_CSharp_FLAGS_DEV)
	mark_as_advanced(FORCE CMAKE_RC_FLAGS_DEV)
endif()

# Install directories
set (INSTALL_BASE_INCLUDE_DIR include)
set (INSTALL_INCLUDE_DIR ${INSTALL_BASE_INCLUDE_DIR}/vgpu)
set (INSTALL_THIRDPARTY_DIR ${INSTALL_INCLUDE_DIR}/ThirdParty)

if (ANDROID)
    set (INSTALL_BIN_DIR bin)
    set (INSTALL_LIB_DIR lib)
    set (INSTALL_ARCHIVE_DIR lib)
else ()
    set (INSTALL_BIN_DIR bin)
    set (INSTALL_LIB_DIR bin)
    set (INSTALL_ARCHIVE_DIR lib)
endif ()

# ThirdParty
add_subdirectory(third_party)

# Source lists
add_library(vgpu
	# Public Headers
	include/vgpu.h
    # Internal Headers
	src/vgpu_driver.h
    # Source Files
	src/vgpu.c
    src/vgpu_driver_vulkan.cpp
    src/vgpu_driver_d3d12.cpp
)

target_include_directories(vgpu PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:${INSTALL_BASE_INCLUDE_DIR}>
)

if (VGPU_BUILD_SHARED)
    target_compile_definitions(vgpu PRIVATE VGPU_SHARED_LIBRARY=1 VGPU_EXPORTS=1)
endif()

if(WIN32 AND NOT DISABLE_D3D12)
    target_compile_definitions(vgpu PRIVATE VGPU_DRIVER_D3D12=1)
endif()

if(NOT EMSCRIPTEN)
    target_compile_definitions(vgpu PRIVATE VGPU_DRIVER_VULKAN=1)
    target_link_libraries(vgpu PRIVATE volk vma spirv-reflect)
endif()

# Compiler-specific setup
if(MSVC)
    # Set warning level
    target_compile_options(vgpu PRIVATE $<$<CONFIG:DEBUG>:/W3> $<$<NOT:$<CONFIG:DEBUG>>:/W4>)

    # Warnings as Errors Enabled
    target_compile_options(vgpu PRIVATE /WX)

    target_compile_options(vgpu PRIVATE /fp:fast)
    target_compile_options(vgpu PRIVATE /permissive- /JMC- /Zc:__cplusplus)
endif ()

if (VGPU_SAMPLES)
    add_subdirectory(samples)
endif ()

# Print current build configuration
message(STATUS "VGPU version ${VGPU_VERSION}")
message(STATUS "GIT Revision ID: ${VGPU_REVISION_ID}")
message(STATUS "GIT Short ChangeSet: ${VGPU_SHORT_CHANGE_SET}")
message(STATUS "GIT ChangeSet: ${VGPU_CHANGE_SET}")
message(STATUS "GIT ChangeSet Date: ${VGPU_CHANGE_SET_DATE}")

if (VGPU_BUILD_SHARED)
    message(STATUS "  Library         SHARED")
else ()
    message(STATUS "  Library         STATIC")
endif ()

message(STATUS "  Samples         ${VGPU_SAMPLES}")

# Install files
# README.md and license
install (FILES
	${CMAKE_CURRENT_SOURCE_DIR}/README.md
	${CMAKE_CURRENT_SOURCE_DIR}/LICENSE
	DESTINATION .
)

install(TARGETS vgpu
    EXPORT vgpu
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

if (NOT ANDROID)
    # DLLs
    if(WIN32 AND NOT (WINDOWS_STORE))
	    #set(DXIL_LIBRARY "${ALIMER_THIRD_PARTY_DIR}/dxc/bin/win-x64/dxil.dll")
	    #set(DXCOMPILER_LIBRARY "${ALIMER_THIRD_PARTY_DIR}/dxc/bin/win-x64/dxcompiler.dll")
    
	    #file (COPY ${DXIL_LIBRARY} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
	    #file (COPY ${DXCOMPILER_LIBRARY} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    
	    #install (FILES
        #    ${DXIL_LIBRARY}
		#    ${DXCOMPILER_LIBRARY}
		#    DESTINATION ${INSTALL_BIN_DIR}
	    #)
    endif ()
endif ()

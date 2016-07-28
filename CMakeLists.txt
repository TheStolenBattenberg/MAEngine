cmake_minimum_required (VERSION 3.5)
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

include(ExternalProject)

# Set variables
set (LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Libraries)

set (BULLET_DIR ${LIBRARY_DIR}/bullet3)
set (BULLET_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/bullet3)
set (BULLET_LIBRARY_DIR ${BULLET_BINARY_DIR}/lib/$<CONFIG>/)

# Build bullet
ExternalProject_Add (Bullet
    SOURCE_DIR ${BULLET_DIR}
    BINARY_DIR ${BULLET_BINARY_DIR}
    CMAKE_ARGS
        -DBUILD_OPENGL3_DEMOS=OFF
        -DBUILD_BULLET3=OFF
        -DBUILD_BULLET2_DEMOS=OFF
        -DBUILD_CPU_DEMOS=OFF
        -DBUILD_EXTRAS=OFF
        -DBUILD_UNIT_TESTS=OFF
        -DCMAKE_DEBUG_POSTFIX=
        -DCMAKE_INSTALL_PREFIX=
    BUILD_COMMAND
        ${CMAKE_COMMAND}
        --build .
        --config $<CONFIG>
    )

# Function to set up file folders that follow directory structure
function(assign_source_groups files relative_to)
    foreach (_source IN ITEMS ${${files}})
        file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}/${relative_to}" "${_source}")
        get_filename_component (_source_path "${_source_rel}" PATH)
        string (REPLACE "/" "\\" _source_path_msvc "${_source_path}")
        source_group ("Source\\${_source_path_msvc}" FILES "${_source}")
    endforeach ()
endfunction(assign_source_groups)

include_directories ("Libraries/recastnavigation/Recast/Include"
                     "Libraries/recastnavigation/DebugUtils/Include"
                     "Libraries/recastnavigation/Detour/Include"
                     "Libraries/recastnavigation/DetourCrowd/Include"
                     "Libraries/recastnavigation/DetourTileCache/Include"
                     "Libraries/bullet3/src"
                     "Libraries/FMOD/inc"
                     "$ENV{DXSDK_DIR}/Include"
                     "Specifications"
                     "MAE"
                     )

project (Recast)
file (GLOB_RECURSE RECAST_SOURCES
    "Libraries/recastnavigation/DebugUtils/*.cpp" "Libraries/recastnavigation/DebugUtils/*.h"
    "Libraries/recastnavigation/Detour/*.cpp" "Libraries/recastnavigation/Detour/*.h"
    "Libraries/recastnavigation/DetourCrowd/*.cpp" "Libraries/recastnavigation/DetourCrowd/*.h"
    "Libraries/recastnavigation/DetourTileCache/*.cpp" "Libraries/recastnavigation/DetourTileCache/*.h"
    "Libraries/recastnavigation/Recast/*.cpp" "Libraries/recastnavigation/Recast/*.h"
    )
assign_source_groups (RECAST_SOURCES "Libraries/recastnavigation")
add_library (Recast STATIC ${RECAST_SOURCES})

project (GMLAPI)
add_definitions(-D_SCL_SECURE_NO_WARNINGS -DNOMINMAX)
file (GLOB_RECURSE GMLAPI_SOURCES "MAE/GMLAPI/*.cpp" "MAE/GMLAPI/*.h")
assign_source_groups (GMLAPI_SOURCES "MAE/GMLAPI")
add_library (GMLAPI SHARED ${GMLAPI_SOURCES})
target_link_libraries (GMLAPI MAE)

# Copy DLL to Game Maker Project

add_custom_command (TARGET GMLAPI POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:GMLAPI> "${CMAKE_SOURCE_DIR}/GML/MAE.gmx/datafiles/MAE.dll"
    )

add_custom_command (TARGET GMLAPI POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:GMLAPI> "${CMAKE_SOURCE_DIR}/GML/Extension/MAE.dll"
    )

add_custom_command (TARGET GMLAPI POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:GMLAPI> "${CMAKE_SOURCE_DIR}/GML/MAE.gmx/extensions/MAE/Assets/datafiles/MAE.dll"
    )

project (MAE)
add_definitions(-D_SCL_SECURE_NO_WARNINGS -DNOMINMAX)
file (GLOB_RECURSE MAE_SOURCES "MAE/MAE/*.cpp" "MAE/MAE/*.h")
assign_source_groups (MAE_SOURCES "MAE/MAE")
add_library (MAE STATIC ${MAE_SOURCES})
add_dependencies (MAE Bullet)
target_link_libraries (MAE Recast
    ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/FMOD/lib/fmod_vc.lib
    $ENV{DXSDK_DIR}Lib/x86/d3dx9.lib
    $ENV{DXSDK_DIR}Lib/x86/d3d9.lib
    ${BULLET_LIBRARY_DIR}BulletCollision.lib
    ${BULLET_LIBRARY_DIR}BulletDynamics.lib
    ${BULLET_LIBRARY_DIR}LinearMath.lib
    )

# Force static linkage of MSVC runtime
foreach (flag_var
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
   if (${flag_var} MATCHES "/MD")
      string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
   endif (${flag_var} MATCHES "/MD")
endforeach (flag_var)


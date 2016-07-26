cmake_minimum_required (VERSION 3.5)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED 11)

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
project (Bullet)
file (GLOB_RECURSE BULLET_SOURCES
    "Libraries/bullet3/src/btBulletCollisionCommon.h" "Libraries/bullet3/src/btBulletDynamicsCommon.h"
    "Libraries/bullet3/src/BulletCollision/*.cpp" "Libraries/bullet3/src/BulletCollision/*.h"
    "Libraries/bullet3/src/BulletDynamics/*.cpp" "Libraries/bullet3/src/BulletDynamics/*.h"
    "Libraries/bullet3/src/LinearMath/*.cpp" "Libraries/bullet3/src/LinearMath/*.h"
    )
assign_source_groups (BULLET_SOURCES "Libraries/bullet3/src")
add_library (Bullet STATIC ${BULLET_SOURCES})

project (Recast)
file (GLOB_RECURSE RECAST_SOURCES "Libraries/recastnavigation/*.cpp" "Libraries/recastnavigation/*.h")
assign_source_groups (RECAST_SOURCES "Libraries/recastnavigation")
add_library (Recast STATIC ${RECAST_SOURCES})

project (GMLAPI)
file (GLOB_RECURSE GMLAPI_SOURCES "MAE/GMLAPI/*.cpp" "MAE/GMLAPI/*.h")
assign_source_groups (GMLAPI_SOURCES "MAE/GMLAPI")
add_library (GMLAPI SHARED ${GMLAPI_SOURCES})
target_link_libraries (GMLAPI MAE)
add_custom_command (TARGET GMLAPI POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:GMLAPI> "${CMAKE_SOURCE_DIR}/GML/MAE.gmx/datafiles/MAE.dll"
    )

project (MAE)
file (GLOB_RECURSE MAE_SOURCES "MAE/MAE/*.cpp" "MAE/MAE/*.h")
assign_source_groups (MAE_SOURCES "MAE/MAE")
add_library (MAE STATIC ${MAE_SOURCES})
target_link_libraries (MAE Recast Bullet
    ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/FMOD/lib/fmod_vc.lib
    $ENV{DXSDK_DIR}/Lib/x86/d3dx9.lib
    $ENV{DXSDK_DIR}/Lib/x86/d3d9.lib
    )

# Force static linkage of MSVC runtime
foreach (flag_var
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
   if (${flag_var} MATCHES "/MD")
      string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
   endif (${flag_var} MATCHES "/MD")
endforeach (flag_var)


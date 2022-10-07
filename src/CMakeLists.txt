# CMakeList.txt : CMake project for Framework3D, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12)

set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_RELWITHDEBINFO_POSTFIX rd)
set(CMAKE_MINSIZEREL_POSTFIX s)

if(WIN32)       
    set(FRAMEWORK_SOURCE_FILES
        "${FRAMEWORK_SOURCE_DIR}/main.cpp"
        "${FRAMEWORK_INCLUDE_DIR}/Framework3D.h"
    )

	set(VERTEX_SHADERS 
		"${SHADER_DIR}/vertex.hlsl"
	)

	set(PIXEL_SHADERS
		"${SHADER_DIR}/pixel.hlsl"
	)

	set(SHADERS
		${VERTEX_SHADERS}
		${PIXEL_SHADERS}
	)

	source_group("Resources\\Shaders" FILES ${SHADERS})

	set_source_files_properties(${VERTEX_SHADERS}
		PROPERTIES 
			VS_SHADER_TYPE Vertex
			VS_SETTINGS "ExcludedFromBuild=true"
	)

	set_source_files_properties(${PIXEL_SHADERS}
		PROPERTIES 
			VS_SHADER_TYPE Pixel
			VS_SETTINGS "ExcludedFromBuild=true"
	)	

    if(WIN32 AND ${CMAKE_GENERATOR} MATCHES "Visual Studio.*")
        set(D3D12_SAMPLE_SOURCE_FILES ${D3D12_SAMPLE_SOURCE_FILES} Framework3D.natvis)
    endif()

    # Add source to this project's executable.
    add_executable(Framework3D ${FRAMEWORK_SOURCE_FILES}) # ${SHADER_DIR}

	set_target_properties(
        Framework3D PROPERTIES

        CXX_EXTENSIONS OFF
        # Use C++14
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON

        OUTPUT_NAME "Framework"
    )

    target_include_directories(
        Framework3D PUBLIC

        ${FRAMEWORK_INCLUDE_DIR}
    )

    target_link_libraries(
        Framework3D

		PUBLIC d3d12.lib
		PUBLIC dxgi.lib
		PUBLIC dxguid.lib
		PUBLIC Shlwapi.lib
    )

    # Visual Studio specific settings
    if(${CMAKE_GENERATOR} MATCHES "Visual Studio.*")
        # Use Unicode instead of multibyte set
        add_compile_definitions(UNICODE _UNICODE)
            
        # Set VmaSample as startup project
        set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "Framework3D")
            
        # Enable multithreaded compiling
        target_compile_options(Framework3D PRIVATE "/MP")

        # Set working directory for Visual Studio debugger
        # TODO - parametarise the build directory!
        set_target_properties(
            Framework3D
            PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/build"
        )
    endif()
else()
    message(STATUS "D3D12Sample application is not supported on UNIX-based platforms.")
endif()



# TODO: Add tests and install targets if needed.

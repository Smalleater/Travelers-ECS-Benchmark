cmake_minimum_required(VERSION 3.28)

project(Benchmark)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB SRC_FILES src/*.cpp)
add_executable(Benchmark ${SRC_FILES})

target_include_directories(Benchmark 
	PRIVATE 
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Benchmark PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/tra_ecs.lib)

target_compile_features(Benchmark PRIVATE cxx_std_17)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    file(GLOB DLL_FILES "${CMAKE_CURRENT_SOURCE_DIR}/dll/debug/*.dll")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    file(GLOB DLL_FILES "${CMAKE_CURRENT_SOURCE_DIR}/dll/release/*.dll")
endif()

if(DLL_FILES)
    add_custom_command(TARGET Benchmark POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${DLL_FILES} $<TARGET_FILE_DIR:Benchmark>
        COMMENT "Copie des DLLs vers le répertoire de sortie"
    )
endif()

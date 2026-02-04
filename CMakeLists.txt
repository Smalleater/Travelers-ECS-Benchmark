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

target_compile_features(Benchmark PRIVATE cxx_std_17)

if(WIN32)
    add_library(tra_ecs SHARED IMPORTED)
    set_target_properties(tra_ecs PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/dll/release/tra_ecs.dll
        IMPORTED_IMPLIB  ${CMAKE_CURRENT_SOURCE_DIR}/lib/tra_ecs.lib
    )

    file(GLOB DLL_FILES "${CMAKE_CURRENT_SOURCE_DIR}/dll/release/*.dll")
else()
    add_library(tra_ecs SHARED IMPORTED)
    set_target_properties(tra_ecs PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/dll/release/libtra_ecs.so
    )

    file(GLOB DLL_FILES "${CMAKE_CURRENT_SOURCE_DIR}/dll/release/*.so")
endif()

target_link_libraries(Benchmark PRIVATE tra_ecs)

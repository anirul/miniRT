cmake_minimum_required(VERSION 3.14)

project(minirt
	DESCRIPTION "mini real-time raytracing"
	LANGUAGES CXX)

# Set standard.
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# External packages
find_package(GLEW CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)

add_subdirectory(sources)

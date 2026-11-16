cmake_minimum_required(VERSION 3.16)
project(VisualizadorOrdenamientos LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Deja que dependencias antiguas (FreeType) se configuren con CMake 4
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

# Descarga y compila SFML automáticamente
include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
set(BUILD_SHARED_LIBS OFF)    # enlaza estático: un solo ejecutable
set(SFML_BUILD_AUDIO OFF)     # no usamos sonido: se compila más rápido
set(SFML_BUILD_NETWORK OFF)   # ni red
FetchContent_MakeAvailable(SFML)

add_executable(visualizador
    src/main.cpp
    src/Utilidades.cpp
    src/BubbleSort.cpp
)
target_include_directories(visualizador PRIVATE include)
target_link_libraries(visualizador PRIVATE SFML::Graphics)
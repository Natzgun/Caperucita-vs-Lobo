cmake_minimum_required(VERSION 3.28)
project(Caperucita LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

set(HEADERS includes)
set(SOURCES
  src/AStar.cc
  src/Character.cc
  src/Graph.cc
  src/Caperucita.cc
  src/Lobo.cc
  src/Terrain.cc
)

add_executable(sfml-game src/main.cc ${SOURCES} ${HEADERS})

target_include_directories(sfml-game PRIVATE ${CMAKE_SOURCE_DIR}/includes)
target_link_libraries(sfml-game PRIVATE sfml-graphics sfml-audio)
target_compile_features(sfml-game  PRIVATE cxx_std_17)

if(WIN32)
  add_custom_command(
        TARGET sfml-game
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()

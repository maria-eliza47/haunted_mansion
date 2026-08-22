cmake_minimum_required(VERSION 3.26)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
# for now, the project name is used as the executable name
set(MAIN_PROJECT_NAME "oop")
set(MAIN_EXECUTABLE_NAME "${MAIN_PROJECT_NAME}")


project(${MAIN_PROJECT_NAME})
# set(CMAKE_PROJECT_VERSION_MAJOR 0)
# set(CMAKE_PROJECT_VERSION_MINOR 0)
# set(CMAKE_PROJECT_VERSION_PATCH 1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Options.cmake)
include(cmake/CompilerFlags.cmake)
include(cmake/CopyHelper.cmake)

###############################################################################

# external dependencies with FetchContent
include(FetchContent)

set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG        v3.11.3
        GIT_SHALLOW    1
)

FetchContent_MakeAvailable(nlohmann_json)

###############################################################################

# external dependencies with find_package

# find_package(Threads REQUIRED)

###############################################################################

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing name here
add_executable(${MAIN_EXECUTABLE_NAME}
        main.cpp
        Header/Room.cpp
        Header/Player.cpp
        Header/Ghost.cpp
        Header/Mansion.cpp
        Header/Item.cpp
        Header/Game.h
        Header/Game.cpp
        Header/DataLoader.h
        Header/DataLoader.cpp
        Header/UI.h
        Header/UI.cpp
        Header/Interactions/Interaction.h
        Header/Interactions/Interaction.cpp
        Header/Interactions/ItemInteraction.h
        Header/Interactions/ItemInteraction.cpp
        Header/Interactions/GhostInteraction.h
        Header/Interactions/GhostInteraction.cpp
        Header/Interactions/RoomInteraction.h
        Header/Interactions/RoomInteraction.cpp
        Header/Exceptions/GameException.h
        Header/Exceptions/InvalidActionException.h
        Header/Exceptions/MissingItemException.h
        Header/Exceptions/RoomLockedException.h
        Header/Exceptions/DataParseException.h
        Header/Interactions/CasperInteraction.h
        Header/Interactions/CasperInteraction.cpp
        Header/Interactions/RitualInteraction.h
        Header/Interactions/RitualInteraction.cpp
)
include_directories(${CMAKE_SOURCE_DIR}/Header)
# NOTE: Add all defined targets (e.g. executables, libraries, etc. )
# NOTE: RUN_SANITIZERS is optional, if it's not present it will default to true
set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ${MAIN_EXECUTABLE_NAME})
# set_compiler_flags(TARGET_NAMES ${MAIN_EXECUTABLE_NAME} ${FOO} ${BAR})
# where ${FOO} and ${BAR} represent additional executables or libraries
# you want to compile with the set compiler flags

###############################################################################

# use SYSTEM so cppcheck and clang-tidy do not report warnings from these directories
target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE ${nlohmann_json_SOURCE_DIR}/include)
target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE nlohmann_json::nlohmann_json)

###############################################################################

# copy binaries to "bin" folder; these are uploaded as artifacts on each release
# DESTINATION_DIR is set as "bin" in cmake/Options.cmake:6
install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

copy_files(FILES tastatura.txt DIRECTORY data COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})


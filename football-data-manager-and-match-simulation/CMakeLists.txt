# CMakeList.txt : CMake project for football-data-manager-and-match-simulation, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (football-data-manager-and-match-simulation  "source/main.cpp" "source/data_manager.cpp" "source/team_data.cpp" "source/player_data.cpp" "source/func.cpp")
target_include_directories (football-data-manager-and-match-simulation PRIVATE "include/")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET football-data-manager-and-match-simulation PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

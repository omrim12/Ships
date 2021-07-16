cmake_minimum_required(VERSION 3.19)
project(ex3_Boats_simulation)

set(CMAKE_CXX_STANDARD 11)

file(GLOB EX3_SRC
        "Controller/*.h"
        "Controller/*.cpp"
        "Model/*.h"
        "Model/*.cpp"
        "View/*.h"
        "View/*.cpp"
        )

add_executable(EX3 main_lobby.cpp ${EX3_SRC})

#add_executable(ex3_Boats_simulation ships_simulation-main/src/Model/Model.cpp ships_simulation-main/src/Model/Model.h ships_simulation-main/src/Model/gameObj.cpp ships_simulation-main/src/Controller/Terminal.cpp ships_simulation-main/src/Controller/Terminal.h ships_simulation-main/src/View/View.cpp ships_simulation-main/src/View/View.h ships_simulation-main/src/Model/Boat.cpp)
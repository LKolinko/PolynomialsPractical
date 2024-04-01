cmake_minimum_required(VERSION 3.26.1)
project(PolinomPractice)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(CMAKE_CXX_STANDARD 17)

add_executable(PolinomPractice main.cpp
        Polinom.cpp
        Polinom.h
        list.h
        FSM.cpp
        FSM.h
        App.cpp
        App.h
        EventHandler.cpp
        EventHandler.h
        Singleton.h
        Screen.h
        Locale.h
        Button.h
        RoundedRectangle.cpp
        Button.cpp
        TextBox.cpp
        TextBox.cpp
        TextBox.cpp
        Table.cpp)

target_link_libraries(PolinomPractice PRIVATE sfml-graphics)
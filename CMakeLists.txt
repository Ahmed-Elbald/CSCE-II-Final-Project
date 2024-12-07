cmake_minimum_required(VERSION 3.29)
project(CSCE_II_Final_Project)

# Enable Qt's automatic handling of moc, uic, and rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)

# Specify the path to the Qt installation
set(CMAKE_PREFIX_PATH "/Users/ayman/Qt/6.7.2/macos")

# Find required Qt modules
find_package(Qt6 COMPONENTS Core Gui Widgets Multimedia REQUIRED)

# Add the source files for the project
add_executable(CSCE_II_Final_Project
        game.cpp
        game.h

        main.cpp

        player.cpp
        player.h

        sound.cpp
        sound.h

        spritesheet.cpp
        spritesheet.h

        resources.qrc

        settingsmanager.cpp
        settingsmanager.h

        block.h
        block.cpp

        trap.h
        trap.cpp

        state.cpp
        state.h

        level.h
        level.cpp

        shieldeffect.cpp
        shieldeffect.h

        utils.cpp
        utils.h

        coin.cpp
        coin.h

        coinsdisplay.cpp
        coinsdisplay.h

        enemy.cpp
        enemy.h

        lifedisplay.h
        lifedisplay.cpp

        healthpotion.cpp
        healthpotion.h

        soundplayer.h
        soundplayer.cpp

        startingmenu.h
        startingmenu.cpp

        lifedisplay.cpp
        lifedisplay.h

        score.cpp
        score.h


)

# Link the Qt libraries to the target
target_link_libraries(CSCE_II_Final_Project
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Multimedia
)
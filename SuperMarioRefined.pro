QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    block.cpp \
    coinsdisplay.cpp \
    game.cpp \
    level.cpp \
    life.cpp \
    main.cpp \
    player.cpp \
    score.cpp \
    settingsmanager.cpp \
    shieldeffect.cpp \
    sound.cpp \
    spritesheet.cpp \
    state.cpp \
    trap.cpp \
    utils.cpp \
    coin.cpp

HEADERS += \
    block.h \
    coinsdisplay.h \
    game.h \
    level.h \
    life.h \
    player.h \
    score.h \
    settingsmanager.h \
    shieldeffect.h \
    sound.h \
    spritesheet.h \
    state.h \
    trap.h \
    utils.h \
    coin.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

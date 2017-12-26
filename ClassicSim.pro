QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    Event/Event.cpp \
    Engine/Engine.cpp \
    Event/Events/EncounterEnd.cpp \
    Event/Events/EncounterStart.cpp \
    Queue/Queue.cpp \
    Character/Race/Races/Human.cpp \
    Character/Race/Races/Dwarf.cpp \
    Character/Race/Races/NightElf.cpp \
    Character/Race/Races/Gnome.cpp \
    Character/Race/Races/Orc.cpp \
    Character/Race/Races/Undead.cpp \
    Character/Race/Races/Tauren.cpp \
    Character/Race/Races/Troll.cpp \
    Character/Class/Classes/Warrior.cpp \
    Character/Class/Classes/Priest.cpp \
    Character/Class/Classes/Rogue.cpp \
    Character/Class/Classes/Mage.cpp \
    Character/Class/Classes/Druid.cpp \
    Character/Class/Classes/Hunter.cpp \
    Character/Class/Classes/Warlock.cpp \
    Character/Class/Classes/Shaman.cpp \
    Character/Class/Classes/Paladin.cpp \
    Character/Character.cpp \
    Event/Events/PlayerAction.cpp

HEADERS += \
    Queue/Queue.h \
    Event/Event.h \
    Engine/Engine.h \
    Event/Events/EncounterEnd.h \
    Event/Events/EncounterStart.h \
    Character/Character.h \
    Character/Race/Race.h \
    Character/Race/Races/Human.h \
    Character/Race/Races/Dwarf.h \
    Character/Race/Races/NightElf.h \
    Character/Race/Races/Gnome.h \
    Character/Race/Races/Orc.h \
    Character/Race/Races/Undead.h \
    Character/Race/Races/Tauren.h \
    Character/Race/Races/Troll.h \
    Character/Class/Class.h \
    Character/Class/Classes/Warrior.h \
    Character/Class/Classes/Priest.h \
    Character/Class/Classes/Rogue.h \
    Character/Class/Classes/Mage.h \
    Character/Class/Classes/Druid.h \
    Character/Class/Classes/Hunter.h \
    Character/Class/Classes/Warlock.h \
    Character/Class/Classes/Shaman.h \
    Character/Class/Classes/Paladin.h \
    Event/Events/PlayerAction.h

INCLUDEPATH = C:\C++\ClassicSim\Engine \
    C:\C++\ClassicSim\Event \
    C:\C++\ClassicSim\Event\Events \
    C:\C++\ClassicSim\Queue \
    C:\C++\ClassicSim\Character \
    C:\C++\ClassicSim\Character\Race \
    C:\C++\ClassicSim\Character\Race\Races \
    C:\C++\ClassicSim\Character\Class \
    C:\C++\ClassicSim\Character\Class\Classes

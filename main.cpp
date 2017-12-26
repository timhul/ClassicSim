#include <QCoreApplication>
#include <iostream>
#include "Engine.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Engine engine;
    engine.test_queue();
    engine.test_character_creation();

    return a.exec();
}

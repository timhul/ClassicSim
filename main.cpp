#include <QCoreApplication>
#include <iostream>
#include "Engine.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Engine engine;
    engine.test_queue();

    return a.exec();
}

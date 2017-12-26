#include <QCoreApplication>
#include <iostream>
#include "Engine.h"
#include "Test.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Test test;
    test.test_character_creation();
    test.test_queue();

    return a.exec();
}

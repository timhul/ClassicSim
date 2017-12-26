#include <QCoreApplication>
#include <iostream>
#include "Engine.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::cout << "Hello, world!";

    return a.exec();
}

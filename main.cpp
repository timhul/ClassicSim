#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickImageProvider>

#include "Engine.h"
#include "Test.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.addImageProvider(QLatin1String("graphics"), new QQuickImageProvider(QQuickImageProvider::Image));
    engine.clearComponentCache();
    engine.load(QUrl(QStringLiteral("qrc:/QML/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

//    Test test;
//    test.test_all();

    return app.exec();
}

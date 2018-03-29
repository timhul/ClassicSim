#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickImageProvider>
#include <QQmlContext>

#include "GUIControl.h"

#include "Engine.h"
#include "Test.h"
#include "Equipment.h"
#include "Target.h"
#include "CombatRoll.h"
#include "Talents.h"

#include "Dwarf.h"
#include "Gnome.h"
#include "Human.h"
#include "NightElf.h"
#include "Orc.h"
#include "Tauren.h"
#include "Troll.h"
#include "Undead.h"

#include "Druid.h"
#include "Hunter.h"
#include "Mage.h"
#include "Paladin.h"
#include "Priest.h"
#include "Rogue.h"
#include "Shaman.h"
#include "Warlock.h"
#include "Warrior.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    Test test;
    test.test_all();

    QGuiApplication app(argc, argv);

    Engine* engine = new Engine();
    Equipment* equipment = new Equipment();
    Target* target = new Target(63);
    Random* random = new Random(0, 9999);
    CombatRoll* combat = new CombatRoll(target, random);

    GUIControl* gui_control = new GUIControl();

    Race* orc = new Orc();
    Warrior* warrior = new Warrior(orc, engine, equipment, combat);

    QQmlApplicationEngine qml_engine;
    QQmlContext* context = qml_engine.rootContext();

    context->setContextProperty("warrior", warrior);
    context->setContextProperty("character", gui_control);
    context->setContextProperty("talents", gui_control);

    qml_engine.clearComponentCache();
    qml_engine.load(QUrl(QStringLiteral("qrc:/QML/main.qml")));
    if (qml_engine.rootObjects().isEmpty())
        return -1;


    return app.exec();
}

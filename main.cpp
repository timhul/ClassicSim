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
    Talents* talents = new Talents();

    GUIControl* gui_control = new GUIControl(talents);

    Race* dwarf = new Dwarf();
    Race* gnome = new Gnome();
    Race* human = new Human();
    Race* nelf = new NightElf();
    Race* orc = new Orc();
    Race* tauren = new Tauren();
    Race* troll = new Troll();
    Race* undead = new Undead();

    Druid* druid = new Druid(nelf, engine, equipment, combat, talents);
    Hunter* hunter = new Hunter(dwarf, engine, equipment, combat, talents);
    Mage* mage = new Mage(gnome, engine, equipment, combat, talents);
    Paladin* paladin = new Paladin(human, engine, equipment, combat, talents);
    Priest* priest = new Priest(undead, engine, equipment, combat, talents);
    Rogue* rogue = new Rogue(undead, engine, equipment, combat, talents);
    Shaman* shaman = new Shaman(tauren, engine, equipment, combat, talents);
    Warlock* warlock = new Warlock(troll, engine, equipment, combat, talents);
    Warrior* warrior = new Warrior(orc, engine, equipment, combat, talents);

    QQmlApplicationEngine qml_engine;
    QQmlContext* context = qml_engine.rootContext();

    context->setContextProperty("druid", druid);
    context->setContextProperty("hunter", hunter);
    context->setContextProperty("mage", mage);
    context->setContextProperty("paladin", paladin);
    context->setContextProperty("priest", priest);
    context->setContextProperty("rogue", rogue);
    context->setContextProperty("shaman", shaman);
    context->setContextProperty("warlock", warlock);
    context->setContextProperty("warrior", warrior);
    context->setContextProperty("character", gui_control);
    context->setContextProperty("talents", gui_control);

    qml_engine.clearComponentCache();
    qml_engine.load(QUrl(QStringLiteral("qrc:/QML/main.qml")));
    if (qml_engine.rootObjects().isEmpty())
        return -1;


    return app.exec();
}

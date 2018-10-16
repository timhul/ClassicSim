#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickImageProvider>
#include <QQmlContext>

#include "GUIControl.h"
#include "PieChart.h"
#include "PieChartModel.h"
#include "EnchantName.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    Test test;
    test.test_all();

    QApplication app(argc, argv);
    auto* gui_control = new GUIControl();

    QQmlApplicationEngine qml_engine;
    QQmlContext* context = qml_engine.rootContext();

    context->setContextProperty("character", gui_control);
    context->setContextProperty("talents", gui_control);
    context->setContextProperty("equipment", gui_control);
    context->setContextProperty("statistics", gui_control);
    context->setContextProperty("settings", gui_control);
    context->setContextProperty("itemModel", gui_control->get_item_model());
    context->setContextProperty("itemTypeFilterModel", gui_control->get_item_type_filter_model());
    context->setContextProperty("activeStatFilterModel", gui_control->get_active_stat_filter_model());
    context->setContextProperty("availableStatFilterModel", gui_control->get_available_stat_filter_model());
    context->setContextProperty("weaponModel", gui_control->get_weapon_model());
    context->setContextProperty("buffModel", gui_control->get_buff_model());
    context->setContextProperty("debuffModel", gui_control->get_debuff_model());
    context->setContextProperty("rotationModel", gui_control->get_rotation_model());
    context->setContextProperty("pieChart", new PieChart());
    context->setContextProperty("pieChartModel", new PieChartModel());

    qmlRegisterType<WeaponSorting>("WeaponSort", 1, 0, "WeaponSort");
    qmlRegisterType<ItemSorting>("ItemSort", 1, 0, "ItemSort");
    qmlRegisterType<EnchantName>("EnchantName", 1, 0, "EnchantName");

    qml_engine.clearComponentCache();
    qml_engine.load(QUrl(QStringLiteral("qrc:/QML/main.qml")));
    if (qml_engine.rootObjects().isEmpty())
        return -1;


    return QApplication::exec();
}

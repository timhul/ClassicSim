#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickImageProvider>
#include <QQmlContext>

#include "AvailableFactions.h"
#include "EnchantName.h"
#include "EnchantModel.h"
#include "GUIControl.h"
#include "PieChart.h"
#include "PieChartModel.h"
#include "SimOption.h"

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
    context->setContextProperty("buffBreakdownModel", gui_control->get_buff_breakdown_model());
    context->setContextProperty("debuffBreakdownModel", gui_control->get_debuff_breakdown_model());
    context->setContextProperty("meleeDamageBreakdownModel", gui_control->get_dmg_breakdown_model());
    context->setContextProperty("meleeAvoidanceBreakdownModel", gui_control->get_dmg_breakdown_avoidance_model());
    context->setContextProperty("procBreakdownModel", gui_control->get_proc_breakdown_model());
    context->setContextProperty("resourceBreakdownModel", gui_control->get_resource_breakdown_model());
    context->setContextProperty("simScaleModel", gui_control->get_sim_scale_model());
    context->setContextProperty("scaleResultModel", gui_control->get_scale_result_model());
    context->setContextProperty("mhTempEnchantModel", gui_control->get_mh_temporary_enchant_model());
    context->setContextProperty("ohTempEnchantModel", gui_control->get_oh_temporary_enchant_model());
    context->setContextProperty("headLegsEnchantModel", gui_control->get_head_legs_enchant_model());
    context->setContextProperty("pieChart", new PieChart());
    context->setContextProperty("pieChartModel", new PieChartModel());

    qmlRegisterType<WeaponSorting>("WeaponSort", 1, 0, "WeaponSort");
    qmlRegisterType<ItemSorting>("ItemSort", 1, 0, "ItemSort");
    qmlRegisterType<EnchantName>("EnchantName", 1, 0, "EnchantName");
    qmlRegisterType<AvailableFactions>("Faction", 1, 0, "Faction");
    qmlRegisterType<SimOption>("SimOption", 1, 0, "SimOption");
    qmlRegisterType<BuffBreakdownSorting>("BuffBreakdownSorting", 1, 0, "BuffBreakdownSorting");
    qmlRegisterType<MeleeDamageBreakdownSorting>("MeleeDamageBreakdownSorting", 1, 0, "MeleeDamageBreakdownSorting");
    qmlRegisterType<MeleeDamageAvoidanceBreakdownSorting>("MeleeDamageAvoidanceBreakdownSorting", 1, 0, "MeleeDamageAvoidanceBreakdownSorting");
    qmlRegisterType<ProcBreakdownSorting>("ProcBreakdownSorting", 1, 0, "ProcBreakdownSorting");
    qmlRegisterType<ResourceBreakdownSorting>("ResourceBreakdownSorting", 1, 0, "ResourceBreakdownSorting");
    qmlRegisterType<ScaleResultSorting>("ScaleResultSorting", 1, 0, "ScaleResultSorting");

    qml_engine.clearComponentCache();
    qml_engine.load(QUrl(QStringLiteral("qrc:/QML/main.qml")));
    if (qml_engine.rootObjects().isEmpty())
        return -1;

    return QApplication::exec();
}

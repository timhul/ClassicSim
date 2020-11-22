#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickImageProvider>

#include "ActiveItemStatFilterModel.h"
#include "AvailableFactions.h"
#include "AvailableItemStatFilterModel.h"
#include "BuffModel.h"
#include "ContentPhase.h"
#include "DamageMetersModel.h"
#include "DebuffBreakdownModel.h"
#include "DebuffModel.h"
#include "EnchantModel.h"
#include "EnchantName.h"
#include "EngineBreakdownModel.h"
#include "GUIControl.h"
#include "ItemModel.h"
#include "ItemTypeFilterModel.h"
#include "MeleeDamageAvoidanceBreakdownModel.h"
#include "MeleeDamageBreakdownModel.h"
#include "ProcBreakdownModel.h"
#include "RandomAffixModel.h"
#include "ResourceBreakdownModel.h"
#include "RotationConditionsModel.h"
#include "RotationExecutorBreakdownModel.h"
#include "RotationExecutorListModel.h"
#include "RotationModel.h"
#include "ScaleResultModel.h"
#include "SimOption.h"
#include "SimScaleModel.h"
#include "TemplateCharacterModel.h"
#include "Test.h"
#include "ThreatBreakdownModel.h"
#include "WeaponModel.h"

int main(int argc, char* argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    Test().test_all();

    QApplication app(argc, argv);
    auto gui_control = new GUIControl();

    QQmlApplicationEngine qml_engine;
    QQmlContext* context = qml_engine.rootContext();

    context->setContextProperty("character", gui_control);
    context->setContextProperty("talents", gui_control);
    context->setContextProperty("equipment", gui_control);
    context->setContextProperty("statistics", gui_control);
    context->setContextProperty("settings", gui_control);
    context->setContextProperty("raid", gui_control);
    context->setContextProperty("itemModel", gui_control->get_item_model());
    context->setContextProperty("itemTypeFilterModel", gui_control->get_item_type_filter_model());
    context->setContextProperty("activeStatFilterModel", gui_control->get_active_stat_filter_model());
    context->setContextProperty("availableStatFilterModel", gui_control->get_available_stat_filter_model());
    context->setContextProperty("weaponModel", gui_control->get_weapon_model());
    context->setContextProperty("buffModel", gui_control->get_buff_model());
    context->setContextProperty("debuffModel", gui_control->get_debuff_model());
    context->setContextProperty("rotationModel", gui_control->get_rotation_model());
    context->setContextProperty("rotationConditionsModel", gui_control->get_rotation_model()->get_rotation_conditions_model());
    context->setContextProperty("buffBreakdownModel", gui_control->get_buff_breakdown_model());
    context->setContextProperty("debuffBreakdownModel", gui_control->get_debuff_breakdown_model());
    context->setContextProperty("engineBreakdownModel", gui_control->get_engine_breakdown_model());
    context->setContextProperty("meleeDamageBreakdownModel", gui_control->get_dmg_breakdown_model());
    context->setContextProperty("threatBreakdownModel", gui_control->get_thrt_breakdown_model());
    context->setContextProperty("meleeAvoidanceBreakdownModel", gui_control->get_dmg_breakdown_avoidance_model());
    context->setContextProperty("procBreakdownModel", gui_control->get_proc_breakdown_model());
    context->setContextProperty("resourceBreakdownModel", gui_control->get_resource_breakdown_model());
    context->setContextProperty("rotationExecutorBreakdownModel", gui_control->get_rotation_executor_model());
    context->setContextProperty("rotationExecutorListModel", gui_control->get_rotation_executor_list_model());
    context->setContextProperty("simScaleModel", gui_control->get_sim_scale_model());
    context->setContextProperty("dpsScaleResultModel", gui_control->get_dps_scale_result_model());
    context->setContextProperty("tpsScaleResultModel", gui_control->get_tps_scale_result_model());
    context->setContextProperty("damageMetersModel", gui_control->get_damage_meters_model());
    context->setContextProperty("mhEnchantModel", gui_control->get_mh_enchant_model());
    context->setContextProperty("mhTempEnchantModel", gui_control->get_mh_temporary_enchant_model());
    context->setContextProperty("ohEnchantModel", gui_control->get_oh_enchant_model());
    context->setContextProperty("ohTempEnchantModel", gui_control->get_oh_temporary_enchant_model());
    context->setContextProperty("rangedEnchantModel", gui_control->get_ranged_enchant_model());
    context->setContextProperty("headLegsEnchantModel", gui_control->get_head_legs_enchant_model());
    context->setContextProperty("shoulderEnchantModel", gui_control->get_shoulder_enchant_model());
    context->setContextProperty("backEnchantModel", gui_control->get_back_enchant_model());
    context->setContextProperty("wristEnchantModel", gui_control->get_wrist_enchant_model());
    context->setContextProperty("glovesEnchantModel", gui_control->get_gloves_enchant_model());
    context->setContextProperty("chestEnchantModel", gui_control->get_chest_enchant_model());
    context->setContextProperty("bootsEnchantModel", gui_control->get_boots_enchant_model());
    context->setContextProperty("randomAffixModel", gui_control->get_random_affix_model());
    context->setContextProperty("templateCharacterModel", gui_control->get_template_character_model());

    qmlRegisterType<AvailableFactions>("Faction", 1, 0, "Faction");
    qmlRegisterType<BuffBreakdownSorting>("BuffBreakdownSorting", 1, 0, "BuffBreakdownSorting");
    qmlRegisterType<Content>("ContentPhase", 1, 0, "ContentPhase");
    qmlRegisterType<EnchantName>("EnchantName", 1, 0, "EnchantName");
    qmlRegisterType<EngineBreakdownSorting>("EngineBreakdownSorting", 1, 0, "EngineBreakdownSorting");
    qmlRegisterType<ItemSorting>("ItemSort", 1, 0, "ItemSort");
    qmlRegisterType<MeleeDamageAvoidanceBreakdownSorting>("MeleeDamageAvoidanceBreakdownSorting", 1, 0, "MeleeDamageAvoidanceBreakdownSorting");
    qmlRegisterType<MeleeDamageBreakdownSorting>("MeleeDamageBreakdownSorting", 1, 0, "MeleeDamageBreakdownSorting");
    qmlRegisterType<ThreatBreakdownSorting>("ThreatBreakdownSorting", 1, 0, "ThreatBreakdownSorting");
    qmlRegisterType<ProcBreakdownSorting>("ProcBreakdownSorting", 1, 0, "ProcBreakdownSorting");
    qmlRegisterType<ResourceBreakdownSorting>("ResourceBreakdownSorting", 1, 0, "ResourceBreakdownSorting");
    qmlRegisterType<ScaleResultSorting>("ScaleResultSorting", 1, 0, "ScaleResultSorting");
    qmlRegisterType<SimOption>("SimOption", 1, 0, "SimOption");
    qmlRegisterType<WeaponSorting>("WeaponSort", 1, 0, "WeaponSort");
    qmlRegisterType<RotationExecutorBreakdownSorting>("RotationExecutorBreakdownSorting", 1, 0, "RotationExecutorBreakdownSorting");

    qml_engine.clearComponentCache();
    qml_engine.load(QUrl(QStringLiteral("qrc:/QML/main.qml")));
    if (qml_engine.rootObjects().isEmpty())
        return -1;

    int return_code = QApplication::exec();

    gui_control->save_settings();

    return return_code;
}

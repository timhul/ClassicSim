#pragma once

#include <QMap>
#include <QObject>
#include <QSet>
#include <QVariant>
#include <QVector>

#include "EnchantName.h"

class ActiveItemStatFilterModel;
class AvailableItemStatFilterModel;
class BuffBreakdownModel;
class BuffModel;
class Character;
class CharacterDecoder;
class CharacterEncoder;
class CharacterTalents;
class CombatRoll;
class DamageMetersModel;
class DebuffBreakdownModel;
class DebuffModel;
class EnchantModel;
class Engine;
class EngineBreakdownModel;
class EquipmentDb;
class Item;
class ItemModel;
class ItemTypeFilterModel;
class MeleeDamageAvoidanceBreakdownModel;
class MeleeDamageBreakdownModel;
class NumberCruncher;
class ProcBreakdownModel;
class Race;
class RaidControl;
class RandomAffixes;
class RandomAffixModel;
class ResourceBreakdownModel;
class RotationExecutorBreakdownModel;
class RotationExecutorListModel;
class RotationModel;
class ScaleResult;
class ScaleResultModel;
class SimControl;
class SimScaleModel;
class SimSettings;
class SimulationThreadPool;
class Target;
class TemplateCharacterModel;
class ThreatBreakdownModel;
class WeaponModel;

class ClassicSimControl : public QObject {
    Q_OBJECT
public:
    ClassicSimControl(QObject* parent = nullptr);
    ~ClassicSimControl();

    void save_settings();

    /* Character */
    Q_PROPERTY(QString classColor READ get_class_color NOTIFY classChanged)
    Q_PROPERTY(QString className READ get_class_name NOTIFY classChanged)
    Q_PROPERTY(QString raceName READ get_race_name NOTIFY raceChanged)
    Q_PROPERTY(bool isAlliance READ get_is_alliance NOTIFY factionChanged)
    Q_PROPERTY(bool isHorde READ get_is_horde NOTIFY factionChanged)

    Q_INVOKABLE void selectRace(const QString& race_name);
    Q_INVOKABLE void selectFaction(const int faction);

    Q_INVOKABLE bool raceAvailable(const QString& race_name);
    /* End of Character */

    /* Talents */
    Q_PROPERTY(int talentPointsRemaining READ get_talent_points_remaining NOTIFY talentsUpdated)
    Q_PROPERTY(QString leftTalentTreeBackground READ getLeftBackgroundImage NOTIFY classChanged)
    Q_PROPERTY(QString midTalentTreeBackground READ getMidBackgroundImage NOTIFY classChanged)
    Q_PROPERTY(QString rightTalentTreeBackground READ getRightBackgroundImage NOTIFY classChanged)
    Q_PROPERTY(int leftTreePoints READ get_left_talent_tree_points NOTIFY talentsUpdated)
    Q_PROPERTY(int midTreePoints READ get_mid_talent_tree_points NOTIFY talentsUpdated)
    Q_PROPERTY(int rightTreePoints READ get_right_talent_tree_points NOTIFY talentsUpdated)
    Q_PROPERTY(QString talentAllocation READ get_formatted_talent_allocation NOTIFY talentsUpdated)

    Q_INVOKABLE QString getIcon(const QString& tree_position, const QString& talent_position) const;
    Q_INVOKABLE bool showPosition(const QString& tree_position, const QString& talent_position) const;
    Q_INVOKABLE bool showBottomArrow(const QString& tree_position, const QString& talent_position) const;
    Q_INVOKABLE bool showRightArrow(const QString& tree_position, const QString& talent_position) const;

    Q_INVOKABLE QString getBottomArrow(const QString& tree_position, const QString& talent_position) const;
    Q_INVOKABLE QString getRightArrow(const QString& tree_position, const QString& talent_position) const;
    Q_INVOKABLE bool bottomChildAvailable(const QString& tree_position, const QString& talent_position) const;
    Q_INVOKABLE bool bottomChildActive(const QString& tree_position, const QString& talent_position) const;
    Q_INVOKABLE bool rightChildAvailable(const QString& tree_position, const QString& talent_position) const;
    Q_INVOKABLE bool rightChildActive(const QString& tree_position, const QString& talent_position) const;
    Q_INVOKABLE bool isActive(const QString& tree_position, const QString& talent_position) const;
    Q_INVOKABLE bool isAvailable(const QString& tree_position, const QString& talent_position) const;
    Q_INVOKABLE bool isMaxed(const QString& tree_position, const QString& talent_position) const;
    Q_INVOKABLE bool hasTalentPointsRemaining() const;
    Q_INVOKABLE QString getRank(const QString& tree_position, const QString& talent_position) const;
    Q_INVOKABLE QString getMaxRank(const QString& tree_position, const QString& talent_position) const;
    Q_INVOKABLE void incrementRank(const QString& tree_position, const QString& talent_position);
    Q_INVOKABLE void decrementRank(const QString& tree_position, const QString& talent_position);
    Q_INVOKABLE QString getRequirements(const QString& tree_position, const QString& talent_position) const;
    Q_INVOKABLE QString getCurrentRankDescription(const QString& tree_position, const QString& talent_position) const;
    Q_INVOKABLE QString getNextRankDescription(const QString& tree_position, const QString& talent_position) const;
    Q_INVOKABLE QString getTreeName(const QString& tree_position) const;
    Q_INVOKABLE QString getTalentName(const QString& tree_position, const QString& talent_position) const;
    Q_INVOKABLE void maxRank(const QString& tree_position, const QString& talent_position);
    Q_INVOKABLE void minRank(const QString& tree_position, const QString& talent_position);

    Q_INVOKABLE void clearTree(const QString& tree_position);

    Q_INVOKABLE void setTalentSetup(const int talent_index);
    int get_left_talent_tree_points() const;
    int get_mid_talent_tree_points() const;
    int get_right_talent_tree_points() const;
    int get_tree_points(const QString& tree_position) const;
    QString get_formatted_talent_allocation() const;
    /* End of Talents */

    Q_INVOKABLE void toggleTank();
    Q_PROPERTY(bool isTanking READ get_is_tanking NOTIFY tankingChanged)
    bool get_is_tanking() const;

    /* Stats */
    Q_PROPERTY(unsigned strength READ get_strength NOTIFY statsChanged)
    Q_PROPERTY(unsigned agility READ get_agility NOTIFY statsChanged)
    Q_PROPERTY(unsigned stamina READ get_stamina NOTIFY statsChanged)
    Q_PROPERTY(unsigned intellect READ get_intellect NOTIFY statsChanged)
    Q_PROPERTY(unsigned spirit READ get_spirit NOTIFY statsChanged)

    Q_PROPERTY(QString meleeCritChance READ get_melee_crit_chance NOTIFY statsChanged)
    Q_PROPERTY(QString meleeHitChance READ get_melee_hit_chance NOTIFY statsChanged)
    Q_PROPERTY(int meleeAttackPower READ get_melee_attack_power NOTIFY statsChanged)
    Q_PROPERTY(int wpnSkillMh READ get_mainhand_wpn_skill NOTIFY statsChanged)
    Q_PROPERTY(int wpnSkillOh READ get_offhand_wpn_skill NOTIFY statsChanged)
    Q_PROPERTY(QString rangedCritChance READ get_ranged_crit_chance NOTIFY statsChanged)
    Q_PROPERTY(QString rangedHitChance READ get_ranged_hit_chance NOTIFY statsChanged)
    Q_PROPERTY(int rangedAttackPower READ get_ranged_attack_power NOTIFY statsChanged)
    Q_PROPERTY(int wpnSkillRanged READ get_ranged_wpn_skill NOTIFY statsChanged)
    Q_PROPERTY(int spellPower READ get_spell_power NOTIFY statsChanged)
    Q_PROPERTY(QString spellHitChance READ get_spell_hit_chance NOTIFY statsChanged)
    Q_PROPERTY(QString spellCritChance READ get_spell_crit_chance NOTIFY statsChanged)
    Q_PROPERTY(QString displayStatsType READ get_stats_type_to_display NOTIFY displayStatsTypeChanged)
    Q_SIGNAL void displayStatsTypeChanged();
    QString get_stats_type_to_display() const;
    QString get_attack_mode_as_string() const;
    unsigned get_ranged_wpn_skill() const;
    unsigned get_spell_power() const;
    QString get_spell_hit_chance() const;
    QString get_spell_crit_chance() const;
    Q_INVOKABLE void selectDisplayStat(const QString& attack_mode);
    /* End of Stats */

    /* Equipment */
    Q_PROPERTY(QString mainhandIcon READ get_mainhand_icon NOTIFY equipmentChanged)
    Q_PROPERTY(QString offhandIcon READ get_offhand_icon NOTIFY equipmentChanged)
    Q_PROPERTY(QString rangedIcon READ get_ranged_icon NOTIFY equipmentChanged)
    Q_PROPERTY(QString headIcon READ get_head_icon NOTIFY equipmentChanged)
    Q_PROPERTY(QString neckIcon READ get_neck_icon NOTIFY equipmentChanged)
    Q_PROPERTY(QString shouldersIcon READ get_shoulders_icon NOTIFY equipmentChanged)
    Q_PROPERTY(QString backIcon READ get_back_icon NOTIFY equipmentChanged)
    Q_PROPERTY(QString chestIcon READ get_chest_icon NOTIFY equipmentChanged)
    Q_PROPERTY(QString wristIcon READ get_wrist_icon NOTIFY equipmentChanged)
    Q_PROPERTY(QString glovesIcon READ get_gloves_icon NOTIFY equipmentChanged)
    Q_PROPERTY(QString beltIcon READ get_belt_icon NOTIFY equipmentChanged)
    Q_PROPERTY(QString legsIcon READ get_legs_icon NOTIFY equipmentChanged)
    Q_PROPERTY(QString bootsIcon READ get_boots_icon NOTIFY equipmentChanged)
    Q_PROPERTY(QString ring1Icon READ get_ring1_icon NOTIFY equipmentChanged)
    Q_PROPERTY(QString ring2Icon READ get_ring2_icon NOTIFY equipmentChanged)
    Q_PROPERTY(QString trinket1Icon READ get_trinket1_icon NOTIFY equipmentChanged)
    Q_PROPERTY(QString trinket2Icon READ get_trinket2_icon NOTIFY equipmentChanged)
    Q_PROPERTY(QString projectileIcon READ get_projectile_icon NOTIFY equipmentChanged)
    Q_PROPERTY(QString relicIcon READ get_relic_icon NOTIFY equipmentChanged)
    Q_PROPERTY(QString quiverIcon READ get_quiver_icon NOTIFY equipmentChanged)

    Q_INVOKABLE void setEquipmentSetup(const int equipment_index);

    Q_SIGNAL void enchantChanged();
    Q_INVOKABLE bool hasItemEquipped(const QString& slot_string) const;
    Q_INVOKABLE bool hasEnchant(const QString& slot_string) const;
    Q_INVOKABLE bool hasTemporaryEnchant(const QString& slot_string) const;
    Q_INVOKABLE QString getEnchantEffect(const QString& slot_string) const;
    Q_INVOKABLE QString getTemporaryEnchantEffect(const QString& slot_string) const;
    Q_INVOKABLE void applyEnchant(const QString& slot_string, const int enchant_name);
    Q_INVOKABLE void applyTemporaryEnchant(const QString& slot_string, const int enchant_name);
    Q_INVOKABLE void clearEnchant(const QString& slot_string);
    Q_INVOKABLE void clearTemporaryEnchant(const QString& slot_string);
    EnchantModel* get_mh_enchant_model() const;
    EnchantModel* get_mh_temporary_enchant_model() const;
    EnchantModel* get_oh_enchant_model() const;
    EnchantModel* get_oh_temporary_enchant_model() const;
    EnchantModel* get_ranged_enchant_model() const;
    EnchantModel* get_head_legs_enchant_model() const;
    EnchantModel* get_shoulder_enchant_model() const;
    EnchantModel* get_back_enchant_model() const;
    EnchantModel* get_wrist_enchant_model() const;
    EnchantModel* get_gloves_enchant_model() const;
    EnchantModel* get_chest_enchant_model() const;
    EnchantModel* get_boots_enchant_model() const;
    /* End of Equipment */

    /* ItemModel */
    ItemModel* get_item_model() const;
    WeaponModel* get_weapon_model() const;
    ItemTypeFilterModel* get_item_type_filter_model() const;
    ActiveItemStatFilterModel* get_active_stat_filter_model() const;
    AvailableItemStatFilterModel* get_available_stat_filter_model() const;
    Q_INVOKABLE bool getFilterActive(const int filter) const;
    Q_INVOKABLE void toggleSingleFilter(const int filter);
    Q_INVOKABLE void clearFiltersAndSelectSingle(const int filter);
    Q_INVOKABLE void selectRangeOfFiltersFromPrevious(const int filter);
    /* End of ItemModel */

    /* Random affixes model */
    RandomAffixModel* get_random_affix_model() const;
    Q_INVOKABLE void setRandomAffixesModelId(const int item_id);
    /* End of Random affixes model */

    /* Buffs and debuffs */
    BuffModel* get_buff_model() const;
    DebuffModel* get_debuff_model() const;
    Q_INVOKABLE void toggleSingleBuff(const QString& buff);
    Q_INVOKABLE void clearBuffsAndSelectSingleBuff(const QString& buff);
    Q_INVOKABLE void selectRangeOfBuffs(const QString& buff);
    Q_INVOKABLE bool buffActive(const QString& buff) const;
    Q_INVOKABLE void toggleSingleDebuff(const QString& debuff);
    Q_INVOKABLE void clearDebuffsAndSelectSingleDebuff(const QString& buff);
    Q_INVOKABLE void selectRangeOfDebuffs(const QString& buff);
    Q_INVOKABLE bool debuffActive(const QString& debuff) const;
    Q_INVOKABLE void setBuffSetup(const int buff_index);
    /* End of Buffs and debuffs */

    /* Statistics */
    BuffBreakdownModel* get_buff_breakdown_model() const;
    DebuffBreakdownModel* get_debuff_breakdown_model() const;
    EngineBreakdownModel* get_engine_breakdown_model() const;
    MeleeDamageBreakdownModel* get_dmg_breakdown_model() const;
    MeleeDamageAvoidanceBreakdownModel* get_dmg_breakdown_avoidance_model() const;
    ProcBreakdownModel* get_proc_breakdown_model() const;
    ResourceBreakdownModel* get_resource_breakdown_model() const;
    RotationExecutorBreakdownModel* get_rotation_executor_model() const;
    RotationExecutorListModel* get_rotation_executor_list_model() const;
    ScaleResultModel* get_dps_scale_result_model() const;
    ScaleResultModel* get_tps_scale_result_model() const;
    ThreatBreakdownModel* get_thrt_breakdown_model() const;
    TemplateCharacterModel* get_template_character_model() const;
    Q_SLOT void compile_thread_results();
    Q_PROPERTY(QString minDps READ get_min_dps NOTIFY statisticsReady)
    Q_PROPERTY(QString maxDps READ get_max_dps NOTIFY statisticsReady)
    Q_PROPERTY(QString dpsStdDev READ get_standard_deviation NOTIFY statisticsReady)
    Q_PROPERTY(QString dpsConfInterval READ get_confidence_interval NOTIFY statisticsReady)
    Q_PROPERTY(QString engineHandledEventsPerSecond READ get_handled_events_per_second NOTIFY statisticsReady)
    QString get_handled_events_per_second() const;
    /* End of Statistics */

    /* Target */
    Q_PROPERTY(QString creatureType READ get_creature_type NOTIFY creatureTypeChanged)
    Q_PROPERTY(int targetArmor READ get_target_armor NOTIFY targetUpdated)
    Q_PROPERTY(int targetBaseArmor READ get_target_base_armor NOTIFY targetUpdated)
    Q_INVOKABLE void setCreatureType(const QString& creature_type);
    Q_SIGNAL void targetUpdated();
    int get_target_armor() const;
    int get_target_base_armor() const;
    Q_INVOKABLE void setTargetBaseArmor(const int armor);
    /* End of Target */

    /* Content phase */
    Q_INVOKABLE void setPhase(const int phase);
    Q_INVOKABLE QString getDescriptionForPhase(const int phase);
    /* End of Content phase */

    /* Rotation */
    RotationModel* get_rotation_model() const;
    Q_INVOKABLE void selectRotation();
    Q_INVOKABLE void selectInformationRotation(const int);
    Q_PROPERTY(QString rotationName READ get_curr_rotation_name NOTIFY rotationChanged)
    Q_PROPERTY(QString rotationDescription READ get_curr_rotation_description NOTIFY rotationChanged)
    Q_PROPERTY(QString rotationInfoName READ get_information_rotation_name NOTIFY informationRotationChanged)
    Q_PROPERTY(QString rotationInfoDesc READ get_information_rotation_description NOTIFY informationRotationChanged)
    /* End of Rotation */

    /* SimSettings */
    Q_INVOKABLE void resetDefaultSettings();
    Q_PROPERTY(int combatLength READ get_combat_length NOTIFY combatLengthChanged)
    Q_PROPERTY(int combatIterationsFullSim READ get_combat_iterations_full_sim NOTIFY combatIterationsChanged)
    Q_PROPERTY(int combatIterationsQuickSim READ get_combat_iterations_quick_sim NOTIFY combatIterationsChanged)
    Q_PROPERTY(int numThreads READ get_num_threads NOTIFY numThreadsChanged)
    Q_PROPERTY(int maxThreads READ get_max_threads NOTIFY numThreadsChanged)
    Q_INVOKABLE void setCombatLength(const int);
    Q_INVOKABLE void setCombatIterationsFullSim(const int);
    Q_INVOKABLE void setCombatIterationsQuickSim(const int);
    Q_INVOKABLE void setNumThreads(const int);
    Q_SIGNAL void combatLengthChanged();
    Q_SIGNAL void combatIterationsChanged();
    Q_SIGNAL void numThreadsChanged();
    Q_INVOKABLE void selectRuleset(const int);
    Q_PROPERTY(QString simProgressString READ get_sim_progress_string NOTIFY simProgressChanged)
    Q_SIGNAL void simProgressChanged();
    Q_INVOKABLE void runQuickSim();
    Q_INVOKABLE void runFullSim();
    Q_SIGNAL void simPersonalResultUpdated(QString dps, QString dpsChange, QString tps, bool positive);
    Q_SIGNAL void simRaidResultUpdated(QString dps, QString dpsChange, bool positive);
    SimScaleModel* get_sim_scale_model() const;
    Q_PROPERTY(int combatProgress READ get_combat_progress NOTIFY combatProgressChanged)
    Q_PROPERTY(bool simInProgress READ get_sim_in_progress NOTIFY simProgressChanged)
    int get_combat_progress() const;
    bool get_sim_in_progress() const;
    Q_SIGNAL void combatProgressChanged() const;
    /* End of SimSettings */

    /* Raid setup */
    Q_INVOKABLE void selectPartyMember(const int party, const int member);
    Q_INVOKABLE void clearPartyMember(const int party, const int member);
    Q_INVOKABLE QVariantMap partyMemberInfo(const int party, const int member);
    Q_INVOKABLE void selectTemplateCharacter(QString template_char);
    Q_SIGNAL void partyMembersUpdated();
    Q_SIGNAL void selectedPartyMemberChanged();
    DamageMetersModel* get_damage_meters_model();
    /* End of Raid setup */

    /* GUI initialization */
    Q_INVOKABLE QString getStartWindow() const;
    Q_INVOKABLE void changeActiveWindow(const QString& active_window);
    Q_INVOKABLE int getCurrentRuleset() const;
    Q_INVOKABLE int getCurrentCreatureType() const;
    Q_INVOKABLE int getContentPhase() const;
    /* End of GUI initialization */

signals:
    void tankingChanged();
    void classChanged();
    void raceChanged();
    void factionChanged();
    void talentsUpdated();
    void statsChanged();
    void equipmentChanged();
    void tooltipChanged();
    void statisticsCleared();
    void statisticsReady();
    void creatureTypeChanged();
    void filtersUpdated();
    void equipmentSlotSelected();
    void rotationChanged();
    void informationRotationChanged();

public slots:
    void update_progress(double percent);

protected:
    int get_talent_points_remaining() const;
    QString get_class_color() const;
    QString get_class_name() const;
    QString get_race_name() const;
    bool get_is_alliance() const;
    bool get_is_horde() const;

    void reset_race(Character* pchar);

    QString get_creature_type() const;

    QString getLeftBackgroundImage() const;
    QString getMidBackgroundImage() const;
    QString getRightBackgroundImage() const;

    unsigned get_strength() const;
    unsigned get_agility() const;
    unsigned get_stamina() const;
    unsigned get_intellect() const;
    unsigned get_spirit() const;

    QString get_melee_crit_chance() const;
    QString get_melee_hit_chance() const;
    QString get_ranged_crit_chance() const;
    QString get_ranged_hit_chance() const;

    unsigned get_melee_attack_power() const;
    unsigned get_ranged_attack_power() const;
    unsigned get_mainhand_wpn_skill() const;
    unsigned get_offhand_wpn_skill() const;

    QString get_curr_rotation_name() const;
    QString get_curr_rotation_description() const;
    QString get_information_rotation_name() const;
    QString get_information_rotation_description() const;

    int get_combat_iterations_full_sim() const;
    int get_combat_iterations_quick_sim() const;
    int get_combat_length() const;
    int get_num_threads() const;
    int get_max_threads() const;

    QString get_mainhand_icon() const;
    QString get_offhand_icon() const;
    QString get_ranged_icon() const;
    QString get_head_icon() const;
    QString get_neck_icon() const;
    QString get_shoulders_icon() const;
    QString get_back_icon() const;
    QString get_chest_icon() const;
    QString get_wrist_icon() const;
    QString get_gloves_icon() const;
    QString get_belt_icon() const;
    QString get_legs_icon() const;
    QString get_boots_icon() const;
    QString get_ring1_icon() const;
    QString get_ring2_icon() const;
    QString get_trinket1_icon() const;
    QString get_trinket2_icon() const;
    QString get_projectile_icon() const;
    QString get_relic_icon() const;
    QString get_quiver_icon() const;

    QString get_initial_upper_case_rest_lower_case(const QString&) const;
    void set_character(Character* pchar);
    void run_sim(const bool full_sim);
    void calculate_displayed_dps_value();
    void update_displayed_dps_value(const double new_dps_value, const double new_tps_value);
    void update_displayed_raid_dps_value(const double new_dps_value);

    QString get_sim_progress_string() const;

    QString get_min_dps() const;
    QString get_max_dps() const;
    QString get_standard_deviation() const;
    QString get_confidence_interval() const;

    Character* load_character(const QString& class_name);
    Character* get_new_character(const QString& class_name);
    void save_user_setup(Character* pchar);

    void save_configuration();
    void load_configuration();
    void activate_configuration(const QStringRef& name, const QString& value);

    EquipmentDb* equipment_db;
    RandomAffixes* random_affixes_db;
    CharacterEncoder* character_encoder;
    CharacterDecoder* character_decoder;
    SimulationThreadPool* thread_pool;
    SimControl* sim_control;
    SimSettings* sim_settings;
    Target* target;
    RaidControl* raid_control;
    NumberCruncher* number_cruncher;
    QMap<QString, Character*> chars;
    QMap<QString, Race*> races;
    QSet<QString> supported_classes;
    QMap<QString, RaidControl*> raid_controls;
    QVector<QVector<QVariantMap>> raid_setup;
    Character* current_char;
    ItemModel* item_model;
    ActiveItemStatFilterModel* active_stat_filter_model;
    AvailableItemStatFilterModel* available_stat_filter_model;
    ItemTypeFilterModel* item_type_filter_model;
    WeaponModel* weapon_model;
    BuffModel* buff_model;
    DamageMetersModel* damage_meters_model;
    DebuffModel* debuff_model;
    RotationModel* rotation_model;
    BuffBreakdownModel* buff_breakdown_model;
    DebuffBreakdownModel* debuff_breakdown_model;
    EngineBreakdownModel* engine_breakdown_model;
    MeleeDamageBreakdownModel* damage_breakdown_model;
    MeleeDamageAvoidanceBreakdownModel* damage_avoidance_breakdown_model;
    ProcBreakdownModel* proc_breakdown_model;
    ResourceBreakdownModel* resource_breakdown_model;
    RotationExecutorListModel* rotation_executor_list_model;
    SimScaleModel* sim_scale_model;
    ScaleResultModel* dps_scale_result_model;
    ScaleResultModel* tps_scale_result_model;
    ScaleResult* dps_distribution;
    ThreatBreakdownModel* threat_breakdown_model;
    TemplateCharacterModel* template_character_model;
    EnchantModel* mh_enchants;
    EnchantModel* mh_temporary_enchants;
    EnchantModel* oh_enchants;
    EnchantModel* oh_temporary_enchants;
    EnchantModel* ranged_enchants;
    EnchantModel* head_legs_enchants;
    EnchantModel* shoulder_enchants;
    EnchantModel* back_enchants;
    EnchantModel* wrist_enchants;
    EnchantModel* gloves_enchants;
    EnchantModel* chest_enchants;
    EnchantModel* boots_enchants;
    RandomAffixModel* random_affixes;
    double last_personal_sim_result {0.0};
    double last_personal_sim_result_tps {0.0};
    double last_raid_sim_result {0.0};
    double last_engine_handled_events_per_second {0.0};
    bool sim_in_progress;
    double sim_percent_completed {0.0};
    int current_party {1};
    int current_member {1};
    QString active_window;
    QString stats_type_to_display;
    QVector<Race*> raid_member_races;
};

#ifndef GUICONTROL_H
#define GUICONTROL_H

#include <QObject>

#include "Engine.h"
#include "Test.h"
#include "Equipment.h"
#include "Target.h"
#include "CombatRoll.h"
#include "Talents.h"
#include "Character.h"
#include "Race.h"
#include "ItemModel.h"
#include "WeaponModel.h"

class GUIControl: public QObject {
    Q_OBJECT
public:
    GUIControl(QObject* parent = 0);
    ~GUIControl();

    /* Character */
    Q_PROPERTY(QString classColor READ get_class_color NOTIFY classChanged)
    Q_PROPERTY(QString className READ get_class_name NOTIFY classChanged)

    /* End of Character */

    /* Talents */
    Q_PROPERTY(int talentPointsRemaining READ get_talent_points_remaining NOTIFY talentsUpdated)
    Q_PROPERTY(QString leftTalentTreeBackground READ getLeftBackgroundImage NOTIFY classChanged)
    Q_PROPERTY(QString midTalentTreeBackground READ getMidBackgroundImage NOTIFY classChanged)
    Q_PROPERTY(QString rightTalentTreeBackground READ getRightBackgroundImage NOTIFY classChanged)

    Q_INVOKABLE QString getIcon(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE bool showPosition(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE bool showBottomArrow(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE bool showRightArrow(const QString tree_position, const QString talent_position) const;

    Q_INVOKABLE QString getBottomArrow(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE QString getRightArrow(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE bool bottomChildAvailable(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE bool bottomChildActive(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE bool rightChildAvailable(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE bool rightChildActive(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE bool isActive(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE bool isAvailable(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE bool isMaxed(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE bool hasTalentPointsRemaining() const;
    Q_INVOKABLE QString getRank(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE QString getMaxRank(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE void incrementRank(const QString tree_position, const QString talent_position);
    Q_INVOKABLE void decrementRank(const QString tree_position, const QString talent_position);
    Q_INVOKABLE QString getRequirements(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE QString getCurrentRankDescription(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE QString getNextRankDescription(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE int getTreePoints(const QString tree_position) const;
    Q_INVOKABLE QString getTreeName(const QString tree_position) const;
    Q_INVOKABLE QString getTalentName(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE void maxRank(const QString tree_position, const QString talent_position);
    Q_INVOKABLE void minRank(const QString tree_position, const QString talent_position);

    Q_INVOKABLE void clearTree(const QString tree_position);

    Q_INVOKABLE void setTalentSetup(const int talent_index);
    /* End of Talents */

    /* Stats */
    Q_PROPERTY(int strength READ get_strength NOTIFY statsChanged)
    Q_PROPERTY(int agility READ get_agility NOTIFY statsChanged)
    Q_PROPERTY(int stamina READ get_stamina NOTIFY statsChanged)
    Q_PROPERTY(int intellect READ get_intellect NOTIFY statsChanged)
    Q_PROPERTY(int spirit READ get_spirit NOTIFY statsChanged)

    Q_PROPERTY(QString critChance READ get_crit_chance NOTIFY statsChanged)
    Q_PROPERTY(QString hitChance READ get_hit_chance NOTIFY statsChanged)

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

    Q_INVOKABLE void clearSlot(QString slot_string);
    Q_INVOKABLE void setSlot(QString slot_string, QString item);

    /* End of Equipment */

    /* ItemModel */
    ItemModel* get_item_model() const;
    WeaponModel* get_weapon_model() const;

    /* End of ItemModel */


    Q_INVOKABLE void runQuickSim();
    Q_INVOKABLE void setPatch(QString patch);



Q_SIGNALS:
    void talentsUpdated();
    void classChanged();
    void statsChanged();
    void equipmentChanged();
    void quickSimChanged(QString value, QString change, bool positive);

private:
    int get_talent_points_remaining() const;
    QString get_class_color() const;
    QString get_class_name() const;

    QString getLeftBackgroundImage() const;
    QString getMidBackgroundImage() const;
    QString getRightBackgroundImage() const;

    int get_strength() const;
    int get_agility() const;
    int get_stamina() const;
    int get_intellect() const;
    int get_spirit() const;

    QString get_crit_chance() const;
    QString get_hit_chance() const;

    void run_quick_sim();

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


    Engine* engine;
    Equipment* equipment;
    Target* target;
    Random* random;
    CombatRoll* combat;
    QMap<QString, Character*> chars;
    QMap<QString, Race*> races;
    Character* current_char;
    float last_quick_sim_result;
    ItemModel* item_model;
    WeaponModel* weapon_model;
};

#endif // GUICONTROL_H

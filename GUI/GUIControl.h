#pragma once

#include "ClassicSimControl.h"

class GUIControl : public ClassicSimControl {
    Q_OBJECT
public:
    GUIControl(QObject* parent = nullptr);
    ~GUIControl();

    /* Character */
    Q_INVOKABLE void selectClass(const QString& class_name);
    /* End of Character */

    QVariantList get_tooltip_from_item(Item* item);

    Q_INVOKABLE QVariantList getTooltip(const QString& slot_string);
    Q_INVOKABLE QVariantList getTooltip(const int item_id);

    Q_INVOKABLE void setSlot(const QString& slot_string, const int item_id, const uint affix_id = 0);
    Q_INVOKABLE void clearSlot(const QString& slot_string);
    Q_INVOKABLE void selectSlot(const QString& slot_string);

private:
    void set_weapon_tooltip(Item*& item, QString& slot, QString type, QString& dmg_range, QString& wpn_speed, QString& dps);
    void set_projectile_tooltip(Item* item, QString& slot, QString& dps);
    void set_class_restriction_tooltip(Item*& item, QString& restriction);
    void set_set_bonus_tooltip(Item* item, QVariantList& tooltip) const;
};

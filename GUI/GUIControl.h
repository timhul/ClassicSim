#pragma once

#include "ClassicSimControl.h"

class GUIControl : public ClassicSimControl {
    Q_OBJECT
public:
    GUIControl(QObject* parent = nullptr);
    ~GUIControl();

    QVariantList get_tooltip_from_item(Item* item);

    Q_INVOKABLE QVariantList getTooltip(const QString& slot_string);
    Q_INVOKABLE QVariantList getTooltip(const int item_id);

private:
    void set_weapon_tooltip(Item*& item, QString& slot, QString type, QString& dmg_range, QString& wpn_speed, QString& dps);
    void set_projectile_tooltip(Item* item, QString& slot, QString& dps);
    void set_class_restriction_tooltip(Item*& item, QString& restriction);
    void set_set_bonus_tooltip(Item* item, QVariantList& tooltip) const;
};

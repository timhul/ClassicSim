#ifndef BUFF_H
#define BUFF_H

#include <QString>
#include <assert.h>

class Character;
class StatisticsBuff;

namespace BuffStatus {
    static const int INACTIVE = -1;
    static const int INITIAL_ID = 0;
}

namespace BuffDuration {
    static const int PERMANENT = -1;
}

namespace Hidden {
    static const bool Yes = true;
    static const bool No = false;
}

namespace Debuff {
    static const bool Yes = true;
    static const bool No = false;
}

static const QString NO_ICON = "no-icon";

class Buff {
public:
    Buff(Character* pchar, QString  name, QString icon, const int duration, const int base_charges);
    virtual ~Buff() = default;

    QString get_name() const;
    QString get_icon() const;
    int get_charges() const;
    void apply_buff();
    void refresh_buff();
    void remove_buff(const int);
    void use_charge();
    void cancel_buff();
    bool is_active() const;
    double time_left() const;

    void reset();
    void initialize();
    void prepare_set_of_combat_iterations();

    bool is_enabled() const;
    bool is_hidden() const;
    bool is_debuff() const;

    void set_instance_id(const int);
    int get_instance_id() const;

    void enable_buff();
    void disable_buff();

protected:
    Character* pchar;
    StatisticsBuff* statistics_buff;
    const QString name;
    const QString icon;
    int duration;
    const int base_charges;
    int current_charges{};
    int iteration{};
    double applied{};
    double refreshed{};
    double expired{};
    bool active{};
    bool enabled;
    double uptime{};
    bool hidden;
    bool debuff;

    int instance_id;

    void force_remove_buff();
    virtual void buff_effect_when_applied() = 0;
    virtual void buff_effect_when_removed() = 0;

    virtual void buff_effect_when_refreshed();
    virtual void reset_effect();
    virtual void charge_change_effect();
};

#endif // BUFF_H

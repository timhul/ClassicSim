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

class Buff {
public:
    Buff(Character*, const QString, const int, const int);
    virtual ~Buff();

    StatisticsBuff* get_statistics_for_buff() const;
    QString get_name() const;
    int get_charges() const;
    void apply_buff();
    void remove_buff(const int);
    void use_charge();
    void cancel_buff();
    bool is_active() const;
    float time_left() const;

    void reset();
    void initialize();

    bool is_enabled() const;
    bool is_hidden() const;

    void increase_rank();
    void decrease_rank();

    void set_instance_id(const int);
    int get_instance_id() const;

    void enable_buff();
    void disable_buff();

    void add_buff_statistic();
    void remove_buff_statistic();

protected:
    Character* pchar;
    StatisticsBuff* statistics_buff;
    const QString name;
    int duration;
    const int base_charges;
    int current_charges;
    int iteration;
    float applied;
    float refreshed;
    float expired;
    bool active;
    int rank_talent;
    float uptime;
    bool hidden;

    int instance_id;

private:
    void force_remove_buff();
    virtual void buff_effect_when_applied() = 0;
    virtual void buff_effect_when_removed() = 0;
};

#endif // BUFF_H

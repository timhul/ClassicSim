#ifndef BUFF_H
#define BUFF_H

#include <QString>
#include <assert.h>

class Character;

class Buff {
public:
    Buff(Character*, const QString, const int, const int);
    virtual ~Buff();

    QString get_name() const;
    void apply_buff();
    void remove_buff(const int);
    void use_charge();
    bool is_active() const;
    float time_left() const;

    void reset();
    void initialize();

    bool is_enabled() const;

    void increase_rank();
    void decrease_rank();

protected:
    Character* pchar;
    const QString name;
    const int duration;
    const int base_charges;
    int current_charges;
    int iteration;
    float applied;
    float refreshed;
    float expired;
    bool active;
    int rank;

private:
    void force_remove_buff();
    virtual void buff_effect_when_applied() = 0;
    virtual void buff_effect_when_removed() = 0;
};

#endif // BUFF_H

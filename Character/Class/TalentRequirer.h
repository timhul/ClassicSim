#ifndef TALENTREQUIRER_H
#define TALENTREQUIRER_H

class Buff;
class Spell;

#include <QString>

namespace DisabledAtZero {
    static const bool Yes = true;
    static const bool No = false;
}

class TalentRequirer {
public:
    TalentRequirer(const int max_talent_rank, const bool disabled_at_zero);
    virtual ~TalentRequirer() = default;

protected:

    int curr_talent_rank;
    const int max_talent_rank;
    const bool disabled_at_zero;

    void increase_talent_rank(Buff* buff, const QString &talent_name = "");
    void decrease_talent_rank(Buff* buff, const QString &talent_name = "");

    void increase_talent_rank(Spell* spell, const QString &talent_name = "");
    void decrease_talent_rank(Spell* spell, const QString &talent_name = "");

    virtual void increase_talent_rank_effect(const QString& talent_name = "") = 0;
    virtual void decrease_talent_rank_effect(const QString& talent_name = "") = 0;
};


#endif // TALENTREQUIRER_H

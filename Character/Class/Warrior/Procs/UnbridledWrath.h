#ifndef UNBRIDLEDWRATH_H
#define UNBRIDLEDWRATH_H

#include "Proc.h"
#include "TalentRequirer.h"

class Warrior;

class UnbridledWrath: public Proc, public TalentRequirer {
public:
    UnbridledWrath(Character* pchar);
    ~UnbridledWrath() override;

    void proc_effect() override;

protected:
private:
    friend class UnbridledWrathTalent;

    Warrior* warr;

    void increase_talent_rank_effect(const int curr, const QString& talent_name) override;
    void decrease_talent_rank_effect(const int curr, const QString& talent_name) override;
};

#endif // UNBRIDLEDWRATH_H

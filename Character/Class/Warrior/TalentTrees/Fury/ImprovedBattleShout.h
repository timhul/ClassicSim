#ifndef IMPROVEDBATTLESHOUT_H
#define IMPROVEDBATTLESHOUT_H

#include "Talent.h"

class ImprovedBattleShout: public Talent {
    Q_OBJECT
public:
    ImprovedBattleShout(Character *pchar);
    virtual ~ImprovedBattleShout();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

    QString get_requirement_string() const override;

private:
};

#endif // IMPROVEDBATTLESHOUT_H

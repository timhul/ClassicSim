#ifndef DEATHWISH_H
#define DEATHWISH_H

#include "Talent.h"

class DeathWish: public Talent {
    Q_OBJECT
public:
    DeathWish(Character *pchar);
    virtual ~DeathWish();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

    QString get_requirement_string() const override;

private:
};

#endif // DEATHWISH_H

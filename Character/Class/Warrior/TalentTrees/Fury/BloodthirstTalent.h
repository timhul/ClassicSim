#ifndef BLOODTHIRSTTALENT_H
#define BLOODTHIRSTTALENT_H

#include "Talent.h"

class BloodthirstTalent: public Talent {
    Q_OBJECT
public:
    BloodthirstTalent(Character *pchar);
    virtual ~BloodthirstTalent();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

    QString get_requirement_string() const override;

private:
};

#endif // BLOODTHIRSTTALENT_H

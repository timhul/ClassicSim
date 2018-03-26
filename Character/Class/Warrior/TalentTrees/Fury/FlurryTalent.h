#ifndef FLURRYTALENT_H
#define FLURRYTALENT_H

#include "Talent.h"

class FlurryTalent: public Talent {
    Q_OBJECT
public:
    FlurryTalent(Character *pchar);
    virtual ~FlurryTalent();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

    QString get_requirement_string() const override;

private:
};

#endif // FLURRYTALENT_H

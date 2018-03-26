#ifndef IMPROVEDDEMORALIZINGSHOUT_H
#define IMPROVEDDEMORALIZINGSHOUT_H

#include "Talent.h"

class ImprovedDemoralizingShout: public Talent {
    Q_OBJECT
public:
    ImprovedDemoralizingShout(Character *pchar);
    virtual ~ImprovedDemoralizingShout();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

    QString get_requirement_string() const override;

private:
};

#endif // IMPROVEDDEMORALIZINGSHOUT_H

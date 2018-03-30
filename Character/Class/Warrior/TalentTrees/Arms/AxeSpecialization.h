#ifndef AXESPECIALIZATION_H
#define AXESPECIALIZATION_H

#include "Talent.h"

class AxeSpecialization: public Talent {
    Q_OBJECT
public:
    AxeSpecialization(Character *pchar);
    virtual ~AxeSpecialization();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

    QString get_requirement_string() const override;

private:
};

#endif // AXESPECIALIZATION_H

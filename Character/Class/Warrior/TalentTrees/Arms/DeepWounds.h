#ifndef DEEPWOUNDS_H
#define DEEPWOUNDS_H

#include "Talent.h"

class DeepWounds: public Talent {
    Q_OBJECT
public:
    DeepWounds(Character* pchar);
    virtual ~DeepWounds();

    virtual void apply_rank_effect() override;
    virtual void remove_rank_effect() override;

    QString get_requirement_string() const override;

private:
};

#endif // DEEPWOUNDS_H

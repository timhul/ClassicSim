#ifndef ASPECTOFTHEHAWKPROC_H
#define ASPECTOFTHEHAWKPROC_H

#include "Proc.h"
#include "TalentRequirer.h"

class AspectOfTheHawkBuff;
class ImprovedAspectOfTheHawkBuff;

class ImprovedAspectOfTheHawkProc: public Proc, public TalentRequirer {
public:
    ImprovedAspectOfTheHawkProc(Character* pchar, AspectOfTheHawkBuff* hawk_buff);
    ~ImprovedAspectOfTheHawkProc() override;

    void proc_effect() override;

    ImprovedAspectOfTheHawkBuff* get_improved_aspect_of_the_hawk_proc() const;

private:
    AspectOfTheHawkBuff* hawk_buff;
    ImprovedAspectOfTheHawkBuff* imp_hawk_buff;

    QVector<unsigned> talent_ranks;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;

    bool proc_specific_conditions_fulfilled() const override;
};

#endif // ASPECTOFTHEHAWKPROC_H

#ifndef WHITEHITTABLE_H
#define WHITEHITTABLE_H

#include "AttackTable.h"

class WhiteHitTable: public AttackTable {
public:
    WhiteHitTable(float _miss, float _dodge, float _parry,
                  float _glancing, float _block, float _critical, const int _wpn_skill):
        miss(_miss), dodge(_dodge), parry(_parry), glancing(_glancing),
        block(_block), critical(_critical), wpn_skill(_wpn_skill), range(10000) {
        set_attack_table();
    }

    void set_attack_table(void) override;
    int get_outcome(const int) override;
    void dump_table(void) override;
protected:
private:
    float miss;
    float dodge;
    float parry;
    float glancing;
    float block;
    float critical;
    int wpn_skill;

    int range;
    int miss_range;
    int dodge_range;
    int parry_range;
    int glancing_range;
    int block_range;
    int critical_range;
};

#endif // WHITEHITTABLE_H

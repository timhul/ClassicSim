#ifndef MELEESPECIALTABLE_H
#define MELEESPECIALTABLE_H

#include "AttackTable.h"
#include "Random.h"

class MeleeSpecialTable: public AttackTable {
public:
    MeleeSpecialTable(Random* _rand,
            float _miss, float _dodge, float _parry,
            float _block, float _critical, const int _wpn_skill):
        random(_rand), miss(_miss), dodge(_dodge), parry(_parry),
        block(_block), critical(_critical), wpn_skill(_wpn_skill), range(10000) {
        set_attack_table();
    }

    void set_attack_table(void) override;
    int get_outcome(const int) override;
    void dump_table(void) override;
protected:
private:
    Random* random;
    float miss;
    float dodge;
    float parry;
    float block;
    float critical;
    int wpn_skill;

    int range;
    int miss_range;
    int dodge_range;
    int parry_range;
    int block_range;
    int critical_range;
};

#endif // MELEESPECIALTABLE_H

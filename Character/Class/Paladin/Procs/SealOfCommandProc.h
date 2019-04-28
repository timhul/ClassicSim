#ifndef SEALOFCOMMANDPROC_H
#define SEALOFCOMMANDPROC_H

#include "ProcPPM.h"

class Paladin;

class SealOfCommandProc: public ProcPPM {
public:
    SealOfCommandProc(Character* pchar);

    void proc_effect() override;

private:
    Paladin* paladin;

    void prepare_set_of_combat_iterations_spell_specific() override;
};

#endif // SEALOFCOMMANDPROC_H

#ifndef NIGHTFALLPROC_H
#define NIGHTFALLPROC_H

#include "Proc.h"

class Nightfall;

class NightfallProc: public Proc {
public:
    NightfallProc(Character* pchar, const double proc_rate);
    ~NightfallProc() override;

private:
    Nightfall* buff;
    void proc_effect() override;
};

#endif // NIGHTFALLPROC_H

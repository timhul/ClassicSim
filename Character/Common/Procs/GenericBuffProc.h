#ifndef GENERICBUFFPROC_H
#define GENERICBUFFPROC_H

#include "Proc.h"

class Buff;

class GenericBuffProc: public Proc {
public:
    GenericBuffProc(Character* pchar,
                              const QString& proc_name,
                              const QString &icon,
                              const QVector<ProcInfo::Source>& proc_sources,
                              const double proc_rate,
                              Buff *buff);
    ~GenericBuffProc() override;

private:
    Buff* buff;
    void proc_effect() override;
};

#endif // GENERICBUFFPROC_H

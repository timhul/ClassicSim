#ifndef EXTERNALBUFF_H
#define EXTERNALBUFF_H

#include "Buff.h"
#include <QVersionNumber>

class ExternalBuff: public Buff {
public:
    ExternalBuff(Character*, const QString& name, const int dur, const int base_charges,
                 QString icon, QString description, QVersionNumber min_patch);
    virtual ~ExternalBuff();

    QString get_icon() const;
    QString get_description() const;
    bool valid_for_patch(const QString& patch) const;

protected:
    virtual void buff_effect_when_applied() = 0;
    virtual void buff_effect_when_removed() = 0;

    const QString icon;
    const QString description;
    const QVersionNumber min_patch;

private:
};

#endif // EXTERNALBUFF_H

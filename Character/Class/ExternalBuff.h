#ifndef EXTERNALBUFF_H
#define EXTERNALBUFF_H

#include "Buff.h"
#include <QVersionNumber>

enum ExternalBuffName {
    RallyingCryOfTheDragonslayer = 0,
    SpiritOfZandalar,
    SongflowerSerenade,
    ElixirOfTheMongoose,
    ElixirOfBruteForce,
    ElixirOfGiants,
    WinterfallFirewater,
    JujuPower,
    MarkOfTheWild,
    ScrollOfStrengthIV,
    SmokedDesertDumplings,
    SunderArmor,
    FaerieFire,
    CurseOfRecklessness,
    Annihilator
};

class ExternalBuff;

ExternalBuff* get_external_buff_by_name(const ExternalBuffName, Character*);

class ExternalBuff: public Buff {
public:
    ExternalBuff(Character*,
                 const QString& name,
                 const int dur,
                 const int base_charges,
                 ExternalBuffName buff_name,
                 QString icon,
                 QString description,
                 QVersionNumber min_patch);
    virtual ~ExternalBuff();

    QString get_icon() const;
    QString get_description() const;
    bool valid_for_patch(const QString& patch) const;

protected:
    virtual void buff_effect_when_applied();
    virtual void buff_effect_when_removed();

    const ExternalBuffName buff_name;
    const QString icon;
    const QString description;
    const QVersionNumber min_patch;

private:
};

#endif // EXTERNALBUFF_H

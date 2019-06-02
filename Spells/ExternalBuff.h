#ifndef EXTERNALBUFF_H
#define EXTERNALBUFF_H

#include "AvailableFactions.h"
#include "Buff.h"

#include <QVersionNumber>

enum class ExternalBuffName: int {
    Annihilator = 0,
    BattleShout,
    BattleSquawk,
    BlessingOfKings,
    BlessingOfMight,
    BlessingOfWisdom,
    CurseOfRecklessness,
    ElixirOfBruteForce,
    ElixirOfGiants,
    ElixirOfTheMongoose,
    FaerieFire,
    FengusFerocity,
    FlaskOfDistilledWisdom,
    FlaskOfSupremePower,
    GreaterArcaneElixir,
    GrilledSquid,
    GroundScorpokAssay,
    JujuMight,
    JujuPower,
    MagebloodPotion,
    MarkOfTheWild,
    NightfinSoup,
    ROIDS,
    RallyingCryOfTheDragonslayer,
    SaygesDarkFortuneOfDamage,
    ScrollOfStrengthIV,
    SlipkiksSavvy,
    SmokedDesertDumplings,
    SongflowerSerenade,
    SpiritOfZandalar,
    SunderArmor,
    TotemManaSpring,
    TotemStrengthOfEarth,
    WinterfallFirewater,
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
                 AvailableFactions::Name faction,
                 QString icon,
                 QString description);
    virtual ~ExternalBuff();

    QString get_description() const;
    bool valid_for_faction(AvailableFactions::Name faction) const;
    ExternalBuffName get_enum_value() const;

protected:
    virtual void buff_effect_when_applied();
    virtual void buff_effect_when_removed();

    const ExternalBuffName buff_name;
    AvailableFactions::Name faction;
    const QString description;
};

#endif // EXTERNALBUFF_H

#pragma once

#include "AvailableFactions.h"
#include "SelfBuff.h"

#include <QVersionNumber>

enum class ExternalBuffName: int {
    Annihilator = 0,
    BattleShout,
    BattleSquawk,
    BlessingOfKings,
    BlessingOfMight,
    BlessingOfWisdom,
    CurseOfRecklessness,
    DragonbreathChili,
    ElixirOfBruteForce,
    ElixirOfGiants,
    ElixirOfGreaterAgility,
    ElixirOfTheMongoose,
    FaerieFire,
    FengusFerocity,
    FireVulnerability,
    FlaskOfDistilledWisdom,
    FlaskOfSupremePower,
    GreaterArcaneElixir,
    GrilledSquid,
    GroundScorpokAssay,
    ImprovedShadowBolt,
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
    TrueshotAura,
    WinterfallFirewater,
};

class ExternalBuff;

ExternalBuff* get_external_buff_by_name(const ExternalBuffName, Character*);

class ExternalBuff: public SelfBuff {
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

protected:
    virtual void buff_effect_when_applied();
    virtual void buff_effect_when_removed();

    const ExternalBuffName buff_name;
    AvailableFactions::Name faction;
    const QString description;
};

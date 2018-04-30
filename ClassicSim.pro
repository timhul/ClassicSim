QT += quick
CONFIG += c++11 console

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    Event/Event.cpp \
    Engine/Engine.cpp \
    Event/Events/EncounterEnd.cpp \
    Event/Events/EncounterStart.cpp \
    Queue/Queue.cpp \
    Character/Race/Races/Human.cpp \
    Character/Race/Races/Dwarf.cpp \
    Character/Race/Races/NightElf.cpp \
    Character/Race/Races/Gnome.cpp \
    Character/Race/Races/Orc.cpp \
    Character/Race/Races/Undead.cpp \
    Character/Race/Races/Tauren.cpp \
    Character/Race/Races/Troll.cpp \
    Character/Class/Warrior/Warrior.cpp \
    Character/Class/Priest/Priest.cpp \
    Character/Class/Rogue/Rogue.cpp \
    Character/Class/Mage/Mage.cpp \
    Character/Class/Druid/Druid.cpp \
    Character/Class/Hunter/Hunter.cpp \
    Character/Class/Warlock/Warlock.cpp \
    Character/Class/Shaman/Shaman.cpp \
    Character/Class/Paladin/Paladin.cpp \
    Character/Character.cpp \
    Event/Events/PlayerAction.cpp \
    Test/Test.cpp \
    Equipment/Item/MeleeWeapon/Specialization/Mainhand.cpp \
    Equipment/Item/MeleeWeapon/Specialization/Offhand.cpp \
    Equipment/Item/MeleeWeapon/Specialization/TwoHander.cpp \
    Equipment/Equipment.cpp \
    CombatRoll/AttackResult.cpp \
    CombatRoll/CombatRoll.cpp \
    CombatRoll/AttackTables/WhiteHitTable.cpp \
    Character/Class/Spell.cpp \
    Character/Class/Warrior/Spells/Bloodthirst.cpp \
    Event/Events/OffhandMeleeHit.cpp \
    Event/Events/MainhandMeleeHit.cpp \
    Event/Events/CooldownReady.cpp \
    Character/Class/Warrior/Spells/Whirlwind.cpp \
    Character/Class/Warrior/Spells/Execute.cpp \
    Character/Class/Warrior/Spells/HeroicStrike.cpp \
    Character/Class/Warrior/Spells/Overpower.cpp \
    Character/Class/Warrior/Spells/Hamstring.cpp \
    Character/Class/Warrior/Spells/Recklessness.cpp \
    Statistics/Statistics.cpp \
    CombatRoll/AttackTables/MeleeSpecialTable.cpp \
    Mechanics/Mechanics.cpp \
    Character/Class/Buff.cpp \
    Character/Class/Warrior/Buffs/Flurry.cpp \
    Event/Events/BuffApplication.cpp \
    Event/Events/BuffRemoval.cpp \
    CombatLog/CombatLog.cpp \
    Character/Class/TalentTree.cpp \
    Character/Class/Talent.cpp \
    Character/Class/Warrior/TalentTrees/Arms.cpp \
    Character/Class/Warrior/TalentTrees/Fury.cpp \
    Character/Class/Warrior/TalentTrees/Protection.cpp \
    Character/Class/Warrior/TalentTrees/Fury/Cruelty.cpp \
    Character/Class/Warrior/TalentTrees/Arms/ImprovedRend.cpp \
    Character/Class/Warrior/TalentTrees/Arms/Impale.cpp \
    Character/Talents.cpp \
    Character/Class/Warrior/TalentTrees/Fury/BoomingVoice.cpp \
    Character/Class/Warrior/TalentTrees/Fury/ImprovedDemoralizingShout.cpp \
    Character/Class/Warrior/TalentTrees/Fury/ImprovedCleave.cpp \
    Character/Class/Warrior/TalentTrees/Fury/ImprovedBattleShout.cpp \
    Character/Class/Warrior/TalentTrees/Fury/DualWieldSpecialization.cpp \
    Character/Class/Warrior/TalentTrees/Fury/ImprovedExecute.cpp \
    Character/Class/Warrior/TalentTrees/Fury/ImprovedSlam.cpp \
    Character/Class/Warrior/TalentTrees/Fury/ImprovedBerserkerRage.cpp \
    Character/Class/Warrior/TalentTrees/Fury/FlurryTalent.cpp \
    Character/Class/Warrior/TalentTrees/Fury/BloodthirstTalent.cpp \
    Character/Class/GenericTalent.cpp \
    GUI/GUIControl.cpp \
    Character/Class/Warrior/TalentTrees/Arms/ImprovedHeroicStrike.cpp \
    Character/Class/Warrior/TalentTrees/Arms/TacticalMastery.cpp \
    Character/Class/Warrior/TalentTrees/Arms/ImprovedOverpower.cpp \
    Character/Class/Warrior/TalentTrees/Arms/TwoHandedWeaponSpecialization.cpp \
    Character/Class/Warrior/TalentTrees/Arms/AxeSpecialization.cpp \
    Character/Class/Warrior/TalentTrees/Arms/SweepingStrikes.cpp \
    Character/Class/Warrior/TalentTrees/Arms/SwordSpecialization.cpp \
    Character/Class/Warrior/TalentTrees/Arms/PolearmSpecialization.cpp \
    Character/Class/Warrior/TalentTrees/Arms/MortalStrikeTalent.cpp \
    Character/Stats.cpp \
    Character/Class/Warrior/TalentTrees/Arms/DeepWoundsTalent.cpp \
    Character/Class/Warrior/Spells/DeepWounds.cpp \
    Event/Events/DotTick.cpp \
    Character/Class/Warrior/Buffs/HeroicStrikeBuff.cpp \
    Character/Class/Warrior/TalentTrees/Fury/UnbridledWrathTalent.cpp \
    Character/Class/Warrior/Procs/UnbridledWrath.cpp \
    Character/Class/Warrior/TalentTrees/Fury/DeathWishTalent.cpp \
    Character/Class/Warrior/Spells/DeathWish.cpp \
    Character/Class/Warrior/Buffs/DeathWishBuff.cpp \
    Character/Class/Warrior/Buffs/BattleShoutBuff.cpp \
    Character/Class/Warrior/Spells/BattleShout.cpp \
    Character/Class/Warrior/Spells/BerserkerRage.cpp \
    Equipment/Item/MeleeWeapon/Specialization/Onehand.cpp \
    Equipment/EquipmentDb/EquipmentDb.cpp \
    Equipment/Item/Item.cpp \
    Equipment/Item/ItemModel.cpp \
    Equipment/Item/MeleeWeapon/WeaponModel.cpp \
    Equipment/EquipmentDb/ItemFileReader.cpp \
    Equipment/EquipmentDb/WeaponFileReader.cpp \
    Equipment/Item/MeleeWeapon/Specialization/Ranged.cpp \
    Equipment/Item/MeleeWeapon/Weapon.cpp \
    Test/Warrior/TestWarrior.cpp \
    Test/Warrior/Spells/TestExecute.cpp \
    Test/TestSpell.cpp \
    Test/Warrior/TestSpellWarrior.cpp \
    Test/Warrior/Spells/TestHeroicStrike.cpp \
    Test/Warrior/Spells/TestBloodthirst.cpp \
    Character/Class/GeneralSpells/MainhandAttack.cpp \
    Character/Class/GeneralSpells/OffhandAttack.cpp \
    Character/Class/Warrior/Spells/MainhandAttackWarrior.cpp \
    Character/Class/Warrior/Spells/OffhandAttackWarrior.cpp \
    Test/Warrior/Spells/TestMainhandAttackWarrior.cpp \
    Test/Warrior/Spells/TestWhirlwind.cpp \
    Test/Warrior/Spells/TestOverpower.cpp \
    Test/TestBuff.cpp \
    Test/Warrior/Buffs/TestFlurryWarrior.cpp \
    Test/Warrior/TestBuffWarrior.cpp \
    Test/Warrior/Spells/TestOffhandAttackWarrior.cpp \
    Test/Warrior/Spells/TestDeepWounds.cpp \
    Character/Class/Warrior/Spells/Bloodrage.cpp \
    Event/Events/ResourceGain.cpp \
    Test/Warrior/Spells/TestBloodrage.cpp \
    Character/Class/Proc.cpp \
    Character/Class/GeneralSpells/Enchants/WindfuryTotemAttack.cpp

HEADERS += \
    Queue/Queue.h \
    Event/Event.h \
    Engine/Engine.h \
    Event/Events/EncounterEnd.h \
    Event/Events/EncounterStart.h \
    Character/Character.h \
    Character/Race/Race.h \
    Character/Race/Races/Human.h \
    Character/Race/Races/Dwarf.h \
    Character/Race/Races/NightElf.h \
    Character/Race/Races/Gnome.h \
    Character/Race/Races/Orc.h \
    Character/Race/Races/Undead.h \
    Character/Race/Races/Tauren.h \
    Character/Race/Races/Troll.h \
    Character/Class/Warrior/Warrior.h \
    Character/Class/Priest/Priest.h \
    Character/Class/Rogue/Rogue.h \
    Character/Class/Mage/Mage.h \
    Character/Class/Druid/Druid.h \
    Character/Class/Hunter/Hunter.h \
    Character/Class/Warlock/Warlock.h \
    Character/Class/Shaman/Shaman.h \
    Character/Class/Paladin/Paladin.h \
    Event/Events/PlayerAction.h \
    Test/Test.h \
    Equipment/Equipment.h \
    Equipment/Item/Item.h \
    Equipment/Item/MeleeWeapon/Specialization/Mainhand.h \
    Equipment/Item/MeleeWeapon/Specialization/Offhand.h \
    Equipment/Item/MeleeWeapon/Specialization/TwoHander.h \
    Target/Target.h \
    CombatRoll/AttackResult.h \
    CombatRoll/AttackTable.h \
    CombatRoll/CombatRoll.h \
    CombatRoll/AttackTables/WhiteHitTable.h \
    CombatRoll/Random.h \
    Character/Class/Spell.h \
    Character/Class/Warrior/Spells/Bloodthirst.h \
    Character/Class/AutoAttack.h \
    Event/Events/OffhandMeleeHit.h \
    Event/Events/MainhandMeleeHit.h \
    Event/Events/CooldownReady.h \
    Character/Class/Warrior/Spells/Whirlwind.h \
    Character/Class/Warrior/Spells/Execute.h \
    Character/Class/Warrior/Spells/HeroicStrike.h \
    Character/Class/Warrior/Spells/Overpower.h \
    Character/Class/Warrior/Spells/Hamstring.h \
    Character/Class/Warrior/Spells/Recklessness.h \
    Statistics/Statistics.h \
    CombatRoll/AttackTables/MeleeSpecialTable.h \
    Mechanics/Mechanics.h \
    Character/Class/Buff.h \
    Character/Class/Warrior/Buffs/Flurry.h \
    Event/Events/BuffApplication.h \
    Event/Events/BuffRemoval.h \
    CombatLog/CombatLog.h \
    Character/Class/TalentTree.h \
    Character/Class/Talent.h \
    Character/Class/Warrior/TalentTrees/Arms.h \
    Character/Class/Warrior/TalentTrees/Fury.h \
    Character/Class/Warrior/TalentTrees/Protection.h \
    Character/Class/Warrior/TalentTrees/Fury/Cruelty.h \
    Character/Class/Warrior/TalentTrees/Arms/ImprovedRend.h \
    Character/Class/Warrior/TalentTrees/Arms/Impale.h \
    Character/Talents.h \
    Character/Class/Warrior/TalentTrees/Fury/BoomingVoice.h \
    Character/Class/Warrior/TalentTrees/Fury/ImprovedDemoralizingShout.h \
    Character/Class/Warrior/TalentTrees/Fury/ImprovedCleave.h \
    Character/Class/Warrior/TalentTrees/Fury/ImprovedBattleShout.h \
    Character/Class/Warrior/TalentTrees/Fury/DualWieldSpecialization.h \
    Character/Class/Warrior/TalentTrees/Fury/ImprovedExecute.h \
    Character/Class/Warrior/TalentTrees/Fury/ImprovedSlam.h \
    Character/Class/Warrior/TalentTrees/Fury/ImprovedBerserkerRage.h \
    Character/Class/Warrior/TalentTrees/Fury/FlurryTalent.h \
    Character/Class/Warrior/TalentTrees/Fury/BloodthirstTalent.h \
    Character/Class/GenericTalent.h \
    GUI/GUIControl.h \
    Character/Class/Warrior/TalentTrees/Arms/ImprovedHeroicStrike.h \
    Character/Class/Warrior/TalentTrees/Arms/TacticalMastery.h \
    Character/Class/Warrior/TalentTrees/Arms/ImprovedOverpower.h \
    Character/Class/Warrior/TalentTrees/Arms/TwoHandedWeaponSpecialization.h \
    Character/Class/Warrior/TalentTrees/Arms/AxeSpecialization.h \
    Character/Class/Warrior/TalentTrees/Arms/SweepingStrikes.h \
    Character/Class/Warrior/TalentTrees/Arms/SwordSpecialization.h \
    Character/Class/Warrior/TalentTrees/Arms/PolearmSpecialization.h \
    Character/Class/Warrior/TalentTrees/Arms/MortalStrikeTalent.h \
    Character/Stats.h \
    Character/Class/Warrior/TalentTrees/Arms/DeepWoundsTalent.h \
    Character/Class/Warrior/Spells/DeepWounds.h \
    Event/Events/DotTick.h \
    Character/Class/Warrior/Buffs/HeroicStrikeBuff.h \
    Character/Class/Warrior/Procs/UnbridledWrath.h \
    Character/Class/Warrior/TalentTrees/Fury/UnbridledWrathTalent.h \
    Character/Class/Warrior/TalentTrees/Fury/DeathWishTalent.h \
    Character/Class/Warrior/Spells/DeathWish.h \
    Character/Class/Warrior/Buffs/DeathWishBuff.h \
    Character/Class/Warrior/Buffs/BattleShoutBuff.h \
    Character/Class/Warrior/Spells/BattleShout.h \
    Character/Class/Warrior/Spells/BerserkerRage.h \
    Equipment/Item/MeleeWeapon/Specialization/Onehand.h \
    Equipment/EquipmentDb/EquipmentDb.h \
    Equipment/Item/ItemModel.h \
    Equipment/Item/MeleeWeapon/WeaponModel.h \
    Equipment/EquipmentDb/ItemFileReader.h \
    Equipment/EquipmentDb/WeaponFileReader.h \
    Equipment/Item/MeleeWeapon/Specialization/Ranged.h \
    Equipment/Item/MeleeWeapon/Weapon.h \
    Test/Warrior/TestWarrior.h \
    Test/Warrior/Spells/TestExecute.h \
    Test/TestSpell.h \
    Test/Warrior/TestSpellWarrior.h \
    Test/Warrior/Spells/TestHeroicStrike.h \
    Test/Warrior/Spells/TestBloodthirst.h \
    Character/Class/GeneralSpells/MainhandAttack.h \
    Character/Class/GeneralSpells/OffhandAttack.h \
    Character/Class/Warrior/Spells/MainhandAttackWarrior.h \
    Character/Class/Warrior/Spells/OffhandAttackWarrior.h \
    Test/Warrior/Spells/TestMainhandAttackWarrior.h \
    Test/Warrior/Spells/TestWhirlwind.h \
    Test/Warrior/Spells/TestOverpower.h \
    Test/TestBuff.h \
    Test/Warrior/Buffs/TestFlurryWarrior.h \
    Test/Warrior/TestBuffWarrior.h \
    Test/Warrior/Spells/TestOffhandAttackWarrior.h \
    Test/Warrior/Spells/TestDeepWounds.h \
    Event/Events/ResourceGain.h \
    Character/Class/Warrior/Spells/Bloodrage.h \
    Test/Warrior/Spells/TestBloodrage.h \
    Character/Class/Proc.h \
    Character/Class/GeneralSpells/Enchants/WindfuryTotemAttack.h

INCLUDEPATH = C:\C++\ClassicSim\Engine \
    C:\C++\ClassicSim\Event \
    C:\C++\ClassicSim\Event\Events \
    C:\C++\ClassicSim\Queue \
    C:\C++\ClassicSim\Character \
    C:\C++\ClassicSim\Character\Race \
    C:\C++\ClassicSim\Character\Race\Races \
    C:\C++\ClassicSim\Character\Class \
    C:\C++\ClassicSim\Character\Class\Warrior \
    C:\C++\ClassicSim\Character\Class\Warrior\Spells \
    C:\C++\ClassicSim\Character\Class\Warrior\Buffs \
    C:\C++\ClassicSim\Character\Class\Warrior\Procs \
    C:\C++\ClassicSim\Character\Class\Warrior\TalentTrees \
    C:\C++\ClassicSim\Character\Class\Warrior\TalentTrees\Fury \
    C:\C++\ClassicSim\Character\Class\Warrior\TalentTrees\Arms \
    C:\C++\ClassicSim\Character\Class\Priest \
    C:\C++\ClassicSim\Character\Class\Rogue \
    C:\C++\ClassicSim\Character\Class\Mage \
    C:\C++\ClassicSim\Character\Class\Druid \
    C:\C++\ClassicSim\Character\Class\Hunter \
    C:\C++\ClassicSim\Character\Class\Warlock \
    C:\C++\ClassicSim\Character\Class\Shaman \
    C:\C++\ClassicSim\Character\Class\Paladin \
    C:\C++\ClassicSim\Equipment \
    C:\C++\ClassicSim\Equipment\Item \
    C:\C++\ClassicSim\Equipment\Item\MeleeWeapon \
    C:\C++\ClassicSim\Equipment\Item\MeleeWeapon\Specialization \
    C:\C++\ClassicSim\Equipment\EquipmentDb \
    C:\C++\ClassicSim\CombatRoll \
    C:\C++\ClassicSim\CombatRoll\AttackTables \
    C:\C++\ClassicSim\Target \
    C:\C++\ClassicSim\Statistics \
    C:\C++\ClassicSim\Mechanics \
    C:\C++\ClassicSim\Test \
    C:\C++\ClassicSim\Test\Warrior \
    C:\C++\ClassicSim\Test\Warrior\Spells \
    C:\C++\ClassicSim\Test\Warrior\Buffs \
    C:\C++\ClassicSim\Character\Class\GeneralSpells \
    C:\C++\ClassicSim\Character\Class\GeneralSpells\Enchants \
    C:\C++\ClassicSim\GUI

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

	

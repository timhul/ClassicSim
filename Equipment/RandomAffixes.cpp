#include "RandomAffixes.h"

#include <QDebug>
#include <QFile>

#include "RandomAffix.h"
#include "Stats.h"

RandomAffixes::RandomAffixes() {
    read_random_affixes("random_affixes.xml");
}

RandomAffixes::~RandomAffixes() {
    qDeleteAll(random_affixes_db);
    random_affixes_db.clear();
}

bool RandomAffixes::read_random_affixes(const QString& xml_file_path) {
    QFile file(xml_file_path);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Cannot read file" << xml_file_path << ":" << file.errorString();
        return false;
    }

    QXmlStreamReader reader(&file);

    if (reader.readNextStartElement()) {
        if (reader.name() == "random_affixes")
            random_affixes_file_handler(reader);
        else
            qDebug() << "Did not find initial <random_affixes> element in" << xml_file_path;
    }

    file.close();

    return true;
}

RandomAffix * RandomAffixes::get_affix(unsigned id) const {
    return random_affixes_db.contains(id) ? random_affixes_db[id] : nullptr;
}

bool RandomAffixes::random_affixes_file_handler(QXmlStreamReader &reader) {
    // Iterate on random affixes elements
    while (reader.readNextStartElement()) {
        if (!reader.attributes().hasAttribute("id")) {
            qDebug() << "Missing id attribute for <random_affix> element";
            for (const auto & attr : reader.attributes())
                qDebug() << attr.name() << attr.value();
            reader.skipCurrentElement();
            continue;
        }

        if (!reader.attributes().hasAttribute("phase")) {
            qDebug() << "Missing phase attribute for <random_affix> element";
            for (const auto & attr : reader.attributes())
                qDebug() << attr.name() << attr.value();
            reader.skipCurrentElement();
            continue;
        }

        // Initialize affix attributes
        unsigned affix_id = reader.attributes().value("id").toUInt();
        int affix_phase_uint = reader.attributes().value("phase").toInt();
        Content::Phase affix_phase = Content::get_phase(affix_phase_uint);
        QString affix_name;
        QStringList stats_list;
        QMap<ItemStats, unsigned> affix_stat_values;
        auto affix_stats = new Stats();

        // Duplicate checking
        if (random_affixes_db.contains(affix_id)) {
            qDebug() << QStringLiteral("Duplicate affixes with id : %1").arg(affix_id);
            continue;
        }

        while (reader.readNextStartElement()) {
            if (reader.name() == "info") {

                if (!reader.attributes().hasAttribute("name")) {
                    qDebug() << QString("Missing 'name' attribute for <info> element in <random_affix> '%1'").arg(affix_id);
                    reader.skipCurrentElement();
                    continue;
                }
                affix_name = reader.attributes().value("name").toString();
                reader.skipCurrentElement();
            }
            else if (reader.name() == "stats") {

                while (reader.readNextStartElement()) {
                    QXmlStreamAttributes attrs = reader.attributes();
                    if (reader.name() == "stat") {
                        affix_stats->add(attrs.value("type").toString(), attrs.value("value").toString());
                        QString typeString = attrs.value("type").toString();
                        typeString.replace("_", " ");
                        typeString = typeString.toLower();
                        typeString[0] = typeString[0].toUpper();

                        add_stat_to_map(attrs.value("type").toString(), attrs.value("value").toString(), affix_stat_values);
                        stats_list.append(QString("+%1 %2").arg(attrs.value("value").toString(), typeString));
                    }
                    reader.skipCurrentElement();
                }
            }
            else {
                reader.skipCurrentElement();
            }

        }

        // Add current affix to databse
        auto affix = new RandomAffix(affix_id, affix_phase, affix_name, affix_stats, stats_list, affix_stat_values);
        random_affixes_db[affix_id] = affix;
    }

    return true;
}

void RandomAffixes::add_stat_to_map(const QString &type, const QString &value, QMap<ItemStats, unsigned> &map) {
    if (type == "STRENGTH") {
        map.insert(ItemStats::Strength, value.toUInt());
    }
    else if (type == "AGILITY") {
        map.insert(ItemStats::Agility, value.toUInt());
    }
    else if (type == "STAMINA") {
        map.insert(ItemStats::Stamina, value.toUInt());
    }
    else if (type == "INTELLECT") {
        map.insert(ItemStats::Intellect, value.toUInt());
    }
    else if (type == "SPIRIT") {
        map.insert(ItemStats::Spirit, value.toUInt());
    }
    else if (type == "ATTACK_POWER") {
        map.insert(ItemStats::AttackPower, value.toUInt());
    }
    else if (type == "RANGED_ATTACK_POWER") {
        map.insert(ItemStats::RangedAttackPower, value.toUInt());
    }
    else if (type == "AXE_SKILL") {
        map.insert(ItemStats::SkillAxe, value.toUInt());
    }
    else if (type == "DAGGER_SKILL") {
        map.insert(ItemStats::SkillDagger, value.toUInt());
    }
    else if (type == "MACE_SKILL") {
        map.insert(ItemStats::SkillMace, value.toUInt());
    }
    else if (type == "SWORD_SKILL") {
        map.insert(ItemStats::SkillSword, value.toUInt());
    }
    else if (type == "TWOHAND_AXE_SKILL") {
        map.insert(ItemStats::Skill2hAxe, value.toUInt());
    }
    else if (type == "TWOHAND_MACE_SKILL") {
        map.insert(ItemStats::Skill2hMace, value.toUInt());
    }
    else if (type == "TWOHAND_SWORD_SKILL") {
        map.insert(ItemStats::Skill2hSword, value.toUInt());
    }
    else if (type == "BOW_SKILL") {
        map.insert(ItemStats::SkillBow, value.toUInt());
    }
    else if (type == "CROSSBOW_SKILL") {
        map.insert(ItemStats::SkillCrossbow, value.toUInt());
    }
    else if (type == "GUN_SKILL") {
        map.insert(ItemStats::SkillGun, value.toUInt());
    }
    else if (type == "MANA_PER_5") {
        map.insert(ItemStats::ManaPer5, value.toUInt());
    }
    else if (type == "HEALTH_PER_5") {
        map.insert(ItemStats::HealthPer5, value.toUInt());
    }
    else if (type == "SPELL_DAMAGE") {
        map.insert(ItemStats::SpellDamage, value.toUInt());
    }
    else if (type == "SPELL_DAMAGE_ARCANE") {
        map.insert(ItemStats::SpellDamageArcane, value.toUInt());
    }
    else if (type == "SPELL_DAMAGE_FIRE") {
        map.insert(ItemStats::SpellDamageFire, value.toUInt());
    }
    else if (type == "SPELL_DAMAGE_FROST") {
        map.insert(ItemStats::SpellDamageFrost, value.toUInt());
    }
    else if (type == "SPELL_DAMAGE_HOLY") {
        map.insert(ItemStats::SpellDamageHoly, value.toUInt());
    }
    else if (type == "SPELL_DAMAGE_NATURE") {
        map.insert(ItemStats::SpellDamageNature, value.toUInt());
    }
    else if (type == "SPELL_DAMAGE_SHADOW") {
        map.insert(ItemStats::SpellDamageShadow, value.toUInt());
    }
    else if (type == "SPELL_DAMAGE_BEAST") {
        map.insert(ItemStats::SpellDamageVersusBeast, value.toUInt());
    }
    else if (type == "SPELL_DAMAGE_DEMON") {
        map.insert(ItemStats::SpellDamageVersusDemon, value.toUInt());
    }
    else if (type == "SPELL_DAMAGE_DRAGONKIN") {
        map.insert(ItemStats::SpellDamageVersusDragonkin, value.toUInt());
    }
    else if (type == "SPELL_DAMAGE_ELEMENTAL") {
        map.insert(ItemStats::SpellDamageVersusElemental, value.toUInt());
    }
    else if (type == "SPELL_DAMAGE_GIANT") {
        map.insert(ItemStats::SpellDamageVersusGiant, value.toUInt());
    }
    else if (type == "SPELL_DAMAGE_HUMANOID") {
        map.insert(ItemStats::SpellDamageVersusHumanoid, value.toUInt());
    }
    else if (type == "SPELL_DAMAGE_MECHANICAL") {
        map.insert(ItemStats::SpellDamageVersusMechanical, value.toUInt());
    }
    else if (type == "SPELL_DAMAGE_UNDEAD") {
        map.insert(ItemStats::SpellDamageVersusUndead, value.toUInt());
    }
    else if (type == "ARMOR") {
        map.insert(ItemStats::Armor, value.toUInt());
    }
    else if (type == "DEFENSE") {
        map.insert(ItemStats::Defense, value.toUInt());
    }
    else if (type == "DODGE_CHANCE") {
        map.insert(ItemStats::DodgeChance, value.toUInt());
    }
    else if (type == "PARRY_CHANCE") {
        map.insert(ItemStats::ParryChance, value.toUInt());
    }
    else if (type == "ARCANE_RESISTANCE") {
        map.insert(ItemStats::ResistanceArcane, value.toUInt());
    }
    else if (type == "FIRE_RESISTANCE") {
        map.insert(ItemStats::ResistanceFire, value.toUInt());
    }
    else if (type == "FROST_RESISTANCE") {
        map.insert(ItemStats::ResistanceFrost, value.toUInt());
    }
    else if (type == "HOLY_RESISTANCE") {
        map.insert(ItemStats::ResistanceHoly, value.toUInt());
    }
    else if (type == "NATURE_RESISTANCE") {
        map.insert(ItemStats::ResistanceNature, value.toUInt());
    }
    else if (type == "SHADOW_RESISTANCE") {
        map.insert(ItemStats::ResistanceShadow, value.toUInt());
    }
}

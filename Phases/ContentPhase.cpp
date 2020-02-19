#include "ContentPhase.h"

#include "Utils/Check.h"

QString Content::get_description_for_phase(const Content::Phase phase) {
    switch (phase) {
    case Content::Phase::MoltenCore:
        return "(1) Molten Core, Onyxia, Maraudon";
    case Content::Phase::DireMaul:
        return "(2) Dire Maul, Azuregos, Kazzak, Honor rewards";
    case Content::Phase::BlackwingLair:
        return "(3) Blackwing Lair, Darkmoon Faire, AV/WSG";
    case Content::Phase::ZulGurub:
        return "(4) Zul'Gurub, Green Dragons, Arathi Basin";
    case Content::Phase::AhnQiraj:
        return "(5) Ahn'Qiraj, improved dungeon loot";
    case Content::Phase::Naxxramas:
        return "(6) Naxxramas";
    }

    return "<missing phase>";
}

QString Content::get_shortname_for_phase(const Content::Phase phase) {
    switch (phase) {
    case Content::Phase::MoltenCore:
        return "(1) MC/Ony";
    case Content::Phase::DireMaul:
        return "(2) DM";
    case Content::Phase::BlackwingLair:
        return "(3) BWL";
    case Content::Phase::ZulGurub:
        return "(4) ZG/AB";
    case Content::Phase::AhnQiraj:
        return "(5) AQ";
    case Content::Phase::Naxxramas:
        return "(6) Naxx";
    }

    return "<missing phase>";
}

Content::Phase Content::get_phase(const int phase) {
    check((phase >= static_cast<int>(Content::Phase::MoltenCore) && phase <= static_cast<int>(Content::Phase::Naxxramas)),
          QString("Phase %1 out of enum range").arg(phase).toStdString());

    return static_cast<Content::Phase>(phase);
}

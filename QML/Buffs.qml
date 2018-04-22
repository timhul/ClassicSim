import QtQuick 2.0

Rectangle {
    color: "transparent"

    anchors.fill: parent

    ListModel {
        id: buffModel

        ListElement {
            bname: "BATTLE_SHOUT"
            bicon: "Assets/warrior/fury/tier3/Ability_warrior_battleshout.png"
            btext: "Improved Battle Shout\nIncreases attack power by 290"
        }
        ListElement {
            bname: "LEADER_OF_THE_PACK"
            bicon: "Assets/buffs/Spell_nature_unyeildingstamina.png"
            btext: "Leader of the Pack\n+3% Critical Strike"
        }
        ListElement {
            bname: "WINDFURY"
            bicon: "Assets/buffs/Spell_nature_windfury.png"
            btext: "Windfury Totem\n20% chance to grant 1 extra attack with extra melee ap"
        }
        ListElement {
            bname: "MARK_OF_THE_WILD"
            bicon: "Assets/buffs/Spell_nature_regeneration.png"
            btext: "Improved Mark of the Wild\n+20 all attributes"
        }
        ListElement {
            bname: "BLESSING_OF_KINGS"
            bicon: "Assets/buffs/Spell_magic_greaterblessingofkings.png"
            btext: "Greater Blessing of Kings\nIncreases total stats by 10%"
        }
        ListElement {
            bname: "BLESSING_OF_MIGHT"
            bicon: "Assets/buffs/Spell_holy_greaterblessingofkings.png"
            btext: "Greater Blessing of Kings\nIncreases melee attack power by 185"
        }
        ListElement {
            bname: "MONGOOSE"
            bicon: "Assets/buffs/Inv_potion_32.png"
            btext: "Elixir of the Mongoose\n+25 Agility, +%2 Critical Strike"
        }
        ListElement {
            bname: "GIANTS"
            bicon: "Assets/buffs/Inv_potion_61.png"
            btext: "Elixir of Giants\n+25 Strength"
        }
        ListElement {
            bname: "BRUTE_FORCE"
            bicon: "Assets/buffs/Inv_potion_40.png"
            btext: "Elixir of Brute Force\n+18 Strength and Stamina"
        }
        ListElement {
            bname: "JUJU_POWER"
            bicon: "Assets/buffs/Inv_misc_monsterscales_11.png"
            btext: "Juju Power\n+30 Strength"
        }
        ListElement {
            bname: "JUJU_MIGHT"
            bicon: "Assets/buffs/Inv_misc_monsterscales_07.png"
            btext: "Juju Might\n+40 Attack power"
        }
        ListElement {
            bname: "ROIDS"
            bicon: "Assets/buffs/Inv_stone_15.png"
            btext: "R.O.I.D.S\n+25 Strength"
        }
        ListElement {
            bname: "WINTERFALL_FIREWATER"
            bicon: "Assets/buffs/Inv_potion_92.png"
            btext: "Winterfall Firewater\n+35 Melee attack power"
        }
        ListElement {
            bname: "SMOKED_DESERT_DUMPLINGS"
            bicon: "Assets/buffs/Inv_misc_food_64.png"
            btext: "Smoked Desert Dumplings\n+20 Strength"
        }
        ListElement {
            bname: "SCROLL_OF_STRENGTH_IV"
            bicon: "Assets/buffs/Inv_scroll_02.png"
            btext: "Scroll of Strength IV\n+17 Strength"
        }
        ListElement {
            bname: "ONYXIA_BUFF"
            bicon: "Assets/buffs/Inv_misc_head_dragon_01.png"
            btext: "Rallying Cry of the Dragonslayer\n+10% Spell crit, +5% melee/ranged crit, +140 attack power"
        }
        ListElement {
            bname: "SONGFLOWER_SERENADE"
            bicon: "Assets/buffs/Spell_holy_mindvision.png"
            btext: "Songflower Serenade\n+5% Crit, +15 all attributes"
        }
        ListElement {
            bname: "SPIRIT_OF_ZANDALAR"
            bicon: "Assets/buffs/Ability_creature_poison_05.png"
            btext: "Spirit of Zandalar\n15% all stats and 10% movement speed"
        }
        ListElement {
            bname: "FENGUS_FEROCITY"
            bicon: "Assets/buffs/Spell_nature_undyingstrength.png"
            btext: "Fengus' Ferocity\n+200 Attack power"
        }
    }

    GridView {
        anchors.fill: parent
        anchors.margins: 20

        cellWidth: 300
        cellHeight: 70

        model: buffModel
        delegate: BuffBox {
            buffName: bname
            buffIcon: bicon
            buffText: btext
        }

        flow: GridView.FlowTopToBottom
    }
}

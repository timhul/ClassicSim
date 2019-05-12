# Introduction

This is an event-driven gameplay simulator for World of Warcraft Classic written in C++. It is called "ClassicSim", or
CSIM for short. Its purpose is to provide feedback to a user regarding the value of equipment, talents, consumables,
rotation choices, etc.

For information regarding new features / bug fixes in upcoming release, check [Next release](#next-release).

# Licensing

Licensing information can be found in [LICENSE.md](https://github.com/timhul/ClassicSim/blob/master/LICENSE).

# Downloads

Releases are available at [the ClassicSim website](https://classicsim.org/?C=M;O=D).

# Features of this tool

These are some of the features of this tool:

* Talent calculator (try shift-left/right click talents)
* World buffs and consumables
* Enchants
* Rulesets (Standard, Vaelastrasz, Loatheb)
* Equipment sheet (with full stat filter support)
* Data-driven rotations
* Statistics

# Mechanic implementation details

Interested in how certain mechanics are currently implemented? Check
[Mechanics Details](https://github.com/timhul/ClassicSim/wiki/Mechanics-Details) in the wiki.

# Future work

See [the Release Roadmap](https://github.com/timhul/ClassicSim/wiki/Release-Roadmap) for information regarding the
upcoming releases.

# Next release

Upcoming features and bug fixes that are merged but not yet built and made available as a release:

* Target base armor now modifiable in Settings.
* Button to reset defaults in Settings now available.
* UX improvements - more obvious buttons, improved layout in Settings, faction text colors for certain elements.

# Release notes

## v0.3-alpha-1 (released 2019-05-08):

* Paladin support (spells, talents, gear sets, Seal of the Crusader and Seal of Command rotations).
* Items now sorted according to content phases rather than original vanilla patches.
* More two-hand weapons, necks, backs, and plate items available.
* Fix bug for Warriors using Vaelastrasz ruleset which caused Execute to not be evaluated properly.
* Demonic Runes and Night Dragon's Breath now usable in rotations.
* Buffs and debuffs can now be range-selected with shift-click and toggled with ctrl.
* Flask of Supreme Power, Flask of Distilled Wisdom, Mageblood Potion are available to use as external buffs.
* Mutually exclusive buff groups are now in place, selecting e.g. a flask will deactivate any other active flask effect.
* Improved Backstab now yields the proper crit chance to Backstab.

## v0.2 (released 2019-04-22):

* Conditions for rotational choices are now displayed in the GUI under Rotations.
* Rotation and internal engine statistics now displayed in the GUI under Statistics.
* Hunter PvP sets and many non-set mail items added.
* Enchants are now stored between gear setup changes and sessions.
* Vaelastrasz ruleset properly yields resource gains again.
* Resource gains now displayed by gain per 5s instead of total gain.

## Restrictions:

* If scrolling down to the bottom of a rotation and selecting another then the new rotation is not displayed properly. Fixed by re-selecting the rotation.

## v0.2-alpha-3 (released 2019-04-14):

* All DPS increasing talents except melee/Arcane Shot/Serpent Sting boosts now available for Hunter.
* Pet (Cat) has been added. It is fully affected by Beast Mastery talents.
* Many Hunter-relevant items and sets added.
* Projectiles can now be equipped.
* Usage of Hunter's Mark/Rapid Fire/Aspect of the Hawk/Bestial Wrath.
* Lesser/Brilliant Mana Oil available as temporary enchants.
* Sniper scopes available as enchants for Hunters.
* Blessing of Wisdom/Mana Spring Totem and Grilled Squid available as external buffs.
* Quiver bonus is hardcoded as a 15% ranged attack speed increase.
* Added player reaction to auto shot to improve the flow of Hunter AS/MS rotation.
* Fix crash if simming Hunter with a mainhand equipped but no ranged weapon.

## Restrictions

* Only Cat is available to use as pet.
* It is not possible to simulate without 15% quiver bonus for Hunter.
* Sorting projectiles on type does not work.

## v0.2-alpha-2 (released 2019-03-24):

- Rudimentary Hunter support (Aimed Shot / Multi-Shot rotation).
- User setup saved on exit and loaded on boot.
- Battle Shout now selectable as external buff for non-Warriors.

## Restrictions

* Crash if simming Hunter with a mainhand equipped but no ranged weapon.
* Only Aimed Shot/Multi-Shot available for hunter rotation.
* Only Efficiency and Aimed Shot available as implemented talents.
* Only a single bow available for selection.
* Ammunition not available for selection.
* No mp5 gear is available for selection.
* No pet.

## v0.2-alpha-1 (released 2019-01-20):

- Set bonus information now displayed in item tooltips.
- Many set bonuses added to existing items.
- New set items added.
- Berserker Rage used in rotations again.
- Bloodfang Bracers are now bracers rather than gloves.

## v0.1 (released 2018-12-29):

- Hemorrhage with basic rotation added.
- More Subtletly talents added (Deadliness, Serrated Blades).
- Items not available for class or faction now filtered.
- Many leather items and several daggers added.
- Dense and Consecrated Sharpening Stones added.
- Add base melee AP and melee critical strike chance to rogues.
- Fix bug which caused rogues to evaluate 1 CP Eviscerate as a valid rotational choice.

## v0.1-alpha-4 (released 2018-12-16):

* Sinister Strike added; regular Combat rotation added to use it.
* Combat talents now implemented (those that are directly damage increasing in a target dummy environment).
* Assassination talents mostly implemented (missing Cold Blood, Imp EA, Imp KS, Remorseless Attacks).
* Few Subtletly talents now implemented (Opportunity).
* Poisons are available to be applied as temporary enchants.
* Update rogue white hit spells such that they use the new-ish way of calculating target armor and crit chance. This
fixes the bug that rogue white hits (1) could not crit, (2) ignored target armor.

## v0.1-alpha-3 (released 2018-12-01):

* Rudimentary Rogue support (Combat Dagger rotation with Backstab, SnD, Eviscerate available).
* More enchants (all superior versions for physical DPS now available).
* Fix melee AP double dip from STR/AGI gained via buffs / base stats (i.e. not including equipment).
* Felstriker buff duration fixed (duration was missing due to including old .xml-file).
* Extra attacks no longer trigger new proc checks.
* Extra attacks no longer consume Flurry charges.
* Using an Alliance race with Blessings enabled is once again possible to simulate.
* Fix crash when switching talent setups where setups specced talent with active children.
* For contributors: the .pro file now has relative INCLUDEPATHs; project directory structure no longer forced.
* For contributors: it is now possible to build on Linux (Ubuntu 18.04) using the directions in the Wiki.

## Restrictions

* Only the following rogue spells are available: Backstab, SnD, Eviscerate.
* Only the following rogue talents have an effect on the character: Adrenaline Rush.
* Some rogue talents have wrong tooltips.
* Rogue has likely incorrect base stat values as they were borrowed from Warrior (changing STR to AGI).

## v0.1-alpha-2 (released 2018-11-08):

* Full sim with stat weight calculations.
* Debuff uptime statistics.
* Use trinkets supported in rotation (Diamond Flask, Zandalarian Hero Medallion, Earthstrike, Badge of the Swarmguard,
Slayer's Crest, Jom Gabbar, Kiss of the Spider).
* Rend and Anger Management added. Arms/Fury now fully supported for single-target damage.
* Fury rotations now cast Bloodthirst over Execute if above 2k melee AP.
* Loatheb ruleset now has no glancing blows.

### Restrictions

No new restrictions; all delivered features, improvements, and bug fixes are expected to be complete.

## v0.1-alpha-1 (released 2018-10-27):

Initial release:

* Warrior advanced support (missing Protection talents, Rend, Anger Management)
* Supporting systems (talent calculator, equipment selection, world buffs / consumables, data-driven rotations)
* Quick sim with statistics

### Restrictions

* No full sim
* Some missing statistics (stat weight calculations, rotation, dps distribution, debuff uptimes)
* Character level locked to 60
* Spell ranks locked
* Only warrior available
* Items lists incomplete
* Rotations must be viewed in the actual .xml files instead of within the application
* Only single target simulation available
* and more..

# Anticipated questions and answers

Q: Why do this..?

A: For me it is an ode to vanilla.

Q: When is class X or specialization Y supported?

A: See [the Release Roadmap](https://github.com/timhul/ClassicSim/wiki/Release-Roadmap) for information when specific
classes/specs are planned to be supported.

Q: What is the proc chance of Ironfoe or other procs?
A: Ironfoe has at the time of writing a 2.7% proc chance. Most procs have a placeholder proc chance at 5%, but you can
change the 'rate' attribute in the .xml files. Try a 100% proc rate Ironfoe!

Q: Only Windows support? And 32-bit?

A: I plan to make a Linux release available, it is all a matter of priority. Compiling 64-bit is not supported by Qt
Creator on Windows out of the box (at least not in the open-source version). If you know more about this feel free to
contact me!

Q: (not really a question) Nothing happens when I click "Click me!" / "Run Full Sim".

A: Make sure you have equipped a mainhand weapon if a melee rotation is used, or a ranged weapon if a ranged rotation
is used.

Q: How many iterations are being run?

A: Clicking the "Click me!" button in the top-right corner runs the quick sim, which by default runs 1000 iterations.
Clicking the bottom-left "Run Full Sim" button runs the full sim, which by default runs 10000 iterations. Both of these
can be changed under "Settings".

Q: How is this or that mechanic implemented?

A: A lot of scouring the forums. The demo showed how some mechanics work but we know for a fact their work is not yet
complete. So far the main focus have been to make sure the mechanics are easily updated. Check
[Mechanics Details](https://github.com/timhul/ClassicSim/wiki/Mechanics-Details) in the wiki for fairly detailed
information regarding how the more obvious mechanics are implemented.

Q (not really a question): This mechanic is implemented incorrectly!

A: If the mechanic is incorrect because of a bug, then feel free to open an issue or discuss it with me in messages. If
you disagree that is how the mechanic should work because it is either not vanilla-like, or not the way one private
server implemented it then it will probably not get changed until Classic is released and we can find the actual answer.

Q (not really a question): It crashed!

A: Please let me know what you were doing!

# Credits

Thanks to all the theorycrafters over the years that have tirelessly worked towards refining our understanding of the
game. None mentioned, none forgotten.

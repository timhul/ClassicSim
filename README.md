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

# Known issues

* Most procs have a 5% placeholder proc rate (you can change the 'rate' attribute in the .xml files)
* Item lists are incomplete (these are manually added for now)
* Some MC items have the wrong patch availability (a number of items in MC were added after 1.0)
* Tooltip for Protection talent Improved Shield Block is incorrect
* Rotations need to define a variable to be parsed correctly
* Fiery Weapon rolls on melee hit table rather than spell table

# Next release

Upcoming features and bug fixes that are merged but not yet built and made available as a release:

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
* Some rogue talents have wrong tooltips.
* Rogue has likely incorrect base stat values as they were borrowed from Warrior (changing STR to AGI).

# Release notes

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

Q: Only a single class? WTF!

A: The intent of the current release is to show all the supporting systems that are shared between classes (talent
calculator, world buffs, etc). See [the Release Roadmap](https://github.com/timhul/ClassicSim/wiki/Release-Roadmap) for
information when specific classes/specs are planned to be supported.

Q: Only Windows support? And 32-bit?

A: I plan to make a Linux release available, it is all a matter of priority. Compiling 64-bit is not supported by Qt
Creator on Windows out of the box (at least not in the open-source version). If you know more about this feel free to
contact me!

Q: (not really a question) Nothing happens when I click "Click me!" / "Run Full Sim".

A: Make sure you have equipped a mainhand weapon.

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

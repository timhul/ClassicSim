# Introduction 

This is an event-driven gameplay simulator for World of Warcraft Classic written in C++. It is called ClassicSim, or
CSim for short. Its purpose is to provide feedback for a user regarding the value of equipment, talents, consumables,
rotation choices, etc.

# Licensing

Licensing information can be found in LICENSE.md.

# Features of this tool

These are some of the features of this tool:

* Talent calculator (try shift-left/right click talents)
* World buffs and consumables
* Enchants
* Rulesets (Standard, Vaelastrasz, Loatheb)
* Equipment sheet (with full stat filter support)
* Data-driven rotations
* Statistics

# Getting a built release

Releases are available at [http://classicsim.org].

Current restrictions:

* Only warrior supported
* The patch dropdown list currently only affects the available items
* Full simulation that includes stat weight calculations have been disabled due to me not having added the graph representation of the stat weights yet (the full sim and stat weight calculations are already in place, it is only a matter of displaying the data)
* Warrior is missing the following: Rend (and therefore Improved Rend has no effect), Anger Management, and Protection talents.
* Only level 60 vs 63 targets (i.e. bosses supported)
* Only single target simulation available

# Anticipated questions and answers

Q: Why do this..?

A: For me it is an ode to vanilla.

Q: Only a single class? WTF!

A: The intent of the current release is to show all the supporting systems that are shared between classes (calculator, world buffs, etc). The base for all classes are created, expanding the classes is mechanically time-consuming but in most cases not particularly difficult with a framework in place (although some refactoring will be required in a few places).

Q: Only Windows support? And 32-bit?

A: I plan to make a Linux release available, it is all a matter of priority. Compiling 64-bit is not supported by Qt Creator on Windows out of the box (at least not in the open-source version). If you know more about this feel free to contact me!

Q: Nothing happens when I click "Click me!"

A: Make sure you equipped a mainhand weapon.

Q: How many iterations are being run?

A: In the current release only the Quick Sim option is available. By default it runs 1000 iterations, although this value can be modified under Settings.

Q: How is this or that mechanic implemented?

A: A lot of scouring the forums. Since we have yet no way of knowing before the demo how some mechanics work, the main focus have been to make sure the mechanics are easily updated. Check Mechanics/ in the repository link for at least how some of the mechanics work if you are really interested.

Q (not really a question): This mechanic is wrongly implemented!

A: If the mechanic is incorrect because it was implemented wrong, then feel free to open an issue or discuss it with me in messages. If you disagree that is how the mechanic should work because it is either not vanilla-like, or not the way one private server implemented it then it will probably not get changed until Classic is released and we can find the actual answer.

Q (not really a question): It crashed!

A: Please let me know what you were doing!

# Known issues

* Item lists are incomplete (these are manually added for now)
* Some MC items have the wrong patch availability (a number of items in MC were added after 1.0)
* Tooltip for Protection talent Improved Shield Block is incorrect

# Future work

So, so many things.. Note that the timeframe for these may be reconsidered if things are re-prioritized. These are only some of the major things. Have a suggestion? Let me know either here or on GitHub.

## Near, near future (like, within 1-2 weeks):

* Use-trinkets supported
* Full stat weight calculations w/ confidence intervals
* DPS distribution w/ standard deviation

## Near future (~1 month):

* Rotation possible view and to edit directly in the application
* More melee classes support
* Removing character level 60 restriction

## More long-term future (2 months+)

* Caster classes
* TPS
* Healing

# Credits

Thanks to all the theorycrafters over the years that have tirelessly worked towards refining our understanding of the game. None mentioned, none forgotten.
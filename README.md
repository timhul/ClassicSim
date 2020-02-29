# Introduction

This is an event-driven gameplay simulator for World of Warcraft Classic written in C++. It is called "ClassicSim", or
CSIM for short. Its purpose is to provide feedback to a user regarding the value of equipment, talents, consumables,
rotation choices, etc.

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

# Q&A

Q: When is class X or specialization Y supported?

A: See [the Release Roadmap](https://github.com/timhul/ClassicSim/wiki/Release-Roadmap) for information when specific
classes/specs are planned to be supported.

Q: What is the proc chance of Ironfoe or other procs?

A: You can find proc rates by either running the sim and checking the proc statistics or look
directly in the equipment .xml file, which will include a \<proc\> element that specifies the rate.

Q: How is this or that mechanic implemented?

A: Check [Mechanics Details](https://github.com/timhul/ClassicSim/wiki/Mechanics-Details) in the wiki for fairly detailed
information regarding how important mechanics are implemented.

Q (not really a question): This mechanic is implemented incorrectly!

A: Open an issue describing the deviation and provide proof of the actual behavior.

Q (not really a question): It crashed!

A: Please let us know what you were doing! Open an issue describing the procedure, and attach saves under
\<classic-sim-directory\>Saves/ (at least GUI + the class you have active).

Q: Why do this..?

A: To satisfy the academic curiosity that literally dozens of us feel.

# Credits

Thanks to all the theorycrafters over the years that have tirelessly worked towards refining our understanding of the
game.

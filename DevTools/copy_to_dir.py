#!/usr/bin/env python3
import pathlib
import shutil
import os
import sys


def fail():
    print(
        "This script copies the necessary resources to run ClassicSim to directory listed in the first argument"
    )
    print("Usage: copy_to_dir.py directory-to-copy-to")
    sys.exit(1)


if len(sys.argv) != 2:
    fail()

REPO_ROOT = pathlib.Path(".")
DEST_DIR = pathlib.Path(sys.argv[1])

if not os.path.exists(DEST_DIR):
    fail()


def main():
    copy_rotations()
    copy_items()
    copy_random_affixes()
    create_saves()


def copy_rotations():
    src_path = REPO_ROOT / "Rotation" / "Rotations"
    class_directories = {
        "Hunter",
        "Rogue",
        "Warrior",
        "Paladin",
        "Shaman",
        "Mage",
        "Druid",
        "Priest",
        "Warlock",
    }
    if (DEST_DIR / "Rotations").exists():
        shutil.rmtree(str(DEST_DIR / "Rotations"))
    for directory in class_directories:
        if not (src_path / directory).exists():
            print("Skipping " + directory + " because source does not exist")
            continue

        shutil.copytree(
            src=str(src_path / directory), dst=str(DEST_DIR / "Rotations" / directory)
        )
    shutil.copy2(
        src=str(src_path / "rotation_paths.xml"),
        dst=str(DEST_DIR / "rotation_paths.xml"),
    )


def copy_items():
    source = REPO_ROOT / "Equipment" / "EquipmentDb"
    item_directories = {
        "Belts",
        "Boots",
        "Chests",
        "Gloves",
        "Helms",
        "Legs",
        "Misc",
        "Shoulders",
        "Weapons",
        "Wrists",
    }
    for directory in item_directories:
        if (DEST_DIR / directory).exists():
            shutil.rmtree(str(DEST_DIR / directory))
        shutil.copytree(src=str(source / directory), dst=str(DEST_DIR / directory))

    shutil.copy2(
        src=str(source / "equipment_paths.xml"),
        dst=str(DEST_DIR / "equipment_paths.xml"),
    )
    shutil.copy2(
        src=str(source / "set_bonuses.xml"), dst=str(DEST_DIR / "set_bonuses.xml")
    )


def copy_random_affixes():
    source = REPO_ROOT / "Equipment" / "EquipmentDb"
    shutil.copy2(
        src=str(source / "random_affixes.xml"), dst=str(DEST_DIR / "random_affixes.xml")
    )


def create_saves():
    if not (DEST_DIR / "Saves").exists():
        os.mkdir((DEST_DIR / "Saves"))


if __name__ == "__main__":
    main()

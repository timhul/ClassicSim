import configparser
import pathlib
import sys


CONFIG_FILE = pathlib.Path(__file__).parent.parent / "build.config"

DEBUG_LOC_STRING = " ".join(
    ["<path to debug directory, e.g.",
     "C:/C++/build-ClassicSim-Desktop_Qt_5_11_3_MinGW_32bit-Debug>"])
RELEASE_LOC_STRING = " ".join(
    ["<path to release directory",
     "(only required if creating release), e.g.",
     "C:/C++/build-ClassicSim-Desktop_Qt_5_11_3_MinGW_32bit-Release>"])
QT_LOC_STRING = " ".join(
    ["<path to bin/ in Qt installation",
     "(only required if creating release), e.g.",
     "C:/Qt/5.11.3/mingw53_32/bin>"])


DEFAULT = {
    "debug_location": DEBUG_LOC_STRING,
    "release_location": RELEASE_LOC_STRING,
    "qt_location": QT_LOC_STRING,
}

def create_default_config():
    config = configparser.ConfigParser()
    config["BUILD"] = DEFAULT
    with open(CONFIG_FILE, 'w') as configfile:
        config.write(configfile)


def get_config():
    if not CONFIG_FILE.exists():
        print(f"Could not find config file at '{CONFIG_FILE.resolve()}', a "
              "default config file was written, please fill with info.")
        create_default_config()
        sys.exit(0)

    config = configparser.ConfigParser()
    config.read(CONFIG_FILE)
    return config

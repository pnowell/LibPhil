# LibPhil README

This is repository of all the utility classes I've written for my own purposes

## Directory Structure

* bin
    * build.py to grab the CWD and pass it to the jam build system
    * build.bat to first call visual studio's setenv batch file and then pass off to build.py
* jamcore
    * the location of the various jam configuration files split up according to target/platform specificity
* src
    * libs
        * all of the various basic libs that any of my applications can use
    * samples
        * a place for all the applications I write with those libs to live
* vim
    * vim configuration files

## Configuration

* Environment variables
    * LIBPHIL_BASEDIR - The path to parent directory of the libphil directory structure.  This is the only required environment variable
* Jam variables (settable with the -s command line argument)
    * LIBPHIL_CWD - What part of the code tree you want to build
    * LIBPHIL_TARGETPLAT - 'winvs' or 'wingcc'
    * LIBPHIL_BUILDTYPE - 'debug' or 'release'

## Links

* Long term plans / ideas I have for libPhil can be found [here](https://github.com/pnowell/LibPhil/wiki/Plans)

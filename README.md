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
    * LIBPHIL_BASEDIR - The path to parent directory of the libphil directory structure.  This is the only requred environment variable
* Jam variables (settable with the -s command line argument)
    * LIBPHIL_CWD - What part of the code tree you want to build
    * LIBPHIL_TARGETPLAT - 'winvs' or 'wingcc'
    * LIBPHIL_BUILDTYPE - 'debug' or 'release'

## Future Plans

* Get a list of words and randomly combine them to brainstorm ideas for a game
* Look into auto generating library dependencies based on header scan results
* Begin work on integrating the Android NDK
    * Try to get the NDK working as a stand-alone tool chain
* Begin working toward a graphical sandbox to work both in windows and Android
* Possibly set up some unit tests to try to ensure some basic level of functionality in the libs that I'm writing
* Add support for platforms beyond cygwin (need to figure out how to rebuild Jam not under cygwin first)

[jam-link]: http://www.perforce.com/jam/jam.html  "Jam build tool"

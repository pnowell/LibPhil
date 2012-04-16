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

## Future Plans

* Work on some file i/o utilities to facilitate parsing the codejam input files
* Try to optimize my codejam submission process to keep from timing out
    * Particularly, maybe it would be good to have kjam be able to zip up all the files that are needed to build a particular executable
* Extend the library auto-detect functionality to
    * Let libraries specify any extra parameters to pass to the linker when linking them into executables
* Work more on 2D/3D math functionality
* Set up some unit tests to try to ensure some basic level of functionality in the libs that I'm writing

[jam-link]: http://www.perforce.com/jam/jam.html  "Jam build tool"

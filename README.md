# LibPhil README

This is repository of all the utility classes I've written for my own purposes

## Directory Structure

* src
    * libs
        * all of the various basic libs that any of my applications can use
    * samples
        * a place for all the applications I write with those libs to live
* jamcore
    * the location of the various jam configuration files split up according to target/platform specificity

## Configuration

* Environment variables
    * LIBPHIL_BASEDIR - The path to parent directory of the libphil directory structure.  This is the only requred environment variable
* Jam variables (settable with the -s command line argument)
    * LIBPHIL_CWD - What part of the code tree you want to build
    * LIBPHIL_TARGET - So far this can only be set to winvs

## Future Plans

* Continue flushing out my [Jam][jam-link]-based build system
* Integrate my build process with vim (for ease of fixing compiler errors)
* Begin working toward a graphical sandbox (for a possible projector-based party favor)
* Possibly set up some unit tests to try to ensure some basic level of functionality in the libs that I'm writing
* Add support for winvs32 VS winvs64 target (right now winvs is 32-bit)
* Add support for gcc32 and gcc64
* Add support for platforms beyond cygwin (need to figure out how to rebuild Jam not under cygwin first)

[jam-link]: http://www.perforce.com/jam/jam.html  "Jam build tool"

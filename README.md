CREST-MI: CREST with More User-friendly Interfaces
=====

CREST-MI is a variant of CREST a concolic test generation tool for C programs
developed by Jacob Burnim (https://burn.im/crest). CREST-MI extends CREST to 
provide more user interfaces useful for adopting concoilc test generation to 
conventional C program testing. CREST-MI differs from the original CREST in
the following points:
  * CRETS-MI uses Z3 for constraint solving (instead of Yices 1.x)
  * CREST-MI can define an initial value of a symbolic variable  
  * CREST-MI can show the internal information of symbolic execution for testers to better understand the symbolic execution progress.

Build CREST-MI
=====

Please find the following instruction to download a constraint solver Z3, to build CIL,
and to build CREST-MI in sequence.

1. Clone this repository to your local

```	# git clone http://github.com/arise-handong/crest ```

2. Download Z3-4.8.4 (or more recent version) to the 'lib' directory. For example of Ubuntu 16.04,

``` # wget https://github.com/Z3Prover/z3/releases/download/z3-4.8.4/z3-4.8.4.d6df51951f4c-x64-ubuntu-16.04.zip  
	# unzip z3-4.8.4.d6df51951f4c-x64-ubuntu-16.04.zip  
	# ln -s z3-4.8.4.d6df51951f4c-x64-ubuntu-16.04 z3 ```

3. Build CIL

``` # cd cil
	# ./configure
	# make 
	# cd .. ```


4. Build CREST and update PATH

``` # cd src
	# make
	# PATH=$PATH:$(pwd) ```
	

Setup Target Program  
========
To use CREST on a C program, use functions CREST_int, CREST_char,
etc., declared in "crest.h", to generate symbolic inputs for your
program.  For examples, see the programs in test/.

For simple, single-file programs, you can use the build script
"bin/crestc" to instrument and compile your test program.

CREST can be used to instrument multi-file programs, too --
instructions may be added later.  In the meantime, you can take a look
at an example, instrumented form of grep-2.2, available at
https://github.com/jburnim/crest/tree/master/benchmarks/grep-2.2 .
For further information, please see this
[post](https://groups.google.com/forum/#!topic/crest-users/KwgP9JkajOw)
on the CREST-users mailing list.


Running Crest
=====

CREST is run on an instrumented program as:

    bin/run_crest PROGRAM NUM_ITERATIONS -STRATEGY

Possibly strategies include: dfs, cfg, random, uniform_random, random_input.
Some strategies take optional parameters.

Example commands to test the "test/uniform_test.c" program:

    cd test
    ../bin/crestc uniform_test.c
    ../bin/run_crest ./uniform_test 10 -dfs

This should produce output roughly like:

    ... [GARBAGE] ...
    Read 8 branches.
    Read 13 nodes.
    Wrote 6 branch edges.

    Iteration 0 (0s): covered 0 branches [0 reach funs, 0 reach branches].
    Iteration 1 (0s): covered 1 branches [1 reach funs, 8 reach branches].
    Iteration 2 (0s): covered 3 branches [1 reach funs, 8 reach branches].
    Iteration 3 (0s): covered 5 branches [1 reach funs, 8 reach branches].
    Iteration 4 (0s): covered 7 branches [1 reach funs, 8 reach branches].
    GOAL!
    Iteration 5 (0s): covered 8 branches [1 reach funs, 8 reach branches].

NOTE: run_crest and crestc currently leave a lot of files lying
around, some of which are temporary and some of which must be kept.
In particular, "cfg_branches" and "branches" are output by the
instrumentation process and are needed to run run_crest, and run_crest
produces "coverage", a list of the ID's of all covered branches.


Setup
=====

License
=====

CREST is distributed under the revised BSD license.  See LICENSE for
details.

This distribution includes a modified version of CIL, a tool for
parsing, analyzing, and transforming C programs.  CIL is written by
George Necula, Scott McPeak, Wes Weimer, Ben Liblit, and Matt Harren.
It is also distributed under the revised BSD license.  See cil/LICENSE
for details.

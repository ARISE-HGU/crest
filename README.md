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
```	
$ git clone http://github.com/arise-handong/crest 
```

2. Download [Z3](https://github.com/Z3Prover/z3) version 4.8.4 (or a more recent version) to the 'lib' directory. For example of Ubuntu 16.04:
``` 
$ cd crest/lib
crest/lib$ wget https://github.com/Z3Prover/z3/releases/download/z3-4.8.4/z3-4.8.4.d6df51951f4c-x64-ubuntu-16.04.zip  
crest/lib$ unzip z3-4.8.4.d6df51951f4c-x64-ubuntu-16.04.zip
crest/lib$ ln -s z3-4.8.4.d6df51951f4c-x64-ubuntu-16.04 z3
```

3. Build ```cil```, a variant of [CIL](https://cil-project.github.io/cil/) for CREST
``` 
$ cd crest/cil
crest/cil$ ./configure
crest/cil$ make 
```

4. Build CREST and update PATH
``` 
$ cd crest/src
crest/src$ make
crest/src$ cd ../bin
crest/bin$ PATH=$PATH:$(pwd) 
```

Run CREST
=====

A target program must declare one or more variables as symbolic variables.
CREST-MI extracts a symbolic path condition over these symbolic varialbes 
along a concret execution, and then generates a test input as a concrete value 
assignments to these symbolic variables. To declare a variable ```x``` as 
a symoblic variable, a target program must include ```<crest.h>``` and invoke
```CREST_int(x)``` (or ```CREST_char(x)```) at the moment when x is defined by
input.

Once symbolic variables are declared, a target program must be built by
```bin/crestc```. For instance, if ```target/prog.c``` is a target program,
execute the following command:

```
target$ crestc prog.c
```

```crestc``` is a script to produce an executable of a target program while inserting 
additional code (i.e., instrumentation) for running dynamic symbolic analyses along 
a program execution in background. For code insertion, ```crestc``` first invokes CIL 
to run a source-code transformation scheme as programmed in ```lib/cil```.
The source-code transformation inserts CREST API calls at every target program statement 
depending on thier kinds in order to emit which operation is executed with which operands 
(i.e., variables or memory locations) in a target program execution. 
After source-code transformation, ```crestc``` invokes a C compiler (e.g., gcc) to build 
the transformed target program to get an executable. 
Note that ```crestc``` does not produce the executable only, but also a suite of data files 
(as side-products) needed for CREST-MI to conduct symbolic analyses.


```bin/run_crest``` runs concolic test generation on an instrumented executable program.
The command line options of ```bin/run_crest``` are as follows:  

<center> ``` run_crest <PROGRAM> <NUM_ITERATIONS> <STRATEGY> [STRATEGY OPTION] [-random_init] ```  </center>

```<PROGRAM>``` is a pathname of a target program executable compiled by ```crestc```.
```<NUM_ITER>``` gives the maximum number of concolic executions, which is the same as
the maximum number of test inputs to generate.
```<STRATEGY>``` defines which search strategy will be used for concolic test generation.
Currently, CREST-MI supports six search strategies: ```pdfs``` for DFS, ```rdfs``` for 
Reverse DFS, ```random``` for Random Negation, ```uniform_random``` for Uniform Random,
and ```cfg``` for Control-flow Graph-based heuristics. Depending on ```<STRATEGY>```,
we may give an argument ```[STRATEGY OPTION]``` optionally. Finally, it is possible to
configure CREST-MI to set the initial value of a symbolic variable at first execution
as a random number by giving the ```-random_init``` option.

For example of ```target/prog.c```, the following command will start CREST-MI to generate
test input with the DFS search strategy up to 1000 times.

```
target$ run_crest ./prog 1000 -pdfs
```

The test execution results will be printed out to standard output. In addition, *i*-th
test execution creates ```stdout.i``` and ```stderr.i``` which capture standard output
and standard error produced by running the target program with i-th test input.

License
=====

CREST-MI inherits the license of CREST. 
CREST is distributed under the revised BSD license.  See LICENSE for details.

This distribution includes a modified version of CIL, a tool for
parsing, analyzing, and transforming C programs.  CIL is written by
George Necula, Scott McPeak, Wes Weimer, Ben Liblit, and Matt Harren.
It is also distributed under the revised BSD license.  See cil/LICENSE
for details.

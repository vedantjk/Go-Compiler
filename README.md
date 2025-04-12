# proj

## Steps to run

We need to compile the project. In the project root, execute the following commands.

```
$ mkdir build && cd build
$ cmake ..
$ make
```

It takes a long time to compile because it has to download the ANTLR4 source file and then install it. 

We have the following command line arguments -

`-l`: prints the tokens and exits

`-ast`: prints the AST and exits

`-llvm-ir=[stack|reg]`: writes the register / stack based version of LLVM IR and terminates

`-S`: writes the ARM generated code

`-target=STRING`: sets the target triple in the .ll file

Note: `-target=STRING` should be used after `-llvm-ir=[stack|reg]` or `-S` like this ->
`./golite -llvm-ir=stack -target=x86_64-linux-gnu simple.golite`

By default, the target triple is for the linux machines. If you don't use atleast one of the `-l`, `-ast`, `-llvm-ir=[stack|reg]`, or `-S` the program does generates the ARM code. The `wing` linux servers do not have `cmake` or `make`, so you will need to compile the code in `focal` linux servers, generate the `ARM` code for the required benchmarks, and then use `gcc` in the `wing` linux server to generate the executable. This is not optimal but this is how I was able to test it.

The benchmark folder is the same as the one provided to us. If you want to run your own files, you need to put them in the `benchmarks/` directory before compiling the project. If you have already compiled the project, then you can put them in `build/` directory and then use the same command as above.

The code correctly generates ARM code for Thermopylae, Primes and Prime2 and register based LLVM IR for all the benchmarks provided. No optimizations have been implemented.
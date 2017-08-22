# microbenches
Repository containing microbenchmarks meant for manifold0.12-ei

To build the benchmarks, just run 
$ make

The Makefile will create the tarball which can now be used to run with qsim separately or with manifold.

runme_orig.sh : This is just a dummy script which is used as a placeholder for runme.sh

tarball contents: 
- runme.sh
- threads

runme.sh
#!/sbin/ash

./threads $NPUS

pure_memory.cpp: This is to test memory fetches on all 16 cores
pure_memory_single_core.cpp: This is to test memory fetches on a single core.
single_core_mips_mem.cpp: This is to test MIPS and mem fetches on a single core.


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




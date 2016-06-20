MAKEFILE USAGE DOCUMENTATION

Changing target architecture
----------------------------------------------------------------

Default compiler is gcc. To use ARM compiler for cross-compile,
pass in the variable TARGET_BUILD=arm in the command line while
using the makefile command

makefile functions
----------------------------------------------------------------

make %.o
	compile any source file into object file

make %.s
	compile any source file into assembly file

make %.asm
	disassemble any object file into assembly file

make compile-all
	compiles all object files, without linking

make build
	compile all object files and link

make upload
	upload the executable onto Beaglebone Black

make clean
	remove all object, executable and build output files

#!/bin/sh

: << 'END'
!!!!!!!!!!!!!!!!READ THIS FIRST!!!!!!!!!!!!!!!!!!!!!!
Core mapping
0  ->  2
1  ->  3
2  ->  4
...
12 ->  14
13 ->  15
14 ->  0
15 ->  1

L2 Bank mapping
0  ->  13
1  ->  14
2  ->  15
3  ->  0
...
15 ->  12
END

NUMOPT=3
NCPUOPS=10
for CNUM in 0 1 14
do
	if [ ${CNUM} -eq 14 ]; then
#---------------------------------------------------------------------------
# CORE 0 BANK 0, 1, 3, 15
#---------------------------------------------------------------------------
		# L2BANK2_3_4_6
		for L2BANK in 2 3 4 6
		do
			echo " CORE_NUMBER " ${CNUM} " L2BANKID ${L2BANK} OPTMEM${NUMOPT} "
			sed 's/\#define CORE_NUMBER 0/\#define CORE_NUMBER '"${CNUM}"'/' test_threads.h |
			sed 's/\#define L2BANKID 6/\#define L2BANKID '"${L2BANK}"'/' |
			sed '/\#endif/i\\#define OPTMEM'"${NUMOPT}"'' > threads.h
			#echo -n "Enter a character and press [Enter] to continue "
			#read var
			make -s clean
			make -s -f Makefile.MV
			mv mips_variation.tar tarballs/core${CNUM}/mv_core${CNUM}_bank${L2BANK}_cpuop${NCPUOPS}_optmem${NUMOPT}.tar
			echo "Done. Created mv_core${CNUM}_bank${L2BANK}_cpuop${NCPUOPS}_optmem${NUMOPT}.tar"				
		done
	fi

	if [ ${CNUM} -eq 0 ]; then
#---------------------------------------------------------------------------- 
# CORE 2 BANK 0, 2, 3, 13
#---------------------------------------------------------------------------
		# L2BANK0_3_5_6 
		for L2BANK in 0 3 5 6
		do
			echo " CORE_NUMBER " ${CNUM} " L2BANKID ${L2BANK} OPTMEM${NUMOPT} "
			sed 's/\#define CORE_NUMBER 0/\#define CORE_NUMBER '"${CNUM}"'/' test_threads.h |
			sed 's/\#define L2BANKID 6/\#define L2BANKID '"${L2BANK}"'/' |
			sed '/\#endif/i\ \#define OPTMEM'"${NUMOPT}"'' > threads.h
			#echo -n "Enter a character and press [Enter] to continue "
			#read var
			make -s clean
			make -s -f Makefile.MV
			mv mips_variation.tar tarballs/core${CNUM}/mv_core${CNUM}_bank${L2BANK}_cpuop${NCPUOPS}_optmem${NUMOPT}.tar
			echo "Done. Created mv_core${CNUM}_bank${L2BANK}_cpuop${NCPUOPS}_optmem${NUMOPT}.tar"
		done
	fi
	if [ ${CNUM} -eq 1 ]; then 
#----------------------------------------------------------------------------
# CORE 3 BANK 0, 1, 3, 5, 6
#---------------------------------------------------------------------------
		# L2BANK3_4_6_8_9 
		for L2BANK in 3 4 6 8 9
		do
			echo " CORE_NUMBER " ${CNUM} " L2BANKID ${L2BANK} OPTMEM${NUMOPT} "
			sed 's/\#define CORE_NUMBER 0/\#define CORE_NUMBER '"${CNUM}"'/' test_threads.h |
			sed 's/\#define L2BANKID 6/\#define L2BANKID '"${L2BANK}"'/' |
			sed '/\#endif/i\ \#define OPTMEM'"${NUMOPT}"'' > threads.h
			#echo -n "Enter a character and press [Enter] to continue "
			#read var
			make -s clean
			make -s -f Makefile.MV
			mv mips_variation.tar tarballs/core${CNUM}/mv_core${CNUM}_bank${L2BANK}_cpuop${NCPUOPS}_optmem${NUMOPT}.tar
			echo "Done. Created mv_core${CNUM}_bank${L2BANK}_cpuop${NCPUOPS}_optmem${NUMOPT}.tar"
		done
	fi
done

NUMOPT=2
for NCPUOPS in 1 5
do
	for CNUM in 0 1 14
	do
		if [ ${CNUM} -eq 14 ]; then
#---------------------------------------------------------------------------
# CORE 0 BANK 0, 1, 3, 15
#---------------------------------------------------------------------------
			# L2BANK2_3_4_6
			for L2BANK in 2 3 4 6
			do
				echo "NCPUOPS " ${NCPUOPS} " CORE_NUMBER " ${CNUM} " L2BANKID ${L2BANK} OPTMEM${NUMOPT} "
				sed 's/\#define CORE_NUMBER 0/\#define CORE_NUMBER '"${CNUM}"'/' test_threads.h |
				sed 's/\#define L2BANKID 6/\#define L2BANKID '"${L2BANK}"'/' |
				sed 's/\#define NUM_CPU_OPS 10/\#define NUM_CPU_OPS '"${NCPUOPS}"'/' |
				sed '/\#endif/i\\#define OPTMEM'"${NUMOPT}"'' > threads.h
				#echo -n "Enter a character and press [Enter] to continue "
				#read var
				make -s clean
				make -s -f Makefile.MV
				mv mips_variation.tar tarballs/core${CNUM}/mv_core${CNUM}_bank${L2BANK}_cpuop${NCPUOPS}_optmem${NUMOPT}.tar
				echo "Done. Created mv_core${CNUM}_bank${L2BANK}_cpuop${NCPUOPS}_optmem${NUMOPT}.tar"				
			done
		fi

		if [ ${CNUM} -eq 0 ]; then
#---------------------------------------------------------------------------- 
# CORE 2 BANK 0, 2, 3, 13
#---------------------------------------------------------------------------
			# L2BANK0_3_5_6
			for L2BANK in 0 3 5 6
			do
				echo "NCPUOPS " ${NCPUOPS} " CORE_NUMBER " ${CNUM} " L2BANKID ${L2BANK} OPTMEM${NUMOPT} "
				sed 's/\#define CORE_NUMBER 0/\#define CORE_NUMBER '"${CNUM}"'/' test_threads.h |
				sed 's/\#define L2BANKID 6/\#define L2BANKID '"${L2BANK}"'/' |
				sed 's/\#define NUM_CPU_OPS 10/\#define NUM_CPU_OPS '"${NCPUOPS}"'/' |
				sed '/\#endif/i\ \#define OPTMEM'"${NUMOPT}"'' > threads.h
				#echo -n "Enter a character and press [Enter] to continue "
				#read var
				make -s clean
				make -s -f Makefile.MV
				mv mips_variation.tar tarballs/core${CNUM}/mv_core${CNUM}_bank${L2BANK}_cpuop${NCPUOPS}_optmem${NUMOPT}.tar
				echo "Done. Created mv_core${CNUM}_bank${L2BANK}_cpuop${NCPUOPS}_optmem${NUMOPT}.tar"
			done
		fi
		if [ ${CNUM} -eq 1 ]; then 
#----------------------------------------------------------------------------
# CORE 3 BANK 0, 1, 3, 5, 6
#---------------------------------------------------------------------------
			# L2BANK3_4_6_8_9
			for L2BANK in 3 4 6 8 9
			do
				echo "NCPUOPS " ${NCPUOPS} " CORE_NUMBER " ${CNUM} " L2BANKID ${L2BANK} OPTMEM${NUMOPT} "
				sed 's/\#define CORE_NUMBER 0/\#define CORE_NUMBER '"${CNUM}"'/' test_threads.h |
				sed 's/\#define L2BANKID 6/\#define L2BANKID '"${L2BANK}"'/' |
				sed 's/\#define NUM_CPU_OPS 10/\#define NUM_CPU_OPS '"${NCPUOPS}"'/' |
				sed '/\#endif/i\ \#define OPTMEM'"${NUMOPT}"'' > threads.h
				#echo -n "Enter a character and press [Enter] to continue "
				#read var
				make -s clean
				make -s -f Makefile.MV
				mv mips_variation.tar tarballs/core${CNUM}/mv_core${CNUM}_bank${L2BANK}_cpuop${NCPUOPS}_optmem${NUMOPT}.tar
				echo "Done. Created mv_core${CNUM}_bank${L2BANK}_cpuop${NCPUOPS}_optmem${NUMOPT}.tar"
			done
		fi
	done
done

NUMOPT=1
for NCPUOPS in 0 1 5 10
do
	for CNUM in 0 1 14
	do
		if [ ${CNUM} -eq 14 ]; then
#---------------------------------------------------------------------------
# CORE 0 BANK 0, 1, 3, 15
#---------------------------------------------------------------------------
			# L2BANK2_3_4_6
			for L2BANK in 2 3 4 6
			do
				echo "NCPUOPS " ${NCPUOPS} " CORE_NUMBER " ${CNUM} " L2BANKID ${L2BANK} OPTMEM${NUMOPT} "
				sed 's/\#define CORE_NUMBER 0/\#define CORE_NUMBER '"${CNUM}"'/' test_threads.h |
				sed 's/\#define L2BANKID 6/\#define L2BANKID '"${L2BANK}"'/' |
				sed 's/\#define NUM_CPU_OPS 10/\#define NUM_CPU_OPS '"${NCPUOPS}"'/' |
				sed '/\#endif/i\\#define OPTMEM'"${NUMOPT}"'' > threads.h
				#echo -n "Enter a character and press [Enter] to continue "
				#read var
				make -s clean
				make -s -f Makefile.MV
				mv mips_variation.tar tarballs/core${CNUM}/mv_core${CNUM}_bank${L2BANK}_cpuop${NCPUOPS}_optmem${NUMOPT}.tar
				echo "Done. Created mv_core${CNUM}_bank${L2BANK}_cpuop${NCPUOPS}_optmem${NUMOPT}.tar"				
			done
		fi

		if [ ${CNUM} -eq 0 ]; then
#---------------------------------------------------------------------------- 
# CORE 2 BANK 0, 2, 3, 13
#---------------------------------------------------------------------------
			# L2BANK0_3_5_6
			for L2BANK in 0 3 5 6
			do
				echo "NCPUOPS " ${NCPUOPS} " CORE_NUMBER " ${CNUM} " L2BANKID ${L2BANK} OPTMEM${NUMOPT} "
				sed 's/\#define CORE_NUMBER 0/\#define CORE_NUMBER '"${CNUM}"'/' test_threads.h |
				sed 's/\#define L2BANKID 6/\#define L2BANKID '"${L2BANK}"'/' |
				sed 's/\#define NUM_CPU_OPS 10/\#define NUM_CPU_OPS '"${NCPUOPS}"'/' |
				sed '/\#endif/i\ \#define OPTMEM'"${NUMOPT}"'' > threads.h
				#echo -n "Enter a character and press [Enter] to continue "
				#read var
				make -s clean
				make -s -f Makefile.MV
				mv mips_variation.tar tarballs/core${CNUM}/mv_core${CNUM}_bank${L2BANK}_cpuop${NCPUOPS}_optmem${NUMOPT}.tar
				echo "Done. Created mv_core${CNUM}_bank${L2BANK}_cpuop${NCPUOPS}_optmem${NUMOPT}.tar"
			done
		fi
		if [ ${CNUM} -eq 1 ]; then 
#----------------------------------------------------------------------------
# CORE 3 BANK 0, 1, 3, 5, 6
#---------------------------------------------------------------------------
			# L2BANK3_4_6_8_9
			for L2BANK in 3 4 6 8 9
			do
				echo "NCPUOPS " ${NCPUOPS} " CORE_NUMBER " ${CNUM} " L2BANKID ${L2BANK} OPTMEM${NUMOPT} "
				sed 's/\#define CORE_NUMBER 0/\#define CORE_NUMBER '"${CNUM}"'/' test_threads.h |
				sed 's/\#define L2BANKID 6/\#define L2BANKID '"${L2BANK}"'/' |
				sed 's/\#define NUM_CPU_OPS 10/\#define NUM_CPU_OPS '"${NCPUOPS}"'/' |
				sed '/\#endif/i\ \#define OPTMEM'"${NUMOPT}"'' > threads.h
				#echo -n "Enter a character and press [Enter] to continue "
				#read var
				make -s clean
				make -s -f Makefile.MV
				mv mips_variation.tar tarballs/core${CNUM}/mv_core${CNUM}_bank${L2BANK}_cpuop${NCPUOPS}_optmem${NUMOPT}.tar
				echo "Done. Created mv_core${CNUM}_bank${L2BANK}_cpuop${NCPUOPS}_optmem${NUMOPT}.tar"
			done
		fi
	done
done

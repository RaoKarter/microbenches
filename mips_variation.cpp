#include "threads.h"

using namespace std;

int main(int argc, char *argv[])
{
	int NUM_THREADS;
	if(argc < 2)
	{
		cout << "Usage: threads NUM_THREADS " << endl;
		exit(0);
	}
	NUM_THREADS = atoi(argv[1]);
	
	int i, j, k, l, m;
	double double_element[NUM_THREADS], double_element1;
	double int_element; 
	int page_num = 0;

	double *p_db = NULL;
	p_db = (double*) calloc(DB_2_MB*NUM_THREADS, sizeof(double));

	for(i = 0; i < DB_2_MB*NUM_THREADS; i++)
		p_db[i] = 3.1415;

	omp_set_num_threads(NUM_THREADS);
	qsim_magic_enable();

	j = 0;
	#pragma omp parallel for private(j, k, l, m, int_element, double_element1) shared (p_db)
	for (i = 0; i < NUM_THREADS; i++)
	{
		/*
		Choose a single thread. i = 0 "somehow" maps to
		CORE2 (i.e. the 3rd core). qsim does this mapping.
		TODO: Figure out border cores and central cores
		*/
		if(i == CORE_NUMBER)
		{
			k = 0;
			/*
			We need k > 0 because in the first iteration
			on k, IPC of COREX (X \in {0,1,3,4,...,15} 
			is non-zero.
			*/
			
			while( k < NUM_MEM_FETCHES )
			{
				//cout << "k = " << k << endl << flush;
				for(j = 0; j < DB_2_MB*NUM_THREADS; j++)
				{
					/*
					The factor 512 is used to align with a 4KB page
					The factor 16 is to skip all the other L2 banks
					except the required one.
					Eg: sizeof(double) = 8B. 512 * 8B = 4KB.
					
					page_num = 0 maps addresses to L2BANK #13 i.e.
								 the 14th L2 BANK.

					page_num = 5 maps addresses to L2BANK #2 i.e.
								 the 3rd L2 BANK.			
					*/
// Expts 15 16 17 18/
#ifdef OPTMEM1
					for(l = 0; l < NUM_CPU_OPS;l++)
					{
						int_element = 9 + 12;
						int_element = 9 * 12;
						int_element = 12 / 9;
						double_element1 = 12.345 * 67.891;
					
					}
					double_element[i] = p_db[j];
#endif
// Expts 12 13
#ifdef OPTMEM2

					for(m = 0; m < NUM_THREADS;m++)
					{
						double_element[i] = p_db[j + (512*m)];
						for(l = 0; l < NUM_CPU_OPS;l++)
						{
							int_element = 9 + 12;
							int_element = 9 * 12;
							int_element = 12 / 9;
							double_element1 = 12.345 * 67.891;						
						}
					}
#endif
// Expt 1
#ifdef OPTMEM3
					double_element[i] = p_db[j];
					double_element[i] = p_db[j + 512];
					double_element[i] = p_db[j + 1024];
					double_element[i] = p_db[j + 1536];
					double_element[i] = p_db[j + 2048];
					double_element[i] = p_db[j + 2560];
					double_element[i] = p_db[j + 3072];
					double_element[i] = p_db[j + 3584];
					double_element[i] = p_db[j + 4096];
					double_element[i] = p_db[j + 4608];
					double_element[i] = p_db[j + 5120];
					double_element[i] = p_db[j + 5632];
					double_element[i] = p_db[j + 6144];
					double_element[i] = p_db[j + 6656];
					double_element[i] = p_db[j + 7168];
					double_element[i] = p_db[j + 7680];
#endif
				}
				k += 1;				
			}
		}
	}
	qsim_magic_disable();

	return 0;
}

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
	
	int i, j, k;
	double double_element[NUM_THREADS]; 
	int page_num = 0;

	double *p_db = NULL;
	p_db = (double*) calloc(DB_2_MB, sizeof(double));

	for(i = 0; i < DB_2_MB; i++)
		p_db[i] = 3.1415;

	omp_set_num_threads(NUM_THREADS);
	qsim_magic_enable();

	j = 0;
	#pragma omp parallel for private(j, k, page_num) shared (p_db)
	for (i = 0; i < NUM_THREADS; i++)
	{
		/*
		Choose a single thread. i = 0 "somehow" maps to
		CORE2 (i.e. the 3rd core). qsim does this mapping.
		TODO: Figure out border cores and central cores
		*/
		if(i == 0)
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
				for(j = 0; j < DB_2_MB; j++)
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
					page_num = ((j / 512) % 16);
					if(page_num == L2BANKID)
					{
						//cout << "\npage_num = " << page_num << " " << &p_db[j] << endl << flush;
						double_element[i] = p_db[j];
					}
					else if (page_num == L2BANKID+1)
					{
						//cout << "j was " << j ; 						
						j += (512 * (16 - 1)) - 1;
						//cout << " now " << j << endl << flush;
					}
				}
				k += 1;				
			}
		}
	}
	qsim_magic_disable();

	return 0;
}

#include "threads.h"
#define DB_2_MB 262144

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
	double dummy = 0.1;

	double *p_db = NULL;
	p_db = (double*) calloc(DB_2_MB*NUM_THREADS, sizeof(double));

	/*
	for(i = 0; i < NUM_THREADS; i++)
	{
		double_element[i] = 0.0;
		for(j = 0; j < (DBMB); j++)
			arr1[i][j] = 3.1415 + i;
	}
	*/

	for(i = 0; i < DB_2_MB*NUM_THREADS; i++)
		p_db[i] = 3.1415;

	omp_set_num_threads(NUM_THREADS);
	qsim_magic_enable();

	j = 0;
	#pragma omp parallel for private(j, k, page_num) shared (p_db)
	for (i = 0; i < NUM_THREADS; i++)
	{
		for(j = 0; j < DB_2_MB*NUM_THREADS; j++)
		{
			page_num = ((j / 512) % 16);
			if(page_num == i)
			{
				//cout << "\npage_num = " << page_num << endl << flush;
				double_element[i] = p_db[j];
			}
			
		}
	}
	qsim_magic_disable();

	return 0;
}

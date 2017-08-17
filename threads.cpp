#include "threads.h"

using namespace std;

int main(int argc, char * argv[])
{
	int NUM_THREADS;
	if(argc < 2)
	{
		cout << "Usage: threads NUM_THREADS " << endl;
		exit(0);
	}
	NUM_THREADS = atoi(argv[1]);
	
	int i, j, k;
	vector<int> iter;

	s_var **p_str;
	p_str = new s_var* [NUM_THREADS];
	iter.resize(NUM_THREADS);

	for(i = 0; i < NUM_THREADS; i++)
	{
		p_str[i] = (s_var*) calloc(L2BANKMUL, sizeof(s_var));
	}
	
	for(i = 0; i < NUM_THREADS; i++)
	{
		for(j = 0; j < L2BANKMUL; j++)
		{
			for(k = 0; k < L1MUL; k++)
			{
				p_str[i][j].var1[k] = 12 + k;
				p_str[i][j].var2[k] = double (3.1415 + k);
			}
		}
	}

	omp_set_num_threads(NUM_THREADS);
	qsim_magic_enable();

	#pragma omp parallel for private(j, k)
	for (i = 0; i < NUM_THREADS; i++)
	{
		// cout << "Thread" << omp_get_thread_num() << endl << flush;
		// For each thread / core, access one element of the structure
		
		// element number in the range 0 - L2BANKMUL
		j = 0;
		while (j < L2BANKMUL) 
		{
			// cout << "Element number: " << j << endl << flush;
		
			// Integer Ops
			for(k = 0; k < L1MUL - 3; k++)
			{
				while (iter[i] < NUM_CPU_OPS)
				{
					p_str[i][j].var1[k] = p_str[i][j].var1[k] + 15;
					p_str[i][j].var1[k+1] = p_str[i][j].var1[k+1] * 25;
					p_str[i][j].var1[k+2] = p_str[i][j].var1[k+2] / 23;
					iter[i] += 1;
				}
				iter[i] = 0;
				//cout << endl << flush;
			}
			iter[i] = 0;

			// Floating point Ops
			for(k = 0; k < L1MUL - 3; k++)
			{
				while (iter[i] < NUM_CPU_OPS)
				{
					p_str[i][j].var2[k] = p_str[i][j].var2[k] + 15.5567;
					p_str[i][j].var2[k+1] = p_str[i][j].var2[k+1] * 25.3346;
					p_str[i][j].var2[k+2] = p_str[i][j].var2[k+2] / 27.5678;
					iter[i] += 1;
				}
				iter[i] = 0;
				//cout << endl << flush;
			}
			iter[i] = 0; 	
			j = j + MEM_FETCH_INTERVAL;	
		}
	}
	qsim_magic_disable();

	for(i = 0; i < NUM_THREADS; i++)
		free(p_str[i]);

	delete [] p_str;
	return 0;
}

/*
int p[NUM_THREADS][NUM_ITER1], i, j;	
int inum1, inum2, iresult[NUM_THREADS];
inum1 = 0x15;
inum2 = 0x44;

double dnum1, dnum2, dresult[NUM_THREADS];
dnum1 = 123.4567;
dnum2 = 987.6543;

for(i = 0; i < NUM_THREADS; i++)
{
	iresult[i] = 0;
	dresult[i] = 0;
}

omp_set_num_threads(NUM_THREADS);
qsim_magic_enable();
#pragma omp parallel for private(j)
for (i = 0; i < NUM_THREADS; i++)
{
	cout << "Thread" << omp_get_thread_num() << endl << flush;
	// Integer Ops
	for(j = 0; j < NUM_ITER1;j++)
	{
		iresult[i] = inum1 + 0x25;
		iresult[i] = inum2 + 0x59;
		iresult[i] = inum1 + 0x51;
		iresult[i] = inum1 * 0x19;
		iresult[i] = inum2 / 0x2;		 
		cout << iresult[i] << endl << flush;
	}
	// Floating point Ops
	for(j = 0; j < NUM_ITER1;j++)
	{
		dresult[i] = dnum1 + 12.3456;
		dresult[i] = dnum2 + 98.7654;
		dresult[i] = dnum1 + 23.4567;
		dresult[i] = dnum1 * 87.6543;
		dresult[i] = dnum2 / 65.4321;		 
		cout << dresult[i] << endl << flush;
	}
}
qsim_magic_disable();
*/

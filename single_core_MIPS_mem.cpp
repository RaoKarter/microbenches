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
	
	/* Variable description:
	i = iterator for NUM_THREADS
	j = iterator for array elements
	k = iterator for number of memory fetches
	l = iterator for number of int and double operations
	*/
	int i, j, k, l;
	int page_num = 0;
	s_16B temp_str;
	

	s_16B *p_str = NULL;
	p_str = (s_16B*) calloc(STR_2_MB, sizeof(s_16B));

	for(i = 0; i < STR_2_MB; i++)
	{
		p_str[i].double_var3 = 3.1415;
		p_str[i].int_var1 = 12;
		p_str[i].int_var2 = 9;
	}
	temp_str.double_var3 = 0.1;
	temp_str.int_var1 = 0;
	temp_str.int_var2 = 0;	

	//cout << "NUM_ELE_IN_PAGE: " << NUM_ELE_IN_PAGE << endl;
	omp_set_num_threads(NUM_THREADS);
	qsim_magic_enable();

	j = 0;
	#pragma omp parallel for private(j, k, l, page_num, temp_str) shared (p_str)
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
				for(j = 0; j < STR_2_MB; j++)
				{
					/*
					The factor NUM_ELE_IN_PAGE is used to align with 
					a 4KB page.	The factor 16 is to skip all the other 
					L2 banks except the required one.
					Eg: sizeof(s_16B) = 16B. NUM_ELE_IN_PAGE * 16B = 4KB.
					
					page_num = 0 maps addresses to L2BANK #13 i.e.
								 the 14th L2 BANK.

					page_num = 5 maps addresses to L2BANK #2 i.e.
								 the 3rd L2 BANK.			
					*/
					page_num = ((j / NUM_ELE_IN_PAGE) % 16);
					if(page_num == L2BANKID)
					{
						//cout << "page_num = " << page_num << " " << &p_str[j] << endl << flush;

						l = 0;
						// 	Fetch from memory and Perform operations on the fetched elements
						while (l < NUM_CPU_OPS)
						{
							temp_str.double_var3 = p_str[j].double_var3 * 12.345;
							temp_str.int_var1 = p_str[j].int_var1 + 18;
							temp_str.int_var2 = p_str[j].int_var2 + 21;
/*
							temp_str.double_var3 = p_str[j+1].double_var3 / 12.345;
							temp_str.int_var1 = p_str[j+1].int_var1 + 18;
							temp_str.int_var2 = p_str[j+1].int_var2 + 21;

							temp_str.double_var3 = p_str[j+2].double_var3 * 12.345;
							temp_str.int_var1 = p_str[j+2].int_var1 + 18;
							temp_str.int_var2 = p_str[j+2].int_var2 + 21;

							temp_str.double_var3 = p_str[j+3].double_var3 / 12.345;
							temp_str.int_var1 = p_str[j+3].int_var1 + 18;
							temp_str.int_var2 = p_str[j+3].int_var2 + 21;			
*/
							l += 1;
						}
					}
					else if (page_num == L2BANKID+1)
					{
						//cout << "j was " << j ; 						
						j += (NUM_ELE_IN_PAGE * (16 - 1)) - 1;
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

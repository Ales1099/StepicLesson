#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <malloc.h>

#define PML4    	0x0000ff8000000000
#define PDPT    	0x0000007fc0000000
#define PD  		0x000000003fe00000
#define PT  		0x00000000001ff000
#define OFFSET		0x0000000000000fff
#define PERPOSE		0xfffffffffffff000
#define P           0x0000000000000001

#define fPML4E(number)((number)>>39)
#define fPDPTE(number)((number)>>30)
#define fPDE(number)((number)>>21)
#define fPTE(number)((number)>>12)

int main(int argc, char ** argv)
{
	long int ** memory_prt_value;
	uint64_t test;
	uint64_t PML4E;
	uint64_t PDPTE;
	uint64_t PDE;
	uint64_t PTE;
	uint64_t offset;

	long int m,q,r;
	FILE * fileInput = fopen("input.txt","r+");
	long int position = ftell(fileInput);
	int error = fscanf(fileInput,"%ld %ld %ld",&m,&q,&r);
	if(error == EOF)
	{
		fclose(fileInput);
		return(-1);
	}
	
	memory_prt_value = (long int**)malloc(m*sizeof(long int*));

	for(long int index = 0; index < m; ++index)
	{
		memory_prt_value[index] = (long int*)malloc(2*sizeof(long int));
		error = fscanf(fileInput,"%ld %ld",&memory_prt_value[index][0],&memory_prt_value[index][1]);
		if(error == EOF)
		{
			fclose(fileInput);
			return(-1);
		}
	}

	uint64_t local_logical_adress;
	uint64_t check_p;
	uint64_t local_offset = r;
	uint64_t physical_adress;
	long int ok = 0;

	for(long int i = 0; i<q; i++)
	{
		error = fscanf(fileInput,"%ld\n",&test);
		if(error == EOF)
		{
			fclose(fileInput);
			return(-1);
		}
		else
		{
			offset = test & OFFSET;
			PML4E = test & PML4;
			PDPTE = test & PDPT;
			PDE = test & PD;
			PTE = test & PT;
	
			PML4E = fPML4E(PML4E);
			PDPTE = fPDPTE(PDPTE);
			PDE = fPDE(PDE);
			PTE = fPTE(PTE);

			if(ok == 0)
			{
				physical_adress = PML4E * 8 + local_offset;

				for(long int i = 0; i<m; i++)
				{
					if(physical_adress == memory_prt_value[i][0])
					{
						check_p = memory_prt_value[i][1] & P;
						printf("%ld\n", check_p );
						if(check_p == 1)
						{
							local_offset = (memory_prt_value[i][1] & PERPOSE);//>>12;
							break;
						//	printf("%ld\n", physical_adress);
						//	printf("%ld\n", local_offset);
						}
						else
						{
							ok = 1;
							printf("fault\n");
							break;
						}
					}
				}
			}
			else
			{
				ok = 0;
				printf("fault\n");
				continue;
			}

			if(ok == 0)
			{
				physical_adress = PDPTE * 8 + local_offset;

				for(long int i = 0; i<m; i++)
				{
					if(physical_adress == memory_prt_value[i][0])
					{
						check_p = memory_prt_value[i][1] & P;
						printf("%ld\n", check_p );
						if(check_p == 1)
						{
							local_offset = (memory_prt_value[i][1] & PERPOSE);//>>12;
							break;
						//	printf("%ld\n", physical_adress);
						//	printf("%ld\n", local_offset);						
						}
					}
				}
			}
			else
			{
				ok = 0;
				printf("fault\n");
				continue;
			}

			if(ok == 0)
			{
				physical_adress = PDE * 8 + local_offset;

				for(long int i = 0; i<m; i++)
				{
					if(local_logical_adress == memory_prt_value[i][0])
					{
						check_p = memory_prt_value[i][1] & P;
						printf("%ld\n", check_p );
						if(check_p == 1)
						{
							local_offset = (memory_prt_value[i][1] & PERPOSE);//>>12;
							break;
							//printf("%ld\n", physical_adress);
							//printf("%ld\n", local_offset);						
						}
						else
						{
							ok = 1;
							printf("fault\n");
							break;
						}
					}
				}
			}
			else
			{
				ok = 0;
				printf("fault\n");
				continue;
			}

			if(ok == 0)
			{
				physical_adress = PTE * 8 + local_offset;

				for(long int i = 0; i<m; i++)
				{
					if(physical_adress == memory_prt_value[i][0])
					{
						check_p = memory_prt_value[i][1] & P;
						printf("%ld\n", check_p );
						if(check_p == 1)
						{
							local_offset = (memory_prt_value[i][1] & PERPOSE);
							break;
							//printf("%ld\n", physical_adress);
							//printf("%ld\n", local_offset);
						}
						else
						{
							ok = 1;
							printf("fault\n");
							break;
						}
					}
				}
			}
			else
			{
				ok = 0;
				printf("fault\n");
				continue;
			}

			physical_adress = local_offset;
			if(ok == 0)
			{
				for(long int i = 0; i<m; i++)
				{
					if(physical_adress == memory_prt_value[i][0])
					{
						check_p = memory_prt_value[i][1] & P;
						printf("%ld\n", check_p);
						if(check_p == 1)
						{
							local_offset = (memory_prt_value[i][1] & PERPOSE);
							break;
						}
						else
						{
							ok = 1;
							printf("fault\n");
							break;
						}
					}
				}
			}
			else
			{
				ok = 0;
				printf("fault\n");
				continue;
			}

			if(ok == 0)
			{
				physical_adress = local_offset + offset;

				printf("%ld \n", physical_adress);

				local_offset = r;
			}
			else
			{
				ok = 0;
				printf("fault\n");
			}
		}

	}

	fclose(fileInput);
	return(0);
}

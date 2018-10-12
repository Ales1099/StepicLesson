#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define PML4    	0x0000ff8000000000
#define PDPT    	0x0000007fc0000000
#define PD  		0x000000003fe00000
#define PT  		0x00000000001ff000
#define OFFSET		0x0000000000000fff
#define PERPOSE	        0x000ffffffffff000
#define P               0x0000000000000001

int main(int argc, char ** argv)
{
	unsigned long long int ** memory_prt_value;
	unsigned long long int test = 0;
	unsigned long long int PML4E = 0;
	unsigned long long int PDPTE = 0;
	unsigned long long int PDE = 0;
	unsigned long long int PTE = 0;
	unsigned long long int offset = 0;

	unsigned long long int b1, b2;

	long int m, q, r;
	FILE * fileInput = fopen("input.txt", "r+");
	FILE * fileOutput = fopen("output.txt", "w+");
	long int position = ftell(fileInput);
	int error = fscanf(fileInput, "%ld %ld %ld", &m, &q, &r);
	if (error == EOF)
	{
		fclose(fileInput);
		return(-1);
	}

	memory_prt_value = (unsigned long long int**)malloc(m * sizeof(unsigned long long int*));

	for (long int index = 0; index < m; ++index)
	{
		memory_prt_value[index] = (unsigned long long int*)malloc(2 * sizeof(unsigned long long int));
		error = fscanf(fileInput, "%llu %llu", &b1, &b2);
		memory_prt_value[index][0] = b1;
		memory_prt_value[index][1] = b2;
		if (error == EOF)
		{
			fclose(fileInput);
			return(-1);
		}
	}

	unsigned long long int local_logical_adress = 0;
	unsigned long long int check_p;
	unsigned long long int local_offset = r;
	unsigned long long int physical_adress = 0;
	short int ok = 0;

	for (long int i = 0; i < q; i++)
	{
		error = fscanf(fileInput, "%llu\n", &b1);
		local_logical_adress = b1;
		if (error == EOF)
		{
			fclose(fileInput);
			return(-1);
		}
		else
		{
			local_offset = r;
			offset = local_logical_adress & OFFSET;
			PML4E  = local_logical_adress & PML4;
			PDPTE  = local_logical_adress & PDPT;
			PDE    = local_logical_adress & PD;
			PTE    = local_logical_adress & PT;

			PML4E >>= 39;
			PDPTE >>= 30;
			PDE   >>= 21;
			PTE   >>= 12;

			if (ok == 0)
			{
				physical_adress = PML4E * 8 + local_offset;

				for (long int j = 0; j < m; j++)
				{
					if (physical_adress == memory_prt_value[j][0])
					{
						check_p = memory_prt_value[j][1] & P;
						if (check_p == 1)
						{
							ok = 0;
							local_offset = (memory_prt_value[j][1] & PERPOSE);
							break;
						}
						else
						{
							ok++;
							break;
						}
					}
					else
					{
						ok++;
					}
				}
			}
			else
			{
				ok = 0;
				fprintf(fileOutput,"%s","fault\n");
				continue;
			}

			if (ok == 0)
			{
				physical_adress = PDPTE * 8 + local_offset;

				for (long int j = 0; j < m; j++)
				{
					if (physical_adress == memory_prt_value[j][0])
					{
						check_p = memory_prt_value[j][1] & P;
						if (check_p == 1)
						{
							ok = 0;
							local_offset = (memory_prt_value[j][1] & PERPOSE);
							break;
						}
						else
						{
							ok++;
							break;
						}
					}
					else
					{
						ok++;
					}
				}
			}
			else
			{
				ok = 0;
				fprintf(fileOutput, "%s", "fault\n");
				continue;
			}

			if (ok == 0)
			{
				physical_adress = PDE * 8 + local_offset;

				for (long int j = 0; j < m; j++)
				{
					if (physical_adress == memory_prt_value[j][0])
					{
						check_p = memory_prt_value[j][1] & P;
						if (check_p == 1)
						{
							ok = 0;
							local_offset = (memory_prt_value[j][1] & PERPOSE);
							break;
						}
						else
						{
							ok++;
							break;
						}
					}
					else
					{
						ok++;
					}
				}
			}
			else
			{
				ok = 0;
				fprintf(fileOutput, "%s", "fault\n");
				continue;
			}


			if (ok == 0)
			{
				physical_adress = PTE * 8 + local_offset;

				for (long int j = 0; j < m; j++)
				{
					if (physical_adress == memory_prt_value[j][0])
					{
						check_p = memory_prt_value[j][1] & P;
						if (check_p == 1)
						{
							ok = 0;
							local_offset = (memory_prt_value[j][1] & PERPOSE);
							break;
						}
						else
						{
							ok++;
							break;
						}
					}
					else
					{
						ok++;
					}
				}
			}
			else
			{
				ok = 0;
				fprintf(fileOutput, "%s", "fault\n");
				continue;
			}

			if (ok == 0)
			{
				physical_adress = local_offset + offset;

				fprintf(fileOutput, "%ld\n", physical_adress);

				PML4E = 0;
				PDPTE = 0;
				PDE = 0;
				PTE = 0;
				local_logical_adress = r;
				physical_adress = 0;
				offset = 0;
				ok = 0;
			}
			else
			{
				ok = 0;
				fprintf(fileOutput, "%s", "fault\n");
				continue;
			}
		}

	}

	free(memory_prt_value);

	fclose(fileInput);
	fclose(fileOutput);
	return(0);
}

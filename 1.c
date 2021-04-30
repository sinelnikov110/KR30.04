#define EPS 0.0000000000001
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
int count(  FILE *fp , int * c);
int file_arr( FILE *fp, double * b, int n);
void Process(double *b, int *c, int n);


int count(  FILE *fp , int * c)
{
	
	int n=0;
	
	if(!(fscanf( fp, "%d", c+0)))
	{
		return - 1;
	}
	if(!(fscanf( fp, "%d", c+1)))
	{	
		return - 1;
	}
	if(c[0] < 0 && c[1] > 0)
	{
		return -1;
	}
	
	if(c[1] < 0 && c[0] > 0)
	{
		return -1;
	}
	
	n=c[0]*c[1];
	
	return n;
}
 
int file_arr(  FILE *fp, double * b, int n)
{
	int i;
	double x, tmp;
	
	for(  i = 0; i < n; i++)
	{
		
		if(fscanf(fp,"%lf",&tmp) ==EOF)
		{
		return -1;
		}
		
		if(!(fscanf( fp, "%lf", b + i)))
		{
			return - 1;
		}
	}
	
	
	if(fscanf(fp,"%lf",&tmp)!=EOF)
	{
		return -1;
	}
	return 0;
	
}

void Process(double *b, int *c, int n)
{
	int i, k, l_1, k_1;
	double min;
	double trans;
	min = b[0];
	l_1 = 0;
	
	for(k = 0; k < c[0]; k++)
	{
		for(i = 0; i < c[1]; i++)
		{
			if( b[i + c[1]*k] < min )
			{
				min = b[i + c[1]*k];
				l_1 = k;
			}
		}
	}
	
	
	for(i = 0; i < c[1]; i++)
	{
		trans = b[i + l_1*c[1]];
		
		b[i + l_1*c[1]] = b[i + (c[0] - 1)*c[1]];
			
		b[i + (c[0] - 1)*c[1]] = trans;
		
	}
	
	
}












int main (int argc, char **argv)
{
	int n,i,k;
	FILE *fp;
	FILE *fw;
	char *ch;
	double *b;
	int c[2];
	int N, M;
	
	ch = argv[1];
	if( !(fp = fopen( ch, "r")))
	{	
		printf("File ERROR");
		return -1;
	}
	
	n = count(fp, c);
	
	if(!(b = (double*)malloc((n)*sizeof(double))))
	{	
		fclose(fp);
		printf("fall with memory");
		return -1;
	}
	
	if(file_arr(fp, b, n) == -1)
	{
		free(b);
		fclose(fp);
		printf("input File ERROR");
		return -1;
	
	}
	
	Process(b, c, n);
	
	
	ch = argv[2];
	if( !(fw = fopen( ch, "w")))
	{	
		printf("File ERROR");
		return -1;
	}
	
	
	
	for(k = 0; k < c[0]; k++)
	{	
		for(i = 0; i < c[1]; i++)
		{
			fprintf(fw, "%lf ", b[i + k*c[1]] );
		}
		fprintf(fw, "\r\n");
	}
	
	
	free(b);
	fclose(fp);
	fclose(fw);
	return 0;
	
	
	
}


#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated

void heapify(int arr[], int n, int x)//helper function for the heapsort
{
	int max = x;
	int l = 2 * x + 1;
	int r = 2 * x + 2;

	if(l < n && arr[l] > arr[max])
	{
		max = l;
	}

	if(r < n && arr[r] > arr[max])
	{
		max = r;
	}

	if(max != x)
	{
		int temp = arr[x];
		arr[x] = arr[max];
		arr[max] = temp;

		heapify(arr, n, max);
	}
}
void heapSort(int arr[], int n)
{
	int i;

	for(i = n / 2 - 1; i >= 0; i--)
	{
		heapify(arr, n, i);
	}

	for(i = n - 1; i >= 0; i--)
	{
		int temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;

		heapify(arr, i, 0);
	}
}


// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void merge(int data[], int l, int m, int r)//Helper function for the mergeSort
{
	int i, j, z;
	int n1 = m - l + 1;
	int n2 = r - m;

	int *temp1 = (int*) malloc(n1 * sizeof(int));
	int *temp2 = (int*) malloc(n2 * sizeof(int));
	extraMemoryAllocated += n1 * sizeof(int) + n2 * sizeof(int);

	for(i = 0; i < n1; i++) 
	{
		temp1[i] = data[l + i];	
	}
	
	for(j = 0; j < n2; j++)
	{
		temp2[j] = data[m + 1 + j];
	}

		i = 0;
		j = 0;
		z = l;

		while(i < n1 && j < n2)
		{
			if(temp1[i] <= temp2[j])
			{
				data[z] = temp1[i];
				i++;
			}
			else
			{
				data[z] = temp2[j];
				j++;
			}
			z++;
		}

		while(i < n1)
		{
			data[z] = temp1[i];
			i++;
			z++;
		}

		while(j < n2)
		{
			data[z] = temp2[j];
			j++;
			z++;
		}

		free(temp1);
		free(temp2);
}

void mergeSort(int pData[], int l, int r)
{
	if(l < r)
	{
		int mid = (l + r) / 2;

		mergeSort(pData, l, mid);
		mergeSort(pData, mid + 1, r);

		
		merge(pData, l, mid, r);
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		
		if(i >= dataSz)
		{
			printf("\n\n");
			return;
		}
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}
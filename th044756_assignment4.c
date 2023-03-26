#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;


//merge function
void merge(int arr[], int left, int mid, int right){
	//placeholder vars
	int i, j, k;

	//Array partitions
	int n1 = mid - left + 1;
	int n2 = right - mid;

	//temp arrays
	int *leftA = (int*)malloc(n1*sizeof(int));
	int *rightA = (int*)malloc(n2*sizeof(int));


	//merge sort uses temporary arrays, so increase extraMemoryAllocated based on size of arrays
	extraMemoryAllocated += n1*sizeof(int) + n2*sizeof(int);

	//Data copying
	for(i = 0; i < n1; i++){
		leftA[i] = arr[left + i];
	}
	for(j = 0; j < n2; j++){
		rightA[j] = arr[mid + 1 + j];
	}
	//initial indexes
	i = 0;
	j = 0;
	k = left;
	//merging back into arrays
	while(i < n1 && j < n2){
		if(leftA[i] <= rightA[j]){
			arr[k] = leftA[i];
			i++;
		}
		else{
			arr[k] = rightA[j];
			j++;
		}
		k++;

	}
	//checks for remaining elements
	while(i < n1){
		arr[k] = leftA[i];
		i++;
		k++;
	}

	while(j < n2){
		arr[k] = rightA[j];
		j++;
		k++;
	}

	free(leftA);
	free(rightA);

}


// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int left, int right)
{
	if(left < right){
		//finds middle of array
		int mid = left + (right-left)/2;
		//recursively sorts both halves of array 
		mergeSort(pData, left, mid);
		mergeSort(pData, mid + 1, right);
		//merges sorted arrays back together
		merge(pData, left, mid, right);
	}
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	int key;
    //insertion sort doesnt require additional memory allocation
    extraMemoryAllocated = 0;
    for(int i = 0; i < n; i++){
        key = pData[i];
        int j = i - 1;

        while(j >= 0 && pData[j] > key){
            pData[j + 1] = pData[j];
            j = j - 1;
        }
        pData[j + 1] = key;
    }
}

//swap function for bubble sort
void swap(int *xp, int *yp){
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}


// implement bubble sort
// use variable extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
	//loops through array n-1 times
	for(int i = 0; i < n - 1; i++){
		//loops through unsorted part of array
		for(int j = 0; j < n - i - 1; j++){
			//if next element in array is larger than current element, swap data
			if(pData[j] > pData[j + 1]){
				swap(&pData[j], &pData[j + 1]);
			}
		}
	}
	
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	int min_idx;
	int temp;
	//moves boundary of unsorted array
	for(int i = 0; i < n-1; i++){
		//locates minimun element for each pass
		min_idx = i;
		for(int j = i + 1; j < n; j++){
			if(pData[j] < pData[min_idx]){
				min_idx = j;
			}
		}
		//swaps the minimum element with the first element 
		temp = pData[min_idx];
		pData[min_idx] = pData[i];
		pData[i] = temp;
		//inplace sorting algorithm, doesnt require extra memory allocation

		
	}
	
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		for(int i = 0; i < dataSz; i++){
			fscanf(inFile, "%d", &((*ppData)[i]));
		}
	}
	fclose(inFile);
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
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
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
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
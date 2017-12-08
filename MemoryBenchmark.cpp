#include<pthread.h>
#include<stdio.h>
#include<time.h>
#include <iostream>
#include <sys/time.h>
#include <cstring>
#include <cstdlib>

using namespace std;

//CUDA Accelerated Linpack
#define MEMSIZE 1000000000
#define MB 1000000

float executionTime;
int numThreads;
long blockSize;
int seqOrRandomRead,seqOrRandomWrite;
void *seq_read(void *blockSize);
void *random_read(void *blockSize);
void *seq_write(void *blockSize);
void *random_write(void *blockSize);
float throughPut,latency;
int readOrWrite;
double totalOperations;
FILE *fp;

//0.96385
//1.61

int main() {
string input;
    cout<<"press s to start"<<endl;

  while (getline(std::cin, input) && input != "q"){
if(input=="s"){


    cout <<"Memory Benchmarking"<< endl;
    cout<< "---------------------"<<endl;
    cout << "Enter 1 to Read or 2 to Write : "<<endl;
    cin >> readOrWrite;
    cout << "Enter number of Threads" <<endl;
    cin >> numThreads;
    cout << "Enter BlockSize in Byte" <<endl;
    cin >> blockSize;

    int i;
    struct timeval start_time, end_time;

    pthread_t pt[numThreads];

    if(readOrWrite==1){

        cout << "Enter 0 for Sequential Read Access Or 1 for Random Read Access:"<<endl;
        cin >>seqOrRandomRead;

        gettimeofday(&start_time,NULL);

        for(i=0;i<numThreads;i++){

            if(seqOrRandomRead==0){

                pthread_create(&pt[i], NULL,seq_read, (void*)(long)blockSize);
            }
            else if(seqOrRandomRead==1){

                pthread_create(&pt[i], NULL,random_read,(void*)(long)blockSize);
            }
        }

        for(i=0;i<numThreads;i++)
        {
            pthread_join(pt[i], NULL);
        }
        gettimeofday(&end_time, NULL);

    }
    else if(readOrWrite==2){

        cout << "Enter 0 for Sequential Write Access Or 1 for Random Write Access:"<<endl;

        cin >>seqOrRandomWrite;

        gettimeofday(&start_time, NULL);

        for(i=0;i<numThreads;i++){

            if(seqOrRandomWrite==0){

                pthread_create(&pt[i], NULL,seq_write, (void*)(long)blockSize);
            }
            else if(seqOrRandomWrite==1){


                pthread_create(&pt[i], NULL,random_write,(void*)(long)blockSize);

            }
        }
        
        for(i=0;i<numThreads;i++)
        {
            pthread_join(pt[i], NULL);

        }
        gettimeofday(&end_time, NULL);
    }

    executionTime=((end_time.tv_sec - start_time.tv_sec) + ((double)(end_time.tv_usec - start_time.tv_usec)/1000000));

    throughPut=MEMSIZE/executionTime;
    throughPut=throughPut/MB;

    totalOperations=MEMSIZE/blockSize;
    latency = (executionTime /totalOperations)*1000;

    fp= fopen( "memoryLogs.txt", "ab" );

    fprintf(fp,"\nIn Random Write with BlockSize of %d and number thread %d, the ThroughPut in Mbps: %f",blockSize,numThreads,throughPut);
    fprintf(fp,"\nIn Random Write with BlockSize of %d and number thread %d, the Latency in msecond: %f",blockSize,numThreads,latency);

    cout << "Elapsed Time:"<< executionTime <<endl<< "ThroughPut : "<<throughPut<<"MB/sec"<<endl;
    cout << "Latency in ms: "<< latency<<endl;
cout<<"press s to start again or press q to quit"<<endl;
}
    return 0;
}

void *seq_read(void *blockSize){

    int input_size=(int)(long)blockSize;
    char *a= new char[MEMSIZE];
    int i;
    char *b= new char[input_size];

    for(i=0;i<MEMSIZE/input_size;i++)
    {
        memcpy(b, a + i * input_size, input_size);
    }
    free(a);
    free(b);

}

void *random_read(void *blockSize){

 int input_size=(int)(long)blockSize;

    char *a= new char[MEMSIZE];
    int i;
    int r;
    char *b = new char[input_size];
    for(i=0;i<MEMSIZE/input_size;i++)
    {
        r = rand()%(MEMSIZE/input_size);
        memcpy(b, a + r * input_size, input_size);
    }
    free(a);
    free(b);
}

void *seq_write(void *blockSize){

    int input_size=(int)(long)blockSize;

    char *a= new char[MEMSIZE];

    int i;
    for(i=0;i<MEMSIZE/input_size;i++)
    {
        memset(a + i * input_size,'1',input_size);
    }
    free(a);

}

void *random_write(void *blockSize){

    int input_size=(int)(long)blockSize;

    char *a= new char[MEMSIZE];
    int i;
    int r;

    for(i=0;i<MEMSIZE/input_size;i++)
    {
        r = rand()%(MEMSIZE/input_size);
        memset(a + r * input_size,'0',input_size);
    }
    free(a);

}

/*
Enter 1 to Read or 2 to Write :
1
Enter number of Threads
2
Enter BlockSize in Byte
1048576
Enter 0 for Sequential Read Access Or 1 for Random Read Access:
0
Elapsed Time:1.87536
ThroughPut : 1066.46
*/















#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;

#define diskSize 1200000000
#define MB 1000000

int numThreads;
int seqOrRandomRead,seqOrRandomWrite;

float throughput,latency;
int readOrWrite;
long double executionTime;
long blockSize;
void *seq_read(void *blockSize);
void *random_read(void *blockSize);
void *seq_write(void *blockSize);
void *random_write(void *blockSize);
double totalOperations;
FILE *fp;


int main() {

    string input;
    cout<<"press s to start"<<endl;

  while (getline(std::cin, input) && input != "q"){
  if(input=="s"){

    cout <<"Disk Benchmarking"<< endl;
    cout<< "---------------------"<<endl;
    cout << "Enter 1 to Read or 2 to Write into Disk : "<<endl;
    cin >> readOrWrite;
    cout << "Enter number of Threads" <<endl;
    cin >> numThreads;
    cout << "Enter BlockSize in Byte" <<endl;
    cin >> blockSize;

    int i;

    struct timeval start_time, end_time;

    pthread_t pt[numThreads];

    if(readOrWrite==1){

        cout << "Enter 0 for Sequential Read Access Or 1 for Random Read Access to Disk:"<<endl;
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

        cout << "Enter 0 for Sequential Write Access Or 1 for Random Write Access to Disk:"<<endl;

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

    executionTime=((end_time.tv_sec - start_time.tv_sec) + ((double)(end_time.tv_usec - start_time.tv_usec)/1000000.0));
    //executionTime=executionTime/1000;

    throughput=float(diskSize)/executionTime;
    throughput=throughput/MB;

    totalOperations=diskSize/blockSize;

    latency = (executionTime /totalOperations)*1000;

    cout << "Elapsed Time:"<< executionTime <<endl<< "ThroughPut : "<<throughput<<"MB/sec"<<endl;

    fp= fopen("diskLogs.txt", "ab");

    fprintf(fp,"\nIn Sequential Read with BlockSize of %d and number thread %d, the ThroughPut in Mbps: %f",blockSize,numThreads,throughput);
    fprintf(fp,"\nIn Sequential Read with BlockSize of %d and number thread %d, the Latency in msecond: %f",blockSize,numThreads,latency);

    cout << "Latency in Seconds: "<< latency<<endl;
    cout<<"press s to start again or press q to quit"<<endl;

}

 }

    return 0;
}

void *seq_read(void *blockSize){

    int input_size=(int)(long)blockSize;
    int i;
    int fil;
    fil=open("test.txt", O_RDONLY, 0666);
    char *b= new char[input_size];
    for(i=0;i<diskSize/input_size;i++)

    {
        
        read(fil,b,input_size);
    }
free(b);
  close(fil);

}


void *random_read(void *blockSize){


    int input_size=(int)(long)blockSize;
    int fil;
    fil=open("test.txt", O_RDONLY, 0666);
    int i;
    int r;
    char *b = new char[input_size];
    for(i=0;i<diskSize/input_size;i++)
    {
        //char *b = new char[input_size];
        r = rand()%(diskSize/input_size);
        lseek(fil,r*input_size,SEEK_SET);
        read(fil,b,input_size);
    }
    free(b);
    close(fil);

}

void *seq_write(void *blockSize){

    int input_size=(int)(long)blockSize;
    int fil;
    fil=open("test.txt", O_CREAT|O_TRUNC|O_WRONLY, 0666);
    int i;
     char *b = new char[input_size];
    for(i=0;i<diskSize/input_size;i++)
    {
       //char *b = new char[input_size];
        memset(b,'1',input_size);
        write(fil,b,input_size);

    }
free(b);
    close(fil);

}

void *random_write(void *blockSize){

    int input_size=(int)(long)blockSize;
    int fil;
    fil=open("test.txt",O_CREAT|O_TRUNC|O_WRONLY, 0666);
    int i;
    int r;
     char *b = new char[input_size];
    for(i=0;i<diskSize/input_size;i++)
    {
        r = rand()%(diskSize/input_size);
       //char *b = new char[input_size];
        memset(b,'0',input_size);
        lseek(fil,r*input_size,SEEK_SET);
        write(fil,b,input_size);
    }
free(b);
    close(fil);
}
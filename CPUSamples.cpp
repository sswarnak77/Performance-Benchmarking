#include <iostream>
#include<pthread.h>
#include<stdio.h>
#include<time.h>
#include <sys/time.h>
#include <algorithm>

using namespace std;
#define size 8
#define giga 1000000000

long double executionTime;
float iopsSamples;
float flopsSamples;

long flopOperations[size];
long IopsOperations[size];

void GFLOPSamples();
void IOPSamples();
void* GFLOPS(void *p);
void* IOPS(void *p);
void reset();

pthread_t pt_float[size];


int main() {

    cout <<"Collecting CPU Samples"<< endl;

    cout<< "---------------------"<<endl;
    GFLOPSamples();
    return 0; 
}

void GFLOPSamples(){

    int timeTaken=0;
    int usedTime;

    struct timeval start_float, end_float;
    long numberOfOperations;

    gettimeofday(&start_float, NULL);

    int i;
    for(i=0;i<8;i++){

        pthread_create(&pt_float[i], NULL,GFLOPS, &i);
    }
    do{
        gettimeofday(&end_float, NULL);
        usedTime =((end_float.tv_sec - start_float.tv_sec)*1000L) + ((double)(end_float.tv_usec - start_float.tv_usec)/1000L);
        if(usedTime >= 1){
            numberOfOperations=flopOperations[0]+flopOperations[1]+flopOperations[2]+flopOperations[3]+flopOperations[4]+flopOperations[5]+flopOperations[6]+flopOperations[7];
            cout << numberOfOperations<<endl;
            reset();
            timeTaken++;
            gettimeofday(&start_float, NULL);
        }

    }while(timeTaken<600);

}

void* GFLOPS(void *p){
    int c= *(int *)p;
    long t;

    while(1){
        174.1+148.14;
        3.254-47.78;
        47.14+76.34;
        1.74-68.65;
        4.98+7.78;
        3.754-98.67;
        4.85+36.84;
        3.4+5.4;
        2.2+5.6;
        3.8+7.23;
        78.12+4.78;
        4.47+7.58;
        47.14+14.89;
        7.47+149.25;
        74.43-743.78;
        36.45-47.647;
        75.47-21.4;
        47.47-367.57;
        4.784-7.456;
        36.45-47.647;
        75.47-21.4;
        47.47-367.57;
        4.784-7.456;
        flopOperations[c]=flopOperations[c]+22;
    }
}

void reset(){
    int i;

    for(i=0;i<8;i++){
        flopOperations[i]=0;
    }

}
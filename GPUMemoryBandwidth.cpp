#include <cstdlib>
#include<iostream>
#include<cuda.h>
#include <sys/time.h>
#include <cuda_fp16.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define SIZE 1024
using namespace std;

float writeBandwidth,readBandwidth,executionTime;

__global__ void multiplyInt(int *a,int *b,int n){
    
    int i=blockIdx.x*blockDim.x+threadIdx.x;
    
    if(i<n){
        
      b[i]=b[i]+a[i];

    }
}

int main()
 
{
  
 cudaDeviceProp prop;
 cudaGetDeviceProperties(&prop, 0);
 cout << "Device name : "<< prop.name<<endl;
 cout << "Memory Clock Rate (KHz) :" << prop.memoryClockRate<<endl;;
 cout << "Memory Bus Width (bits): " << prop.memoryBusWidth<<endl;
 cout << "Peak Memory Bandwidth (GB/s):"<< 2.0*prop.memoryClockRate*(prop.memoryBusWidth/8)/1.0e6) <<endl;
    
 int *a,*b;
 int *d_a,*d_b;

 struct timeval start_read, end_read;
 struct timeval start_write, end_write;

  a= new int[SIZE];
  b=new int[SIZE];

cudaMalloc(&d_a, SIZE*sizeof(int));
cudaMalloc(&d_b, SIZE*sizeof(int));

    int i;

    for (i = 0; i < SIZE;i++) {
        a[i] = i;
        b[i] = 1;
    }

gettimeofday(&start_read, NULL);

for(i=0;i<1000000;i++){

    cudaMemcpy(d_a, a,SIZE*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b,SIZE*sizeof(int), cudaMemcpyHostToDevice);
  }

 gettimeofday(&end_read, NULL);

 executionTime=(1000.0 * (end_read.tv_sec - start_read.tv_sec) + (end_read.tv_usec - start_read.tv_usec) / 1000.0)

readBandwidth=float(SIZE*2*1000000*sizeof(int))/executionTime;

cout << "Read Bandwidth for GPU Memory in Mbps:" << readBandwidth<<endl;

multiplyInt<<<1,SIZE>>>(d_a,d_b,SIZE);

gettimeofday(&start_write, NULL);

for(i=0;i<1000000;i++){

    cudaMemcpy(a,d_a,SIZE*sizeof(int), cudaMemcpyDeviceToHost);
    cudaMemcpy(b,d_b,SIZE*sizeof(int), cudaMemcpyDeviceToHost);
  }

gettimeofday(&end_write, NULL);

executionTime=(1000.0 * (end_write.tv_sec - start_write.tv_sec) + (end_write.tv_usec - start_write.tv_usec) / 1000.0)
writeBandwidth=float(SIZE*1000000*sizeof(int))/executionTime;

cout << "Write Bandwidth for GPU Memory in Mbps:" <<writeBandwidth<<endl;

    cudaFree(d_a);
    cudaFree(d_b);

    return 0;  
}

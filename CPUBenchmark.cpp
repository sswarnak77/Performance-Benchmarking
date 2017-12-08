#include<pthread.h>
#include<stdio.h>
#include<time.h>
#include <iostream>
#include <sys/time.h>

using namespace std;

#define giga 1000000000

double executionTime;
float finaliops;
float finalflops;

void findGFLOPS(int c);
void findIOPS(int c);
void* GFLOPS(void *);
void* IOPS(void *);
FILE *fp;

int GIOPS;


int main() {

    int numThreads;
    string input;
    cout<<"press s to start"<<endl;

  while (getline(std::cin, input) && input != "q")
  {

   if(input=="s"){

    cout <<"CPU Benchmarking"<< endl;

    cout<< "---------------------"<<endl;

    cout << "Enter 1 for GFLOPS or 2 for IOPS : "<<endl;
    cin >> GIOPS;

    cout << "Enter number of Threads" <<endl;
    cin >> numThreads;

    if(GIOPS==1){
        findGFLOPS(numThreads);
    }
    else if(GIOPS==2){
        findIOPS(numThreads);
}
 cout<<"press s to start again or press q to quit"<<endl;
}

}
    return 0;
}

void findGFLOPS(int c){

    pthread_t pt[c];
    int i;
    struct timeval start_float, end_float;

    gettimeofday(&start_float, NULL);

    for(i=0;i<c;i++){

        pthread_create(&pt[i],NULL,GFLOPS,NULL);
    }

    for(i=0;i<c;i++){
        pthread_join(pt[i],NULL);
    }
    gettimeofday(&end_float, NULL);

    executionTime=((end_float.tv_sec - start_float.tv_sec) + ((end_float.tv_usec - start_float.tv_usec)/1000000.0));

    cout << "execution time :" << executionTime <<"second"<<endl;

    finalflops=(35*1000000*c)/executionTime;
    finalflops=(finalflops)/giga;
    
    fp= fopen( "CPULogs.txt", "ab" );

    fprintf(fp,"\nGLOPS Using %d Thread: %f",c,finalflops);
    cout << "GFLOPS: "<<finalflops<<endl;

}

    void findIOPS(int c){

        pthread_t pt[c];

        int i;
        struct timeval start_int, end_int;

        gettimeofday(&start_int, NULL);

        for(i=0;i<c;i++){

            pthread_create(&pt[i],NULL,IOPS,NULL);
        }
 
        for(i=0;i<c;i++){
            pthread_join(pt[i],NULL);
        }

        gettimeofday(&end_int, NULL);

        executionTime=((end_int.tv_sec - start_int.tv_sec) + ((end_int.tv_usec - start_int.tv_usec)/1000000.0));
        cout << "execution time :" << executionTime <<"second"<<endl;
        finaliops=(35*1000000)/executionTime;
        cout << finaliops << endl;
        finaliops=(c*finaliops)/giga;
        fp= fopen( "CPULogs.txt", "ab" );
        fprintf(fp,"\nIOPS Using %d Thread: %f",c,finaliops);
        cout << "IOPS: "<<finaliops<<endl;
        }



    void* GFLOPS(void *){
            long i;
            
            for(i=0;i<1000000;i++){
                1.0+1111.0;
                1111.0+2189.0;
                111.12343-1231.12312;
                213123.666+23123.0;
                123.123+12312.123;
                123123.123-544.2131;
                1.0+1111.0;
                1111.0+2189.0;
                111.12343+1231.12312;
                213123.666-23123.0;
                123.123-12312.123;
                123123.123+544.2131;
                1.0-1111.0;
                1111.0-2189.0;
                111.12343+1231.12312;
                213123.666-23123.0;
                123.123+12312.123;
                123123.123-544.2131;
                1.0+1111.0;
                1111.0+2189.0;
                111.12343-1231.12312;
                213123.666+23123.0;
                123.123-12312.123;
                123123.123+544.2131;1.0+1111.0;
                1111.0+2189.0;
                111.12343-1231.12312;
                213123.666+23123.0;
                123.123+12312.123;
                123123.123-544.2131;
                1.0+1111.0;
                1111.0+2189.0;
                111.12343-1231.12312;
                213123.666+23123.0;
                123.123-12312.123;
                123123.123+544.2131;

            }
        }





        void* IOPS(void *){

            long i;

            for(i=0;i<1000000;i++){

                1+1111;
                1111-2189;
                111+1231;
                21312+23123;
                12-1231;
                12312+544;
                1+1111;
                11-218;
                11+123;
                21312+2312;
                12-1231;
                12312+54;
                1+1111;
                111-21;
                11+123;
                213123+23123;
                1+1111;
                1111-2189;
                111+1231;
                21312-23123;
                12+1231;
                12312-544;
                1+1111;
                11+218;
                11+123;
                21312-2312;
                12+1231;
                12312-54;
                1+1111;
                111-21;
                1234-123;
                1112-129;
                238-33;
                3271+1245;
                213+1123;

            }
        }

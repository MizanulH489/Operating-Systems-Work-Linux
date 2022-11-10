#include <pthread.h>
#include <stdio.h>
#define NUM_THREADS 5

// Declare  variable 
pthread_mutex_t mtx1;

// void printHello
void *PrintHello(void *threadid)
{
    long tid;
    tid = (long)threadid;
    pthread_mutex_lock(&mtx1);//pthread_mutex_unlock function to lock mutex
    printf("Hello World! It's me, thread #%ld!\n", tid); 
    pthread_mutex_unlock(&mtx1); //pthread_mutex_unlock function to unlock mutex
    pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
    // create an array of thread struct instances with appropiate lenght
    long t;
    pthread_t thread[NUM_THREADS];

    int j_tc // variable for thread creation
    int k_jt; // k_jt variable to join creat thread 
  
    //// pthread_mutex_init function for mutex 
    pthread_mutex_init(&mtx1, NULL);
    
    // for loop to craete thread 
    for(t=0; t<NUM_THREADS; t++){
        printf("In main: creating thread %ld\n", t);
        
        //start a new thread and call the appropriate routine with. You need to 
        //handle errors. 
        //args of the routine should be cast as (void *)t 
        
        // pethread create functon to create thread and print
       j_tc = pthread_create(&thread[t], NULL, PrintHello, (void*)t );
        if ( j_tc!= 0) {
            printf("Thread has not been created:%d",  j_tc); // printoutput if creation failed
        }
        
       //pthread to join thread and print
        k_jt = pthread_join(thread[t], NULL);
        if (k_jt!= 0) {
            printf("Thread has not joined:%d", j_tc); // print output if joining fails
        }
    }
    
    /* Last thing that main() should do */
    pthread_exit(NULL);
}

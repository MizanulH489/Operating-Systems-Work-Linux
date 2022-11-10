#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>

//void function to print mfunction 
void *print_message_function( void *ptr ); // points to ptr

int main() {
    // Declare Variable
    pthread_t thread1, thread2;
    char *message1 = "Thread 1";
    char *message2 = "Thread 2";
    int iret1, iret2;
    
    	/* Create independent threads each of which will execute function */
    iret1 = pthread_create(&thread1, NULL, print_message_function, (void*) message1); // print message1 fromt hraed
    iret2 = pthread_create(&thread2, NULL, print_message_function, (void*) message2); // print message 2 from thread

	// use thread join function to wait for the thread thread1 to terminate 
    pthread_join( thread1, NULL); // pthread functuin to go into NULL and then terminate

    	// do the same for thread2
    pthread_join( thread2, NULL);  // pthread functuin to go into NULL and then terminate

	// print the return value of each thread
    printf("Thread 1: %d\n", iret1); // return value of thread 1
    printf("Thread 2: %d\n", iret2); //return value of thread 2
    
    return(0);
}

// void function to print message
void *print_message_function( void *ptr ) {
    char *message;
    message = (char *) ptr;
    printf("%s \n", message);
}

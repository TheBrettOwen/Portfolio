#include <pthread.h>
#include <stdio.h>
#include <iostream>
#define NUM_THREADS     5

void *PrintHello(void *threadid)
{
   long tid;
   tid = (long)threadid;
   std::cout << "Hello World! It's me, thread #" << tid << std::endl;
   pthread_exit(NULL); 
}

int main (int argc, char *argv[])
{
   pthread_t threads[NUM_THREADS];
   int rc;
   long t;
   for(t=0; t<NUM_THREADS; t++){
     std::cout << "In main: creating thread " << t << std::endl;
      rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
      if (rc){
	std::cout << "ERROR; return code from pthread_create() is" << rc << std::endl;
         exit(-1);
      }
   }

   /* Last thing that main() should do */
   pthread_exit(NULL);
   return 0;
}

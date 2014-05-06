/*=====================================================================
 * purpose: Learn how to use pthreads
 * Author: Maximilian Kerp
 * Gruop:  7
 * Date:   30.04.2014
 *
=====================================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

//====================================================================
// char print parms type
typedef struct char_print_parms
{
int n;  //how often the char the will be printed
char *c;  // the char that will be printed
} char_print_params_t;

//====================================================================
// char_print_params_t constructor
char_print_params_t *char_params_create(char *c, int n)
{
  char_print_params_t *params = malloc(sizeof(char_print_params_t));
  if(params == NULL)
    printf("Error creating struct from type char_print_params_t\n");

  params->c = c;
  params->n = n;

  return params;
}

//====================================================================
// char_print_params_t clean up
void char_params_destroy( char_print_params_t *p)
{
  if(p == NULL)
    printf("Error! nothing to clean up");

  free(p->c);
  free(p);
}
//====================================================================
// function that is executed by each thread
void *char_print(void *p)
{
  int i;
  printf("\nHello from Thread\n");
  char_print_params_t *params = ( char_print_params_t *) p;
  for(i = 0; i < params->n; i++)
    printf("%s",  params->c);

  return NULL;
}

//====================================================================
// global variable
static pthread_t threads[2];
static int threads_num = 2;
//====================================================================
// Main Function

int main( int argc, char **argv)
{

  printf("Function main() starts here:\n");
  // create an array of type char_print_params_t
  char_print_params_t **array = calloc(2,sizeof(char_print_params_t));
  array[0] = char_params_create(strdup("a"), 5234);
  array[1] = char_params_create(strdup("b"), 5234);

  // create two threads
  int i,s;
  for(i = 0; i < threads_num; i++)
  {
    s = pthread_create(&threads[i], NULL, char_print, (void *) array[i]);
    if( s != 0)
      printf("Error creating thread!\n");
  }

  // join the threads
  for(i = 0; i < threads_num; i++)
  {
    s = pthread_join(threads[i], NULL);
    if( s != 0)
      printf("Error joining thread!\n");

    char_params_destroy(array[i]);
  }

  free(array);

  printf("\nFunction main() ends here.\n");

 return 0;
}

/*=====================================================================
 * Purpose: Learn how to use pthreads
 * Author: Maximilian Kerp
 * Group:  7
 * Date:   30.04.2014
 * Name: Blatt 4 Aufgabe 2
 *
=====================================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

//====================================================================
// struct mocking an http-request
typedef struct http_request
{
int host;  // numerical address of the host to get the answer from
char *method;  // the http-method
char *params; // a string holding parameters
} http_request_t;

typedef struct http_response
{
int status; // the status code
char *answer; // a string with a response
} http_response_t;

//====================================================================
// http_request_t constructor
http_request_t *http_request_create(int host, char *method, char *params)
{
  http_request_t *request = malloc(sizeof(http_request_t));
  if(request == NULL)
    printf("Error creating struct from type http_request_t\n");

  request->host = host;
  request->method = method;
  request->params = params;

  return request;
}

//====================================================================
// http_request_t clean up
void http_request_destroy( http_request_t *r)
{
  if(r == NULL)
    printf("Error! nothing to clean up\n");

  free(r->method);
  free(r->params);
  free(r);
}

//====================================================================
// http_response_constructor
http_response_t *http_response_create(int status, char *answer)
{
  http_response_t *response = malloc(sizeof(http_response_t));
  if (response == NULL)
    printf("Error creating struct from type http_repsonse_t\n");

  response->status = status;
  response->answer = answer;

  return response;
}

//====================================================================
// http_response_t clean up
void http_response_destroy(http_response_t *r)
{
  if(r == NULL)
    printf("Error! nothing to clean up\n");

  free(r->answer);
  free(r);
}

//====================================================================
// function that is executed by each thread
void *answer_request(void *r)
{
  //printf("\nHello from Thread\n");
  http_request_t *request = ( http_request_t *) r;

  //char *answer = calloc(200, sizeof(char));
  //answer = "Answering to this: ";
  //answer = strcat(answer, request->params);

  http_response_t *response = http_response_create(200, request->params);

  //printf("Goodbye from Thread\n");
  return (void *) response;
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
  // create an array of type http_request_t
  http_request_t **request_array = calloc(2,sizeof(http_request_t));
  request_array[0] = http_request_create(1, strdup("GET"), strdup("eins, zwei, drei\n"));
  request_array[1] = http_request_create(2, strdup("POST"), strdup("1 2 3\n"));
  //request_array[2] = http_request_create(1, strdup("DELET"), strdup("deleting\n"));

  // create two threads
  int i,s;
  void *res = 0;
  for(i = 0; i < threads_num; i++)
  {
    s = pthread_create(&threads[i], NULL, answer_request, (void *) request_array[i]);
    if( s != 0)
      printf("Error creating thread!\n");
  }

  // join the threads
  for(i = 0; i < threads_num; i++)
  {
    s = pthread_join(threads[i], &res);
    if( s != 0)
      printf("Error joining thread!\n");
    http_response_t *response = (http_response_t *) res;
    printf("\n*******************\nTHREAD: %d\nSTATUS_CODE: %d\nRESPONSE: %s\n*******************", i, response->status, response->answer);

    http_request_destroy(request_array[i]);
    http_response_destroy(response);
  }

  free(request_array);

  printf("\nFunction main() ends here.\n");

 return 0;
}

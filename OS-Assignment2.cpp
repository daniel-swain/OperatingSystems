/*
	There are two threads, parent and child, that repeatedly
	implement the following tasks. The parent thread will
	write a message into a buffer and the child thread will 
	read and print the contents of the buffer in parallel.
*/
/*
	@author Daniel Swain Jr
*/
#include <iostream>
#include <pthread.h>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <Windows.h>

#define BUFFERSIZE 10
#define END "end" 

void* parent(void* args);
void* child(void* args);

pthread_mutex_t mute;
pthread_cond_t pCond, cCond;

/*==========================================================================*/
int main()
{
	using namespace std;
	queue<string> buffer;
	pthread_t par, chi;		/* Create Parent and Child threads */

	// Initialize mutex and condition variables
	pthread_mutex_init(&mute, NULL);
	pthread_cond_init(&pCond, NULL);
	pthread_cond_init(&cCond, NULL);

	// Initialize threads
	pthread_create(&par, NULL, parent, &buffer);
	pthread_create(&chi, NULL, child, &buffer);

	// Wait for threads to finish
	pthread_join(par, NULL);
	pthread_join(chi, NULL);

	// Destroy stuff because why not
	pthread_cond_destroy(&pCond);
	pthread_cond_destroy(&cCond);

	return 0;
}
/*==========================================================================*/
void* parent(void* ptr) 
{	
	std::queue<std::string> *buffer;
	buffer = (std::queue<std::string> *)ptr;

	std::cout << "Enter a string, when done enter 'end'\n";
	std::string message = "";
	
	while (message.compare(END)) {		/* Until the user enters 'end' */
		pthread_mutex_lock(&mute);

		while (buffer->size() != 0) {	/* if the queue is occupied, wait */
			pthread_cond_wait(&pCond, &mute);
		}

		std::cin >> message;			/* Read the input*/
		buffer->push(message);			/* Push into the buffer*/

		pthread_cond_signal(&cCond);
		pthread_mutex_unlock(&mute);
	}
	pthread_exit(0);
	return (NULL);
}
/*==========================================================================*/
void* child(void* ptr)
{
	std::queue<std::string> *buffer;
	buffer = (std::queue<std::string> *)ptr;
	
	std::string message = "";

	while (message.compare(END)) {		/* Until the user enters 'end' */
		pthread_mutex_lock(&mute);

		while (buffer->size() == 0) {	/* if the queue is empty, wait */
			pthread_cond_wait(&cCond, &mute);
		}
		message = buffer->front();		/* Read from the buffer */
		std::cout << message << " ";	/* Print the message */
		buffer->pop();					/* Remove the head of the buffer */
		Sleep(400);						/* Stagger the message*/

		pthread_cond_signal(&pCond);
		pthread_mutex_unlock(&mute);
	}

	pthread_exit(0);
	return (NULL);
}
/*
	Creation and utilization of a named Pipe.
*/
/*
	Write two different programs to represent two processes A and B.
	These processes run on the same Linux box but on two different 
	terminals at the same time. Process A accepts a message from
	user through the first terminal and writes the message into a 
	named pipe. Process B gets the message from the named pipe and
	prints it on the second terminal.
*/
/*
	@author Daniel Swain Jr
*/

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>

int main() 
{

}
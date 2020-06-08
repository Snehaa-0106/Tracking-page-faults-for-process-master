#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include <sys/types.h>

#define BUFFER_LENGTH 10000
static char buffer[BUFFER_LENGTH];

int main(){
	int ret_val, fd;
	/* allocate memory for character buffers HERE before you use them */
	fd = open("/dev/process_list", O_RDONLY);             // Open the device with read only access
	ret_val = read(fd, buffer, BUFFER_LENGTH);        // Read the response
	/* check for errors HERE */
	if (fd < 0){
		perror("Failed to open the device process_list!");
		return errno;
	}
	else
	{
		printf("Device process_list has opened");
	}
	/* check for errors HERE */
	if (ret_val < 0){
		perror("Failed to read the message from the process_list");
		return errno;
	}
	else
	{
		printf("Message read from the process_list");
	}
	printf("\n%s\n", buffer);			// display the buffer contents
	close(fd);
	return 0;
}

/* File copy program. Error checking and reporting is minimal. */
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h> 
/* include necessary header files */
int main(int argc, char * argv[]); /* ANSI prototype */
#define BUF_SIZE 3
#define BUF_SIZE_TWO 54
#define OUTPUT_MODE 0700 
#define TRUE 1
/* use a buffer size of 3 bytes */
/* protection bits for output file */
int main(int argc, char * argv[])
{

	int in_fd, out_fd, rd_count, wt_count;
	char buffer[BUF_SIZE];
	char startbuffer[BUF_SIZE_TWO];
	if (argc != 3) exit(1);
    /* syntax error if argc is not 3 */
    /* Open the input file and create the output file */
    /* open the source file */
	in_fd = open(argv[1], O_RDONLY);
    /* if it cannot be opened, exit */
	if (in_fd < 0) 
        exit(2);
	out_fd = creat(argv[2], OUTPUT_MODE); /* create the destination file */
    /* if it cannot be created, exit */
	if (out_fd < 0) 
        exit(3);
    /* Copy loop */
	rd_count = read(in_fd, startbuffer, BUF_SIZE_TWO);
	wt_count = write(out_fd, startbuffer, rd_count);
	while (TRUE) 
    {
		rd_count = read(in_fd, buffer, BUF_SIZE); /* read a block of data */
        /* if end of file or error, exit loop */
	    if (rd_count <= 0) break;
	    buffer[0] = '\0';
	    wt_count = write(out_fd, buffer, rd_count); /* wr ite data */
        /* wt_count <= 0 is an error */
	    if (wt_count <= 0) exit(4);
    }

/* Close the files */
close(in_fd);
close(out_fd);
if (rd_count == 0)
	exit(0);
else
	exit(5);
}
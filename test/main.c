#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

// int	main(int argc, char const *argv[])
// {
// 	int	f;
//     int r;

// 	f = open("file", O_WRONLY | O_APPEND, 0666);
// 	printf("f:%d;;; %s\n", f , strerror(errno));
//     r = write(f, "hello\n", 6);
// 	printf("r = %d ;;; %s", r , strerror(errno));
//     return (0);
// }
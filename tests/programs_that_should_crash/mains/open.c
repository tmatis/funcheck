#include <signal.h>
#include <fcntl.h>

int main(void)
{
    int fd = open("/dev/zero", O_RDONLY);
    if (fd == -1)
        raise(SIGSEGV);
    return 0;
}
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
    int fd = open("/home/theaux/cub3d/textures/wolfenstein/grey_stone.xpm\n", O_RDONLY);
    if (fd == -1)
        return (1);
    char buffer[100];

    read(fd, buffer, 100);
    write(1, buffer, 100);
    return (0);
}
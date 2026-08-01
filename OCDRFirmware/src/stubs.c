#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
    
int _write(int file, char *ptr, int len) {
    // Ти можеш тут реалізувати передачу в UART або просто повернути len
    return len;
}

int _read(int file, char *ptr, int len) {
    return 0;
}
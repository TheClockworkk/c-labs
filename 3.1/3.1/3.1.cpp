#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

#define BUFFSIZE 10


void swap(char* c1, char* c2) 
{
    char temp = *c1;
    *c1 = *c2;
    *c2 = temp;
}

char* strReverse(char* str) 
{
    int i = 0;
    int size = strlen(str);

    char* begin = str;
    char* end = str + size - 1;

    while (i < size / 2) {
        swap(begin, end);

        begin++;
        end--;
        i++;
    }

    return str;
}


char iSystem(int n) 
{
    if (n < 10)
        return n + '0';
    else
        return n - 10 + 'A';
}


char* dec_to_2_pow_base(int n, int r) {
    int i, mask = 1;
    size_t size = sizeof(char) * BUFFSIZE;
    char* buffer = (char*)malloc(size);
    char* ptr = buffer;

    memset(buffer, '\0', size);

    if (n == 0) {
        *buffer = '0';
        return buffer;
    }

    //масочка
    mask <<= r;
    mask--;

    i = 0;
    while (n > 0) {
        *ptr++ = iSystem(n & mask);

        if (i + 1 == size) {
            size *= 2;
            buffer = (char*)realloc(buffer, size);
            ptr = buffer + i + 1;
            memset(ptr, '\0', size / 2);
        }

        n >>= r;
        i++;
    }

    return strReverse(buffer);
}

int main() {
    int n, r;
    char* res;

    printf("enter n r\n");
    scanf("%d %d", &n, &r);

    if (r < 1 || r > 5) {
        printf("r must be more/equale than 1 and less/equale than 5!!!\n");
        return -1;
    }

    res = dec_to_2_pow_base(abs(n), r);

    if (n < 0)
        printf("%s%s", "-", res);
    else
        printf("%s%s", "", res);

    free(res);

    return 0;
}
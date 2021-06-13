#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INT64 (1<<63)
#define MAX_NUM_DIGIT_PER_BIG_INT 10
#define MAX_VAL_PER_BIG_INT 1000000000 // pow(10,9)

char* readline();
char* ltrim(char*);
char* rtrim(char*);

int parse_int(char*);

/*
 * Complete the 'extraLongFactorials' function below.
 *
 * The function accepts INTEGER n as parameter.
 */
 
void printExtraLong(int num_longs, long* arr_extra_long) {
    for (int i=num_longs; i>-1; --i) {
        if(arr_extra_long[i] == 0) {
            for(int j=0; j<MAX_NUM_DIGIT_PER_BIG_INT-1; ++j) {
                printf("%d", 0);   
            }
        } else {
            if (i != num_longs) {
                int num_big_int_digits = 0;
                int64_t tmp_big_int = arr_extra_long[i];
                while(tmp_big_int != 0) {
                    tmp_big_int /= 10;
                    num_big_int_digits++;
                }
                for(int j=0; \
                j<MAX_NUM_DIGIT_PER_BIG_INT-num_big_int_digits-1; j++) {
                    printf("%d", 0);
                }
                printf("%ld", arr_extra_long[i]);
            } else {
                printf("%ld", arr_extra_long[i]);
            }
        }
    }
}

void extraLongFactorials(int n) {
    assert(n>=1);
    assert(n<=100);
    
    int num_exceed_int_range = 0;
    long arr_extra_long[100] = {1};

    if (n<20) {
        for (int i=1; i<=n; ++i) {
          arr_extra_long[0] *= i;
        }
    } else {
        for (int i=1; i<=n; ++i) {
            for (int j=num_exceed_int_range; j>-1; --j) {
              arr_extra_long[j] *= i;
              if (arr_extra_long[j] >= MAX_VAL_PER_BIG_INT) {
                if (num_exceed_int_range < j + 1) {
                  num_exceed_int_range++;
                  arr_extra_long[j + 1] =
                      arr_extra_long[j] / MAX_VAL_PER_BIG_INT;
                } else {
                  arr_extra_long[j + 1] +=
                      arr_extra_long[j] / MAX_VAL_PER_BIG_INT;
                }
                arr_extra_long[j] = arr_extra_long[j] % MAX_VAL_PER_BIG_INT;
              }
            }
        }
    }
    
    printExtraLong(num_exceed_int_range, arr_extra_long);
}

int main()
{
    int n = parse_int(ltrim(rtrim(readline())));

    extraLongFactorials(n);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}

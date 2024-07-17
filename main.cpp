#include <stddef.h> // for size_t
#include <stdint.h> // for uint8_t, uint32_t
#include <stdio.h>  // for printf, perror, fopen, fread, fclose
#include <stdlib.h> // for EXIT_FAILURE, EXIT_SUCCESS
#include <arpa/inet.h> // for ntohl

void dump(void* p, size_t n) {
    uint8_t* u8 = static_cast<uint8_t*>(p);
    size_t i = 0;
    while (true) {
        printf("%02X ", *u8++);
        if (++i >= n) break;
        if (i % 8 == 0)
            printf("\n");
    }
    printf("\n");
}

void print_usage(const char *prog_name) {
    fprintf(stderr, "Usage: %s <file1> <file2>\n", prog_name);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file1 = fopen(argv[1], "rb");
    if (file1 == NULL) {
        perror("Error opening file1");
        return EXIT_FAILURE;
    }

    FILE *file2 = fopen(argv[2], "rb");
    if (file2 == NULL) {
        perror("Error opening file2");
        fclose(file1);
        return EXIT_FAILURE;
    }

    uint32_t num1, num2;
    if (fread(&num1, sizeof(uint32_t), 1, file1) != 1) {
        perror("Error reading from file1");
        fclose(file1);
        fclose(file2);
        return EXIT_FAILURE;
    }
    if (fread(&num2, sizeof(uint32_t), 1, file2) != 1) {
        perror("Error reading from file2");
        fclose(file1);
        fclose(file2);
        return EXIT_FAILURE;
    }

    fclose(file1);
    fclose(file2);

    num1 = ntohl(num1);
    num2 = ntohl(num2);

    uint32_t sum = num1 + num2;

    printf("%u(0x%x) + %u(0x%x) = %u(0x%x)\n", num1, num1, num2, num2, sum, sum);

    return EXIT_SUCCESS;
}

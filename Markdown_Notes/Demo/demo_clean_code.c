#include <stdio.h>
#include <stdint.h>

/**
 * @brief Print the bits of each byte in the data array.
 * 
 * This function takes a byte array and prints the bits of each byte from the most 
 * significant bit (MSB) to the least significant bit (LSB), separated by spaces.
 * This function assumes the byte-order is Little Endian.
 *
 * @param [in] data Pointer to the byte array to be printed.
 * @param [in] data_size Size of the byte array.
 * 
 * @return None. This function outputs the bits of the array to the standard output.
 */
void print_bits_LE(const uint8_t *data, const size_t data_size)
{
    for(int i = data_size-1; i >= 0; i--)
    {
        for(int j = 7; j >= 0; j--)
        {
            uint8_t byte = data[i];
            printf("%u", (byte>>j)&1 );
        }
        printf(" ");
    }
    printf("\n\r");
}

/**
 * @brief Print the bits of each byte in the data array.
 * 
 * This function takes a byte array and prints the bits of each byte from the most 
 * significant bit (MSB) to the least significant bit (LSB), separated by spaces.
 * This function assumes the byte-order is Big Endian.
 *
 * @param [in] data Pointer to the byte array to be printed.
 * @param [in] data_size Size of the byte array.
 * 
 * @return None. This function outputs the bits of the array to the standard output.
 */
void print_bits_BE(const uint8_t *data, const size_t data_size)
{
    for(int i = 0; i < data_size; i++)
    {
        uint8_t byte = data[i];
        for(int j = 7; j >= 0; j--)
        {
            printf("%u", (byte>>j)&1 );
        }
        printf(" ");
    }
    printf("\n\r");
}

int main() {
    uint32_t testnumber = 0x06060606;
    int n = 1;
    if(*(char *)&n == 1) 
    {
        printf("[Little Endian] \n\r");
        print_bits_LE((uint8_t *)&testnumber, sizeof(testnumber));
    }
    else 
    {
        printf("[Big Endian] \n\r");
        print_bits_BE((uint8_t *)&testnumber, sizeof(testnumber));
    }

    return 0;
}
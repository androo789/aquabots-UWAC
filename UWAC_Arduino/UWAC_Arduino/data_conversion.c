/*
 * data_conversion.c
 *
 * Created: 25-3-2016 11:58:45
 *  Author: Kevin Slagmolen
 */ 
#include "data_conversion.h"
#include <inttypes.h>
#include <stdbool.h>

/**
 * fillDataArray
 *
 * This functions converts the data (in chars) to a array of integers.
 *
 * @param data The data to convert.
 *
 * @return The array of integers which can be send.
 *
*/
uint8_t* fillDataArray(char data[100])
{
    // Reset some stuff and initialize some variables
    dataLength = 0;
    int i;
    uint8_t ret[400]; // The return variable
    uint8_t data_num[100]; // The int representation of the data

    // Convert the chars to ints
    for (i = 0; i < strlen(data); i++)
    {
        data_num[i] = (uint8_t)data[i];
    }

    int checksum = CRC(data_num, strlen(data), POLY, false); // Get a checksum for the data

    #ifdef DEBUG // Debugging
    printf("\nChecksum: %i\n", checksum);
    #endif // DEBUG

    // Loop through all the data
    for (i = 0; i < strlen(data); i++)
    {
        uint8_t j;
        uint8_t ascii = (uint8_t)data[i]; // Take one of the data bytes

        // Loop through the bits 2 at a time
        for (j = 0; j < 4; j++)
        {
            uint8_t tmp = (ascii & 0b11000000) >> 6; // Select the 2 leftmost bits
            ascii = ascii << 2; // Shift the data left by 2

            ret[i*4+j] = tmp; // Store the 2 leftmost bits in an array

            dataLength++; // Add one to the total data length

            #ifdef DEBUG // Debugging
            printf("%i", tmp);
            #endif
        }
        #ifdef DEBUG // Debugging
        printf(" ");
        #endif
    }

    // Loop 4 more times for the CRC byte
    for (i = 0; i < 4; i++)
    {
        int tmp = (checksum & 0b11000000) >> 6; // Select the 2 leftmost bits
        checksum = checksum << 2; // Shift the checksum left by 2

        ret[dataLength] = tmp; // Store the 2 leftmost bits in an array
        dataLength++; // Add one to the total data length
    }

    #ifdef DEBUG // Debugging
    printf("\ndataLength: %i\n", dataLength);
    #endif // DEBUG

    return ret;
}

/**
 * convertToData
 *
 * With this function the incoming bits will be decoded to readable data for the user.
 *
 * @param bits All the bits in an array
 * @param length The length of the array
 *
 * @return The readable data
*/
char* convertToData(uint8_t bits[400], int length)
{
    // Reset some stuff and initialize some variables
    int i;
    int total = 0;
    char ret[100] = ""; // The return value
    char tmp = 0b00000000; // Create a temp char with no data
    uint8_t ascii[100]; // The int representation of the data

    #ifdef DEBUG // Debugging
    printf("length: %i\n", length);
    #endif // DEBUG

    // Loop through all the bits
    for (i = 0; i < length; i++)
    {
        #ifdef DEBUG // Debugging
        printf("\ni:%i", i);
        #endif

        tmp = tmp << 2 | bits[i]; // Add the bits to the right of the previous ones

        #ifdef DEBUG // Debugging
        printf(" bits%i tmp%i,", bits[i], (uint8_t)tmp);
        #endif

        // If this is dividable by 4
        if ((i + 1) % 4 == 0)
        {
            #ifdef DEBUG // Debugging
            printf("\nchar %c\n", tmp);
            #endif // DEBUG

            ret[total] = tmp; // Store the temp value in the return value
            total++; // Add one to the total
            tmp = 0b00000000; // Reset the temp value
        }
    }

    // Loop through all the chars
    for (i = 0; i < strlen(ret); i++)
    {
        ascii[i] = (uint8_t)ret[i]; // Convert them to ints
    }

    int checksum = CRC(ascii, strlen(ret), POLY, true); // Do the checksum

    ret[total - 1] = 0b00000000; // Set the last byte to 0 (this is the checksum)

    #ifdef DEBUG // Debugging
    printf("\n\nChecksum: %i\n\n", checksum);
    #endif // DEBUG

    if (checksum == 0)
    {
        #ifdef DEBUG // Debugging
        printf("No errors.\n");
        #endif // DEBUG
    }
    else
    {
        ret[0] = -1;
        #ifdef DEBUG // Debugging
        printf("Error detected.\n");
        #endif // DEBUG
    }

    return ret;
}

/**
 * CRC
 *
 * Do a Cyclic Redundancy Check (CRC) on the data (to send or receive).
 * For more information about CRC, visit https://en.wikipedia.org/wiki/Cyclic_redundancy_check
 *
 * @param data The data to do the CRC on
 * @param length The length of the data
 * @param poly The used divisor
 * @param received Is the data received or not
 *
 * @return The generated checksum
*/
int CRC(uint8_t data[100], int length, uint16_t poly, bool received)
{
    #ifdef DEBUG // Debugging
    printf("Length: %i\n", length);
    #endif // DEBUG

    // Reset some stuff and initialize some variables
    int i;
    int allData = 0;

    // Loop through all the bits
    for (i = 0; i < length; i++)
    {
        #ifdef DEBUG // Debugging
        printf("Data: %i, ", (uint8_t)data[i]);
        #endif // DEBUG

        allData = allData << 8 | (uint8_t)data[i]; // Add the last byte to the right of the previous ones
    }

    #ifdef DEBUG // Debugging
    printf("\nallData: %i\n", allData);
    #endif // DEBUG

    if (!received) // Check if the data is received or not
    {
        allData = allData << 8; // Add one byte of empty data at the right of the data
    }

    uint64_t calcPoly = poly; // Store the polynomial in a variable so we can modify it

    // Loop endlessly
    while (1)
    {
        bool shiftBack = false; // To see if we need to shift back later

        if (allData < 0xFF) break; // If the data is smaller then 255 (0xFF)
        while (calcPoly < allData)
        {
            calcPoly = calcPoly << 1; // Shift the polynomial left by one
            shiftBack = true;
        }
        if (shiftBack) calcPoly = calcPoly >> 1; // Shift the polynomial back one

        #ifdef DEBUG // Debugging
        printf("%i^%i=", allData, calcPoly);
        #endif // DEBUG

        allData = allData ^ calcPoly; // Do the actual XOR

        #ifdef DEBUG // Debugging
        printf("%i\n", allData);
        #endif // DEBUG

        calcPoly = poly; // Reset the polynomial to its original value
    }

    return allData;
}

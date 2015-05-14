#include <stdio.h>
#include "instructions.h"

void log_instruction(int opcode)
{
    printf("[sending instruction] ");
    switch(opcode)
    {
        case RESET: 
            printf("RESET");
            break;
        case STORE_PUBLIC_KEY_1:
            printf("STORE_PUBLIC_KEY_1");
            break;
        case STORE_PUBLIC_KEY_2:
            printf("STORE_PUBLIC_KEY_2");
            break;
        case DECRYPT_BITS:
            printf("DECRYPT_BITS");
            break;
        case ENCRYPT_BITS:
            printf("ENCRYPT_BITS");
            break;
        case READ_PUBLIC_KEY_1:
            printf("READ_PUBLIC_KEY_1");
            break;
        case READ_PUBLIC_KEY_2:
            printf("READ_PUBLIC_KEY_2");
            break;
        case STORE_MESSAGE:
            printf("STORE_MESSAGE");
            break;
        case STORE_MESSAGE2:
            printf("STORE_MESSAGE2");
            break;
        case STORE_D:
            printf("STORE_D");
            break;
        default:
            break;
   }
   printf("\n");
}

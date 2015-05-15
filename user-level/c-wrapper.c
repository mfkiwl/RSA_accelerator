/*
 * Userspace program that communicates with the RSA_Box device driver
 * primarily through ioctls.
 *
 * Original VGA_LED code by Stephen A. Edwards, Columbia University
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>     
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>       /* for sleep() */
#include <stdint.h>     /* for unit32_t */
#include "../rsa_box.h"
#include "instructions.h"
#include "c-wrapper.h"
#include "exteuc.h"

void read_segment(int32_t *bit_output, int size);
void send_bits(int32_t *value, int count); 
void __store_d(int32_t *d); 
void store_keys(int type, int32_t *key_1, int32_t *key_2);

/* globals */
static int BIT_SEGMENTS[5] =  {1, 2, 3, 4, 5}; 
static int BIT_SEGMENTS_READ[5] = {0, 1, 2, 3, 4};
static int rsa_box_fd = -1;
static int empty[4] = {0, 0, 0, 0}; 

void set_fd()
{
    char *filename = "/dev/rsa_box";
    if ( (rsa_box_fd = open(filename, O_RDWR)) == -1)
    {
        fprintf(stderr, "could not open %s\n", filename);
    }
}

/*
 * Tells hardware what instruction to include the incoming
 * data with.
 */
void send_instruction(int operation)
{
    rsa_box_arg_t rsa_userspace_vals;
    if (rsa_box_fd == -1)
        set_fd();

    rsa_userspace_vals.address =  INSTRUCTION;
    rsa_userspace_vals.data_in = operation;

#ifdef PRINTVERBOSE
    log_instruction(operation);
#endif

    if (ioctl(rsa_box_fd, RSA_BOX_WRITE_DIGIT, &rsa_userspace_vals))
    {
        perror("ioctl(RSA_BOX_WRITE_DIGIT) failed");
    }
}

/*
 * Sends count int32_t's to the hardware. 
 * Always call send_instruction() first or the hardware won't know
 * what to do with the incoming data.
 */
void send_bits(int32_t *value, int count)
{
    rsa_box_arg_t rsa_userspace_vals;
    int i;

    if (rsa_box_fd == -1)
        set_fd();

    for (i = 0; i < count; i++)
    {
        rsa_userspace_vals.address = BIT_SEGMENTS[i];
        rsa_userspace_vals.data_in = value[i];

#ifdef PRINTVERBOSE
        printf("[sending] %d // %d\n", BIT_SEGMENTS[i], value[i]); 
#endif

        if (ioctl(rsa_box_fd, RSA_BOX_WRITE_DIGIT, &rsa_userspace_vals))
        {
            perror("ioctl(RSA_BOX_WRITE_DIGIT) failed");
        }
    }

}

/*
 * Store private keys and get back our public key. 
 */
void key_swap(int32_t *p, int32_t *q, int32_t *our_n)
{
    int32_t p_phi[2];
    int32_t q_phi[2];
    int32_t phi_n[4];
    int32_t d[4];

    // calculate p - 1, q - 1
    p_phi[0] = p[0] - 1;
    p_phi[1] = p[1];

    q_phi[0] = q[0] - 1;
    q_phi[1] = q[1];

    // store d, the extended euclid of (p - 1)(q - 1) and e
    store_keys(PRIVATE, p_phi, q_phi);
    read_our_N(phi_n);

    int32_t E = 65537;
    e_euclid(E, phi_n, d);
    __store_d(d);

    // store actual p and q
    store_keys(PRIVATE, p, q);
    read_our_N(our_n);
}

/*
 * Stores keys into the specified registers, PUBLIC or PRIVATE
 * key registers.
 */
void store_keys(int type, int32_t *key_1, int32_t *key_2)
{
    if (type == PRIVATE)
    {
        send_instruction(STORE_PRIVATE_KEY_1);
        send_bits(key_1, 2); // p
        send_instruction(STORE_PRIVATE_KEY_2);
        send_bits(key_2, 2); // q
    }

    if (type == PUBLIC)
    {
        send_instruction(STORE_PUBLIC_KEY_1);
        send_bits(key_1, 4); // n 
        send_instruction(STORE_PUBLIC_KEY_2);
        send_bits(key_2, 1); // e
    }
}


void __store_d(int32_t *d) 
{
    send_instruction(STORE_D); 
    send_bits(d, 4);
}

/*
 * Writes input to m2, the cyphertext to be decrypted.
 */
void __send_cyphertext(int32_t *m)
{	
    send_instruction(STORE_MESSAGE2); 
    send_bits(m, 4); 
}

/*
 * Send data to encrypt/decrypt to device.
 */
void send_int_encrypt_decrypt(int action, int32_t *input, int32_t *output)
{
    if (action == ENCRYPT_SEND)
    {
        send_instruction(STORE_MESSAGE);
        send_bits(input, 4); // cleartext, m
        __read_encryption(output); 
    }

    if (action == DECRYPT_SEND)
    {
        __send_cyphertext(input);
        __read_decryption(output); 
    }
}

/*
 * Return the public keys on this device. Encrypt data already stored
 * on board.
 *
 * (Note: the interface to read private keys was intentionally ommitted.
 */
void __read_encryption(int32_t *encryption)
{
    int32_t valid[5] = {0,0,0,0,0};
    int i; 		
    send_instruction(ENCRYPT_BITS); 
    send_bits(empty, 2); 
    read_segment(valid, 5); 

    while (valid[4] == 0)
    {
        read_segment(valid+4, 1); 
    } 

    read_segment(valid, 5);

    for (i = 0; i < 5; i++)
    {
        encryption[i] = valid[i]; 
    }
}

void __read_decryption(int32_t *decryption)
{
    int32_t valid[5] = {0, 0, 0, 0, 0};
    int i;

    send_instruction(DECRYPT_BITS); 
    send_bits(empty, 2); 
    read_segment(valid, 5); 

    while (valid[4] == 0 || valid[4] == 1) 
    {
        read_segment(valid + 4, 1); 
    } 

    read_segment(valid, 5);

    for (i = 0; i < 5; i++)
    {
        decryption[i] = valid[i]; 
    }

}

/*
 * Read "size" 32 bit segments into bit output.
 */ 
void read_segment(int32_t *bit_output, int size)
{
    rsa_box_arg_t rsa_userspace_vals;
    int i;

    if (rsa_box_fd == -1)
        set_fd();

    for (i = 0; i < size; i++)
    {
        rsa_userspace_vals.address = BIT_SEGMENTS_READ[i];

        if (ioctl(rsa_box_fd, RSA_BOX_READ_DIGIT, &rsa_userspace_vals)) 
        {
            perror("ioctl(RSA_BOX_READ_DIGIT) failed");
        }

        bit_output[i] = rsa_userspace_vals.data_in; 
#ifdef PRINTVERBOSE
        printf("[sending] %d // %d\n", BIT_SEGMENTS_READ[i], bit_output[i]); 
#endif        
    }
}

/*
 * Get the product of p and q.
 */
void read_our_N(int32_t *n)
{
    send_instruction(MAKE_OUR_N);
    send_bits(empty, 1); 

    send_instruction(READ_OUR_N); 
    send_bits(empty, 1); 
    read_segment(n, 4);
}

/** Extended Euclid's implementation below **/

#include <string.h>
#include <sys/wait.h>

#define READ_BUF 4096

struct IntSet {
    int x[4];
};

void err_sys(char *err) {
    perror(err);
    exit(1);
}

void e_euclid(int32_t e, int32_t phi[4], int32_t *d) 
{
    int phi1 = phi[3];
    int phi2 = phi[2];
    int phi3 = phi[1];
    int phi4 = phi[0];

    pid_t pid;
    int fd[2];

    if(pipe(fd) < 0) {
        err_sys("pipe error");
    }

    if((pid = fork()) < 0) {
        err_sys("fork error");
    } 
    else if(pid > 0) { // parent
        close(fd[1]); // close write end

        if(fd[0] != STDIN_FILENO) { // set STDIN
            if(dup2(fd[0], STDIN_FILENO) != STDIN_FILENO) {
                err_sys("dup2 error");
            }
        }

        char buf[READ_BUF];
        if(read(STDIN_FILENO, buf, READ_BUF) < 0) {
            err_sys("read error");
        }

        // printf("[received]: %s\n", buf);

        struct IntSet my_s;

        /* parse buf */
        const char s[2] = " ";
        char *token = strtok(buf, s);
        int curr = 0;

        while(token != NULL && curr < 4) {
            my_s.x[curr] = atoi(token);
            printf("curr: %d, token: %s\n", curr, token);
            token = strtok(NULL, s);
            curr++;
        }

        if (waitpid(pid, NULL, 0) < 0)
            err_sys("waitpid error");

        d[0] = my_s.x[3]; 
        d[1] = my_s.x[2];
        d[2] = my_s.x[1];
        d[3] = my_s.x[0];
    } 
    else { // child
        close(fd[0]); // close read end

        if(fd[1] != STDOUT_FILENO) { // set STDOUT
            if(dup2(fd[1], STDOUT_FILENO) != STDOUT_FILENO) {
                err_sys("dup2 error");
            }
        }

        char e_s[READ_BUF]; 

        char phi_s[READ_BUF];
        char phi2_s[READ_BUF]; 
        char phi3_s[READ_BUF];
        char phi4_s[READ_BUF];

        snprintf(e_s, READ_BUF, "%d\n", e);

        snprintf(phi_s, READ_BUF, "%d\n", phi1);
        snprintf(phi2_s, READ_BUF, "%d\n", phi2);
        snprintf(phi3_s, READ_BUF, "%d\n", phi3);
        snprintf(phi4_s, READ_BUF, "%d\n", phi4);

        printf("%s\n", e_s);

        printf("%s\n", phi_s);
        printf("%s\n", phi2_s);
        printf("%s\n", phi3_s);
        printf("%s\n", phi4_s);

        // execute Python script
        execlp("python", "python", "exteuc.py", e_s, phi_s, phi2_s, phi3_s, phi4_s, (char *)NULL);
    }
}


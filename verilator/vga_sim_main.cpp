#include "VVGA_LED.h"
#include "verilated.h"
#include <iostream>
#include <string>
#include "../user-level/instructions.h" /* operation instruction codes */

/* 
 * // I/O interface for VGA_LED module
 * module VGA_LED(input logic      clk,
 *       input logic             reset,
 *       input logic[31:0]       data_in,
 *       input logic             write,
 *       input                   chipselect,
 *       input logic[2:0]        address,
 *       output logic[31:0]      data_out 
 *   ); 
 */

#define CYCLE_LEN       12
#define CYCLE_COUNT     10

using namespace std; 

vluint64_t main_time = 0; 

double sc_time_stamp() {
    return main_time;
}

int main(int argc, char **argv, char **env) {
    Verilated::commandArgs(argc, argv);
    VVGA_LED *top = new VVGA_LED; 
    top->reset = 1; 
    top->chipselect = 1;

    while (!Verilated::gotFinish()) {    
        int  curr_instr = 0; // current instruction being written+read       

        // only have reset on for first cycle
        if (main_time > CYCLE_LEN) {
            top->reset = 0; 
        } 

        top->chipselect = 1;
        /* 
        // write in first half of cycle
        if (main_time % CYCLE_LEN < CYCLE_LEN / 2) {
            top->data_in = 0;
            top->write = 1;

        } else { // read in second half of cycle
            top->write = 0;            
        }
        */

        // clock cycles
        if ((main_time % CYCLE_LEN) == 0) {
            top->clk = 1;
        }
        if ((main_time % CYCLE_LEN) == CYCLE_LEN / 2) { 
            top->clk = 0;
        }

        // output data on every cycle
        if (top->data_out > 0) {
            cout << to_string(top->data_out) << endl;
        }
        if (top->data_out == 0) {
            cout << "0" << endl; 
        }

        top->eval();
        
        // finish after CYCLE_COUNT full cycles
        if (main_time > CYCLE_LEN * CYCLE_COUNT) {
            break;  
        }

        if ((main_time % CYCLE_LEN) == 0) {
            cout << "New clock cycle" <<endl; 
        }

        main_time++;  
    }

    top->final(); 
    delete top; 
    exit(0); 
}

#include "VRSA_BOX.h"
#include "verilated.h"
#include <iostream>
#include "verilated_vcd_c.h"
#define MAXTIME 10000 

using namespace std; 

vluint64_t main_time = 1; 
int clock_value = 1;


double sc_time_stamp(){
    return main_time;
}

//toggle clk and set input
void toggle(VRSA_BOX *top){
    if((main_time%5) == 0) {
        clock_value = !clock_value;
        //if(clock_value)
          //  cout << "new clock cycle" <<endl;
    }

    if(main_time == 10){
        top->reset = 0; 
        top->write = 1; 
        top->chipselect = 1; 
        top->address = 0 ; 
        top->data_in = 2;
    }

    if(main_time == 20){
        top->address = 1; 
        top->data_in = 9; 
    }

    if(main_time == 30){
        top->address = 2; 
        top->data_in = 13; 
    }

    if (main_time == 40) {
        top->address = 3;
        top->data_in = 2039423;
    }

    if (main_time == 50) {
        top->address = 4;
        top->data_in = 99872;
    }

    // send READ_PUBLIC_KEY_1 instruction
    if (main_time == 60) {
        top->address = 0;
        top->data_in = 8;
    }

    if (main_time == 70) {
        top->address = 1;
    }

    if (main_time == 80) {
        top->address = 2;
    }
    if (main_time == 90) {
        top->address = 3;
    }
    if (main_time == 100) {
        top->address = 4;
    }

    // read from wire
    if (main_time == 110) {
        top->write = 0;
        top->address = 0;    
    }

    if (main_time == 120) {
        top->address = 1;    
    }

    if (main_time == 130) {
        top->address = 2;    
    }

    if (main_time == 140) {
        top->address = 3;    
    }

    top->clk = clock_value;
    main_time++;
    top->eval();

}



int main(int argc, char **argv, char **env){
    Verilated::commandArgs(argc, argv);    
    //create top module
    VRSA_BOX *top = new VRSA_BOX; 
    //create traces 
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;  
    top->trace(tfp, 99); 
    tfp->open("trace.vcd"); 

    //initialize reset to true, as well as pass in a and b values
    top->reset = 1; 
    top->clk = 0; 
    
    while(!Verilated::gotFinish()){    
        tfp->dump(main_time);
        toggle(top);
        if(main_time > MAXTIME){
            break;  
        }
    }

    tfp->close(); 
    top->final(); 
    delete top; 
    exit(0); 
}
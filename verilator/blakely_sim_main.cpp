#include "Vblakely.h"
#include "verilated.h"
#include <iostream>
#include "verilated_vcd_c.h"
#define MAXTIME 250 

using namespace std; 

vluint64_t main_time = 1; 
int clock_value = 1;


double sc_time_stamp(){
    return main_time;
}

//toggle clk and set input
void toggle(Vblakely *top){
    
    if((main_time%5) == 0){
        clock_value = !clock_value;
        if(clock_value)
            cout << "new clock cycle" <<endl;
    }

    if(main_time == 10){
        top->reset_l = 0; 
    }
    top->clk = clock_value;
    
    main_time++;
    top->eval();

}



int main(int argc, char **argv, char **env){
    Verilated::commandArgs(argc, argv);    

    //create top module
    Vblakely *top = new Vblakely; 

    //create traces 
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;  
    top->trace(tfp, 99); 
    tfp->open("trace.vcd"); 

    //initialize reset to true, as well as pass in a and b values
    top->reset_l = 1; 
    top->a = 3; 
    top->b = 4;    
    top->n = 7;
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

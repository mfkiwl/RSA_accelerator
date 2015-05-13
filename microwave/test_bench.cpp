#include "verilated.h"
#include "VincrementA.h"
#include <iostream>
#include "verilated_vcd_c.h"
#define MAXTIME 3000 

using namespace std; 

vluint64_t main_time = 1; 
int clock_value = 1;


double sc_time_stamp(){
    return main_time;
}

//toggle clk and set input
void toggle(VincrementA *top){
    
    if((main_time%5) == 0){
        clock_value = !clock_value;
        if(clock_value)
            cout << "new clock cycle" <<endl;
    }

    if(main_time == 10){
        top->reset = 0; 
    }
    top->clk = clock_value;
    
    main_time++;
    top->eval();

}



int main(int argc, char **argv, char **env){
    
    int a, b, n; 
    Verilated::commandArgs(argc, argv);    
    
    //create top module
    VincrementA *top = new VincrementA; 
    //create traces 
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;  
    top->trace(tfp, 99); 
    tfp->open("trace.vcd"); 
    //initialize reset to true, as well as pass in a and b values
    top->reset = 1;

    a = 222; 
    b = 125; 
    n = 19; 
    int ans = ( (a*b)%n );  
    top->clk = 0; 
    top->a[0] = a; 
    top->b[0] = b; 
    top->n[0] = n; 

    while(!Verilated::gotFinish()){    
        tfp->dump(main_time);
        toggle(top);
        if(main_time > MAXTIME){
            break;  
        }
    }

    cout << to_string(ans) << endl; 
    cout << to_string(top->outputAnswer[0]) <<endl; 
    tfp->close(); 
    top->final(); 
    delete top;
    exit(0); 
}

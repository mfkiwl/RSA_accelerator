#include "Vour.h"
#include "verilated.h"
#include <iostream>

#ifdef SYSTEMPERL
# include "systemperl.h"        // SystemC + SystemPerl global header
# include "sp_log.h"            // Logging cout to files
# include "SpTraceVcd.h"
# include "SpCoverage.h"
#include "systemc.h"
#else


# include "verilated_vcd_sc.h"  // Tracing
#endif

using namespace std; 

vluint64_t main_time = 0; 

double sc_time_stamp(){
    return main_time;
}

int main(int argc, char **argv, char **env){
    Verilated::commandArgs(argc, argv);
    VOur *top = new VOur; 
    top->reset_l = 1; 

    Verilated:traceEverOn(true);     
    
    
    VerilatedVcdSc *tfp = new VerilatedVcdSc;              
    
    top->trace (tfp, 99);  
    top->open( "vlt_dump.vcd\n"); 
    while(!Verilated::gotFinish()){ 
       
        (tfp) tfp ->flush(); 
           
        if(main_time > 10){
          top->reset_l = 0; 
        }
        if((main_time%10) == 1){
            top->clk = 1; 
        }

        if((main_time%10)== 6){
            top->clk = 0; 
        }
       
        if(main_time>60){
           break;  
        }

        if(top->out_number == 0){
            cout<<"0"<<endl; }
        
        if(top->out_number >0 ){
           cout << to_string(top->out_number) <<endl;}

        top->eval();
 
        if((main_time%10) == 1){
            cout << "New clock cycle" <<endl; 
        }

        main_time++;  
    }
    top->final();
    (tfp) tfp->close(); 
    delete top; 
    exit(0); 
}

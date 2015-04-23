#include "Vour.h"
#include "verilated.h"
#include <iostream>

using namespace std; 

vluint64_t main_time = 0; 

double sc_time_stamp(){
    return main_time;
}

int main(int argc, char **argv, char **env){
    Verilated::commandArgs(argc, argv);
    Vour *top = new Vour; 
    top->reset_l = 1; 
    
    while(!Verilated::gotFinish()){    
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
    delete top; 
    exit(0); 
}

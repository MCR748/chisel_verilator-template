#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <verilated.h>
#include <verilated_vcd_c.h>
//Replace $(Module-name) with the defined module name in chisel
#include "V$(Module-name).h"

// Change simulation time to number of cycles required
// Here 300
#define MAX_SIM_TIME 300
//To keep track of the current cycle
vluint64_t sim_time = 0;
//If need to count posedges
//Cannot use sim_time to keep count of the cycles
//vluint64_t posedge_cnt = 0;


int main(int argc, char** argv, char** env) {
    //Replace $(Module-name) with the defined module name in chisel 
    V$(Module-name) *dut = new V$(Module-name);

    //To generate trace
    Verilated::traceEverOn(true);
    VerilatedVcdC *m_trace = new VerilatedVcdC;
    dut->trace(m_trace, 5);     //Show signals down to 5 levels deep
    m_trace->open("waveform.vcd");

    //Simulation loop
    while (sim_time < MAX_SIM_TIME) {
        dut-> reset = 0;
        //Resetting for one clock cycle between 1 and 2
        if (sim_time >= 1 && sim_time <= 2) {
            dut-> reset = 1;
            //Reset any input signals
            //dut-> io_in = 0;
        }
        
        dut->clock ^= 1;

        //Add input signals here
        //Eval will set the signals in and make them reflect in output

        dut->eval();

        //Add any checks here for output
        //Simulation body
        
        //Can add printf lines to obeserve the outputs

        m_trace->dump(sim_time);
        sim_time++;
    }

    m_trace->close();
    delete dut;
    exit(EXIT_SUCCESS);
}

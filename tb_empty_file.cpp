#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <verilated.h>
#include <verilated_vcd_c.h>
//Replace $(Module-name) with the defined module name in chisel
#include "V$(Module-name).h"

// Change simulation time to number of cycles required
// Here 40
#define MAX_SIM_TIME 40
//To keep track of the current cycle
vluint64_t sim_time = 0;
//If need to count posedges
vluint64_t posedge_cnt = 0;


int main(int argc, char** argv, char** env) {
    //Replace $(Module-name) with the defined module name in chisel 
    V$(Module-name) *dut = new V$(Module-name);

    //To generate trace
    Verilated::traceEverOn(true);
    VerilatedVcdC *m_trace = new VerilatedVcdC;
    dut->trace(m_trace, 5);     //Show signals down to 5 levels deep
    m_trace->open("waveform.vcd");

    //Reading the dat file
    std::ifstream inputFile("data/file-name.dat"); 
    std::vector<unsigned int> hexVector;
    std::string line;

    if (inputFile.is_open()) {
        while (std::getline(inputFile, line)) {
            try {
                unsigned int hexValue = std::stoul(line, nullptr,  16);
                hexVector.push_back(hexValue);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid argument: " << e.what() << std::endl;
            } catch (const std::out_of_range& e) {
                std::cerr << "Out of range error: " << e.what() << std::endl;
            }
        }
        inputFile.close();
    } else {
        std::cerr << "Unable to open file" << std::endl;
    }
    int size = hexVector.size()*2;      //Get twice the size of vector, as 1 cycle = 2 sim_time

    //Simulation loop
    while (sim_time < MAX_SIM_TIME + size) {
        dut-> reset = 0;
        //Resetting for one clock cycle between 1 and 2
        if (sim_time >= 1 && sim_time <= 2) {
            dut-> reset = 1;
            //Reset any input signals
        }
        
        dut->clock ^= 1;

        //Initailizing the vector values
        if (dut-> clock == 1) {     //To keep sync with posedge of clock
            if (sim_time >= 3 && sim_time <= size + 3) {
                //Use hexVector[posedge_cnt] and psoedge to initialize
                //posedge_cnt++;
            }
        }
            
        //Add input signals here
        //Eval will set the signals in and make them reflect in output
        
        dut->eval();

        //Add any checks here for output
        //Simulation body

        m_trace->dump(sim_time);
        sim_time++;
    }
    m_trace->close();
    delete dut;
    exit(EXIT_SUCCESS);
}
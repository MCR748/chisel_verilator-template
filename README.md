This project contains the following.

1. Template to start writing hardware with chisel.
2. Template to start writing testbench with verilator.
3. Makefile to automate compiling the project.


**make all**:	Generate verilog hardware from chisel. 
				Rebuild the entire simulation.
				Display waveform file using gtkWave.

**make sim**:	Rebuild the entire simulation.
				Display waveform file using gtkWave.

**make waves**:	Display waveform file using gtkWave.

**make clean**: Remove unneccesary files generated in build process. 

//Use namespaces if required

import chisel3._
import chisel3.util._

// Change the module name
class MemModule extends Module {
    val io = IO(new Bundle{
        //Add input output ports
    })
    //Add module body
}

// To generate the verilog hardware
// Change the module name as required
object MemModuleMain extends App {
  println("Generating the adder hardware")
  //Hardware files will be out into generated
  emitVerilog(new MemModule(), Array("--target-dir", "generated"))
}

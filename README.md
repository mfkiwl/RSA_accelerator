## RSA Box

From the root on the FPGA, run:
```
make
``` 
This generates the device driver (kernel module). Then, if you run:

```
cd user-level
make
```

You can run:
```
./run.sh
```

This inserts the kernel module and runs the test cases defined in wrapper-test.c.

### Important Source Code (in PDF)
lab3-qsys/RSA_BOX.sv is our primary hardware file. Everything in user-level is also very important, as are rsa_box.c and rsa_box.h in the root, which define the device driver.

### Updating the Linux device tree on FPGA:
* from [device_tree_files](https://github.com/ohEmily/RSA_accelerator/tree/master/device_tree_files), run:
```
/usr/src/linux/scripts/dtc/dtc -O dtb -o socfpga.dtb socfpga.dts
```
 * this should generate a new `dtb` file
 * from the host OS, copy the `dtb` file to overwrite the `dtb` file in `\user6\spring15\[my_uni]\root`

### Getting verilator to work
```
Download from http://www.veripool.org/projects/verilator/wiki/Installing
```
Make sure you have all the required packages like flex and bison, and run the following commands
```
tar xvzf verilator*.t*gz
cd verilator*
./configure
make
sudo make install
```
### Compiling and running Verilog code

In the same directory as the verilog code create a c++ file with the appropriate structure (read man pages, and look at sample code in verilator/)
Compile with the following command: 
```
verilator -Wall -CFLAGS -std=c++11 --cc some_verilog_file.sv --exe some_simulation.cpp
```
This will create a obj_dir/ directory
```
cd obj_dir
make -j -f Vsome_verilog_file.mk Vsome_verilog_file
```
Then run
```
./Vsome_verilog_file
```

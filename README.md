## RSA Box

For the hardware, the updated code is in the same repo as the C code, which is:

```
/sockit/lab3-enp2111/root/root/RSAB
```

From the FPGA, run:
```
make
``` 

To start up the device driver, run:
```
insmod rsa_box.ko
```

With the driver running, run `./hello` in order to demonstrate RSA capabilities.

To finish your session, run:
```
rmmod vga_led
```

### Dependencies:
 * [GMP](https://gmplib.org/)

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
verilator -Wall --cc some_verilog_file.sv --exe some_simulation.cpp
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

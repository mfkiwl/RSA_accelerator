CFLAGS=-std=c++11

RSA_BOX:
	verilator -Wall -CFLAGS $(CFLAGS) -cc -sv RSA_BOX.sv --trace --exe RSA_BOX_sim_main.cpp
	cd obj_dir; make -j -f VRSA_BOX.mk VRSA_BOX
B128:
	verilator -Wall -CFLAGS $(CFLAGS) -cc -sv blakley128.sv --trace --exe blakley128_sim_main.cpp
	cd obj_dir; make -j -f Vblakley128.mk Vblakley128

B5:
	verilator -Wall -CFLAGS $(CFLAGS) -cc -sv blakley5.sv --trace --exe blakley5_sim_main.cpp
	cd obj_dir; make -j -f Vblakley5.mk Vblakley5

VVGA_LED:
	verilator -Wall -CFLAGS $(CFLAGS) -cc VGA_LED.sv --exe vga_sim_main.cpp
	cd obj_dir; make -j -f VVGA_LED.mk VVGA_LED

Vour:
	verilator -Wall -CFLAGS $(CFLAGS) -cc our.sv --exe test_sim_main.cpp
	cd obj_dir; make -j -f Vour.mk Vour

run: RSA_BOX
	cd obj_dir; ./VRSA_BOX

.PHONY: clean
clean:
	rm -rf obj_dir

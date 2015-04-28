CFLAGS=-std=c++11

VBlakely128:
	verilator -Wall -CFLAGS $(CFLAGS) -cc -sv blakely128.sv --trace --exe 128_b.cpp
	cd obj_dir; make -j -f Vblakely128.mk Vblakely128
VBlakely:
	verilator -Wall -CFLAGS $(CFLAGS) -cc -sv blakely5.sv --trace --exe blakely_sim_main.cpp
	cd obj_dir; make -j -f Vblakely5.mk Vblakely5
VVGA_LED:
	verilator -Wall -CFLAGS $(CFLAGS) -cc VGA_LED.sv --exe vga_sim_main.cpp
	cd obj_dir; make -j -f VVGA_LED.mk VVGA_LED

Vour:
	verilator -Wall -CFLAGS $(CFLAGS) -cc our.sv --exe test_sim_main.cpp
	cd obj_dir; make -j -f Vour.mk Vour

run:
	cd obj_dir; ./Vblakely128
.PHONY: clean
clean:
	rm -rf obj_dir

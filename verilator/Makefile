CFLAGS=-std=c++11

VBlakely:
	verilator -Wall -CFLAGS $(CFLAGS) -cc blakely.sv --exe --trace blakely_sim_main.cpp
	cd obj_dir; make -j -f Vblakely.mk Vblakely
VVGA_LED:
	verilator -Wall -CFLAGS $(CFLAGS) -cc VGA_LED.sv --exe vga_sim_main.cpp
	cd obj_dir; make -j -f VVGA_LED.mk VVGA_LED

Vour:
	verilator -Wall -CFLAGS $(CFLAGS) -cc our.sv --exe test_sim_main.cpp
	cd obj_dir; make -j -f Vour.mk Vour

run:
	cd obj_dir; ./Vblakely
.PHONY: clean
clean:
	rm -rf obj_dir

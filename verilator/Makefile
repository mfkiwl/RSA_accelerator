CFLAGS=-std=c++11

B128:
	verilator -Wall -CFLAGS $(CFLAGS) -cc -sv blakley128.sv --trace --exe 128_b.cpp
	cd obj_dir; make -j -f Vblakley128.mk Vblakley128

B5:
	verilator -Wall -CFLAGS $(CFLAGS) -cc -sv blakley5.sv --trace --exe blakley_sim_main.cpp
	cd obj_dir; make -j -f Vblakley5.mk Vblakley5

VVGA_LED:
	verilator -Wall -CFLAGS $(CFLAGS) -cc VGA_LED.sv --exe vga_sim_main.cpp
	cd obj_dir; make -j -f VVGA_LED.mk VVGA_LED

Vour:
	verilator -Wall -CFLAGS $(CFLAGS) -cc our.sv --exe test_sim_main.cpp
	cd obj_dir; make -j -f Vour.mk Vour

run: B128
	cd obj_dir; ./Vblakley128

.PHONY: clean
clean:
	rm -rf obj_dir

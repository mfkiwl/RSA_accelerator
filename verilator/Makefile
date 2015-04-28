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

Vextended_euclid:
	verilator -Wall -CFLAGS $(CFLAGS) -cc extended_euclid.sv extended_euclid_test.cpp
	cd obj_dir; make -j -f Vextended.euclid.mk Vextended_euclid

Vblakley:
	verilator -Wall -CFLAGS $(CFLAGS) -cc blakley.sv --exe blakley_test.cpp
	cd obj_dir; make -j -f Vblakley.mk Vblakley

run:
	cd obj_dir; ./Vblakley

.PHONY: clean
clean:
	rm -rf obj_dir

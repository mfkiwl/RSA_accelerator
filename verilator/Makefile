CFLAGS=-std=c++11

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

.PHONY: clean
clean:
	rm -rf obj_dir

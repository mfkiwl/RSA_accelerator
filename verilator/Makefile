CFLAGS=-std=c++11

Vour:
	verilator -Wall -CFLAGS $(CFLAGS) -cc our.sv --exe test_sim_main.cpp
	cd obj_dir; make -j -f Vour.mk Vour

Vextended_euclid:
	verilator -Wall -CFLAGS $(CFLAGS) -cc extended_euclid.sv blakely_test.cpp
	cd obj_dir; make -j -f Vextended.euclid.mk Vextended_euclid

Vblakley:
	verilator -Wall -CFLAGS $(CFLAGS) -cc blakley.sv --exe test_sim_main.cpp
	cd obj_dir; make -j -f Vblakley.mk Vblakley

.PHONY: clean
clean:
	rm -rf obj_dir

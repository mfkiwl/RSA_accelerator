CFLAGS=-std=c++11

Vour:
	verilator -Wall -CFLAGS $(CFLAGS) -cc our.sv --exe test_sim_main.cpp
	cd obj_dir; make -j -f Vour.mk Vour

.PHONY: clean
clean:
	rm -rf obj_dir

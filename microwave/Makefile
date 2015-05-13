CFLAGS=-std=c++11
VincrementA:
	verilator -Wall -CFLAGS $(CFLAGS) -cc incrementA.sv --trace --exe test_bench.cpp
	cd obj_dir; make -j -f VincrementA.mk VincrementA

run:
	cd obj_dir; ./VincrementA

.PHONY: clean
clean:
	rm -rf obj_dir

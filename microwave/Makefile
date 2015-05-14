CFLAGS=-std=c++11
Vtemp:
	verilator -Wall -CFLAGS $(CFLAGS) -cc temp.sv --trace --exe test_temp.cpp
	cd obj_dir; make -j -f Vtemp.mk Vtemp
VincrementA:
	verilator -Wall -CFLAGS $(CFLAGS) -cc incrementA.sv --trace --exe test_bench.cpp
	cd obj_dir; make -j -f VincrementA.mk VincrementA

Vmultiply:
	verilator -Wall -CFLAGS $(CFLAGS) -cc multiply.sv --trace --exe multiply_test.cpp
	cd obj_dir; make -j -f Vmultiply.mk Vmultiply

Vexponentiate:
	verilator -Wall -CFLAGS $(CFLAGS) -cc exponentiate.sv --trace --exe exponent_test.cpp
	cd obj_dir; make -j -f Vexponentiate.mk Vexponentiate

run:
	cd obj_dir; ./Vtemp

multiply:
	cd obj_dir; ./Vmultiply
	
test:
	cd obj_dir; ./Vexponentiate

.PHONY: clean
clean:
	rm -rf obj_dir

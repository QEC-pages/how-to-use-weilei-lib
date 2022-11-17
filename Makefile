MAKEFLAGS += --no-print-directory

# build options to test dynamic library
LIB_WEILEI_PATH=/rhome/wzeng002/.local/lib
LIB_WEILEI=-L$(LIB_WEILEI_PATH) -lweilei -Iweilei_lib


INC_DIR=weilei_lib
#INC_DIR=~/working/weilei_lib
CXX=g++ -O3 -Wall -std=c++11 -fopenmp
CXX=g++ -O3 -Wall -std=c++11
# optimization options -O2 -O5 -Os
ITPP=`pkg-config --cflags itpp` `pkg-config --libs itpp`
#full command example
#g++ `pkg-config --cflags itpp` -o hello.out hello.cpp `pkg-config --libs itpp` -fopenmp


object_files=$(INC_DIR)/mm_read.o $(INC_DIR)/mmio.o $(INC_DIR)/mm_write.o $(INC_DIR)/lib.o $(INC_DIR)/dist.o $(INC_DIR)/product_lib.o $(INC_DIR)/bp.o 
header_files=$(INC_DIR)/mm_read.h $(INC_DIR)/mmio.h $(INC_DIR)/mm_write.h $(INC_DIR)/lib.h $(INC_DIR)/dist.h $(INC_DIR)/product_lib.h $(INC_DIR)/bp.h

#make object file for target file
%.o:%.cpp $(header_files)
	$(CXX) $(START) $(END) -c $<
#compile object files for lib files
lib:
	cd weilei_lib && make all
#now link object files

%.out:%.o $(object_files)
	$(CXX) $(ITPP) -o $@ $< $(object_files)

cmd=make lib && make $@.o && make $@.out
# eg: make test.o && make lib && make test.out
product:
	$(cmd)
test:
	$(cmd)
test_lib:
	$(cmd)
#add your new files here


clean:
	rm *.o
	rm *.out

#job management
sbatch-dry-run:
	sbatch --test run_prod.sh
sbatch:
	sbatch run_prod.sh
pkill-product:
	pkill .product


#test dynamic lib
dynamic:$(LIB_WEILEI_PATH)/libweilei.so
	cd weilei_lib && make libweilei.so
	$(CXX) $(ITPP) -o test_dynamic.out test.cpp -lweilei -L$(LIB_WEILEI_PATH)
	./test_dynamic.out


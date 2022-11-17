MAKEFLAGS += --no-print-directory

# build options to test dynamic library
#LIB_WEILEI_PATH=/rhome/wzeng002/.local/lib
#LIB_WEILEI_PATH=/home/weileizeng/.local/lib
LIB_WEILEI_PATH=/sharedata01/weileizeng/.local/lib
LIB_WEILEI=-L$(LIB_WEILEI_PATH) -lweilei -Iweilei_lib


INC_DIR=weilei_lib
#INC_DIR=~/working/weilei_lib
CXX=g++ -O3 -Wall -std=c++11 -fopenmp
#CXX=g++ -O3 -Wall -std=c++11
# optimization options -O2 -O5 -Os
#ITPP=`pkg-config --cflags itpp` `pkg-config --libs itpp`
#ITPP=`itpp-config --cflags` `itpp-config --libs`
ITPP=-I/sharedata01/weileizeng/gitrepo/install-itpp-locally/itpp-4.3.1/include -O2 -DNDEBUG -L/sharedata01/weileizeng/gitrepo/install-itpp-locally/itpp-4.3.1/lib -litpp
# $(LIB_WEILEI)
#full command example
#g++ `pkg-config --cflags itpp` -o hello.out hello.cpp `pkg-config --libs itpp` -fopenmp


object_files=$(INC_DIR)/mm_read.o $(INC_DIR)/mmio.o $(INC_DIR)/mm_write.o $(INC_DIR)/lib.o $(INC_DIR)/dist.o $(INC_DIR)/product_lib.o $(INC_DIR)/bp.o 
header_files=$(INC_DIR)/mm_read.h $(INC_DIR)/mmio.h $(INC_DIR)/mm_write.h $(INC_DIR)/lib.h $(INC_DIR)/dist.h $(INC_DIR)/product_lib.h $(INC_DIR)/bp.h

#make object file for target file
%.o:%.cpp $(header_files)
#	$(CXX) $(START) $(END) -c $<
	$(CXX) $(ITPP) -c $<
#compile object files for lib files
lib:
	cd weilei_lib && make all
#now link object files

%.out:%.o $(object_files)
	$(CXX) $(ITPP) -o $@ $< $(object_files)

cmd=make lib && make $@.o && make $@.out #&& ./$@.out
# eg: make test.o && make lib && make test.out
product:
	$(cmd)
test:
	$(cmd)
test_lib:
	$(cmd)
generate_css_code:
	$(cmd)
#because I install it locally, i need to inform where the itpp lib is located
#	export LD_LIBRARY_PATH="/home/weileizeng/.local/lib:$LD_LIBRARY_PATH" && 
#This was moved to .bashrc
#	./$@.out

#add your new files here


clean:
	rm *.o
	rm *.out

#job management
sbatch-dry-run:
	sbatch --test run_prod.sh
sbatch:
	sbatch run_prod.sh
srun:
	srun -n 1 --cpus-per-task=32 --time=12:00:00 ./generate_css_code.out 
short:
	srun -n 1 -q short --cpus-per-task=32 --time=1:00:00 ./generate_css_code.out 
pkill-product:
	pkill .product

#job related
interactive:
	salloc --nodes=1

#test dynamic lib
dynamic:$(LIB_WEILEI_PATH)/libweilei.so
	cd weilei_lib && make libweilei.so
	$(CXX) $(ITPP) -o test_dynamic.out test.cpp -lweilei -L$(LIB_WEILEI_PATH)
	./test_dynamic.out


data-statistics:
	du -sh data/
	ls data/ |wc -l

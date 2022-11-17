#include "weilei_lib/weilei_lib.h"  //general include goes to weilei_lib_h
#include "json.hpp"
using json=nlohmann::json;
#include <chrono> //print computation time
#include <ctime>  
//#include <ctime> //to get current time
//using namespace common;

//int generate_css_code();
int generate_css_code(int n, int Gx_row, int Gz_row);

int main(){
  std::cout<<" --------------------- begin generating CSS codes"<<std::endl;
  //  generate_css_code();

  //set up simulation
  /*
  for (int n=12;n<31;n++){
    for ( int Gx_row = 5;Gx_row<n-1;Gx_row++){
      for ( int Gz_row = 5; Gz_row < n-Gx_row-1 && Gz_row < Gx_row +3 ; Gz_row ++){

  for (int n=7;n<12;n++){

  for (int n=2;n<34;n++){  #didn't get up to 34 due to error (submatrix)
    for ( int Gx_row = 2;Gx_row<n-1;Gx_row++){
      for ( int Gz_row = 2; Gz_row < n-Gx_row && Gz_row < Gx_row +3 ; Gz_row ++){

   */


  for (int n=13;n<31;n++){
    for ( int Gx_row = 2;Gx_row<n-1;Gx_row++){
      for ( int Gz_row = ( 2 > n-Gx_row - 2)? 2 : n-Gx_row - 2; Gz_row < n-Gx_row && Gz_row < Gx_row +3 ; Gz_row ++){ //start from k=2, then k = 1
	std::cout<<"n="<<n<<", Gx_row="<<Gx_row<<", Gz_row="<<Gz_row<<std::endl;

	auto start = std::chrono::system_clock::now();
	std::time_t start_time = std::chrono::system_clock::to_time_t(start);
	std::cout <<".-.-.-.-.-.-.-.-.-.-.-."
		  << "start computation at " << std::ctime(&start_time)<<std::endl;

	generate_css_code(n,Gx_row,Gz_row);
	//When G_x_row or Gz_row is too small (like 1), error occurs, probably get zero matrix somewhere

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	std::cout << "elapsed time: " << elapsed_seconds.count() << "s"
		  << std::endl;
      }
    }
  }
  /*simulation log
    run: n=8..13, Gx_row and Gz_row = 2..n-1
    n=21..30
    n=12..19
   */
  
  std::cout<<" --------------------- finish generating CSS codes"<<std::endl;
  return 0;
}

/*parameters to set up:
  num_cores,32
  num_trials, 10000
  how many instances to save for each parameter set, 3
  data folder, ../data/CSS-Codes/run1
 */
int generate_css_code(int n, int Gx_row, int Gz_row){
  //int generate_css_code(){
  int seed = common::get_time(3)+100;//+seed;
  itpp::RNG_reset(seed);
  itpp::RNG_randomize();

  int num_cores = 32; //32
  int num_trials = num_cores * 10;
  int dx_max=0, dz_max=0;
  //#pragma omp parallel for num_threads(4)
#pragma omp parallel for schedule(guided) num_threads(num_cores)
  for ( int i =0; i < num_trials; i ++ ){
    //random CSS code
    CSSCode codeR;
    codeR.title="random code";
    // good choice: 15,6,6;
    codeR.n=n;//22;
    codeR.Gx_row=Gx_row;//15;
    codeR.Gz_row=Gz_row;//5;

    codeR.getGoodCode(0);//0 for disabling debug
    codeR.dist();
    /* if ( not codeR.is_valid() ){
      std::cout<<"The code is not valid"<<std::endl;
    }else{
       //       try{
       codeR.dist();
	 //       }catch(std::exception e){
	 //	 std::cout<<"The code is not valid. probably zero matrix"<<std::endl;
	 //       }
	 }*/
    //the following part should be in critical in the beginning, after some run it is okay to remove
//#pragma omp critical
    {
      /*
    if (dx_max <= codeR.dx)  {
      dx_max = codeR.dx;
      codeR.k=codeR.n - codeR.Gx.row_rank() - codeR.Gz.row_rank();
      std::cout<<"dx_max = "<<dx_max<<", dz_max = "<<dz_max;
      std::cout<<"; "<<codeR<<std::endl;
    }
    if (dz_max <= codeR.dz)  {
      dz_max = codeR.dz ;
      codeR.k=codeR.n - codeR.Gx.row_rank() - codeR.Gz.row_rank();
      std::cout<<"dx_max = "<<dx_max<<", dz_max = "<<dz_max;
      std::cout<<"; "<<codeR<<std::endl;
    }
      */
    //check if file exists. saev the code if not
    //set up filename
    std::string title_str="../data/CSS-Codes/run1/";
    int d =(codeR.dx < codeR.dz)? codeR.dx : codeR.dz ;
    int Gx_row_rank = codeR.Gx.row_rank(), Gz_row_rank = codeR.Gz.row_rank();
    codeR.k=codeR.n - Gx_row_rank - Gz_row_rank;
    std::string filename_prefix=title_str
      +"n"+std::to_string(codeR.n)+"k"+std::to_string(codeR.k)+"d"+std::to_string(d)
      +"-x"+std::to_string(Gx_row_rank)+"z"+std::to_string(Gz_row_rank)
      +"dx"+std::to_string(codeR.dx)+"dz"+std::to_string(codeR.dz);

    FILE *f;
    for (int j = 0; j<10; j++){//save three instances for the same parameter
      //      std::cout<<"debug:1"<<std::endl;
      //filename_prefix = filename_prefix + "-"+std::to_string(j);
      char filename_Gx[256],filename_Gz[256],filename_json[256];
      sprintf(filename_Gx,"%s-%iGx.mm",filename_prefix.c_str(),j);
      sprintf(filename_Gz,"%s-%iGz.mm",filename_prefix.c_str(),j);
      sprintf(filename_json,"%s-%i.json",filename_prefix.c_str(),j);

      //      std::string filename_Gx = filename_prefix + "-"+std::to_string(j) + "Gx.mm";
      //std::string filename_json = filename_prefix + "-"+std::to_string(j) + ".json";
      //      const char* filename = filename_Gx.c_str();
      const char* filename = filename_Gx;
      //std::cout<<j<<std::endl;
      if ((f = fopen(filename, "r")) == NULL) {
	//save the code if file doesn't exist yet
	//std::cout<<"saving code: "<<filename<<std::endl;
	//codeR.save(filename_prefix + "-" + std::to_string(j) );
	//itpp::GF2mat Gt = codeR.Gz;
	//	std::cout<<filename_Gz<<std::endl;
	GF2mat_to_MM(codeR.Gz,filename_Gx);
	GF2mat_to_MM(codeR.Gz,filename_Gz);

	//save parameters into json file
	json::object_t object_value = {
	  {"n",codeR.n},
	  {"k",codeR.k},
	  {"d",d},
	  {"Gx_row",Gx_row_rank},
	  {"Gz_row",Gz_row_rank},
	  {"dx",codeR.dx},
	  {"dz",codeR.dz},
	  {"index",j},
	  {"filename_Gx",filename_Gx},
	  {"filename_Gz",filename_Gz},
	};
	json j_object_t(object_value);
	//	std::cout<<j_object_t<<std::endl;
	std::ofstream filejson(filename_json);
	filejson << j_object_t;
	filejson.close();

	std::cout<<"saved code to "<<filename_json<<std::endl;
	break;
      }else{
	//std::cout<<"the file exist: "<<filename_prefix<<std::endl;
	fclose(f);
      }
    }
    
    }
    //    std::cout<<codeR.Gx<<std::endl;
    //std::cout<<"run"<<i<<", dx="<<codeR.dx<<std::endl;
  }
  //  std::cout<<"dx_max = "<<dx_max<<", dz_max = "<<dz_max<<std::endl;
  
  //  codeR.set_up_CxCz(); // no need to do it. already genrated in GetRandomCode().
  

  /*std::cout<<codeR.is_C_defined<<std::endl;
  std::cout<<codeR.Gx<<std::endl;
  std::cout<<codeR.Gz<<std::endl;
  std::cout<<codeR.Cx<<std::endl;
  std::cout<<codeR.Cz<<std::endl;
  */
  return 0;
}




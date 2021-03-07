
#include "main3.h"

#define DEPT "Dept"
#define EMP "Emp"
#define JOIN "join"
#define CSV ".csv"
#define STR_SIZE 40
#define NUM_BLOCKS 22


void sort_runs(const char* source_file, const char* run_tag, const int blocks_per_run)
{

   std::fstream read_in;
   std::fstream write_out;

   std::string temp_name;

   read_in.open(source_file, std::ios::in);

   for (int i=0; i<blocks_per_run; i++)
   {
      temp_name = run_tag + std::to_string(i);
      write_out.open(temp_name, std::ios::out | std::ios::app);

   }

}


int main(int argc, char **args)
{

   sort_runs("Dept.csv", "run_R", NUM_BLOCKS);
 
   return 0;
}

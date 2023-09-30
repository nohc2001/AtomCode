#include <iostream>
using namespace std;

inline bool is1(uint32_t inst, uint32_t loc){
  return inst & (1 << loc);
}

enum class op_type{
  Reserved_UDF,
  SME,
  SVP,
  DataProcessing_Immidate,
  Branch_or_ExeptionSystemInstruction,
  Load_or_Store,
  DataProcessing_Register,
  DataProcessing_ScalarFloat_or_SIMD
};

op_type getOP(uint32_t inst){
}

int main(){
  cout << "testing for codespaces" << endl;
  return 0;
}

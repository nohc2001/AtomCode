#include <iostream>
using namespace std;

inline bool is1(uint32_t inst, uint32_t loc){
  return inst & (1 << loc);
}

enum class op_type{
  Undefine,
  Reserved_UDF,
  SME,
  SVP,
  DataProcessing_Immidate,
  Branch_or_ExeptionSystemInstruction,
  Load_or_Store,
  DataProcessing_Register,
  DataProcessing_ScalarFloat_or_SIMD
};

struct op_range{
  int start = 0;
  int end = 0;
};

inline int gr(op_range r, int index){
  return r.end - index;
}

bool masking(uint32_t inst, op_range r, const char* mask){
  int len = 1 + r.end - r.start;
  bool b = true;
  for(int i=0;i<len;++i){
    switch(mask[i]){
      case '1':
      b = b && is1(inst, gr(r, i));
      break;
      case '0':
      b = b && !is1(inst, gr(r, i));
      break;
    }
    
    if(b == false) return false;
  }

  return true;
}

constexpr int op0 = 31;
constexpr op_range op1 = {25, 28};

op_type getOP_Reserved(uint32_t inst){
  return op_type::Undefine;
}

op_type getOP_SME(uint32_t inst){
  return op_type::Undefine;
}

op_type getOP_SVE(uint32_t inst){
  return op_type::Undefine;
}

op_type getOP_DataProcessing_Immediate(uint32_t inst){
  return op_type::Undefine;
}

op_type getOP_Branch_or_ExecptionSystemInstruction(uint32_t inst){
  return op_type::Undefine;
}

op_type getOP_Load_Store(uint32_t inst){
  return op_type::Undefine;
}

op_type getOP_DataProcessing_Register(uint32_t inst){
  return op_type::Undefine;
}

op_type getOP_DataProcessing_ScalarFloat_or_SIMD(uint32_t inst){
  return op_type::Undefine;
}

op_type getOP(uint32_t inst){
  if(!is1(inst, op0)){
    //inst[31] = 0
    if(masking(inst, op1, "0000")){
      return getOP_Reserved(inst);
    }
  }
  else{
    //inst[31] = 1
    if(masking(inst, op1, "0000")){
      return getOP_SME(inst);
    }
  }

  if(masking(inst, op1, "0010")){
    return getOP_SVE(inst);
  }
  if(masking(inst, op1, "100x")){
    return getOP_DataProcessing_Immediate(inst);
  }
  if(masking(inst, op1, "101x")){
    return getOP_Branch_or_ExecptionSystemInstruction(inst);
  }
  if(masking(inst, op1, "x1x0")){
    return getOP_Load_Store(inst);
  }
  if(masking(inst, op1, "x101")){
    return getOP_DataProcessing_Register(inst);
  }
  if(masking(inst, op1, "x111")){
    return getOP_DataProcessing_ScalarFloat_or_SIMD(inst);
  }

  return op_type::Undefine;
}

int main(){
  cout << "testing for codespaces" << endl;
  return 0;
}

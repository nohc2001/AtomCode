#include <iostream>
#include <string.h>
using namespace std;

enum class op_type{
  Undefine,

  Reserved_UDF,

  SME_OuterProduct_64bit_FP64_FMOPA,
  SME_OuterProduct_64bit_FP64_FMOPS,

  SME_OuterProduct_64bit_Int16_FMOPA,
  SME_OuterProduct_64bit_Int16_FMOPS,
  SME_OuterProduct_64bit_Int16_SUMOPA,
  SME_OuterProduct_64bit_Int16_SUMOPS,
  SME_OuterProduct_64bit_Int16_USMOPA,
  SME_OuterProduct_64bit_Int16_USMOPS,
  SME_OuterProduct_64bit_Int16_UMOPA,
  SME_OuterProduct_64bit_Int16_UMOPS,

  SME_FP_OuterProduct_32bit_FP32_FMOPA,
  SME_FP_OuterProduct_32bit_FP32_FMOPS,
  SME_FP_OuterProduct_32bit_Widning_BF16_BFMOPA,
  SME_FP_OuterProduct_32bit_Widning_BF16_BFMOPS,
  SME_FP_OuterProduct_32bit_FP16_Widning_FMOPA,
  SME_FP_OuterProduct_32bit_FP16_Widning_FMOPS,

  SME_2_Binary_OuterProduct_32bit_BMOPA,
  SME_2_Binary_OuterProduct_32bit_BMOPS,

  SME_Integer_Outer_Product_32bit_Int16_2Way_SMOPA,
  SME_Integer_Outer_Product_32bit_Int16_2Way_SMOPS,
  SME_Integer_Outer_Product_32bit_Int16_2Way_UMOPA,
  SME_Integer_Outer_Product_32bit_Int16_2Way_UMOPS,
  SME_Integer_Outer_Product_32bit_Int8_SMOPA,
  SME_Integer_Outer_Product_32bit_Int8_SMOPS,
  SME_Integer_Outer_Product_32bit_Int8_SUMOPA,
  SME_Integer_Outer_Product_32bit_Int8_SUMOPS,
  SME_Integer_Outer_Product_32bit_Int8_USMOPA,
  SME_Integer_Outer_Product_32bit_Int8_USMOPS,
  SME_Integer_Outer_Product_32bit_Int8_UMOPA,
  SME_Integer_Outer_Product_32bit_Int8_UMOPS,

  SME_2_MultiVector_Memory_Continguous_Load_sps_2Register_LD1B,
  SME_2_MultiVector_Memory_Continguous_Load_sps_2Register_LDNT1B,
  SME_2_MultiVector_Memory_Continguous_Load_sps_2Register_LD1H,
  SME_2_MultiVector_Memory_Continguous_Load_sps_2Register_LDNT1H,
  SME_2_MultiVector_Memory_Continguous_Load_sps_2Register_LD1W,
  SME_2_MultiVector_Memory_Continguous_Load_sps_2Register_LDNT1W,
  SME_2_MultiVector_Memory_Continguous_Load_sps_2Register_LD1D,
  SME_2_MultiVector_Memory_Continguous_Load_sps_2Register_LDNT1D,
  SME_2_MultiVector_Memory_Continguous_Load_sps_4Register_LD1B,
  SME_2_MultiVector_Memory_Continguous_Load_sps_4Register_LDNT1B,
  SME_2_MultiVector_Memory_Continguous_Load_sps_4Register_LD1H,
  SME_2_MultiVector_Memory_Continguous_Load_sps_4Register_LDNT1H,
  SME_2_MultiVector_Memory_Continguous_Load_sps_4Register_LD1W,
  SME_2_MultiVector_Memory_Continguous_Load_sps_4Register_LDNT1W,
  SME_2_MultiVector_Memory_Continguous_Load_sps_4Register_LD1D,
  SME_2_MultiVector_Memory_Continguous_Load_sps_4Register_LDNT1D,
  SME_2_MultiVector_Memory_Continguous_Store_sps_2Register_ST1B,
  SME_2_MultiVector_Memory_Continguous_Store_sps_2Register_STNT1B,
  SME_2_MultiVector_Memory_Continguous_Store_sps_2Register_ST1H,
  SME_2_MultiVector_Memory_Continguous_Store_sps_2Register_STNT1H,
  SME_2_MultiVector_Memory_Continguous_Store_sps_2Register_ST1W,
  SME_2_MultiVector_Memory_Continguous_Store_sps_2Register_STNT1W,
  SME_2_MultiVector_Memory_Continguous_Store_sps_2Register_ST1D,
  SME_2_MultiVector_Memory_Continguous_Store_sps_2Register_STNT1D,
  SME_2_MultiVector_Memory_Continguous_Store_sps_4Register_ST1B,
  SME_2_MultiVector_Memory_Continguous_Store_sps_4Register_STNT1B,
  SME_2_MultiVector_Memory_Continguous_Store_sps_4Register_ST1H,
  SME_2_MultiVector_Memory_Continguous_Store_sps_4Register_STNT1H,
  SME_2_MultiVector_Memory_Continguous_Store_sps_4Register_ST1W,
  SME_2_MultiVector_Memory_Continguous_Store_sps_4Register_STNT1W,
  SME_2_MultiVector_Memory_Continguous_Store_sps_4Register_ST1D,
  SME_2_MultiVector_Memory_Continguous_Store_sps_4Register_STNT1D,
  SME_2_MultiVector_Memory_Continguous_Load_spi_2Register_LD1B,
  SME_2_MultiVector_Memory_Continguous_Load_spi_2Register_LDNT1B,
  SME_2_MultiVector_Memory_Continguous_Load_spi_2Register_LD1H,
  SME_2_MultiVector_Memory_Continguous_Load_spi_2Register_LDNT1H,
  SME_2_MultiVector_Memory_Continguous_Load_spi_2Register_LD1W,
  SME_2_MultiVector_Memory_Continguous_Load_spi_2Register_LDNT1W,
  SME_2_MultiVector_Memory_Continguous_Load_spi_2Register_LD1D,
  SME_2_MultiVector_Memory_Continguous_Load_spi_2Register_LDNT1D,
  SME_2_MultiVector_Memory_Continguous_Load_spi_4Register_LD1B,
  SME_2_MultiVector_Memory_Continguous_Load_spi_4Register_LDNT1B,
  SME_2_MultiVector_Memory_Continguous_Load_spi_4Register_LD1H,
  SME_2_MultiVector_Memory_Continguous_Load_spi_4Register_LDNT1H,
  SME_2_MultiVector_Memory_Continguous_Load_spi_4Register_LD1W,
  SME_2_MultiVector_Memory_Continguous_Load_spi_4Register_LDNT1W,
  SME_2_MultiVector_Memory_Continguous_Load_spi_4Register_LD1D,
  SME_2_MultiVector_Memory_Continguous_Load_spi_4Register_LDNT1D,
  SME_2_MultiVector_Memory_Continguous_Store_spi_2Register_ST1B,
  SME_2_MultiVector_Memory_Continguous_Store_spi_2Register_STNT1B,
  SME_2_MultiVector_Memory_Continguous_Store_spi_2Register_ST1H,
  SME_2_MultiVector_Memory_Continguous_Store_spi_2Register_STNT1H,
  SME_2_MultiVector_Memory_Continguous_Store_spi_2Register_ST1W,
  SME_2_MultiVector_Memory_Continguous_Store_spi_2Register_STNT1W,
  SME_2_MultiVector_Memory_Continguous_Store_spi_2Register_ST1D,
  SME_2_MultiVector_Memory_Continguous_Store_spi_2Register_STNT1D,
  SME_2_MultiVector_Memory_Continguous_Store_spi_4Register_ST1B,
  SME_2_MultiVector_Memory_Continguous_Store_spi_4Register_STNT1B,
  SME_2_MultiVector_Memory_Continguous_Store_spi_4Register_ST1H,
  SME_2_MultiVector_Memory_Continguous_Store_spi_4Register_STNT1H,
  SME_2_MultiVector_Memory_Continguous_Store_spi_4Register_ST1W,
  SME_2_MultiVector_Memory_Continguous_Store_spi_4Register_STNT1W,
  SME_2_MultiVector_Memory_Continguous_Store_spi_4Register_ST1D,
  SME_2_MultiVector_Memory_Continguous_Store_spi_4Register_STNT1D,

  SME_2_MultiVector_Memory_Strided,
  SME_MoveIntoArray,
  SME_MoveFromArray,
  SME_AddVectorToArray,
  SME_Zero,
  SME_2_Zero_LookupTable,
  SME_2_Move_LookupTable,
  SME_2_Zero_LookupTable,
  SME_2_Move_LookupTable,
  SME_2_Expand_LookupTable_Continguous,
  SME_2_MultiVector_Indexed_1Register,
  SME_2_MultiVector_Indexed_2Register,
  SME_2_MultiVector_Indexed_4Register,
  SME_2_MultiVector_SVE_Select,
  SME_2_MultiVector_SVE_Constructive_Binary,
  SME_2_MultiVector_SVE_Constructive_Unary,
  SME_2_MultiVector_MultiVector_SVE_Destructive_2Register,
  SME_2_MultiVector_MultiVector_SVE_Destructive_4Register,
  SME_2_MultiVector_MultiAndSingleVector_SVE_Destructive_2Register,
  SME_2_MultiVector_MultiAndSingleVector_SVE_Destructive_4Register,
  SME_2_MultiVector_MultiAndSingle_ArrayVectors,
  SME_2_MultiVector_Multiple_ArrayVectors_2Register,
  SME_2_MultiVector_Multiple_ArrayVectors_4Register,
  SME_Memory,
  SVP,
  DataProcessing_Immidate,
  Branch_or_ExeptionSystemInstruction,
  Load_or_Store,
  DataProcessing_Register,
  DataProcessing_ScalarFloat_or_SIMD
};

inline bool is1(uint32_t inst, uint32_t loc){
  return inst & (1 << loc);
}

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
      case '>':
      return b;
    }
    
    if(b == false) return false;
  }

  return true;
}

struct ccstr{
  char text[124] = {};
  int up = 0;
};

void push_text(ccstr* str, const char* text){
  int len = strlen(text);
  for(int i=0;i<len;++i){
    str->text[str->up] = text[i];
    str->up += 1;
  }
  str->text[str->up] = 0;
}

struct inst_info{
  //mnimonic
  char mnimonic[8] = {};

  //param_array
  int param_len = 0;
  uint32_t params[16] = {};

  // assembly code text
  ccstr asm_text;

  // emulate execute function pointer(uint32* param, int mod)
  // mod - 
  // 0 : emulate / 1 : to machine code / 2 : to assembly
  void (*func)(inst_info*, int);

  //inst type
  op_type inst_type;

  //machine code
  uint32_t inst_data;
};

void Reserved_UDF_func(inst_info* ii, int mod){
  switch(mod){
    case 0:
    break;
    case 1:
    break;
    case 2:
    {
      strcpy(ii->mnimonic, "UDF");
      ii->param_len = 1;
      ii->params[0] = getParam(ii->inst_data, {0, 15});
      push_text(&ii->asm_text, ii->mnimonic);
      push_text(&ii->asm_text, " #");
      push_text(&ii->asm_text, to_string(ii->params[0]).c_str());
    }
    break;
  }
}

uint32_t getParam(uint32_t inst, op_range r){
  uint32_t out = inst;
  int en = (31-r.end);
  out = out << en;
  out = out >> en;
  out = out >> r.start;
  return out;
}

inst_info gii(op_type type, uint32_t inst){
  inst_info ii;
  ii.inst_type = type;
  ii.inst_data = inst;
  switch(ii.inst_type){
    case op_type::Reserved_UDF:
    ii.func = Reserved_UDF_func;
    break;
  }

  ii.func(&ii, 2);

  return ii;
}

constexpr int op0 = 31;
constexpr op_range op1 = {25, 28};

inst_info getOP_Reserved(uint32_t inst){
  static constexpr op_range sop0 = {29, 30};
  static constexpr op_range sop1 = {16, 24};
  if(masking(inst, sop0, "00") && masking(inst, sop1, "000000000")){
    return gii(op_type::Reserved_UDF, inst);
  }

  return gii(op_type::Undefine, inst);
}

inst_info getOP_SME(uint32_t inst){
  static constexpr op_range sop0 = {29, 30};
  static constexpr op_range sop1 = {10, 24};
  static constexpr op_range sop2 = {2, 4};

  if(masking(inst, sop0, "00")){
    if(masking(inst, sop1, "x10>") && masking(inst, sop2, "x00")){
      constexpr int ssop0 = 24;
      constexpr int ssop1 = 21;
      constexpr int S = 4;
      if(!is1(inst, ssop0) && !is1(inst, ssop1)){
        if(!is1(inst, S)){
          return gii(op_type::SME_FP_OuterProduct_32bit_FP32_FMOPA, inst);
        }
        else{
          return gii(op_type::SME_FP_OuterProduct_32bit_FP32_FMOPS, inst);
        }
      }
      if(is1(inst, ssop0)){
        if(!is1(inst, ssop1)){
          if(!is1(inst, S)){
            return gii(op_type::SME_FP_OuterProduct_32bit_Widning_BF16_BFMOPA, inst);
          }
          else{
            return gii(op_type::SME_FP_OuterProduct_32bit_Widning_BF16_BFMOPS, inst);
          }
        }
        else{
          if(!is1(inst, S)){
            return gii(op_type::SME_FP_OuterProduct_32bit_FP16_Widning_FMOPA, inst);
          }
          else{
            return gii(op_type::SME_FP_OuterProduct_32bit_FP16_Widning_FMOPS, inst);
          }
        }
      }
    }
    if(masking(inst, sop1, "010>") && masking(inst, sop2, "x10")){
      //return gii(op_type::SME_2_Binary_OuterProduct_32bit, inst);
      constexpr int ssop0 = 21;
      constexpr int S = 4;
      if(!is1(inst, ssop0)){
        if(!is1(inst, S)){
          return gii(op_type::SME_2_Binary_OuterProduct_32bit_BMOPA, inst);
        }
        else{
          return gii(op_type::SME_2_Binary_OuterProduct_32bit_BMOPA, inst);
        }
      }
    }
  }
  else if(masking(inst, sop0, "01")){
    if(masking(inst, sop1, "x10>") && masking(inst, sop2, "xx1")){
      //return gii(op_type::SME_Integer_Outer_Product_32bit, inst);
      constexpr int ssop0 = 21;
      constexpr int ssop1 = 3;
      constexpr int S = 4;
      if(!is1(inst, ssop0) && is1(inst, ssop1)){
        constexpr int u0 = 24;
        if(!is1(inst, u0)){
          if(!is1(inst, S)){
            return gii(op_type::SME_Integer_Outer_Product_32bit_Int16_2Way_SMOPA, inst);
          }
          else{
            return gii(op_type::SME_Integer_Outer_Product_32bit_Int16_2Way_SMOPS, inst);
          }
        }
        else{
          if(!is1(inst, S)){
            return gii(op_type::SME_Integer_Outer_Product_32bit_Int16_2Way_UMOPA, inst);
          }
          else{
            return gii(op_type::SME_Integer_Outer_Product_32bit_Int16_2Way_UMOPS, inst);
          }
        }
      }
      if(!is1(inst, ssop1)){
        constexpr int u0 = 24;
        constexpr int u1 = 21;
        constexpr op_type oparr[2][2][2] = 
        {
          {
            {
              op_type::SME_Integer_Outer_Product_32bit_Int8_SMOPA,
              op_type::SME_Integer_Outer_Product_32bit_Int8_SMOPS
            },
            {
              op_type::SME_Integer_Outer_Product_32bit_Int8_SUMOPA,
              op_type::SME_Integer_Outer_Product_32bit_Int8_SUMOPS
            }
          },
          {
            {
              op_type::SME_Integer_Outer_Product_32bit_Int8_USMOPA,
              op_type::SME_Integer_Outer_Product_32bit_Int8_USMOPS
            },
            {
              op_type::SME_Integer_Outer_Product_32bit_Int8_UMOPA,
              op_type::SME_Integer_Outer_Product_32bit_Int8_UMOPS
            }
          }
        };
        int ind[3] = {
          is1(inst, u0) ? 1 : 0, 
          is1(inst, u1) ? 1 : 0, 
          is1(inst, S) ? 1 : 0
        };
        return gii(oparr[ind[0]][ind[1]][ind[2]], inst);
      }
    }
    if(masking(inst, sop1, "00>")){
      //return gii(op_type::SME_2_MultiVector_Memory_Continguous, inst);
      constexpr op_range ssop0 = {20, 22};
      constexpr int ssop1 = 15;
      constexpr int ssop2 = 1;
      if(masking(inst, ssop0, "00x")){
        if(!is1(inst, ssop1)){
          constexpr int msz0 = 14;
          constexpr int msz1 = 13;
          constexpr int N = 0;
          constexpr op_type oparr[2][2][2] =
              {
                  {{op_type::SME_2_MultiVector_Memory_Continguous_Load_sps_2Register_LD1B,
                    op_type::SME_2_MultiVector_Memory_Continguous_Load_sps_2Register_LDNT1B},
                   {op_type::SME_2_MultiVector_Memory_Continguous_Load_sps_2Register_LD1H,
                    op_type::SME_2_MultiVector_Memory_Continguous_Load_sps_2Register_LDNT1H}},
                  {{op_type::SME_2_MultiVector_Memory_Continguous_Load_sps_2Register_LD1W,
                    op_type::SME_2_MultiVector_Memory_Continguous_Load_sps_2Register_LDNT1W},
                   {op_type::SME_2_MultiVector_Memory_Continguous_Load_sps_2Register_LD1D,
                    op_type::SME_2_MultiVector_Memory_Continguous_Load_sps_2Register_LDNT1D}}};
          int ind[3] = {
              is1(inst, msz0) ? 1 : 0,
              is1(inst,msz1) ? 1 : 0,
              is1(inst, N) ? 1 : 0};
          return gii(oparr[ind[0]][ind[1]][ind[2]], inst);
        }
      }
      if (masking(inst, ssop0, "01x"))
      {
      }
      if(masking(inst, ssop0, "0xx")){
        
      }
      if(masking(inst, ssop0, "100")){
        
      }
      if(masking(inst, ssop0, "110")){
        
      }
      if(masking(inst, ssop0, "1x0")){
        
      }
      if(masking(inst, ssop0, "1x1")){
        
      }
    }
    if(masking(inst, sop1, "10>")){
      return gii(op_type::SME_2_MultiVector_Memory_Strided, inst);
    }
  }
  else if(masking(inst, sop0, "10")){
    if(masking(inst, sop1, "0xx000x0>") && masking(inst, sop2, "0xx")){
      return gii(op_type::SME_MoveIntoArray, inst);
    }
    if(masking(inst, sop1, "0xx000x1>")){
      return gii(op_type::SME_MoveFromArray, inst);
    }
    if(masking(inst, sop1, "0xx010>") && masking(inst, sop2, "x0x")){
      return gii(op_type::SME_AddVectorToArray, inst);
    }
    if(masking(inst, sop1, "0000010>")){
      return gii(op_type::SME_Zero, inst);
    }
    if(masking(inst, sop1, "0010010>")){
      return gii(op_type::SME_2_Zero_LookupTable, inst);
    }
    if(masking(inst, sop1, "0010011>")){
      return gii(op_type::SME_2_Move_LookupTable, inst);
    }
    if(masking(inst, sop1, "01x001>")){
      return gii(op_type::SME_2_Expand_LookupTable_Continguous, inst);
    }
    if(masking(inst, sop1, "1xx00>")){
      return gii(op_type::SME_2_MultiVector_Indexed_1Register, inst);
    }
    if(masking(inst, sop1, "1xx01xxxx0>")){
      return gii(op_type::SME_2_MultiVector_Indexed_2Register, inst);
    }
    if(masking(inst, sop1, "1xx01xxxx1>")){
      return gii(op_type::SME_2_MultiVector_Indexed_4Register, inst);
    }
    if(masking(inst, sop1, "1xx1xxxxx100>")){
      return gii(op_type::SME_2_MultiVector_SVE_Select, inst);
    }
    if(masking(inst, sop1, "1xx1xxxxx100>")){
      return gii(op_type::SME_2_MultiVector_SVE_Select, inst);
    }
    if(masking(inst, sop1, "1xx1xxxxx110>")){
      return gii(op_type::SME_2_MultiVector_SVE_Constructive_Binary, inst);
    }
    if(masking(inst, sop1, "1xx1xxxxx111000")){
      return gii(op_type::SME_2_MultiVector_SVE_Constructive_Unary, inst);
    }

    if(masking(inst, sop1, "1xx1xxxx010110x")){
      return gii(op_type::SME_2_MultiVector_MultiVector_SVE_Destructive_2Register, inst);
    }
    if(masking(inst, sop1, "1xx1xxxx010111x")){
      return gii(op_type::SME_2_MultiVector_MultiVector_SVE_Destructive_4Register,inst);
    }
    if(masking(inst, sop1, "1xx10xxx010100x")){
      return gii(op_type::SME_2_MultiVector_MultiAndSingleVector_SVE_Destructive_2Register, inst);
    }
    if(masking(inst, sop1, "1xx10xxx010101x")){
      return gii(op_type::SME_2_MultiVector_MultiAndSingleVector_SVE_Destructive_4Register, inst);
    }

    if(masking(inst, sop1, "10x1xxxxx0>")){
      return gii(op_type::SME_2_MultiVector_MultiAndSingle_ArrayVectors, inst);;
    }
    if(masking(inst, sop1, "11x1xxxx00>")){
      return gii(op_type::SME_2_MultiVector_MultiAndSingleVector_SVE_Destructive_2Register, inst);
    }
    if(masking(inst, sop1, "11x1xxxx10>")){
      return gii(op_type::SME_2_MultiVector_MultiAndSingleVector_SVE_Destructive_4Register, inst);
    }
  }
  else if(masking(inst, sop0, "11")){
    return gii(op_type::SME_Memory, inst);
  }

  if(masking(inst, sop0, "0x")){
    if(masking(inst, sop1, "x11>")){
      constexpr int ssop0 = 29;
      constexpr int ssop1 = 24;
      constexpr int ssop2 = 21;
      if(is1(inst, ssop0)){
        constexpr int sssop0 = 4;
        if(is1(inst, sssop0)){
          return gii(op_type::SME_OuterProduct_64bit_FP64_FMOPA, inst);
        }
        else{
          return gii(op_type::SME_OuterProduct_64bit_FP64_FMOPS, inst);
        }
      }
      if((!is1(inst, ssop0) && !is1(inst, ssop1)) && !is1(inst, ssop2)){
        constexpr int u0 = 24;
        constexpr int u1 = 21;
        constexpr int S = 4;
        if(!is1(inst, u0)){
          if(!is1(inst, u1)){
            if(!is1(inst, S)){
              return gii(op_type::SME_OuterProduct_64bit_Int16_FMOPA, inst);
            }
            else{
              return gii(op_type::SME_OuterProduct_64bit_Int16_FMOPS, inst);
            }
          }
          else{
            if(!is1(inst, S)){
              return gii(op_type::SME_OuterProduct_64bit_Int16_SUMOPA, inst);
            }
            else{
              return gii(op_type::SME_OuterProduct_64bit_Int16_SUMOPS, inst);
            }
          }
        }
        else{
          if(!is1(inst, u1)){
            if(!is1(inst, S)){
              return gii(op_type::SME_OuterProduct_64bit_Int16_USMOPA, inst);
            }
            else{
              return gii(op_type::SME_OuterProduct_64bit_Int16_USMOPS, inst);
            }
          }
          else{
            if(!is1(inst, S)){
              return gii(op_type::SME_OuterProduct_64bit_Int16_UMOPA, inst);
            }
            else{
              return gii(op_type::SME_OuterProduct_64bit_Int16_UMOPS, inst);
            }
          }
        }
      }
    }
  }
  return gii(op_type::Undefine, inst);
}

inst_info getOP_SVE(uint32_t inst){
  return gii(op_type::Undefine, inst);
}

inst_info getOP_DataProcessing_Immediate(uint32_t inst){
  return gii(op_type::Undefine, inst);
}

inst_info getOP_Branch_or_ExecptionSystemInstruction(uint32_t inst){
  return gii(op_type::Undefine, inst);
}

inst_info getOP_Load_Store(uint32_t inst){
  return gii(op_type::Undefine, inst);
}

inst_info getOP_DataProcessing_Register(uint32_t inst){
  return gii(op_type::Undefine, inst);
}

inst_info getOP_DataProcessing_ScalarFloat_or_SIMD(uint32_t inst){
  return gii(op_type::Undefine, inst);
}

inst_info getOP(uint32_t inst){
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

  return gii(op_type::Undefine, inst);
}

int main(){
  cout << "testing for codespaces" << endl;
  return 0;
}

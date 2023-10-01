#include <iostream>
#include <string.h>
using namespace std;

enum class op_type{
  //undefined
  Undefine,

  //Reserved
  Reserved_UDF,

  //SME
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

  SME_2_MultiVector_Memory_Strided_Load_sps_2Register_LD1B,
  SME_2_MultiVector_Memory_Strided_Load_sps_2Register_LDNT1B,
  SME_2_MultiVector_Memory_Strided_Load_sps_2Register_LD1H,
  SME_2_MultiVector_Memory_Strided_Load_sps_2Register_LDNT1H,
  SME_2_MultiVector_Memory_Strided_Load_sps_2Register_LD1W,
  SME_2_MultiVector_Memory_Strided_Load_sps_2Register_LDNT1W,
  SME_2_MultiVector_Memory_Strided_Load_sps_2Register_LD1D,
  SME_2_MultiVector_Memory_Strided_Load_sps_2Register_LDNT1D,
  SME_2_MultiVector_Memory_Strided_Load_sps_4Register_LD1B,
  SME_2_MultiVector_Memory_Strided_Load_sps_4Register_LDNT1B,
  SME_2_MultiVector_Memory_Strided_Load_sps_4Register_LD1H,
  SME_2_MultiVector_Memory_Strided_Load_sps_4Register_LDNT1H,
  SME_2_MultiVector_Memory_Strided_Load_sps_4Register_LD1W,
  SME_2_MultiVector_Memory_Strided_Load_sps_4Register_LDNT1W,
  SME_2_MultiVector_Memory_Strided_Load_sps_4Register_LD1D,
  SME_2_MultiVector_Memory_Strided_Load_sps_4Register_LDNT1D,
  SME_2_MultiVector_Memory_Strided_Store_sps_2Register_ST1B,
  SME_2_MultiVector_Memory_Strided_Store_sps_2Register_STNT1B,
  SME_2_MultiVector_Memory_Strided_Store_sps_2Register_ST1H,
  SME_2_MultiVector_Memory_Strided_Store_sps_2Register_STNT1H,
  SME_2_MultiVector_Memory_Strided_Store_sps_2Register_ST1W,
  SME_2_MultiVector_Memory_Strided_Store_sps_2Register_STNT1W,
  SME_2_MultiVector_Memory_Strided_Store_sps_2Register_ST1D,
  SME_2_MultiVector_Memory_Strided_Store_sps_2Register_STNT1D,
  SME_2_MultiVector_Memory_Strided_Store_sps_4Register_ST1B,
  SME_2_MultiVector_Memory_Strided_Store_sps_4Register_STNT1B,
  SME_2_MultiVector_Memory_Strided_Store_sps_4Register_ST1H,
  SME_2_MultiVector_Memory_Strided_Store_sps_4Register_STNT1H,
  SME_2_MultiVector_Memory_Strided_Store_sps_4Register_ST1W,
  SME_2_MultiVector_Memory_Strided_Store_sps_4Register_STNT1W,
  SME_2_MultiVector_Memory_Strided_Store_sps_4Register_ST1D,
  SME_2_MultiVector_Memory_Strided_Store_sps_4Register_STNT1D,
  SME_2_MultiVector_Memory_Strided_Load_spi_2Register_LD1B,
  SME_2_MultiVector_Memory_Strided_Load_spi_2Register_LDNT1B,
  SME_2_MultiVector_Memory_Strided_Load_spi_2Register_LD1H,
  SME_2_MultiVector_Memory_Strided_Load_spi_2Register_LDNT1H,
  SME_2_MultiVector_Memory_Strided_Load_spi_2Register_LD1W,
  SME_2_MultiVector_Memory_Strided_Load_spi_2Register_LDNT1W,
  SME_2_MultiVector_Memory_Strided_Load_spi_2Register_LD1D,
  SME_2_MultiVector_Memory_Strided_Load_spi_2Register_LDNT1D,
  SME_2_MultiVector_Memory_Strided_Load_spi_4Register_LD1B,
  SME_2_MultiVector_Memory_Strided_Load_spi_4Register_LDNT1B,
  SME_2_MultiVector_Memory_Strided_Load_spi_4Register_LD1H,
  SME_2_MultiVector_Memory_Strided_Load_spi_4Register_LDNT1H,
  SME_2_MultiVector_Memory_Strided_Load_spi_4Register_LD1W,
  SME_2_MultiVector_Memory_Strided_Load_spi_4Register_LDNT1W,
  SME_2_MultiVector_Memory_Strided_Load_spi_4Register_LD1D,
  SME_2_MultiVector_Memory_Strided_Load_spi_4Register_LDNT1D,
  SME_2_MultiVector_Memory_Strided_Store_spi_2Register_ST1B,
  SME_2_MultiVector_Memory_Strided_Store_spi_2Register_STNT1B,
  SME_2_MultiVector_Memory_Strided_Store_spi_2Register_ST1H,
  SME_2_MultiVector_Memory_Strided_Store_spi_2Register_STNT1H,
  SME_2_MultiVector_Memory_Strided_Store_spi_2Register_ST1W,
  SME_2_MultiVector_Memory_Strided_Store_spi_2Register_STNT1W,
  SME_2_MultiVector_Memory_Strided_Store_spi_2Register_ST1D,
  SME_2_MultiVector_Memory_Strided_Store_spi_2Register_STNT1D,
  SME_2_MultiVector_Memory_Strided_Store_spi_4Register_ST1B,
  SME_2_MultiVector_Memory_Strided_Store_spi_4Register_STNT1B,
  SME_2_MultiVector_Memory_Strided_Store_spi_4Register_ST1H,
  SME_2_MultiVector_Memory_Strided_Store_spi_4Register_STNT1H,
  SME_2_MultiVector_Memory_Strided_Store_spi_4Register_ST1W,
  SME_2_MultiVector_Memory_Strided_Store_spi_4Register_STNT1W,
  SME_2_MultiVector_Memory_Strided_Store_spi_4Register_ST1D,
  SME_2_MultiVector_Memory_Strided_Store_spi_4Register_STNT1D,

  SME_MoveIntoArray_MOVA_2Register,
  SME_MoveIntoArray_MOVA_4Register,
  SME_MoveIntoArray_MoveVectorToArray,
  SME_MoveIntoArray_2_MoveVectorToTitle_2Register,
  SME_MoveIntoArray_2_MoveVectorToTitle_4Register,

  SME_MoveFromArray_MOVA_2Register,
  SME_MoveFromArray_MOVA_4Register,
  SME_MoveFromArray_MoveArrayToVector,
  SME_MoveFromArray_2_MoveTitleToVector_2Register,
  SME_MoveFromArray_2_MoveTitleToVector_4Register,

  SME_AddVectorToArray_ADDHA_FEAT_SME,
  SME_AddVectorToArray_ADDVA_FEAT_SME,
  SME_AddVectorToArray_ADDHA_FEAT_SME_I16I64,
  SME_AddVectorToArray_ADDVA_FEAT_SME_I16I64,

  SME_Zero,

  SME_2_Zero_LookupTable,

  SME_2_Move_LookupTable_From_MOVT,
  SME_2_Move_LookupTable_Into_MOVT,

  SME_2_Expand_LookupTable_Continguous_4Register_LUTI4,
  SME_2_Expand_LookupTable_Continguous_4Register_LUTI2,
  SME_2_Expand_LookupTable_Continguous_2Register_LUTI4,
  SME_2_Expand_LookupTable_Continguous_2Register_LUTI2,
  SME_2_Expand_LookupTable_Continguous_1Register_LUTI4,
  SME_2_Expand_LookupTable_Continguous_1Register_LUTI2,

  SME_2_MultiVector_Indexed_1Register_longMLA_32bit_SMLALL,
  SME_2_MultiVector_Indexed_1Register_longMLA_32bit_USMLALL,
  SME_2_MultiVector_Indexed_1Register_longMLA_32bit_SMLSLL,
  SME_2_MultiVector_Indexed_1Register_longMLA_32bit_UMLALL,
  SME_2_MultiVector_Indexed_1Register_longMLA_32bit_SUMLALL,
  SME_2_MultiVector_Indexed_1Register_longMLA_32bit_UMLSLL,
  SME_2_MultiVector_Indexed_1Register_longMLA_64bit_SMLALL,
  SME_2_MultiVector_Indexed_1Register_longMLA_64bit_SMLSLL,
  SME_2_MultiVector_Indexed_1Register_longMLA_64bit_UMLALL,
  SME_2_MultiVector_Indexed_1Register_longMLA_64bit_UMLSLL,
  SME_2_MultiVector_Indexed_1Register_longFMA_FMLAL,
  SME_2_MultiVector_Indexed_1Register_longFMA_FMLSL,
  SME_2_MultiVector_Indexed_1Register_longFMA_BFMLAL,
  SME_2_MultiVector_Indexed_1Register_longFMA_BFMLSL,
  SME_2_MultiVector_Indexed_1Register_longMLA_SMLAL,
  SME_2_MultiVector_Indexed_1Register_longMLA_SMLSL,
  SME_2_MultiVector_Indexed_1Register_longMLA_UMLAL,
  SME_2_MultiVector_Indexed_1Register_longMLA_UMLSL,

  SME_2_MultiVector_Indexed_2Register_llongMLA_ts_32bit_SMLALL,
  SME_2_MultiVector_Indexed_2Register_llongMLA_ts_32bit_SMLSLL,
  SME_2_MultiVector_Indexed_2Register_llongMLA_ts_32bit_UMLALL,
  SME_2_MultiVector_Indexed_2Register_llongMLA_ts_32bit_UMLSLL,
  SME_2_MultiVector_Indexed_2Register_llongMLA_ts_32bit_USMLALL,
  SME_2_MultiVector_Indexed_2Register_llongMLA_ts_32bit_SUMLALL,
  SME_2_MultiVector_Indexed_2Register_Ternary_32bit_FMLA,
  SME_2_MultiVector_Indexed_2Register_Ternary_32bit_FVDOT,
  SME_2_MultiVector_Indexed_2Register_Ternary_32bit_FMLS,
  SME_2_MultiVector_Indexed_2Register_Ternary_32bit_BFVDOT,
  SME_2_MultiVector_Indexed_2Register_Ternary_32bit_SVDOT,
  SME_2_MultiVector_Indexed_2Register_Ternary_32bit_UVDOT,
  SME_2_MultiVector_Indexed_2Register_Ternary_32bit_SDOT2,
  SME_2_MultiVector_Indexed_2Register_Ternary_32bit_FDOT,
  SME_2_MultiVector_Indexed_2Register_Ternary_32bit_UDOT,
  SME_2_MultiVector_Indexed_2Register_Ternary_32bit_BFDOT,
  SME_2_MultiVector_Indexed_2Register_Ternary_32bit_SDOT4,
  SME_2_MultiVector_Indexed_2Register_Ternary_32bit_USDOT,
  SME_2_MultiVector_Indexed_2Register_Ternary_32bit_UDOT,
  SME_2_MultiVector_Indexed_2Register_Ternary_32bit_SUDOT,
  SME_2_MultiVector_Indexed_2Register_llongMLA_ts_64bit_SMLALL,
  SME_2_MultiVector_Indexed_2Register_llongMLA_ts_64bit_SMLSLL,
  SME_2_MultiVector_Indexed_2Register_llongMLA_ts_64bit_UMLALL,
  SME_2_MultiVector_Indexed_2Register_llongMLA_ts_64bit_UMLSLL,
  SME_2_MultiVector_Indexed_2Register_longFMA_ts_FMLAL,
  SME_2_MultiVector_Indexed_2Register_longFMA_ts_FMLSL,
  SME_2_MultiVector_Indexed_2Register_longFMA_ts_BFMLAL,
  SME_2_MultiVector_Indexed_2Register_longFMA_ts_BFMLSL,
  SME_2_MultiVector_Indexed_2Register_Ternary_64bit_FMLA,
  SME_2_MultiVector_Indexed_2Register_Ternary_64bit_SDOT,
  SME_2_MultiVector_Indexed_2Register_Ternary_64bit_FMLS,
  SME_2_MultiVector_Indexed_2Register_Ternary_64bit_UDOT,
  SME_2_MultiVector_Indexed_2Register_longMLA_ts_SMLAL,
  SME_2_MultiVector_Indexed_2Register_longMLA_ts_SMLSL,
  SME_2_MultiVector_Indexed_2Register_longMLA_ts_UMLAL,
  SME_2_MultiVector_Indexed_2Register_longMLA_ts_UMLSL,

  SME_2_MultiVector_Indexed_4Register_llongMLA_fs_32bit_SMLALL,
  SME_2_MultiVector_Indexed_4Register_llongMLA_fs_32bit_SMLSLL,
  SME_2_MultiVector_Indexed_4Register_llongMLA_fs_32bit_UMLALL,
  SME_2_MultiVector_Indexed_4Register_llongMLA_fs_32bit_UMLSLL,
  SME_2_MultiVector_Indexed_4Register_llongMLA_fs_32bit_USMLALL,
  SME_2_MultiVector_Indexed_4Register_llongMLA_fs_32bit_SUMLALL,
  SME_2_MultiVector_Indexed_4Register_Ternary_32bit_FMLA,
  SME_2_MultiVector_Indexed_4Register_Ternary_32bit_FMLS,
  SME_2_MultiVector_Indexed_4Register_Ternary_32bit_SVDOT,
  SME_2_MultiVector_Indexed_4Register_Ternary_32bit_USVDOT,
  SME_2_MultiVector_Indexed_4Register_Ternary_32bit_UVDOT,
  SME_2_MultiVector_Indexed_4Register_Ternary_32bit_SUVDOT,
  SME_2_MultiVector_Indexed_4Register_Ternary_32bit_SDOT2,
  SME_2_MultiVector_Indexed_4Register_Ternary_32bit_FDOT,
  SME_2_MultiVector_Indexed_4Register_Ternary_32bit_UDOT2,
  SME_2_MultiVector_Indexed_4Register_Ternary_32bit_BFDOT,
  SME_2_MultiVector_Indexed_4Register_Ternary_32bit_SDOT4,
  SME_2_MultiVector_Indexed_4Register_Ternary_32bit_USDOT,
  SME_2_MultiVector_Indexed_4Register_Ternary_32bit_UDOT4,
  SME_2_MultiVector_Indexed_4Register_Ternary_32bit_SUDOT,
  SME_2_MultiVector_Indexed_4Register_llongMLA_fs_64bit_SMLALL,
  SME_2_MultiVector_Indexed_4Register_llongMLA_fs_64bit_SMLSLL,
  SME_2_MultiVector_Indexed_4Register_llongMLA_fs_64bit_UMLALL,
  SME_2_MultiVector_Indexed_4Register_llongMLA_fs_64bit_UMLSLL,
  SME_2_MultiVector_Indexed_4Register_longFMA_fs_FMLAL,
  SME_2_MultiVector_Indexed_4Register_longFMA_fs_FMLSL,
  SME_2_MultiVector_Indexed_4Register_longFMA_fs_BFMLAL,
  SME_2_MultiVector_Indexed_4Register_longFMA_fs_BFMLSL,
  SME_2_MultiVector_Indexed_4Register_Ternary_64bit_FMLA,
  SME_2_MultiVector_Indexed_4Register_Ternary_64bit_SDOT,
  SME_2_MultiVector_Indexed_4Register_Ternary_64bit_FMLS,
  SME_2_MultiVector_Indexed_4Register_Ternary_64bit_UDOT,
  SME_2_MultiVector_Indexed_4Register_Ternary_64bit_SVDOT,
  SME_2_MultiVector_Indexed_4Register_Ternary_64bit_UVDOT,
  SME_2_MultiVector_Indexed_4Register_longMLA_fs_SMLAL,
  SME_2_MultiVector_Indexed_4Register_longMLA_fs_SMLSL,
  SME_2_MultiVector_Indexed_4Register_longMLA_fs_UMLAL,
  SME_2_MultiVector_Indexed_4Register_longMLA_fs_UMLSL,

  SME_2_MultiVector_SVE_Select_SEL,

  SME_2_MultiVector_SVE_Constructive_Binary_QuadwordsZIP_2Register_ZIP,
  SME_2_MultiVector_SVE_Constructive_Binary_QuadwordsZIP_2Register_UZP,
  SME_2_MultiVector_SVE_Constructive_Binary_SaturatingShiftRight_2Register_SQRSHR,
  SME_2_MultiVector_SVE_Constructive_Binary_SaturatingShiftRight_2Register_UQRSHR,
  SME_2_MultiVector_SVE_Constructive_Binary_SaturatingShiftRight_2Register_SQRSHRU,
  SME_2_MultiVector_SVE_Constructive_Binary_FCLAMP,
  SME_2_MultiVector_SVE_Constructive_Binary_CLAMP_2Register_SCLAMP,
  SME_2_MultiVector_SVE_Constructive_Binary_CLAMP_2Register_UCLAMP,
  SME_2_MultiVector_SVE_Constructive_Binary_CLAMP_4Register_SCLAMP,
  SME_2_MultiVector_SVE_Constructive_Binary_CLAMP_4Register_UCLAMP,
  SME_2_MultiVector_SVE_Constructive_Binary_ZIP_2Register_ZIP,
  SME_2_MultiVector_SVE_Constructive_Binary_ZIP_2Register_UZP,
  SME_2_MultiVector_SVE_Constructive_Binary_SaturatingShiftRight_4Register_SQRSHR,
  SME_2_MultiVector_SVE_Constructive_Binary_SaturatingShiftRight_4Register_UQRSHR,
  SME_2_MultiVector_SVE_Constructive_Binary_SaturatingShiftRight_4Register_SQRSHRU,
  SME_2_MultiVector_SVE_Constructive_Binary_SaturatingShiftRight_4Register_SQRSHRN,
  SME_2_MultiVector_SVE_Constructive_Binary_SaturatingShiftRight_4Register_UQRSHRN,
  SME_2_MultiVector_SVE_Constructive_Binary_SaturatingShiftRight_4Register_SQRSHRUN,

  SME_2_MultiVector_SVE_Constructive_Unary_FPToIntConvert_2Register_FCVTZS,
  SME_2_MultiVector_SVE_Constructive_Unary_FPToIntConvert_2Register_FCVTZU,
  SME_2_MultiVector_SVE_Constructive_Unary_IntToFP_2Register_SCVTF,
  SME_2_MultiVector_SVE_Constructive_Unary_IntToFP_2Register_UCVTF,
  SME_2_MultiVector_SVE_Constructive_Unary_FPToIntConvert_4Register_FCVTZS,
  SME_2_MultiVector_SVE_Constructive_Unary_FPToIntConvert_4Register_FCVTZU,
  SME_2_MultiVector_SVE_Constructive_Unary_IntToFP_4Register_SCVTF,
  SME_2_MultiVector_SVE_Constructive_Unary_IntToFP_4Register_UCVTF,
  SME_2_MultiVector_SVE_Constructive_Unary_QuadwordZIP_4Register_ZIP,
  SME_2_MultiVector_SVE_Constructive_Unary_QuadwordZIP_4Register_UZP,
  SME_2_MultiVector_SVE_Constructive_Unary_FPdownConvert_2Register_FCVT,
  SME_2_MultiVector_SVE_Constructive_Unary_FPdownConvert_2Register_FCVTN,
  SME_2_MultiVector_SVE_Constructive_Unary_FPdownConvert_2Register_BFCVT,
  SME_2_MultiVector_SVE_Constructive_Unary_FPdownConvert_2Register_BFCVTN,
  SME_2_MultiVector_SVE_Constructive_Unary_IntDownConvert_2Regiter_SQCVT,
  SME_2_MultiVector_SVE_Constructive_Unary_IntDownConvert_2Regiter_UQCVT,
  SME_2_MultiVector_SVE_Constructive_Unary_IntDownConvert_2Regiter_SQCVTU,
  SME_2_MultiVector_SVE_Constructive_Unary_Unpack_2Register_SUNPK,
  SME_2_MultiVector_SVE_Constructive_Unary_Unpack_2Register_UUNPK,
  SME_2_MultiVector_SVE_Constructive_Unary_FRINT_2Register_FRINTN,
  SME_2_MultiVector_SVE_Constructive_Unary_FRINT_2Register_FRINTP,
  SME_2_MultiVector_SVE_Constructive_Unary_FRINT_2Register_FRINTM,
  SME_2_MultiVector_SVE_Constructive_Unary_FRINT_2Register_FRINTA,
  SME_2_MultiVector_SVE_Constructive_Unary_IntDownConvert_4Register_SQCVT,
  SME_2_MultiVector_SVE_Constructive_Unary_IntDownConvert_4Register_UQCVT,
  SME_2_MultiVector_SVE_Constructive_Unary_IntDownConvert_4Register_SQCVTN,
  SME_2_MultiVector_SVE_Constructive_Unary_IntDownConvert_4Register_UQCVTN,
  SME_2_MultiVector_SVE_Constructive_Unary_IntDownConvert_4Register_SQCVTU,
  SME_2_MultiVector_SVE_Constructive_Unary_IntDownConvert_4Register_SQCVTUN,
  SME_2_MultiVector_SVE_Constructive_Unary_Unpack_4Register_SUNPK,
  SME_2_MultiVector_SVE_Constructive_Unary_Unpack_4Register_UUNPK,
  SME_2_MultiVector_SVE_Constructive_Unary_ZIP_4Register_ZIP,
  SME_2_MultiVector_SVE_Constructive_Unary_ZIP_4Register_UZP,
  SME_2_MultiVector_SVE_Constructive_Unary_FRINT_4Register_FRINTN,
  SME_2_MultiVector_SVE_Constructive_Unary_FRINT_4Register_FRINTP,
  SME_2_MultiVector_SVE_Constructive_Unary_FRINT_4Register_FRINTM,
  SME_2_MultiVector_SVE_Constructive_Unary_FRINT_4Register_FRINTA,
  
  SME_2_MultiVector_MultiVector_SVE_Destructive_2Register_IntMinMax_SMAX,
  SME_2_MultiVector_MultiVector_SVE_Destructive_2Register_IntMinMax_UMAX,
  SME_2_MultiVector_MultiVector_SVE_Destructive_2Register_IntMinMax_SMIN,
  SME_2_MultiVector_MultiVector_SVE_Destructive_2Register_IntMinMax_UMIN,
  SME_2_MultiVector_MultiVector_SVE_Destructive_2Register_FPMinMax_FMAX,
  SME_2_MultiVector_MultiVector_SVE_Destructive_2Register_FPMinMax_FMIN,
  SME_2_MultiVector_MultiVector_SVE_Destructive_2Register_FPMinMax_FMAXNM,
  SME_2_MultiVector_MultiVector_SVE_Destructive_2Register_FPMinMax_FMINNM,
  SME_2_MultiVector_MultiVector_SVE_Destructive_2Register_Shift_SRSHL,
  SME_2_MultiVector_MultiVector_SVE_Destructive_2Register_Shift_URSHL,
  SME_2_MultiVector_MultiVector_SVE_Destructive_2Register_SQDMULH,

  SME_2_MultiVector_MultiVector_SVE_Destructive_4Register_IntMinMax_SMAX,
  SME_2_MultiVector_MultiVector_SVE_Destructive_4Register_IntMinMax_UMAX,
  SME_2_MultiVector_MultiVector_SVE_Destructive_4Register_IntMinMax_SMIN,
  SME_2_MultiVector_MultiVector_SVE_Destructive_4Register_IntMinMax_UMIN,
  SME_2_MultiVector_MultiVector_SVE_Destructive_4Register_FPMinMax_FMAX,
  SME_2_MultiVector_MultiVector_SVE_Destructive_4Register_FPMinMax_FMIN,
  SME_2_MultiVector_MultiVector_SVE_Destructive_4Register_FPMinMax_FMAXNM,
  SME_2_MultiVector_MultiVector_SVE_Destructive_4Register_FPMinMax_FMINNM,
  SME_2_MultiVector_MultiVector_SVE_Destructive_4Register_Shift_SRSHL,
  SME_2_MultiVector_MultiVector_SVE_Destructive_4Register_Shift_URSHL,
  SME_2_MultiVector_MultiVector_SVE_Destructive_4Register_SQDMULH,

  SME_2_MultiVector_MultiAndSingleVector_SVE_Destructive_2Register_IntMinMax_SMAX,
  SME_2_MultiVector_MultiAndSingleVector_SVE_Destructive_2Register_IntMinMax_UMAX,
  SME_2_MultiVector_MultiAndSingleVector_SVE_Destructive_2Register_IntMinMax_SMIN,
  SME_2_MultiVector_MultiAndSingleVector_SVE_Destructive_2Register_IntMinMax_UMIN,
  SME_2_MultiVector_MultiAndSingleVector_SVE_Destructive_2Register_FPMinMax_FMAX,
  SME_2_MultiVector_MultiAndSingleVector_SVE_Destructive_2Register_FPMinMax_FMIN,
  SME_2_MultiVector_MultiAndSingleVector_SVE_Destructive_2Register_FPMinMax_FMAXNM,
  SME_2_MultiVector_MultiAndSingleVector_SVE_Destructive_2Register_FPMinMax_FMINNM,
  SME_2_MultiVector_MultiAndSingleVector_SVE_Destructive_2Register_Shift_SRSHL,
  SME_2_MultiVector_MultiAndSingleVector_SVE_Destructive_2Register_Shift_URSHL,
  SME_2_MultiVector_MultiAndSingleVector_SVE_Destructive_2Register_ADD,
  SME_2_MultiVector_MultiAndSingleVector_SVE_Destructive_2Register_SQDMULH,

  SME_2_MultiVector_MultiAndSingleVector_SVE_Destructive_4Register,
  SME_2_MultiVector_MultiAndSingle_ArrayVectors,
  SME_2_MultiVector_Multiple_ArrayVectors_2Register,
  SME_2_MultiVector_Multiple_ArrayVectors_4Register,
  SME_Memory,
  
  //SVP
  SVP,

  //DataProcessing_Immidate
  DataProcessing_Immidate,

  //Branch or ExeptionSystemInstruction
  Branch_or_ExeptionSystemInstruction,

  //Load and Store
  Load_or_Store,

  //DataProcessing_Register
  DataProcessing_Register,

  //DataProcessing_ScalarFloat and SIMD
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

        if(is1(inst, ssop1) && !is1(inst, ssop2)){
          constexpr int msz0 = 14;
          constexpr int msz1 = 13;
          constexpr int N = 0;
          constexpr op_type oparr[2][2][2] =
              {
                  {{op_type::SME_2_MultiVector_Memory_Continguous_Load_sps_4Register_LD1B,
                    op_type::SME_2_MultiVector_Memory_Continguous_Load_sps_4Register_LDNT1B},
                   {op_type::SME_2_MultiVector_Memory_Continguous_Load_sps_4Register_LD1H,
                    op_type::SME_2_MultiVector_Memory_Continguous_Load_sps_4Register_LDNT1H}},
                  {{op_type::SME_2_MultiVector_Memory_Continguous_Load_sps_4Register_LD1W,
                    op_type::SME_2_MultiVector_Memory_Continguous_Load_sps_4Register_LDNT1W},
                   {op_type::SME_2_MultiVector_Memory_Continguous_Load_sps_4Register_LD1D,
                    op_type::SME_2_MultiVector_Memory_Continguous_Load_sps_4Register_LDNT1D}}};
          int ind[3] = {
              is1(inst, msz0) ? 1 : 0,
              is1(inst,msz1) ? 1 : 0,
              is1(inst, N) ? 1 : 0};
          return gii(oparr[ind[0]][ind[1]][ind[2]], inst);
        }
      }
      if (masking(inst, ssop0, "01x"))
      {
        if(!is1(inst, ssop1)){
          constexpr int msz0 = 14;
          constexpr int msz1 = 13;
          constexpr int N = 0;
          constexpr op_type oparr[2][2][2] =
              {
                  {{op_type::SME_2_MultiVector_Memory_Continguous_Store_sps_2Register_ST1B,
                    op_type::SME_2_MultiVector_Memory_Continguous_Store_sps_2Register_STNT1B},
                   {op_type::SME_2_MultiVector_Memory_Continguous_Store_sps_2Register_ST1H,
                    op_type::SME_2_MultiVector_Memory_Continguous_Store_sps_2Register_STNT1H}},
                  {{op_type::SME_2_MultiVector_Memory_Continguous_Store_sps_2Register_ST1W,
                    op_type::SME_2_MultiVector_Memory_Continguous_Store_sps_2Register_STNT1W},
                   {op_type::SME_2_MultiVector_Memory_Continguous_Store_sps_2Register_ST1D,
                    op_type::SME_2_MultiVector_Memory_Continguous_Store_sps_2Register_STNT1D}}};
          int ind[3] = {
              is1(inst, msz0) ? 1 : 0,
              is1(inst,msz1) ? 1 : 0,
              is1(inst, N) ? 1 : 0};
          return gii(oparr[ind[0]][ind[1]][ind[2]], inst);
        }

        if(is1(inst, ssop1) && !is1(inst, ssop2)){
          constexpr int msz0 = 14;
          constexpr int msz1 = 13;
          constexpr int N = 0;
          constexpr op_type oparr[2][2][2] =
              {
                  {{op_type::SME_2_MultiVector_Memory_Continguous_Store_sps_4Register_ST1B,
                    op_type::SME_2_MultiVector_Memory_Continguous_Store_sps_4Register_STNT1B},
                   {op_type::SME_2_MultiVector_Memory_Continguous_Store_sps_4Register_ST1H,
                    op_type::SME_2_MultiVector_Memory_Continguous_Store_sps_4Register_STNT1H}},
                  {{op_type::SME_2_MultiVector_Memory_Continguous_Store_sps_4Register_ST1W,
                    op_type::SME_2_MultiVector_Memory_Continguous_Store_sps_4Register_STNT1W},
                   {op_type::SME_2_MultiVector_Memory_Continguous_Store_sps_4Register_ST1D,
                    op_type::SME_2_MultiVector_Memory_Continguous_Store_sps_4Register_STNT1D}}};
          int ind[3] = {
              is1(inst, msz0) ? 1 : 0,
              is1(inst,msz1) ? 1 : 0,
              is1(inst, N) ? 1 : 0};
          return gii(oparr[ind[0]][ind[1]][ind[2]], inst);
        }
      }
      if(masking(inst, ssop0, "100")){
        if(!is1(inst, ssop1)){
          constexpr int msz0 = 14;
          constexpr int msz1 = 13;
          constexpr int N = 0;
          constexpr op_type oparr[2][2][2] =
              {
                  {{op_type::SME_2_MultiVector_Memory_Continguous_Load_spi_2Register_LD1B,
                    op_type::SME_2_MultiVector_Memory_Continguous_Load_spi_2Register_LDNT1B},
                   {op_type::SME_2_MultiVector_Memory_Continguous_Load_spi_2Register_LD1H,
                    op_type::SME_2_MultiVector_Memory_Continguous_Load_spi_2Register_LDNT1H}},
                  {{op_type::SME_2_MultiVector_Memory_Continguous_Load_spi_2Register_LD1W,
                    op_type::SME_2_MultiVector_Memory_Continguous_Load_spi_2Register_LDNT1W},
                   {op_type::SME_2_MultiVector_Memory_Continguous_Load_spi_2Register_LD1D,
                    op_type::SME_2_MultiVector_Memory_Continguous_Load_spi_2Register_LDNT1D}}};
          int ind[3] = {
              is1(inst, msz0) ? 1 : 0,
              is1(inst,msz1) ? 1 : 0,
              is1(inst, N) ? 1 : 0};
          return gii(oparr[ind[0]][ind[1]][ind[2]], inst);
        }

        if(is1(inst, ssop1) && !is1(inst, ssop2)){
          constexpr int msz0 = 14;
          constexpr int msz1 = 13;
          constexpr int N = 0;
          constexpr op_type oparr[2][2][2] =
              {
                  {{op_type::SME_2_MultiVector_Memory_Continguous_Load_sps_4Register_LD1B,
                    op_type::SME_2_MultiVector_Memory_Continguous_Load_sps_4Register_LDNT1B},
                   {op_type::SME_2_MultiVector_Memory_Continguous_Load_sps_4Register_LD1H,
                    op_type::SME_2_MultiVector_Memory_Continguous_Load_sps_4Register_LDNT1H}},
                  {{op_type::SME_2_MultiVector_Memory_Continguous_Load_sps_4Register_LD1W,
                    op_type::SME_2_MultiVector_Memory_Continguous_Load_sps_4Register_LDNT1W},
                   {op_type::SME_2_MultiVector_Memory_Continguous_Load_sps_4Register_LD1D,
                    op_type::SME_2_MultiVector_Memory_Continguous_Load_sps_4Register_LDNT1D}}};
          int ind[3] = {
              is1(inst, msz0) ? 1 : 0,
              is1(inst,msz1) ? 1 : 0,
              is1(inst, N) ? 1 : 0};
          return gii(oparr[ind[0]][ind[1]][ind[2]], inst);
        }
      }
      if(masking(inst, ssop0, "110")){
        if(!is1(inst, ssop1)){
          constexpr int msz0 = 14;
          constexpr int msz1 = 13;
          constexpr int N = 0;
          constexpr op_type oparr[2][2][2] =
              {
                  {{op_type::SME_2_MultiVector_Memory_Continguous_Store_spi_2Register_ST1B,
                    op_type::SME_2_MultiVector_Memory_Continguous_Store_spi_2Register_STNT1B},
                   {op_type::SME_2_MultiVector_Memory_Continguous_Store_spi_2Register_ST1H,
                    op_type::SME_2_MultiVector_Memory_Continguous_Store_spi_2Register_STNT1H}},
                  {{op_type::SME_2_MultiVector_Memory_Continguous_Store_spi_2Register_ST1W,
                    op_type::SME_2_MultiVector_Memory_Continguous_Store_spi_2Register_STNT1W},
                   {op_type::SME_2_MultiVector_Memory_Continguous_Store_spi_2Register_ST1D,
                    op_type::SME_2_MultiVector_Memory_Continguous_Store_spi_2Register_STNT1D}}};
          int ind[3] = {
              is1(inst, msz0) ? 1 : 0,
              is1(inst,msz1) ? 1 : 0,
              is1(inst, N) ? 1 : 0};
          return gii(oparr[ind[0]][ind[1]][ind[2]], inst);
        }

        if(is1(inst, ssop1) && !is1(inst, ssop2)){
          constexpr int msz0 = 14;
          constexpr int msz1 = 13;
          constexpr int N = 0;
          constexpr op_type oparr[2][2][2] =
              {
                  {{op_type::SME_2_MultiVector_Memory_Continguous_Store_spi_4Register_ST1B,
                    op_type::SME_2_MultiVector_Memory_Continguous_Store_spi_4Register_STNT1B},
                   {op_type::SME_2_MultiVector_Memory_Continguous_Store_spi_4Register_ST1H,
                    op_type::SME_2_MultiVector_Memory_Continguous_Store_spi_4Register_STNT1H}},
                  {{op_type::SME_2_MultiVector_Memory_Continguous_Store_spi_4Register_ST1W,
                    op_type::SME_2_MultiVector_Memory_Continguous_Store_spi_4Register_STNT1W},
                   {op_type::SME_2_MultiVector_Memory_Continguous_Store_spi_4Register_ST1D,
                    op_type::SME_2_MultiVector_Memory_Continguous_Store_spi_4Register_STNT1D}}};
          int ind[3] = {
              is1(inst, msz0) ? 1 : 0,
              is1(inst,msz1) ? 1 : 0,
              is1(inst, N) ? 1 : 0};
          return gii(oparr[ind[0]][ind[1]][ind[2]], inst);
        }
      }
    }
    if(masking(inst, sop1, "10>")){
      //return gii(op_type::SME_2_MultiVector_Memory_Strided, inst);
      constexpr op_range ssop0 = {20, 22};
      constexpr int ssop1 = 15;
      constexpr int ssop2 = 2;
      if(masking(inst, ssop0, "00x")){
        if(!is1(inst, ssop1)){
          constexpr int msz0 = 14;
          constexpr int msz1 = 13;
          constexpr int N = 3;
          constexpr op_type oparr[2][2][2] =
              {
                  {{op_type::SME_2_MultiVector_Memory_Strided_Load_sps_2Register_LD1B,
                    op_type::SME_2_MultiVector_Memory_Strided_Load_sps_2Register_LDNT1B},
                   {op_type::SME_2_MultiVector_Memory_Strided_Load_sps_2Register_LD1H,
                    op_type::SME_2_MultiVector_Memory_Strided_Load_sps_2Register_LDNT1H}},
                  {{op_type::SME_2_MultiVector_Memory_Strided_Load_sps_2Register_LD1W,
                    op_type::SME_2_MultiVector_Memory_Strided_Load_sps_2Register_LDNT1W},
                   {op_type::SME_2_MultiVector_Memory_Strided_Load_sps_2Register_LD1D,
                    op_type::SME_2_MultiVector_Memory_Strided_Load_sps_2Register_LDNT1D}}};
          int ind[3] = {
              is1(inst, msz0) ? 1 : 0,
              is1(inst,msz1) ? 1 : 0,
              is1(inst, N) ? 1 : 0};
          return gii(oparr[ind[0]][ind[1]][ind[2]], inst);
        }

        if(is1(inst, ssop1) && !is1(inst, ssop2)){
          constexpr int msz0 = 14;
          constexpr int msz1 = 13;
          constexpr int N = 3;
          constexpr op_type oparr[2][2][2] =
              {
                  {{op_type::SME_2_MultiVector_Memory_Strided_Load_sps_4Register_LD1B,
                    op_type::SME_2_MultiVector_Memory_Strided_Load_sps_4Register_LDNT1B},
                   {op_type::SME_2_MultiVector_Memory_Strided_Load_sps_4Register_LD1H,
                    op_type::SME_2_MultiVector_Memory_Strided_Load_sps_4Register_LDNT1H}},
                  {{op_type::SME_2_MultiVector_Memory_Strided_Load_sps_4Register_LD1W,
                    op_type::SME_2_MultiVector_Memory_Strided_Load_sps_4Register_LDNT1W},
                   {op_type::SME_2_MultiVector_Memory_Strided_Load_sps_4Register_LD1D,
                    op_type::SME_2_MultiVector_Memory_Strided_Load_sps_4Register_LDNT1D}}};
          int ind[3] = {
              is1(inst, msz0) ? 1 : 0,
              is1(inst,msz1) ? 1 : 0,
              is1(inst, N) ? 1 : 0};
          return gii(oparr[ind[0]][ind[1]][ind[2]], inst);
        }
      }
      if (masking(inst, ssop0, "01x"))
      {
        if(!is1(inst, ssop1)){
          constexpr int msz0 = 14;
          constexpr int msz1 = 13;
          constexpr int N = 3;
          constexpr op_type oparr[2][2][2] =
              {
                  {{op_type::SME_2_MultiVector_Memory_Strided_Store_sps_2Register_ST1B,
                    op_type::SME_2_MultiVector_Memory_Strided_Store_sps_2Register_STNT1B},
                   {op_type::SME_2_MultiVector_Memory_Strided_Store_sps_2Register_ST1H,
                    op_type::SME_2_MultiVector_Memory_Strided_Store_sps_2Register_STNT1H}},
                  {{op_type::SME_2_MultiVector_Memory_Strided_Store_sps_2Register_ST1W,
                    op_type::SME_2_MultiVector_Memory_Strided_Store_sps_2Register_STNT1W},
                   {op_type::SME_2_MultiVector_Memory_Strided_Store_sps_2Register_ST1D,
                    op_type::SME_2_MultiVector_Memory_Strided_Store_sps_2Register_STNT1D}}};
          int ind[3] = {
              is1(inst, msz0) ? 1 : 0,
              is1(inst,msz1) ? 1 : 0,
              is1(inst, N) ? 1 : 0};
          return gii(oparr[ind[0]][ind[1]][ind[2]], inst);
        }

        if(is1(inst, ssop1) && !is1(inst, ssop2)){
          constexpr int msz0 = 14;
          constexpr int msz1 = 13;
          constexpr int N = 3;
          constexpr op_type oparr[2][2][2] =
              {
                  {{op_type::SME_2_MultiVector_Memory_Strided_Store_sps_4Register_ST1B,
                    op_type::SME_2_MultiVector_Memory_Strided_Store_sps_4Register_STNT1B},
                   {op_type::SME_2_MultiVector_Memory_Strided_Store_sps_4Register_ST1H,
                    op_type::SME_2_MultiVector_Memory_Strided_Store_sps_4Register_STNT1H}},
                  {{op_type::SME_2_MultiVector_Memory_Strided_Store_sps_4Register_ST1W,
                    op_type::SME_2_MultiVector_Memory_Strided_Store_sps_4Register_STNT1W},
                   {op_type::SME_2_MultiVector_Memory_Strided_Store_sps_4Register_ST1D,
                    op_type::SME_2_MultiVector_Memory_Strided_Store_sps_4Register_STNT1D}}};
          int ind[3] = {
              is1(inst, msz0) ? 1 : 0,
              is1(inst,msz1) ? 1 : 0,
              is1(inst, N) ? 1 : 0};
          return gii(oparr[ind[0]][ind[1]][ind[2]], inst);
        }
      }
      if(masking(inst, ssop0, "100")){
        if(!is1(inst, ssop1)){
          constexpr int msz0 = 14;
          constexpr int msz1 = 13;
          constexpr int N = 3;
          constexpr op_type oparr[2][2][2] =
              {
                  {{op_type::SME_2_MultiVector_Memory_Strided_Load_spi_2Register_LD1B,
                    op_type::SME_2_MultiVector_Memory_Strided_Load_spi_2Register_LDNT1B},
                   {op_type::SME_2_MultiVector_Memory_Strided_Load_spi_2Register_LD1H,
                    op_type::SME_2_MultiVector_Memory_Strided_Load_spi_2Register_LDNT1H}},
                  {{op_type::SME_2_MultiVector_Memory_Strided_Load_spi_2Register_LD1W,
                    op_type::SME_2_MultiVector_Memory_Strided_Load_spi_2Register_LDNT1W},
                   {op_type::SME_2_MultiVector_Memory_Strided_Load_spi_2Register_LD1D,
                    op_type::SME_2_MultiVector_Memory_Strided_Load_spi_2Register_LDNT1D}}};
          int ind[3] = {
              is1(inst, msz0) ? 1 : 0,
              is1(inst,msz1) ? 1 : 0,
              is1(inst, N) ? 1 : 0};
          return gii(oparr[ind[0]][ind[1]][ind[2]], inst);
        }

        if(is1(inst, ssop1) && !is1(inst, ssop2)){
          constexpr int msz0 = 14;
          constexpr int msz1 = 13;
          constexpr int N = 3;
          constexpr op_type oparr[2][2][2] =
              {
                  {{op_type::SME_2_MultiVector_Memory_Strided_Load_sps_4Register_LD1B,
                    op_type::SME_2_MultiVector_Memory_Strided_Load_sps_4Register_LDNT1B},
                   {op_type::SME_2_MultiVector_Memory_Strided_Load_sps_4Register_LD1H,
                    op_type::SME_2_MultiVector_Memory_Strided_Load_sps_4Register_LDNT1H}},
                  {{op_type::SME_2_MultiVector_Memory_Strided_Load_sps_4Register_LD1W,
                    op_type::SME_2_MultiVector_Memory_Strided_Load_sps_4Register_LDNT1W},
                   {op_type::SME_2_MultiVector_Memory_Strided_Load_sps_4Register_LD1D,
                    op_type::SME_2_MultiVector_Memory_Strided_Load_sps_4Register_LDNT1D}}};
          int ind[3] = {
              is1(inst, msz0) ? 1 : 0,
              is1(inst,msz1) ? 1 : 0,
              is1(inst, N) ? 1 : 0};
          return gii(oparr[ind[0]][ind[1]][ind[2]], inst);
        }
      }
      if(masking(inst, ssop0, "110")){
        if(!is1(inst, ssop1)){
          constexpr int msz0 = 14;
          constexpr int msz1 = 13;
          constexpr int N = 0;
          constexpr op_type oparr[2][2][2] =
              {
                  {{op_type::SME_2_MultiVector_Memory_Strided_Store_spi_2Register_ST1B,
                    op_type::SME_2_MultiVector_Memory_Strided_Store_spi_2Register_STNT1B},
                   {op_type::SME_2_MultiVector_Memory_Strided_Store_spi_2Register_ST1H,
                    op_type::SME_2_MultiVector_Memory_Strided_Store_spi_2Register_STNT1H}},
                  {{op_type::SME_2_MultiVector_Memory_Strided_Store_spi_2Register_ST1W,
                    op_type::SME_2_MultiVector_Memory_Strided_Store_spi_2Register_STNT1W},
                   {op_type::SME_2_MultiVector_Memory_Strided_Store_spi_2Register_ST1D,
                    op_type::SME_2_MultiVector_Memory_Strided_Store_spi_2Register_STNT1D}}};
          int ind[3] = {
              is1(inst, msz0) ? 1 : 0,
              is1(inst,msz1) ? 1 : 0,
              is1(inst, N) ? 1 : 0};
          return gii(oparr[ind[0]][ind[1]][ind[2]], inst);
        }

        if(is1(inst, ssop1) && !is1(inst, ssop2)){
          constexpr int msz0 = 14;
          constexpr int msz1 = 13;
          constexpr int N = 0;
          constexpr op_type oparr[2][2][2] =
              {
                  {{op_type::SME_2_MultiVector_Memory_Strided_Store_spi_4Register_ST1B,
                    op_type::SME_2_MultiVector_Memory_Strided_Store_spi_4Register_STNT1B},
                   {op_type::SME_2_MultiVector_Memory_Strided_Store_spi_4Register_ST1H,
                    op_type::SME_2_MultiVector_Memory_Strided_Store_spi_4Register_STNT1H}},
                  {{op_type::SME_2_MultiVector_Memory_Strided_Store_spi_4Register_ST1W,
                    op_type::SME_2_MultiVector_Memory_Strided_Store_spi_4Register_STNT1W},
                   {op_type::SME_2_MultiVector_Memory_Strided_Store_spi_4Register_ST1D,
                    op_type::SME_2_MultiVector_Memory_Strided_Store_spi_4Register_STNT1D}}};
          int ind[3] = {
              is1(inst, msz0) ? 1 : 0,
              is1(inst,msz1) ? 1 : 0,
              is1(inst, N) ? 1 : 0};
          return gii(oparr[ind[0]][ind[1]][ind[2]], inst);
        }
      }
    }
  }
  else if(masking(inst, sop0, "10")){
    if(masking(inst, sop1, "0xx000x0>") && masking(inst, sop2, "0xx")){
      //return gii(op_type::SME_MoveIntoArray, inst);
      constexpr op_range ssop0 = {22, 23};
      constexpr int ssop1 = 18;
      constexpr op_range ssop2 = {15, 16};
      constexpr op_range ssop3 = {10, 12};
      constexpr op_range ssop4 = {5, 6};
      constexpr int ssop5 = 3;
      if((masking(inst, ssop0, "00") && is1(inst, ssop1)) && masking(inst, ssop2, "00")){
        if((masking(inst, ssop3, "010") && masking(inst, ssop4, "x0")) && !is1(inst, ssop5)){
          return gii(op_type::SME_MoveIntoArray_MOVA_2Register, inst);
        }
        if((masking(inst, ssop3, "011") && masking(inst, ssop4, "00")) && !is1(inst, ssop5)){
          return gii(op_type::SME_MoveIntoArray_MOVA_4Register, inst);
        }
      }

      if(!is1(inst, ssop1)){
        constexpr op_range size = {22, 23};
        constexpr int Q = 16;
        if(is1(inst, Q)){
          if(masking(inst, size, "11")){
            return gii(op_type::SME_MoveIntoArray_MoveVectorToArray, inst);
          }
        }
        else{
          return gii(op_type::SME_MoveIntoArray_MoveVectorToArray, inst);
        }
      }
      else{
        if(masking(inst, ssop2, "0x") && !is1(inst, ssop5)){
          if(masking(inst, ssop3, "000") && masking(inst, ssop4, "x0")){
            return gii(op_type::SME_MoveIntoArray_2_MoveVectorToTitle_2Register, inst);
          }
          if(masking(inst, ssop3, "001") && masking(inst, ssop4, "00")){
            constexpr op_range size = {22, 23};
            constexpr int opec = 2;
            if(is1(inst, opec)){
              if(masking(inst, size, "11")){
                return gii(op_type::SME_MoveIntoArray_2_MoveVectorToTitle_4Register, inst);
              }
            }
            else{
              return gii(op_type::SME_MoveIntoArray_2_MoveVectorToTitle_4Register, inst);
            }
          }
        }
      }
    }
    if(masking(inst, sop1, "0xx000x1>")){
      //return gii(op_type::SME_MoveFromArray, inst);
      constexpr op_range ssop0 = {22, 23};
      constexpr int ssop1 = 18;
      constexpr op_range ssop2 = {15, 16};
      constexpr op_range ssop3 = {10, 12};
      constexpr op_range ssop4 = {8, 9};
      constexpr op_range ssop5 = {0, 1};
      if((masking(inst, ssop0, "00") && is1(inst, ssop1)) && (masking(inst, ssop2, "00") && masking(inst, ssop4, "00")))
      {
        if(masking(inst, ssop3, "010") && masking(inst, ssop5, "x0")){
          return gii(op_type::SME_MoveFromArray_MOVA_2Register, inst);
        }
        if(masking(inst, ssop3, "011") && masking(inst, ssop5, "00")){
          return gii(op_type::SME_MoveFromArray_MOVA_4Register, inst);
        }
      }
      if(!is1(inst, ssop1) && masking(inst, ssop4, "0x")){
        constexpr op_range size = {22, 23};
        constexpr int Q = 16;
        if(is1(inst, Q)){
          if(masking(inst, size, "11")){
            return gii(op_type::SME_MoveFromArray_MoveArrayToVector, inst);
          }
        }
        else{
          return gii(op_type::SME_MoveFromArray_MoveArrayToVector, inst);
        }
      }
      if((is1(inst, ssop1) && masking(inst, ssop2, "0x")) && masking(inst, ssop4, "00"))
      {
        if (masking(inst, ssop3, "000") && masking(inst, ssop5, "x0"))
        {
          return gii(op_type::SME_MoveFromArray_2_MoveTitleToVector_2Register, inst);
        }
        if (masking(inst, ssop3, "001") && masking(inst, ssop5, "00"))
        {
          constexpr op_range size = {22, 23};
          constexpr int opec = 2;
          if (is1(inst, opec))
          {
            if (masking(inst, size, "11"))
            {
              return gii(op_type::SME_MoveFromArray_2_MoveTitleToVector_4Register, inst);
            }
          }
          else
          {
            return gii(op_type::SME_MoveFromArray_2_MoveTitleToVector_4Register, inst);
          }
        }
      }
    }
    if(masking(inst, sop1, "0xx010>") && masking(inst, sop2, "x0x")){
      //return gii(op_type::SME_AddVectorToArray, inst);
      constexpr int ssop0 = 23;
      constexpr op_range ssop1 = {17, 18};
      constexpr int ssop2 = 4;
      if((is1(inst, ssop0) && masking(inst, ssop1, "00")) && !is1(inst, ssop2)){
        constexpr int _op = 22;
        constexpr int V = 16;
        constexpr op_range opc2 = {0, 2};
        if(!is1(inst, _op) && masking(inst, opc2, "0xx")){
          if(!is1(inst, V)){
            return gii(op_type::SME_AddVectorToArray_ADDHA_FEAT_SME, inst);
          }
          else{
            return gii(op_type::SME_AddVectorToArray_ADDVA_FEAT_SME, inst);
          }
        }
        else{
          if(!is1(inst, V)){
            return gii(op_type::SME_AddVectorToArray_ADDHA_FEAT_SME_I16I64, inst);
          }
          else{
            return gii(op_type::SME_AddVectorToArray_ADDVA_FEAT_SME_I16I64, inst);
          }
        }
      }
    }
    if(masking(inst, sop1, "0000010>")){
      constexpr op_range ssop0 = {8, 17};
      if(masking(inst, ssop0, "0000000000")){
        return gii(op_type::SME_Zero, inst);
      }
    }
    if(masking(inst, sop1, "0010010>")){
      constexpr op_range ssop0 = {4, 17};
      constexpr op_range opc = {0, 3};
      if(masking(inst, ssop0, "0000000000000") && masking(inst, opc, "0001")){
        return gii(op_type::SME_2_Zero_LookupTable, inst);
      }
    }
    if(masking(inst, sop1, "0010011>")){
      constexpr int ssop0 = 17;
      constexpr op_range ssop1 = {15, 16};
      constexpr op_range opc = {5, 11};
      if(masking(inst, ssop1, "00") && masking(inst, opc, "0011111")){
        if(!is1(inst, ssop0)){
          return gii(op_type::SME_2_Move_LookupTable_From_MOVT, inst);
        }
        else{
          return gii(op_type::SME_2_Move_LookupTable_Into_MOVT, inst);
        }
      }
    }
    if(masking(inst, sop1, "01x001>")){
      //return gii(op_type::SME_2_Expand_LookupTable_Continguous, inst);
      constexpr int ssop0 = 22;
      constexpr op_range ssop1 = {14, 15};
      constexpr op_range ssop2 = {0, 1};
      if((!is1(inst, ssop0) && masking(inst, ssop1, "10")) && masking(inst, ssop2, "00")){
        constexpr op_range opc = {16, 18};
        constexpr op_range opc2 = {10, 11};
        if(masking(inst, opc, "01x") && masking(inst, opc2, "00")){
          return gii(op_type::SME_2_Expand_LookupTable_Continguous_4Register_LUTI4, inst);
        }
        if(masking(inst, opc, "1xx") && masking(inst, opc2, "00")){
          return gii(op_type::SME_2_Expand_LookupTable_Continguous_4Register_LUTI2, inst);
        }
      }
      if((!is1(inst, ssop0) && masking(inst, ssop1, "x1")) && masking(inst, ssop2, "x0")){
        constexpr op_range opc = {15, 18};
        constexpr op_range opc2 = {10, 11};
        if(masking(inst, opc, "01xx") && masking(inst, opc2, "00")){
          return gii(op_type::SME_2_Expand_LookupTable_Continguous_2Register_LUTI4, inst);
        }
        if(masking(inst, opc, "1xxx") && masking(inst, opc2, "00")){
          return gii(op_type::SME_2_Expand_LookupTable_Continguous_2Register_LUTI2, inst);
        }
      }
      if(is1(inst, ssop0)){
        constexpr op_range opc = {14, 18};
        constexpr op_range opc2 = {10, 11};
        if(masking(inst, opc, "01xxx") && masking(inst, opc2, "00")){
          return gii(op_type::SME_2_Expand_LookupTable_Continguous_1Register_LUTI4, inst);
        }
        if(masking(inst, opc, "1xxxx") && masking(inst, opc2, "00")){
          return gii(op_type::SME_2_Expand_LookupTable_Continguous_1Register_LUTI2, inst);
        }
      }
    }
    if(masking(inst, sop1, "1xx00>")){
      //return gii(op_type::SME_2_MultiVector_Indexed_1Register, inst);
      constexpr op_range ssop0 = {22, 23};
      constexpr int ssop1 = 12;
      constexpr int ssop2 = 2;
      if(masking(inst, ssop0, "00")){
        constexpr op_range USop = {2, 4};
        if(masking(inst, USop, "000")){
          return gii(op_type::SME_2_MultiVector_Indexed_1Register_longMLA_32bit_SMLALL, inst);
        }
        if(masking(inst, USop, "001")){
          return gii(op_type::SME_2_MultiVector_Indexed_1Register_longMLA_32bit_USMLALL, inst);
        }
        if(masking(inst, USop, "010")){
          return gii(op_type::SME_2_MultiVector_Indexed_1Register_longMLA_32bit_SMLSLL, inst);
        }
        if(masking(inst, USop, "100")){
          return gii(op_type::SME_2_MultiVector_Indexed_1Register_longMLA_32bit_UMLALL, inst);
        }
        if(masking(inst, USop, "101")){
          return gii(op_type::SME_2_MultiVector_Indexed_1Register_longMLA_32bit_SUMLALL, inst);
        }
        if(masking(inst, USop, "110")){
          return gii(op_type::SME_2_MultiVector_Indexed_1Register_longMLA_32bit_UMLSLL, inst);
        }
      }
      if(masking(inst, ssop0, "10")){
        if(!is1(inst, ssop1) && !is1(inst, ssop2)){
          constexpr op_type oarr[2][2] = {
            {op_type::SME_2_MultiVector_Indexed_1Register_longMLA_64bit_SMLALL,
            op_type::SME_2_MultiVector_Indexed_1Register_longMLA_64bit_SMLSLL}, 
            {op_type::SME_2_MultiVector_Indexed_1Register_longMLA_64bit_UMLALL,
            op_type::SME_2_MultiVector_Indexed_1Register_longMLA_64bit_UMLSLL}};
          constexpr int U = 4;
          constexpr int S = 3;
          return gii(oarr[is1(inst, U) ? 1 : 0][is1(inst, S) ? 1 : 0], inst);
        }
        if(is1(inst, ssop1)){
          constexpr op_type oarr[2][2] = {
            {op_type::SME_2_MultiVector_Indexed_1Register_longFMA_FMLAL,
            op_type::SME_2_MultiVector_Indexed_1Register_longFMA_FMLSL}, 
            {op_type::SME_2_MultiVector_Indexed_1Register_longFMA_BFMLAL,
            op_type::SME_2_MultiVector_Indexed_1Register_longFMA_BFMLSL}};
          constexpr int U = 4;
          constexpr int S = 3;
          return gii(oarr[is1(inst, U) ? 1 : 0][is1(inst, S) ? 1 : 0], inst);
        }
      }
      if(masking(inst, ssop0, "11") && is1(inst, ssop1)){
        constexpr op_type oarr[2][2] = {
            {op_type::SME_2_MultiVector_Indexed_1Register_longMLA_SMLAL,
            op_type::SME_2_MultiVector_Indexed_1Register_longMLA_SMLSL}, 
            {op_type::SME_2_MultiVector_Indexed_1Register_longMLA_UMLAL,
            op_type::SME_2_MultiVector_Indexed_1Register_longMLA_UMLSL}};
        constexpr int U = 4;
        constexpr int S = 3;
        return gii(oarr[is1(inst, U) ? 1 : 0][is1(inst, S) ? 1 : 0], inst);
      }
    }
    if(masking(inst, sop1, "1xx01xxxx0>")){
      //return gii(op_type::SME_2_MultiVector_Indexed_2Register, inst);
      constexpr op_range ssop0 = {20, 21};
      constexpr op_range ssop1 = {11, 12};
      constexpr int ssop2 = 5;
      if(masking(inst, ssop0, "00") && masking(inst, ssop1, "0x")){
        constexpr op_range opus = {3, 5};
        if(masking(inst, opus, "000")){
          return gii(op_type::SME_2_MultiVector_Indexed_2Register_llongMLA_ts_32bit_SMLALL, inst);
        }
        if(masking(inst, opus, "001")){
          return gii(op_type::SME_2_MultiVector_Indexed_2Register_llongMLA_ts_32bit_SMLSLL, inst);
        }
        if(masking(inst, opus, "010")){
          return gii(op_type::SME_2_MultiVector_Indexed_2Register_llongMLA_ts_32bit_UMLALL, inst);
        }
        if(masking(inst, opus, "011")){
          return gii(op_type::SME_2_MultiVector_Indexed_2Register_llongMLA_ts_32bit_UMLSLL, inst);
        }
        if(masking(inst, opus, "100")){
          return gii(op_type::SME_2_MultiVector_Indexed_2Register_llongMLA_ts_32bit_USMLALL, inst);
        }
        if(masking(inst, opus, "110")){
          return gii(op_type::SME_2_MultiVector_Indexed_2Register_llongMLA_ts_32bit_SUMLALL, inst);
        }
      }
      if(masking(inst, ssop0, "01")){
        constexpr int op = 12;
        constexpr op_range opc2 = {3, 5};
        if(!is1(inst, op)){
          if(masking(inst, opc2, "000")){
            return gii(op_type::SME_2_MultiVector_Indexed_2Register_Ternary_32bit_FMLA, inst);
          }
          if(masking(inst, opc2, "001")){
            return gii(op_type::SME_2_MultiVector_Indexed_2Register_Ternary_32bit_FVDOT, inst);
          }
          if(masking(inst, opc2, "010")){
            return gii(op_type::SME_2_MultiVector_Indexed_2Register_Ternary_32bit_FMLS, inst);
          }
          if(masking(inst, opc2, "011")){
            return gii(op_type::SME_2_MultiVector_Indexed_2Register_Ternary_32bit_BFVDOT, inst);
          }
          if(masking(inst, opc2, "100")){
            return gii(op_type::SME_2_MultiVector_Indexed_2Register_Ternary_32bit_SVDOT, inst);
          }
          if(masking(inst, opc2, "110")){
            return gii(op_type::SME_2_MultiVector_Indexed_2Register_Ternary_32bit_UVDOT, inst);
          }
        }
        else{
          if(masking(inst, opc2, "000")){
            return gii(op_type::SME_2_MultiVector_Indexed_2Register_Ternary_32bit_SDOT2, inst);
          }
          if(masking(inst, opc2, "001")){
            return gii(op_type::SME_2_MultiVector_Indexed_2Register_Ternary_32bit_FDOT, inst);
          }
          if(masking(inst, opc2, "010")){
            return gii(op_type::SME_2_MultiVector_Indexed_2Register_Ternary_32bit_UDOT, inst);
          }
          if(masking(inst, opc2, "011")){
            return gii(op_type::SME_2_MultiVector_Indexed_2Register_Ternary_32bit_BFDOT, inst);
          }
          if(masking(inst, opc2, "100")){
            return gii(op_type::SME_2_MultiVector_Indexed_2Register_Ternary_32bit_SDOT4, inst);
          }
          if(masking(inst, opc2, "101")){
            return gii(op_type::SME_2_MultiVector_Indexed_2Register_Ternary_32bit_USDOT, inst);
          }
          if(masking(inst, opc2, "110")){
            return gii(op_type::SME_2_MultiVector_Indexed_2Register_Ternary_32bit_UDOT, inst);
          }
          if(masking(inst, opc2, "111")){
            return gii(op_type::SME_2_MultiVector_Indexed_2Register_Ternary_32bit_SUDOT, inst);
          }
        }
      }
      if(masking(inst, ssop0, "10") && masking(inst, ssop1, "00") && !is1(inst, ssop2)){
        constexpr op_range us = {3, 4};
        if(masking(inst, us, "00")){
          return gii(op_type::SME_2_MultiVector_Indexed_2Register_llongMLA_ts_32bit_SMLALL, inst);
        }
        if(masking(inst, us, "01")){
          return gii(op_type::SME_2_MultiVector_Indexed_2Register_llongMLA_ts_32bit_SMLSLL, inst);
        }
        if(masking(inst, us, "10")){
          return gii(op_type::SME_2_MultiVector_Indexed_2Register_llongMLA_ts_32bit_UMLALL, inst);
        }
        if(masking(inst, us, "11")){
          return gii(op_type::SME_2_MultiVector_Indexed_2Register_llongMLA_ts_32bit_UMLSLL, inst);
        }
      }
      if(masking(inst, ssop0, "10") && masking(inst, ssop1, "1x") && !is1(inst, ssop2)){
        constexpr op_range us = {3, 4};
        if(masking(inst, us, "00")){
          return gii(op_type::SME_2_MultiVector_Indexed_2Register_longFMA_ts_FMLAL, inst);
        }
        if(masking(inst, us, "01")){
          return gii(op_type::SME_2_MultiVector_Indexed_2Register_longFMA_ts_FMLSL, inst);
        }
        if(masking(inst, us, "10")){
          return gii(op_type::SME_2_MultiVector_Indexed_2Register_longFMA_ts_BFMLAL, inst);
        }
        if(masking(inst, us, "11")){
          return gii(op_type::SME_2_MultiVector_Indexed_2Register_longFMA_ts_BFMLSL, inst);
        }
      }
      if(masking(inst, ssop0, "11") && masking(inst, ssop1, "00") && !is1(inst, ssop2)){
        constexpr op_range us = {3, 4};
        if(masking(inst, us, "00")){
          return gii(op_type::SME_2_MultiVector_Indexed_2Register_Ternary_64bit_FMLA, inst);
        }
        if(masking(inst, us, "01")){
          return gii(op_type::SME_2_MultiVector_Indexed_2Register_Ternary_64bit_SDOT, inst);
        }
        if(masking(inst, us, "10")){
          return gii(op_type::SME_2_MultiVector_Indexed_2Register_Ternary_64bit_FMLS, inst);
        }
        if(masking(inst, us, "11")){
          return gii(op_type::SME_2_MultiVector_Indexed_2Register_Ternary_64bit_UDOT, inst);
        }
      }
      if(masking(inst, ssop0, "11") && masking(inst, ssop1, "1x") && !is1(inst, ssop2)){
        constexpr op_range us = {3, 4};
        if(masking(inst, us, "00")){
          return gii(op_type::SME_2_MultiVector_Indexed_2Register_longMLA_ts_SMLAL, inst);
        }
        if(masking(inst, us, "01")){
          return gii(op_type::SME_2_MultiVector_Indexed_2Register_longMLA_ts_SMLSL, inst);
        }
        if(masking(inst, us, "10")){
          return gii(op_type::SME_2_MultiVector_Indexed_2Register_longMLA_ts_UMLAL, inst);
        }
        if(masking(inst, us, "11")){
          return gii(op_type::SME_2_MultiVector_Indexed_2Register_longMLA_ts_UMLSL, inst);
        }
      }
    }
    if(masking(inst, sop1, "1xx01xxxx1>")){
      //return gii(op_type::SME_2_MultiVector_Indexed_4Register, inst);
      constexpr op_range ssop0 = {22, 23};
      constexpr op_range ssop1 = {11, 12};
      constexpr op_range ssop2 = {5, 6};
      if((masking(inst, ssop0, "00") && masking(inst, ssop1, "0x")) && masking(inst, ssop2, "0x")){
        constexpr op_range opus = {3, 5};
        if(masking(inst, opus, "000")){
          return gii(op_type::SME_2_MultiVector_Indexed_4Register_llongMLA_fs_32bit_SMLALL, inst);
        }
        if(masking(inst, opus, "001")){
          return gii(op_type::SME_2_MultiVector_Indexed_4Register_llongMLA_fs_32bit_SMLSLL, inst);
        }
        if(masking(inst, opus, "010")){
          return gii(op_type::SME_2_MultiVector_Indexed_4Register_llongMLA_fs_32bit_UMLALL, inst);
        }
        if(masking(inst, opus, "011")){
          return gii(op_type::SME_2_MultiVector_Indexed_4Register_llongMLA_fs_32bit_UMLSLL, inst);
        }
        if(masking(inst, opus, "100")){
          return gii(op_type::SME_2_MultiVector_Indexed_4Register_llongMLA_fs_32bit_USMLALL, inst);
        }
        if(masking(inst, opus, "110")){
          return gii(op_type::SME_2_MultiVector_Indexed_4Register_llongMLA_fs_32bit_SUMLALL, inst);
        }
      }
      if((masking(inst, ssop0, "01")) && masking(inst, ssop2, "0x")){
        constexpr int _op = 12;
        constexpr op_range opc2 = {3, 5};
        if(!is1(inst, _op)){
          if(masking(inst, opc2, "000")){
            return gii(op_type::SME_2_MultiVector_Indexed_4Register_Ternary_32bit_FMLA, inst);
          }
          if(masking(inst, opc2, "010")){
            return gii(op_type::SME_2_MultiVector_Indexed_4Register_Ternary_32bit_FMLS, inst);
          }
          if(masking(inst, opc2, "100")){
            return gii(op_type::SME_2_MultiVector_Indexed_4Register_Ternary_32bit_SVDOT, inst);
          }
          if(masking(inst, opc2, "101")){
            return gii(op_type::SME_2_MultiVector_Indexed_4Register_Ternary_32bit_USVDOT, inst);
          }
          if(masking(inst, opc2, "110")){
            return gii(op_type::SME_2_MultiVector_Indexed_4Register_Ternary_32bit_UVDOT, inst);
          }
          if(masking(inst, opc2, "111")){
            return gii(op_type::SME_2_MultiVector_Indexed_4Register_Ternary_32bit_SUVDOT, inst);
          }
        }
        else{
          if(masking(inst, opc2, "000")){
            return gii(op_type::SME_2_MultiVector_Indexed_4Register_Ternary_32bit_SDOT2, inst);
          }
          if(masking(inst, opc2, "001")){
            return gii(op_type::SME_2_MultiVector_Indexed_4Register_Ternary_32bit_FDOT, inst);
          }
          if(masking(inst, opc2, "010")){
            return gii(op_type::SME_2_MultiVector_Indexed_4Register_Ternary_32bit_UDOT2, inst);
          }
          if(masking(inst, opc2, "011")){
            return gii(op_type::SME_2_MultiVector_Indexed_4Register_Ternary_32bit_BFDOT, inst);
          }
          if(masking(inst, opc2, "100")){
            return gii(op_type::SME_2_MultiVector_Indexed_4Register_Ternary_32bit_SDOT4, inst);
          }
          if(masking(inst, opc2, "101")){
            return gii(op_type::SME_2_MultiVector_Indexed_4Register_Ternary_32bit_USDOT, inst);
          }
          if(masking(inst, opc2, "110")){
            return gii(op_type::SME_2_MultiVector_Indexed_4Register_Ternary_32bit_UDOT4, inst);
          }
          if(masking(inst, opc2, "111")){
            return gii(op_type::SME_2_MultiVector_Indexed_4Register_Ternary_32bit_SUDOT, inst);
          }
        }
      }
      if((masking(inst, ssop0, "10") && masking(inst, ssop1, "00")) && masking(inst, ssop2, "00")){
        constexpr op_type oarr[2][2] = {{
          op_type::SME_2_MultiVector_Indexed_4Register_llongMLA_fs_64bit_SMLALL,
          op_type::SME_2_MultiVector_Indexed_4Register_llongMLA_fs_64bit_SMLSLL
        }, {
          op_type::SME_2_MultiVector_Indexed_4Register_llongMLA_fs_64bit_UMLALL,
          op_type::SME_2_MultiVector_Indexed_4Register_llongMLA_fs_64bit_UMLSLL
        }};
        constexpr int U = 4;
        constexpr int S = 3;
        return gii(oarr[is1(inst, U) ? 1:0][is1(inst, S) ? 1:0], inst);
      }
      if((masking(inst, ssop0, "10") && masking(inst, ssop1, "1x")) && masking(inst, ssop2, "00")){
        constexpr op_type oarr[2][2] = {{
          op_type::SME_2_MultiVector_Indexed_4Register_longFMA_fs_FMLAL,
          op_type::SME_2_MultiVector_Indexed_4Register_longFMA_fs_FMLSL
        }, {
          op_type::SME_2_MultiVector_Indexed_4Register_longFMA_fs_BFMLAL,
          op_type::SME_2_MultiVector_Indexed_4Register_longFMA_fs_BFMLSL
        }};
        constexpr int U = 4;
        constexpr int S = 3;
        return gii(oarr[is1(inst, U) ? 1:0][is1(inst, S) ? 1:0], inst);
      }
      if((masking(inst, ssop0, "11") && masking(inst, ssop1, "0x")) && masking(inst, ssop2, "00")){
        constexpr int _op = 11;
        constexpr op_range opc2 = {3, 4};
        if(!is1(inst, _op)){
          if(masking(inst, opc2, "00")){
            return gii(op_type::SME_2_MultiVector_Indexed_4Register_Ternary_64bit_FMLA, inst);
          }
          if(masking(inst, opc2, "01")){
            return gii(op_type::SME_2_MultiVector_Indexed_4Register_Ternary_64bit_SDOT, inst);
          }
          if(masking(inst, opc2, "10")){
            return gii(op_type::SME_2_MultiVector_Indexed_4Register_Ternary_64bit_FMLS, inst);
          }
          if(masking(inst, opc2, "11")){
            return gii(op_type::SME_2_MultiVector_Indexed_4Register_Ternary_64bit_UDOT, inst);
          }
        }
        else{
          if(masking(inst, opc2, "01")){
            return gii(op_type::SME_2_MultiVector_Indexed_4Register_Ternary_64bit_SVDOT, inst);
          }
          if(masking(inst, opc2, "11")){
            return gii(op_type::SME_2_MultiVector_Indexed_4Register_Ternary_64bit_UVDOT, inst);
          }
        }
      }
      if((masking(inst, ssop0, "11") && masking(inst, ssop1, "1x")) && masking(inst, ssop2, "00")){
        constexpr op_type oarr[2][2] = {{
          op_type::SME_2_MultiVector_Indexed_4Register_longMLA_fs_SMLAL,
          op_type::SME_2_MultiVector_Indexed_4Register_longMLA_fs_SMLSL
        }, {
          op_type::SME_2_MultiVector_Indexed_4Register_longMLA_fs_UMLAL,
          op_type::SME_2_MultiVector_Indexed_4Register_longMLA_fs_UMLSL
        }};
        constexpr int U = 4;
        constexpr int S = 3;
        return gii(oarr[is1(inst, U) ? 1:0][is1(inst, S) ? 1:0], inst);
      }
    }
    if(masking(inst, sop1, "1xx1xxxxx100>")){
      constexpr op_range ssop0 = {16, 17};
      constexpr op_range ssop1 = {5, 6};
      constexpr op_range ssop2 = {0, 1};
      if((masking(inst, ssop0, "01") && masking(inst, ssop1, "00")) && masking(inst, ssop2, "00")){
        return gii(op_type::SME_2_MultiVector_SVE_Select_SEL, inst);
      }
      if((masking(inst, ssop0, "x0") && masking(inst, ssop1, "x0")) && masking(inst, ssop2, "x0")){
        return gii(op_type::SME_2_MultiVector_SVE_Select_SEL, inst);
      }
    }
    if(masking(inst, sop1, "1xx1xxxxx110>")){
      //return gii(op_type::SME_2_MultiVector_SVE_Constructive_Binary, inst);
      constexpr op_range _op0 = {22, 23};
      constexpr op_range _op1 = {10, 12};
      constexpr op_range _op2 = {0, 1};
      if(masking(inst, _op0, "00") && masking(inst, _op1, "101")){
        if(!is1(inst, 0)){
          return gii(op_type::SME_2_MultiVector_SVE_Constructive_Binary_QuadwordsZIP_2Register_ZIP, inst);
        }
        else{
          return gii(op_type::SME_2_MultiVector_SVE_Constructive_Binary_QuadwordsZIP_2Register_UZP, inst);
        }
      }
      if(masking(inst, _op0, "11") && masking(inst, _op1, "101")){
        constexpr int _op = 20;
        constexpr int U = 5;
        if(!is1(inst, _op)){
          if(!is1(inst, U)){
            return gii(op_type::SME_2_MultiVector_SVE_Constructive_Binary_SaturatingShiftRight_2Register_SQRSHR, inst);
          }
          else{
            return gii(op_type::SME_2_MultiVector_SVE_Constructive_Binary_SaturatingShiftRight_2Register_UQRSHR, inst);
          }
        }
        else{
          if(!is1(inst, U)){
            return gii(op_type::SME_2_MultiVector_SVE_Constructive_Binary_SaturatingShiftRight_2Register_SQRSHRU, inst);
          }
        }
      }
      if((masking(inst, _op2, "x0") && masking(inst, _op1, "000")) || (masking(inst, _op2, "00") && masking(inst, _op1, "010"))){
        return gii(op_type::SME_2_MultiVector_SVE_Constructive_Binary_FCLAMP, inst);
      }
      if(masking(inst, _op1, "001")){
        if(!is1(inst, 0)){
          return gii(op_type::SME_2_MultiVector_SVE_Constructive_Binary_CLAMP_2Register_SCLAMP, inst);
        }
        else{
          return gii(op_type::SME_2_MultiVector_SVE_Constructive_Binary_CLAMP_2Register_UCLAMP, inst);
        }
      }
      if(masking(inst, _op1, "011") && masking(inst, _op2, "0x")){
        if(!is1(inst, 0)){
          return gii(op_type::SME_2_MultiVector_SVE_Constructive_Binary_CLAMP_4Register_SCLAMP, inst);
        }
        else{
          return gii(op_type::SME_2_MultiVector_SVE_Constructive_Binary_CLAMP_4Register_UCLAMP, inst);
        }
      }
      if(masking(inst, _op1, "100")){
        if(!is1(inst, 0)){
          return gii(op_type::SME_2_MultiVector_SVE_Constructive_Binary_ZIP_2Register_ZIP, inst);
        }
        else{
          return gii(op_type::SME_2_MultiVector_SVE_Constructive_Binary_ZIP_2Register_UZP, inst);
        }
      }
      if(masking(inst, _op1, "11x")){
        constexpr int N = 10;
        constexpr op_range opU = {5, 6};
        if(!is1(inst, N)){
          if(masking(inst, opU, "00")){
            return gii(op_type::SME_2_MultiVector_SVE_Constructive_Binary_SaturatingShiftRight_4Register_SQRSHR, inst);
          }
          if(masking(inst, opU, "01")){
            return gii(op_type::SME_2_MultiVector_SVE_Constructive_Binary_SaturatingShiftRight_4Register_UQRSHR, inst);
          }
          if(masking(inst, opU, "10")){
            return gii(op_type::SME_2_MultiVector_SVE_Constructive_Binary_SaturatingShiftRight_4Register_SQRSHRU, inst);
          }
        }
        else{
          if(masking(inst, opU, "00")){
            return gii(op_type::SME_2_MultiVector_SVE_Constructive_Binary_SaturatingShiftRight_4Register_SQRSHRN, inst);
          }
          if(masking(inst, opU, "01")){
            return gii(op_type::SME_2_MultiVector_SVE_Constructive_Binary_SaturatingShiftRight_4Register_UQRSHRN, inst);
          }
          if(masking(inst, opU, "10")){
            return gii(op_type::SME_2_MultiVector_SVE_Constructive_Binary_SaturatingShiftRight_4Register_SQRSHRUN, inst);
          }
        }
      }
    }
    if(masking(inst, sop1, "1xx1xxxxx111000")){
      //return gii(op_type::SME_2_MultiVector_SVE_Constructive_Unary, inst);
      constexpr op_range _op0 = {22, 23};
      constexpr op_range _op1 = {16, 20};
      constexpr op_range _op2 = {5, 6};
      constexpr op_range _op3 = {0, 1};
      constexpr int U = 5;
      if((masking(inst, _op0, "00") && masking(inst, _op1, "00001")) && (masking(inst, _op3, "x0"))){
        if(!is1(inst, U)){
          return gii(op_type::SME_2_MultiVector_SVE_Constructive_Unary_FPToIntConvert_2Register_FCVTZS, inst);
        }
        else{
          return gii(op_type::SME_2_MultiVector_SVE_Constructive_Unary_FPToIntConvert_2Register_FCVTZU, inst);
        }
      }
      if((masking(inst, _op0, "00") && masking(inst, _op1, "00010")) && (masking(inst, _op3, "x0"))){
        if(!is1(inst, U)){
          return gii(op_type::SME_2_MultiVector_SVE_Constructive_Unary_IntToFP_2Register_SCVTF, inst);
        }
        else{
          return gii(op_type::SME_2_MultiVector_SVE_Constructive_Unary_IntToFP_2Register_UCVTF, inst);
        }
      }
      if((masking(inst, _op0, "00") && masking(inst, _op1, "10001")) && (masking(inst, _op2, "0x") && masking(inst, _op3, "00"))){
        if(!is1(inst, U)){
          return gii(op_type::SME_2_MultiVector_SVE_Constructive_Unary_FPToIntConvert_4Register_FCVTZS, inst);
        }
        else{
          return gii(op_type::SME_2_MultiVector_SVE_Constructive_Unary_FPToIntConvert_4Register_FCVTZU, inst);
        }
      }
      if((masking(inst, _op0, "00") && masking(inst, _op1, "10010")) && (masking(inst, _op2, "0x") && masking(inst, _op3, "00"))){
        if(!is1(inst, U)){
          return gii(op_type::SME_2_MultiVector_SVE_Constructive_Unary_IntToFP_4Register_SCVTF, inst);
        }
        else{
          return gii(op_type::SME_2_MultiVector_SVE_Constructive_Unary_IntToFP_4Register_UCVTF, inst);
        }
      }
      if((masking(inst, _op0, "00") && masking(inst, _op1, "10111")) && (masking(inst, _op2, "00") && masking(inst, _op3, "x0"))){
        constexpr int _op = 1;
        if(!is1(inst, _op)){
          return gii(op_type::SME_2_MultiVector_SVE_Constructive_Unary_ZIP_4Register_ZIP, inst);
        }
        else{
          return gii(op_type::SME_2_MultiVector_SVE_Constructive_Unary_ZIP_4Register_UZP, inst);
        }
      }
      if(masking(inst, _op0, "0x") && masking(inst, _op1, "00000")){
        constexpr int _op = 22;
        constexpr int N = 5;
        constexpr op_type oarr[2][2] = {{
          op_type::SME_2_MultiVector_SVE_Constructive_Unary_FPdownConvert_2Register_FCVT,
          op_type::SME_2_MultiVector_SVE_Constructive_Unary_FPdownConvert_2Register_FCVTN
        }, {
          op_type::SME_2_MultiVector_SVE_Constructive_Unary_FPdownConvert_2Register_BFCVT,
          op_type::SME_2_MultiVector_SVE_Constructive_Unary_FPdownConvert_2Register_BFCVTN
        }};
        return gii(oarr[is1(inst, _op)?1:0][is1(inst, N)?1:0], inst);
      }
      if(masking(inst, _op0, "0x") && masking(inst, _op1, "00011")){
        constexpr int _op = 22;
        constexpr int _U = 0;
        constexpr op_type oarr[2][2] = {{
          op_type::SME_2_MultiVector_SVE_Constructive_Unary_FPdownConvert_2Register_FCVT,
          op_type::SME_2_MultiVector_SVE_Constructive_Unary_FPdownConvert_2Register_FCVTN
        }, {
          op_type::SME_2_MultiVector_SVE_Constructive_Unary_FPdownConvert_2Register_BFCVT,
          op_type::Undefine
        }};
        op_type ot = oarr[is1(inst, _op)?1:0][is1(inst, _U)?1:0];
        if(ot != op_type::Undefine){
          return gii(ot, inst);
        }
      }
      if(masking(inst, _op1, "00101")){
        constexpr int _U = 0;
        op_type ot = (!is1(inst, _U)) ? op_type::SME_2_MultiVector_SVE_Constructive_Unary_Unpack_2Register_SUNPK : op_type::SME_2_MultiVector_SVE_Constructive_Unary_Unpack_2Register_UUNPK;
        return gii(ot, inst);
      }
      if((masking(inst, _op1, "01xxx")) && (masking(inst, _op2, "x0") && masking(inst, _op3, "x0"))){
        constexpr op_range size = {22, 23};
        constexpr op_range opc = {16, 18};
        if(masking(inst, size, "10") && masking(inst, opc, "000")){
          return gii(op_type::SME_2_MultiVector_SVE_Constructive_Unary_FRINT_2Register_FRINTN, inst);
        }
        if(masking(inst, size, "10") && masking(inst, opc, "001")){
          return gii(op_type::SME_2_MultiVector_SVE_Constructive_Unary_FRINT_2Register_FRINTP, inst);
        }
        if(masking(inst, size, "10") && masking(inst, opc, "010")){
          return gii(op_type::SME_2_MultiVector_SVE_Constructive_Unary_FRINT_2Register_FRINTM, inst);
        }
        if(masking(inst, size, "10") && masking(inst, opc, "100")){
          return gii(op_type::SME_2_MultiVector_SVE_Constructive_Unary_FRINT_2Register_FRINTA, inst);
        }
      }
      if(masking(inst, _op1, "10011")){
        constexpr int _op = 22;
        constexpr op_range nu = {5, 6};
        if(!is1(inst, _op)){
          if(masking(inst, nu, "00")){
            return gii(op_type::SME_2_MultiVector_SVE_Constructive_Unary_IntDownConvert_4Register_SQCVT, inst);
          }
          if(masking(inst, nu, "01")){
            return gii(op_type::SME_2_MultiVector_SVE_Constructive_Unary_IntDownConvert_4Register_UQCVT, inst);
          }
          if(masking(inst, nu, "10")){
            return gii(op_type::SME_2_MultiVector_SVE_Constructive_Unary_IntDownConvert_4Register_SQCVTN, inst);
          }
          if(masking(inst, nu, "11")){
            return gii(op_type::SME_2_MultiVector_SVE_Constructive_Unary_IntDownConvert_4Register_UQCVTN, inst);
          }
        }
        else{
          if(masking(inst, nu, "00")){
            return gii(op_type::SME_2_MultiVector_SVE_Constructive_Unary_IntDownConvert_4Register_SQCVTU, inst);
          }
          if(masking(inst, nu, "10")){
            return gii(op_type::SME_2_MultiVector_SVE_Constructive_Unary_IntDownConvert_4Register_SQCVTUN, inst);
          }
        }
      }
      if((masking(inst, _op1, "10101")) && (masking(inst, _op2, "x0") && masking(inst, _op3, "0x"))){
        constexpr int _U = 0;
        if(!is1(inst, _U)){
          return gii(op_type::SME_2_MultiVector_SVE_Constructive_Unary_Unpack_4Register_SUNPK, inst);
        }
        else{
          return gii(op_type::SME_2_MultiVector_SVE_Constructive_Unary_Unpack_4Register_UUNPK, inst);
        }
      }
      if((masking(inst, _op1, "10110")) && (masking(inst, _op2, "00") && masking(inst, _op3, "x0"))){
        constexpr int _op = 1;
        if(!is1(inst, _op)){
          return gii(op_type::SME_2_MultiVector_SVE_Constructive_Unary_ZIP_4Register_ZIP, inst);
        }
        else{
          return gii(op_type::SME_2_MultiVector_SVE_Constructive_Unary_ZIP_4Register_UZP, inst);
        }
      }
      if((masking(inst, _op1, "11xxx")) && (masking(inst, _op2, "00") && masking(inst, _op3, "00"))){
        constexpr op_range size = {22, 23};
        constexpr op_range opc = {16, 18};
        if(masking(inst, size, "10") && masking(inst, opc, "000")){
          return gii(op_type::SME_2_MultiVector_SVE_Constructive_Unary_FRINT_4Register_FRINTN, inst);
        }
        if(masking(inst, size, "10") && masking(inst, opc, "001")){
          return gii(op_type::SME_2_MultiVector_SVE_Constructive_Unary_FRINT_4Register_FRINTP, inst);
        }
        if(masking(inst, size, "10") && masking(inst, opc, "010")){
          return gii(op_type::SME_2_MultiVector_SVE_Constructive_Unary_FRINT_4Register_FRINTM, inst);
        }
        if(masking(inst, size, "10") && masking(inst, opc, "100")){
          return gii(op_type::SME_2_MultiVector_SVE_Constructive_Unary_FRINT_4Register_FRINTA, inst);
        }
      }
    }
    if(masking(inst, sop1, "1xx1xxxx010110x")){
      //return gii(op_type::SME_2_MultiVector_MultiVector_SVE_Destructive_2Register, inst);
      constexpr op_range _op0op1 = {5, 10};
      constexpr int _op2 = 0;
      if(masking(inst, _op0op1, "00000x")){
        constexpr op_type oarr[2][2] = {{
          op_type::SME_2_MultiVector_MultiVector_SVE_Destructive_2Register_IntMinMax_SMAX,
          op_type::SME_2_MultiVector_MultiVector_SVE_Destructive_2Register_IntMinMax_UMAX
        }, {
          op_type::SME_2_MultiVector_MultiVector_SVE_Destructive_2Register_IntMinMax_SMIN,
          op_type::SME_2_MultiVector_MultiVector_SVE_Destructive_2Register_IntMinMax_UMIN
        }};
        constexpr int _op = 5;
        constexpr int _U = 0;
        return gii(oarr[is1(inst, _op)?1:0][is1(inst, _U)?1:0], inst);
      }
      if(masking(inst, _op0op1, "00100x")){
        constexpr op_type oarr[2][2] = {{
          op_type::SME_2_MultiVector_MultiVector_SVE_Destructive_2Register_FPMinMax_FMAX,
          op_type::SME_2_MultiVector_MultiVector_SVE_Destructive_2Register_FPMinMax_FMIN
        }, {
          op_type::SME_2_MultiVector_MultiVector_SVE_Destructive_2Register_FPMinMax_FMAXNM,
          op_type::SME_2_MultiVector_MultiVector_SVE_Destructive_2Register_FPMinMax_FMINNM
        }};
        constexpr int _op = 5;
        constexpr int _o2 = 0;
        return gii(oarr[is1(inst, _op)?1:0][is1(inst, _o2)?1:0], inst);
      }
      if(masking(inst, _op0op1, "010xxx")){
        constexpr op_range opc = {5, 7};
        constexpr int _U = 0;
        if(masking(inst, opc, "001") && !is1(inst, _U)){
          return gii(op_type::SME_2_MultiVector_MultiVector_SVE_Destructive_2Register_Shift_SRSHL, inst);
        }
        if(masking(inst, opc, "001") && is1(inst, _U)){
          return gii(op_type::SME_2_MultiVector_MultiVector_SVE_Destructive_2Register_Shift_URSHL, inst);
        }
      }
      if(masking(inst, _op0op1, "10000x") && is1(inst, _op2)){
        return gii(op_type::SME_2_MultiVector_MultiVector_SVE_Destructive_2Register_SQDMULH, inst);
      }
    }
    if(masking(inst, sop1, "1xx1xxxx010111x")){
      //return gii(op_type::SME_2_MultiVector_MultiVector_SVE_Destructive_4Register,inst);
      constexpr op_range _op0op1 = {5, 10};
      constexpr int _op2 = 0;
      if(masking(inst, _op0op1, "00000x")){
        constexpr op_type oarr[2][2] = {{
          op_type::SME_2_MultiVector_MultiVector_SVE_Destructive_4Register_IntMinMax_SMAX,
          op_type::SME_2_MultiVector_MultiVector_SVE_Destructive_4Register_IntMinMax_UMAX
        }, {
          op_type::SME_2_MultiVector_MultiVector_SVE_Destructive_4Register_IntMinMax_SMIN,
          op_type::SME_2_MultiVector_MultiVector_SVE_Destructive_4Register_IntMinMax_UMIN
        }};
        constexpr int _op = 5;
        constexpr int _U = 0;
        return gii(oarr[is1(inst, _op)?1:0][is1(inst, _U)?1:0], inst);
      }
      if(masking(inst, _op0op1, "00100x")){
        constexpr op_type oarr[2][2] = {{
          op_type::SME_2_MultiVector_MultiVector_SVE_Destructive_4Register_FPMinMax_FMAX,
          op_type::SME_2_MultiVector_MultiVector_SVE_Destructive_4Register_FPMinMax_FMIN
        }, {
          op_type::SME_2_MultiVector_MultiVector_SVE_Destructive_4Register_FPMinMax_FMAXNM,
          op_type::SME_2_MultiVector_MultiVector_SVE_Destructive_4Register_FPMinMax_FMINNM
        }};
        constexpr int _op = 5;
        constexpr int _o2 = 0;
        return gii(oarr[is1(inst, _op)?1:0][is1(inst, _o2)?1:0], inst);
      }
      if(masking(inst, _op0op1, "010xxx")){
        constexpr op_range opc = {5, 7};
        constexpr int _U = 0;
        if(masking(inst, opc, "001") && !is1(inst, _U)){
          return gii(op_type::SME_2_MultiVector_MultiVector_SVE_Destructive_4Register_Shift_SRSHL, inst);
        }
        if(masking(inst, opc, "001") && is1(inst, _U)){
          return gii(op_type::SME_2_MultiVector_MultiVector_SVE_Destructive_4Register_Shift_URSHL, inst);
        }
      }
      if(masking(inst, _op0op1, "10000x") && is1(inst, _op2)){
        return gii(op_type::SME_2_MultiVector_MultiVector_SVE_Destructive_4Register_SQDMULH, inst);
      }
    }
    if(masking(inst, sop1, "1xx10xxx010100x")){
      //return gii(op_type::SME_2_MultiVector_MultiAndSingleVector_SVE_Destructive_2Register, inst);
      
    }
    if(masking(inst, sop1, "1xx10xxx010101x")){
      return gii(op_type::SME_2_MultiVector_MultiAndSingleVector_SVE_Destructive_4Register, inst);
    }

    if(masking(inst, sop1, "10x1xxxxx0>")){
      return gii(op_type::SME_2_MultiVector_MultiAndSingle_ArrayVectors, inst);;
    }
    if(masking(inst, sop1, "11x1xxxx00>")){
      return gii(op_type::SME_2_MultiVector_Multiple_ArrayVectors_2Register, inst);
    }
    if(masking(inst, sop1, "11x1xxxx10>")){
      return gii(op_type::SME_2_MultiVector_Multiple_ArrayVectors_4Register, inst);
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

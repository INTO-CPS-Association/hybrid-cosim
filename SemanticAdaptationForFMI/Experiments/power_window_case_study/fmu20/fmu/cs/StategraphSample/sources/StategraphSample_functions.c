#include "StategraphSample_functions.h"
#ifdef __cplusplus
extern "C" {
#endif

#include "StategraphSample_includes.h"


DLLExport
modelica_boolean omc_Modelica_StateGraph_Temporary_anyTrue(threadData_t *threadData, boolean_array _b)
{
  modelica_boolean _result;
  modelica_integer tmp1;
  modelica_integer tmp2;
  modelica_integer tmp3;
  modelica_integer tmp4;
  _tailrecursive: OMC_LABEL_UNUSED
  _result = 0;

  tmp4 = size_of_dimension_base_array(_b, ((modelica_integer) 1));
  tmp1 = ((modelica_integer) 1); tmp2 = 1; tmp3 = tmp4;
  if(!tmp2)
  {
    FILE_INFO info = omc_dummyFileInfo;
    omc_assert(threadData, info, "assertion range step != 0 failed");
  }
  else if(!(((tmp2 > 0) && (tmp1 > tmp3)) || ((tmp2 < 0) && (tmp1 < tmp3))))
  {
    modelica_integer _i;
    for(_i = ((modelica_integer) 1); in_range_integer(_i, tmp1, tmp3); _i += tmp2)
    {
      _result = (_result || (*boolean_array_element_addr1(&_b, 1, /* modelica_integer */ (modelica_integer)_i)));
    }
  }
  _return: OMC_LABEL_UNUSED
  return _result;
}
modelica_metatype boxptr_Modelica_StateGraph_Temporary_anyTrue(threadData_t *threadData, modelica_metatype _b)
{
  modelica_boolean _result;
  modelica_metatype out_result;
  _result = omc_Modelica_StateGraph_Temporary_anyTrue(threadData, *((base_array_t*)_b));
  out_result = mmc_mk_icon(_result);
  return out_result;
}

#ifdef __cplusplus
}
#endif

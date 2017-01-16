/* update bound parameters and variable attributes (start, nominal, min, max) */
#include "StategraphSample_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

int StategraphSample_updateBoundVariableAttributes(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  /* min ******************************************************** */
  
  infoStreamPrint(LOG_INIT, 1, "updating min-values");
  if (ACTIVE_STREAM(LOG_INIT)) messageClose(LOG_INIT);
  
  /* max ******************************************************** */
  
  infoStreamPrint(LOG_INIT, 1, "updating max-values");
  if (ACTIVE_STREAM(LOG_INIT)) messageClose(LOG_INIT);
  
  /* nominal **************************************************** */
  
  infoStreamPrint(LOG_INIT, 1, "updating nominal-values");
  if (ACTIVE_STREAM(LOG_INIT)) messageClose(LOG_INIT);
  
  /* start ****************************************************** */
  
  infoStreamPrint(LOG_INIT, 1, "updating start-values");
  if (ACTIVE_STREAM(LOG_INIT)) messageClose(LOG_INIT);
  
  TRACE_POP
  return 0;
}


/*
 equation index: 61
 type: SIMPLE_ASSIGN
 s1._nIn = 1
 */
void StategraphSample_eqFunction_61(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,61};
  data->simulationInfo->integerParameter[0] /* s1._nIn PARAM */ = ((modelica_integer) 1);
  TRACE_POP
}

/*
 equation index: 62
 type: SIMPLE_ASSIGN
 s1._nOut = 1
 */
void StategraphSample_eqFunction_62(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,62};
  data->simulationInfo->integerParameter[1] /* s1._nOut PARAM */ = ((modelica_integer) 1);
  TRACE_POP
}

/*
 equation index: 63
 type: SIMPLE_ASSIGN
 t1._enableTimer = false
 */
void StategraphSample_eqFunction_63(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,63};
  data->simulationInfo->booleanParameter[0] /* t1._enableTimer PARAM */ = 0;
  TRACE_POP
}

/*
 equation index: 64
 type: SIMPLE_ASSIGN
 t2._enableTimer = true
 */
void StategraphSample_eqFunction_64(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,64};
  data->simulationInfo->booleanParameter[1] /* t2._enableTimer PARAM */ = 1;
  TRACE_POP
}

/*
 equation index: 65
 type: SIMPLE_ASSIGN
 step1._nIn = 1
 */
void StategraphSample_eqFunction_65(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,65};
  data->simulationInfo->integerParameter[2] /* step1._nIn PARAM */ = ((modelica_integer) 1);
  TRACE_POP
}

/*
 equation index: 66
 type: SIMPLE_ASSIGN
 step1._nOut = 1
 */
void StategraphSample_eqFunction_66(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,66};
  data->simulationInfo->integerParameter[3] /* step1._nOut PARAM */ = ((modelica_integer) 1);
  TRACE_POP
}

/*
 equation index: 67
 type: ALGORITHM
 
   assert(s1.nIn >= 0, "Variable violating min constraint: 0 <= s1.nIn, has value: " + String(s1.nIn, "d"));
 */
void StategraphSample_eqFunction_67(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,67};
  modelica_boolean tmp0;
  static const MMC_DEFSTRINGLIT(tmp1,59,"Variable violating min constraint: 0 <= s1.nIn, has value: ");
  modelica_string tmp2;
  static int tmp3 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp3)
  {
    tmp0 = GreaterEq((modelica_integer)data->simulationInfo->integerParameter[0] /* s1._nIn PARAM */,((modelica_integer) 0));
    if(!tmp0)
    {
      tmp2 = modelica_integer_to_modelica_string_format((modelica_integer)data->simulationInfo->integerParameter[0] /* s1._nIn PARAM */, (modelica_string) mmc_strings_len1[100]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp1),tmp2);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/StateGraph.mo",1973,5,1973,67,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\ns1.nIn >= 0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp3 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 68
 type: ALGORITHM
 
   assert(s1.nOut >= 0, "Variable violating min constraint: 0 <= s1.nOut, has value: " + String(s1.nOut, "d"));
 */
void StategraphSample_eqFunction_68(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,68};
  modelica_boolean tmp4;
  static const MMC_DEFSTRINGLIT(tmp5,60,"Variable violating min constraint: 0 <= s1.nOut, has value: ");
  modelica_string tmp6;
  static int tmp7 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp7)
  {
    tmp4 = GreaterEq((modelica_integer)data->simulationInfo->integerParameter[1] /* s1._nOut PARAM */,((modelica_integer) 0));
    if(!tmp4)
    {
      tmp6 = modelica_integer_to_modelica_string_format((modelica_integer)data->simulationInfo->integerParameter[1] /* s1._nOut PARAM */, (modelica_string) mmc_strings_len1[100]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp5),tmp6);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/StateGraph.mo",1974,5,1974,69,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\ns1.nOut >= 0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp7 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 69
 type: ALGORITHM
 
   assert(t1.waitTime >= 0.0, "Variable violating min constraint: 0.0 <= t1.waitTime, has value: " + String(t1.waitTime, "g"));
 */
void StategraphSample_eqFunction_69(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,69};
  modelica_boolean tmp8;
  static const MMC_DEFSTRINGLIT(tmp9,66,"Variable violating min constraint: 0.0 <= t1.waitTime, has value: ");
  modelica_string tmp10;
  static int tmp11 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp11)
  {
    tmp8 = GreaterEq(data->simulationInfo->realParameter[0] /* t1._waitTime PARAM */,0.0);
    if(!tmp8)
    {
      tmp10 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[0] /* t1._waitTime PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp9),tmp10);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/StateGraph.mo",2066,5,2068,61,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nt1.waitTime >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp11 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 70
 type: ALGORITHM
 
   assert(t2.waitTime >= 0.0, "Variable violating min constraint: 0.0 <= t2.waitTime, has value: " + String(t2.waitTime, "g"));
 */
void StategraphSample_eqFunction_70(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,70};
  modelica_boolean tmp12;
  static const MMC_DEFSTRINGLIT(tmp13,66,"Variable violating min constraint: 0.0 <= t2.waitTime, has value: ");
  modelica_string tmp14;
  static int tmp15 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp15)
  {
    tmp12 = GreaterEq(data->simulationInfo->realParameter[1] /* t2._waitTime PARAM */,0.0);
    if(!tmp12)
    {
      tmp14 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[1] /* t2._waitTime PARAM */, (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp13),tmp14);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/StateGraph.mo",2066,5,2068,61,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nt2.waitTime >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp15 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 71
 type: ALGORITHM
 
   assert(step1.nIn >= 0, "Variable violating min constraint: 0 <= step1.nIn, has value: " + String(step1.nIn, "d"));
 */
void StategraphSample_eqFunction_71(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,71};
  modelica_boolean tmp16;
  static const MMC_DEFSTRINGLIT(tmp17,62,"Variable violating min constraint: 0 <= step1.nIn, has value: ");
  modelica_string tmp18;
  static int tmp19 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp19)
  {
    tmp16 = GreaterEq((modelica_integer)data->simulationInfo->integerParameter[2] /* step1._nIn PARAM */,((modelica_integer) 0));
    if(!tmp16)
    {
      tmp18 = modelica_integer_to_modelica_string_format((modelica_integer)data->simulationInfo->integerParameter[2] /* step1._nIn PARAM */, (modelica_string) mmc_strings_len1[100]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp17),tmp18);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/StateGraph.mo",1973,5,1973,67,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nstep1.nIn >= 0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp19 = 1;
    }
  }
  TRACE_POP
}

/*
 equation index: 72
 type: ALGORITHM
 
   assert(step1.nOut >= 0, "Variable violating min constraint: 0 <= step1.nOut, has value: " + String(step1.nOut, "d"));
 */
void StategraphSample_eqFunction_72(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,72};
  modelica_boolean tmp20;
  static const MMC_DEFSTRINGLIT(tmp21,63,"Variable violating min constraint: 0 <= step1.nOut, has value: ");
  modelica_string tmp22;
  static int tmp23 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp23)
  {
    tmp20 = GreaterEq((modelica_integer)data->simulationInfo->integerParameter[3] /* step1._nOut PARAM */,((modelica_integer) 0));
    if(!tmp20)
    {
      tmp22 = modelica_integer_to_modelica_string_format((modelica_integer)data->simulationInfo->integerParameter[3] /* step1._nOut PARAM */, (modelica_string) mmc_strings_len1[100]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp21),tmp22);
      {
        FILE_INFO info = {"C:/OpenModelica1.12.0-dev-32bit/lib/omlibrary/Modelica 3.2.2/StateGraph.mo",1974,5,1974,69,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nstep1.nOut >= 0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp23 = 1;
    }
  }
  TRACE_POP
}
int StategraphSample_updateBoundParameters(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  StategraphSample_eqFunction_61(data, threadData);

  StategraphSample_eqFunction_62(data, threadData);

  StategraphSample_eqFunction_63(data, threadData);

  StategraphSample_eqFunction_64(data, threadData);

  StategraphSample_eqFunction_65(data, threadData);

  StategraphSample_eqFunction_66(data, threadData);

  StategraphSample_eqFunction_67(data, threadData);

  StategraphSample_eqFunction_68(data, threadData);

  StategraphSample_eqFunction_69(data, threadData);

  StategraphSample_eqFunction_70(data, threadData);

  StategraphSample_eqFunction_71(data, threadData);

  StategraphSample_eqFunction_72(data, threadData);
  
  TRACE_POP
  return 0;
}

#if defined(__cplusplus)
}
#endif


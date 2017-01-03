#include "PW_PowerSystem_functions.h"
#ifdef __cplusplus
extern "C" {
#endif

#include "PW_PowerSystem_includes.h"


Modelica_Electrical_Machines_Interfaces_DCMachines_PowerBalanceDCEE omc_Modelica_Electrical_Machines_Interfaces_DCMachines_PowerBalanceDCEE(threadData_t *threadData, modelica_real omc_powerArmature, modelica_real omc_powerMechanical, modelica_real omc_powerInertiaStator, modelica_real omc_powerInertiaRotor, modelica_real omc_lossPowerTotal, modelica_real omc_lossPowerArmature, modelica_real omc_lossPowerCore, modelica_real omc_lossPowerStrayLoad, modelica_real omc_lossPowerFriction, modelica_real omc_lossPowerBrush, modelica_real omc_powerExcitation, modelica_real omc_lossPowerExcitation)
{
  Modelica_Electrical_Machines_Interfaces_DCMachines_PowerBalanceDCEE tmp1;
  tmp1._powerArmature = omc_powerArmature;
  tmp1._powerMechanical = omc_powerMechanical;
  tmp1._powerInertiaStator = omc_powerInertiaStator;
  tmp1._powerInertiaRotor = omc_powerInertiaRotor;
  tmp1._lossPowerTotal = omc_lossPowerTotal;
  tmp1._lossPowerArmature = omc_lossPowerArmature;
  tmp1._lossPowerCore = omc_lossPowerCore;
  tmp1._lossPowerStrayLoad = omc_lossPowerStrayLoad;
  tmp1._lossPowerFriction = omc_lossPowerFriction;
  tmp1._lossPowerBrush = omc_lossPowerBrush;
  tmp1._powerExcitation = omc_powerExcitation;
  tmp1._lossPowerExcitation = omc_lossPowerExcitation;
  return tmp1;
}

modelica_metatype boxptr_Modelica_Electrical_Machines_Interfaces_DCMachines_PowerBalanceDCEE(threadData_t *threadData, modelica_metatype _powerArmature, modelica_metatype _powerMechanical, modelica_metatype _powerInertiaStator, modelica_metatype _powerInertiaRotor, modelica_metatype _lossPowerTotal, modelica_metatype _lossPowerArmature, modelica_metatype _lossPowerCore, modelica_metatype _lossPowerStrayLoad, modelica_metatype _lossPowerFriction, modelica_metatype _lossPowerBrush, modelica_metatype _powerExcitation, modelica_metatype _lossPowerExcitation)
{
  return mmc_mk_box13(3, &Modelica_Electrical_Machines_Interfaces_DCMachines_PowerBalanceDCEE__desc, _powerArmature, _powerMechanical, _powerInertiaStator, _powerInertiaRotor, _lossPowerTotal, _lossPowerArmature, _lossPowerCore, _lossPowerStrayLoad, _lossPowerFriction, _lossPowerBrush, _powerExcitation, _lossPowerExcitation);
}

Modelica_Electrical_Machines_Interfaces_DCMachines_PowerBalanceDCEE$motor$powerBalance omc_Modelica_Electrical_Machines_Interfaces_DCMachines_PowerBalanceDCEE$motor$powerBalance(threadData_t *threadData, modelica_real omc_powerArmature, modelica_real omc_powerMechanical, modelica_real omc_powerInertiaStator, modelica_real omc_powerInertiaRotor, modelica_real omc_lossPowerTotal, modelica_real omc_lossPowerArmature, modelica_real omc_lossPowerCore, modelica_real omc_lossPowerStrayLoad, modelica_real omc_lossPowerFriction, modelica_real omc_lossPowerBrush, modelica_real omc_powerExcitation, modelica_real omc_lossPowerExcitation)
{
  Modelica_Electrical_Machines_Interfaces_DCMachines_PowerBalanceDCEE$motor$powerBalance tmp1;
  tmp1._powerArmature = omc_powerArmature;
  tmp1._powerMechanical = omc_powerMechanical;
  tmp1._powerInertiaStator = omc_powerInertiaStator;
  tmp1._powerInertiaRotor = omc_powerInertiaRotor;
  tmp1._lossPowerTotal = omc_lossPowerTotal;
  tmp1._lossPowerArmature = omc_lossPowerArmature;
  tmp1._lossPowerCore = omc_lossPowerCore;
  tmp1._lossPowerStrayLoad = omc_lossPowerStrayLoad;
  tmp1._lossPowerFriction = omc_lossPowerFriction;
  tmp1._lossPowerBrush = omc_lossPowerBrush;
  tmp1._powerExcitation = omc_powerExcitation;
  tmp1._lossPowerExcitation = omc_lossPowerExcitation;
  return tmp1;
}

modelica_metatype boxptr_Modelica_Electrical_Machines_Interfaces_DCMachines_PowerBalanceDCEE$motor$powerBalance(threadData_t *threadData, modelica_metatype _powerArmature, modelica_metatype _powerMechanical, modelica_metatype _powerInertiaStator, modelica_metatype _powerInertiaRotor, modelica_metatype _lossPowerTotal, modelica_metatype _lossPowerArmature, modelica_metatype _lossPowerCore, modelica_metatype _lossPowerStrayLoad, modelica_metatype _lossPowerFriction, modelica_metatype _lossPowerBrush, modelica_metatype _powerExcitation, modelica_metatype _lossPowerExcitation)
{
  return mmc_mk_box13(3, &Modelica_Electrical_Machines_Interfaces_DCMachines_PowerBalanceDCEE$motor$powerBalance__desc, _powerArmature, _powerMechanical, _powerInertiaStator, _powerInertiaRotor, _lossPowerTotal, _lossPowerArmature, _lossPowerCore, _lossPowerStrayLoad, _lossPowerFriction, _lossPowerBrush, _powerExcitation, _lossPowerExcitation);
}

Modelica_Electrical_Machines_Losses_BrushParameters omc_Modelica_Electrical_Machines_Losses_BrushParameters(threadData_t *threadData, modelica_real omc_V, modelica_real omc_ILinear)
{
  Modelica_Electrical_Machines_Losses_BrushParameters tmp1;
  tmp1._V = omc_V;
  tmp1._ILinear = omc_ILinear;
  return tmp1;
}

modelica_metatype boxptr_Modelica_Electrical_Machines_Losses_BrushParameters(threadData_t *threadData, modelica_metatype _V, modelica_metatype _ILinear)
{
  return mmc_mk_box3(3, &Modelica_Electrical_Machines_Losses_BrushParameters__desc, _V, _ILinear);
}

Modelica_Electrical_Machines_Losses_BrushParameters$motor$brushParameters omc_Modelica_Electrical_Machines_Losses_BrushParameters$motor$brushParameters(threadData_t *threadData, modelica_real omc_V, modelica_real omc_ILinear)
{
  Modelica_Electrical_Machines_Losses_BrushParameters$motor$brushParameters tmp1;
  tmp1._V = omc_V;
  tmp1._ILinear = omc_ILinear;
  return tmp1;
}

modelica_metatype boxptr_Modelica_Electrical_Machines_Losses_BrushParameters$motor$brushParameters(threadData_t *threadData, modelica_metatype _V, modelica_metatype _ILinear)
{
  return mmc_mk_box3(3, &Modelica_Electrical_Machines_Losses_BrushParameters$motor$brushParameters__desc, _V, _ILinear);
}

Modelica_Electrical_Machines_Losses_CoreParameters omc_Modelica_Electrical_Machines_Losses_CoreParameters(threadData_t *threadData, modelica_integer omc_m, modelica_real omc_PRef, modelica_real omc_VRef, modelica_real omc_wRef, modelica_real omc_ratioHysteresis, modelica_real omc_GcRef, modelica_real omc_wMin)
{
  Modelica_Electrical_Machines_Losses_CoreParameters tmp1;
  tmp1._m = omc_m;
  tmp1._PRef = omc_PRef;
  tmp1._VRef = omc_VRef;
  tmp1._wRef = omc_wRef;
  tmp1._ratioHysteresis = omc_ratioHysteresis;
  tmp1._GcRef = omc_GcRef;
  tmp1._wMin = omc_wMin;
  return tmp1;
}

modelica_metatype boxptr_Modelica_Electrical_Machines_Losses_CoreParameters(threadData_t *threadData, modelica_metatype _m, modelica_metatype _PRef, modelica_metatype _VRef, modelica_metatype _wRef, modelica_metatype _ratioHysteresis, modelica_metatype _GcRef, modelica_metatype _wMin)
{
  return mmc_mk_box8(3, &Modelica_Electrical_Machines_Losses_CoreParameters__desc, _m, _PRef, _VRef, _wRef, _ratioHysteresis, _GcRef, _wMin);
}

Modelica_Electrical_Machines_Losses_CoreParameters$motor$coreParameters omc_Modelica_Electrical_Machines_Losses_CoreParameters$motor$coreParameters(threadData_t *threadData, modelica_integer omc_m, modelica_real omc_PRef, modelica_real omc_VRef, modelica_real omc_wRef, modelica_real omc_ratioHysteresis, modelica_real omc_GcRef, modelica_real omc_wMin)
{
  Modelica_Electrical_Machines_Losses_CoreParameters$motor$coreParameters tmp1;
  tmp1._m = omc_m;
  tmp1._PRef = omc_PRef;
  tmp1._VRef = omc_VRef;
  tmp1._wRef = omc_wRef;
  tmp1._ratioHysteresis = omc_ratioHysteresis;
  tmp1._GcRef = omc_GcRef;
  tmp1._wMin = omc_wMin;
  return tmp1;
}

modelica_metatype boxptr_Modelica_Electrical_Machines_Losses_CoreParameters$motor$coreParameters(threadData_t *threadData, modelica_metatype _m, modelica_metatype _PRef, modelica_metatype _VRef, modelica_metatype _wRef, modelica_metatype _ratioHysteresis, modelica_metatype _GcRef, modelica_metatype _wMin)
{
  return mmc_mk_box8(3, &Modelica_Electrical_Machines_Losses_CoreParameters$motor$coreParameters__desc, _m, _PRef, _VRef, _wRef, _ratioHysteresis, _GcRef, _wMin);
}

Modelica_Electrical_Machines_Losses_FrictionParameters omc_Modelica_Electrical_Machines_Losses_FrictionParameters(threadData_t *threadData, modelica_real omc_PRef, modelica_real omc_wRef, modelica_real omc_power_w, modelica_real omc_tauRef, modelica_real omc_linear, modelica_real omc_wLinear, modelica_real omc_tauLinear)
{
  Modelica_Electrical_Machines_Losses_FrictionParameters tmp1;
  tmp1._PRef = omc_PRef;
  tmp1._wRef = omc_wRef;
  tmp1._power_w = omc_power_w;
  tmp1._tauRef = omc_tauRef;
  tmp1._linear = omc_linear;
  tmp1._wLinear = omc_wLinear;
  tmp1._tauLinear = omc_tauLinear;
  return tmp1;
}

modelica_metatype boxptr_Modelica_Electrical_Machines_Losses_FrictionParameters(threadData_t *threadData, modelica_metatype _PRef, modelica_metatype _wRef, modelica_metatype _power_w, modelica_metatype _tauRef, modelica_metatype _linear, modelica_metatype _wLinear, modelica_metatype _tauLinear)
{
  return mmc_mk_box8(3, &Modelica_Electrical_Machines_Losses_FrictionParameters__desc, _PRef, _wRef, _power_w, _tauRef, _linear, _wLinear, _tauLinear);
}

Modelica_Electrical_Machines_Losses_FrictionParameters$motor__frictionParameters omc_Modelica_Electrical_Machines_Losses_FrictionParameters$motor__frictionParameters(threadData_t *threadData, modelica_real omc_PRef, modelica_real omc_wRef, modelica_real omc_power_w, modelica_real omc_tauRef, modelica_real omc_linear, modelica_real omc_wLinear, modelica_real omc_tauLinear)
{
  Modelica_Electrical_Machines_Losses_FrictionParameters$motor__frictionParameters tmp1;
  tmp1._PRef = omc_PRef;
  tmp1._wRef = omc_wRef;
  tmp1._power_w = omc_power_w;
  tmp1._tauRef = omc_tauRef;
  tmp1._linear = omc_linear;
  tmp1._wLinear = omc_wLinear;
  tmp1._tauLinear = omc_tauLinear;
  return tmp1;
}

modelica_metatype boxptr_Modelica_Electrical_Machines_Losses_FrictionParameters$motor__frictionParameters(threadData_t *threadData, modelica_metatype _PRef, modelica_metatype _wRef, modelica_metatype _power_w, modelica_metatype _tauRef, modelica_metatype _linear, modelica_metatype _wLinear, modelica_metatype _tauLinear)
{
  return mmc_mk_box8(3, &Modelica_Electrical_Machines_Losses_FrictionParameters$motor__frictionParameters__desc, _PRef, _wRef, _power_w, _tauRef, _linear, _wLinear, _tauLinear);
}

Modelica_Electrical_Machines_Losses_StrayLoadParameters omc_Modelica_Electrical_Machines_Losses_StrayLoadParameters(threadData_t *threadData, modelica_real omc_PRef, modelica_real omc_IRef, modelica_real omc_wRef, modelica_real omc_power_w, modelica_real omc_tauRef)
{
  Modelica_Electrical_Machines_Losses_StrayLoadParameters tmp1;
  tmp1._PRef = omc_PRef;
  tmp1._IRef = omc_IRef;
  tmp1._wRef = omc_wRef;
  tmp1._power_w = omc_power_w;
  tmp1._tauRef = omc_tauRef;
  return tmp1;
}

modelica_metatype boxptr_Modelica_Electrical_Machines_Losses_StrayLoadParameters(threadData_t *threadData, modelica_metatype _PRef, modelica_metatype _IRef, modelica_metatype _wRef, modelica_metatype _power_w, modelica_metatype _tauRef)
{
  return mmc_mk_box6(3, &Modelica_Electrical_Machines_Losses_StrayLoadParameters__desc, _PRef, _IRef, _wRef, _power_w, _tauRef);
}

Modelica_Electrical_Machines_Losses_StrayLoadParameters$motor$strayLoadParameters omc_Modelica_Electrical_Machines_Losses_StrayLoadParameters$motor$strayLoadParameters(threadData_t *threadData, modelica_real omc_PRef, modelica_real omc_IRef, modelica_real omc_wRef, modelica_real omc_power_w, modelica_real omc_tauRef)
{
  Modelica_Electrical_Machines_Losses_StrayLoadParameters$motor$strayLoadParameters tmp1;
  tmp1._PRef = omc_PRef;
  tmp1._IRef = omc_IRef;
  tmp1._wRef = omc_wRef;
  tmp1._power_w = omc_power_w;
  tmp1._tauRef = omc_tauRef;
  return tmp1;
}

modelica_metatype boxptr_Modelica_Electrical_Machines_Losses_StrayLoadParameters$motor$strayLoadParameters(threadData_t *threadData, modelica_metatype _PRef, modelica_metatype _IRef, modelica_metatype _wRef, modelica_metatype _power_w, modelica_metatype _tauRef)
{
  return mmc_mk_box6(3, &Modelica_Electrical_Machines_Losses_StrayLoadParameters$motor$strayLoadParameters__desc, _PRef, _IRef, _wRef, _power_w, _tauRef);
}

DLLExport
modelica_real omc_Modelica_Electrical_Machines_Losses_DCMachines_brushVoltageDrop(threadData_t *threadData, Modelica_Electrical_Machines_Losses_BrushParameters _brushParameters, modelica_real _i)
{
  modelica_real _v;
  modelica_real tmp1;
  modelica_boolean tmp2;
  modelica_real tmp3;
  modelica_boolean tmp4;
  modelica_real tmp5;
  _tailrecursive: OMC_LABEL_UNUSED
  if((_brushParameters._V <= 0.0))
  {
    _v = 0.0;
  }
  else
  {
    tmp4 = (modelica_boolean)(_i > _brushParameters._ILinear);
    if(tmp4)
    {
      tmp5 = _brushParameters._V;
    }
    else
    {
      tmp2 = (modelica_boolean)(_i < (-_brushParameters._ILinear));
      if(tmp2)
      {
        tmp3 = (-_brushParameters._V);
      }
      else
      {
        tmp1 = _brushParameters._ILinear;
        if (tmp1 == 0) {throwStreamPrint(threadData, "Division by zero %s", "i / brushParameters.ILinear");}
        tmp3 = (_brushParameters._V) * ((_i) / tmp1);
      }
      tmp5 = tmp3;
    }
    _v = tmp5;
  }
  _return: OMC_LABEL_UNUSED
  return _v;
}
modelica_metatype boxptr_Modelica_Electrical_Machines_Losses_DCMachines_brushVoltageDrop(threadData_t *threadData, modelica_metatype _brushParameters, modelica_metatype _i)
{
  Modelica_Electrical_Machines_Losses_BrushParameters tmp1;
  modelica_real tmp2;
  modelica_real tmp3;
  modelica_real tmp4;
  modelica_real _v;
  modelica_metatype out_v;
  modelica_metatype tmpMeta[2] __attribute__((unused)) = {0};
  tmpMeta[0] = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_brushParameters), 2)));
  tmp2 = mmc_unbox_real(tmpMeta[0]);
  tmp1._V = tmp2;
  tmpMeta[1] = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_brushParameters), 3)));
  tmp3 = mmc_unbox_real(tmpMeta[1]);
  tmp1._ILinear = tmp3;tmp4 = mmc_unbox_real(_i);
  _v = omc_Modelica_Electrical_Machines_Losses_DCMachines_brushVoltageDrop(threadData, tmp1, tmp4);
  out_v = mmc_mk_rcon(_v);
  return out_v;
}

#ifdef __cplusplus
}
#endif

/**************************************************************/ 
/* */ 
/* User-Defined Function: Redlich-Kwong Equation of State */ 
/* for Real Gas Modeling */ 
/* */ 
/* Author: Frank Kelecy */ 
/* Date: May 2003 */ 
/* Version: 1.02 */ 
/* */ 
/* This implementation is completely general. */ 
/* Parameters set for CO2. */ 
/* */ 
/**************************************************************/ 
#include "udf.h" 
#include "stdio.h" 
#include "ctype.h" 
#include "stdarg.h" 
/* The variables below need to be set for a particular gas */ 
/* CO2 */ 
/* REAL GAS EQUATION OF STATE MODEL - BASIC VARIABLES */ 
/* ALL VARIABLES ARE IN SI UNITS! */ 
#define RGASU UNIVERSAL_GAS_CONSTANT 
#define PI 3.141592654 
#define MWT 18.015 
#define PCRIT 22.048e6 
#define TCRIT 647.3
#define ZCRIT 0.229
#define VCRIT 3.10852e-3 
#define NRK 0.96 
/* IDEAL GAS SPECIFIC HEAT CURVE FIT */ 
#define CC1 1789.761 
#define CC2 1.0679e-1
#define CC3 5.859e-4 
#define CC4 -1.99637e-7 
#define CC5 0.00 
/* REFERENCE STATE */ 
#define P_REF 101325 
#define T_REF 288.15 
/* OPTIONAL REFERENCE (OFFSET) VALUES FOR ENTHALPY AND ENTROPY */ 
#define H_REF 0.0 
#define S_REF 0.0 
static int (*usersMessage)(const char *,...); 
static void (*usersError)(const char *,...); 
/* Static variables associated with Redlich-Kwong Model */ 
static double rgas, a0, b0, c0, bb, cp_int_ref; 
DEFINE_ON_DEMAND(I_do_nothing) 
{ 
 /* this is a dummy function to allow us */ 
 /* to use the compiled UDFs utility */ 
} 
/*------------------------------------------------------------*/ 
/* FUNCTION: RKEOS_Setup */ 
/*------------------------------------------------------------*/ 
void RKEOS_Setup(Domain *domain, cxboolean vapor_phase, char *species_list, 
 int(*messagefunc)(const char *format,...), 
 void (*errorfunc)(const char *format,...)) 
{ 
 rgas = RGASU/MWT; 
 a0 = 0.42747*rgas*rgas*TCRIT*TCRIT/PCRIT; 
 b0 = 0.08664*rgas*TCRIT/PCRIT;
 c0 = rgas*TCRIT/(PCRIT+a0/(VCRIT*(VCRIT+b0)))+b0-VCRIT; 
 bb = b0-c0; 
 cp_int_ref = CC1*log(T_REF)+T_REF*(CC2+ 
 T_REF*(0.5*CC3+T_REF*(0.333333*CC4+0.25*CC5*T_REF))); 
 usersMessage = messagefunc; 
 usersError = errorfunc; 
 usersMessage("\nLoading Redlich-Kwong Library: %s\n", species_list); 
} 
/*------------------------------------------------------------*/ 
/* FUNCTION: RKEOS_pressure */ 
/* Returns pressure given T and density */ 
/*------------------------------------------------------------*/ 
double RKEOS_pressure(double temp, double density) 
{ 
 double v = 1./density; 
 double afun = a0*pow(TCRIT/temp,NRK); 
 return rgas*temp/(v-bb)-afun/(v*(v+b0)); 
} 
/*------------------------------------------------------------*/ 
/* FUNCTION: RKEOS_spvol */ 
/* Returns specific volume given T and P */ 
/*------------------------------------------------------------*/ 
double RKEOS_spvol(double temp, double press) 
{ 
 double a1,a2,a3; 
 double vv,vv1,vv2,vv3; 
 double qq,qq3,sqq,rr,tt,dd; 
 double afun = a0*pow(TCRIT/temp,NRK); 
 a1 = c0-rgas*temp/press; 
 a2 = -(bb*b0+rgas*temp*b0/press-afun/press); 
 a3 = -afun*bb/press; 
 /* Solve cubic equation for specific volume */
 qq = (a1*a1-3.*a2)/9.; 
 rr = (2*a1*a1*a1-9.*a1*a2+27.*a3)/54.; 
 qq3 = qq*qq*qq; 
 dd = qq3-rr*rr; 
 /* If dd < 0, then we have one real root */ 
 /* If dd >= 0, then we have three roots -> choose largest root */ 
 if (dd < 0.) { 
 tt = pow(sqrt(-dd)+fabs(rr),0.333333); 
 vv = (tt+qq/tt)-a1/3.; 
 } else { 
 tt = acos(rr/sqrt(qq3)); 
 sqq = sqrt(qq); 
 vv1 = -2.*sqq*cos(tt/3.)-a1/3.; 
 vv2 = -2.*sqq*cos((tt+2.*PI)/3.)-a1/3.; 
 vv3 = -2.*sqq*cos((tt+4.*PI)/3.)-a1/3.; 
 vv = (vv1 > vv2) ? vv1 : vv2; 
 vv = (vv > vv3) ? vv : vv3; 
 } 
 return vv; 
} 
/*------------------------------------------------------------*/ 
/* FUNCTION: RKEOS_density */ 
/* Returns density given T and P */ 
/*------------------------------------------------------------*/ 
double RKEOS_density(cell_t cell, Thread *thread, cxboolean vapor_phase, double temp, double press, double yi[]) 
{ 
 return 1./RKEOS_spvol(temp, press); /* (Kg/m3) */ 
} 
/*------------------------------------------------------------*/ 
/* FUNCTION: RKEOS_dvdp */ 
/* Returns dv/dp given T and rho */ 
/*------------------------------------------------------------*/ 
double RKEOS_dvdp(double temp, double density)
{ 
 double a1,a2,a1p,a2p,a3p,v,press; 
 double afun = a0*pow(TCRIT/temp,NRK); 
 press = RKEOS_pressure(temp, density); 
 v = 1./density; 
 a1 = c0-rgas*temp/press; 
 a2 = -(bb*b0+rgas*temp*b0/press-afun/press); 
 a1p = rgas*temp/(press*press); 
 a2p = a1p*b0-afun/(press*press); 
 a3p = afun*bb/(press*press); 
 return -(a3p+v*(a2p+v*a1p))/(a2+v*(2.*a1+3.*v)); 
} 
/*------------------------------------------------------------*/ 
/* FUNCTION: RKEOS_dvdt */ 
/* Returns dv/dT given T and rho */ 
/*------------------------------------------------------------*/ 
double RKEOS_dvdt(double temp, double density) 
{ 
 double a1,a2,dadt,a1t,a2t,a3t,v,press; 
 double afun = a0*pow(TCRIT/temp,NRK); 
 press = RKEOS_pressure(temp, density); 
 v = 1./density; 
 dadt = -NRK*afun/temp; 
 a1 = c0-rgas*temp/press; 
 a2 = -(bb*b0+rgas*temp*b0/press-afun/press); 
 a1t = -rgas/press; 
 a2t = a1t*b0+dadt/press; 
 a3t = -dadt*bb/press; 
 return -(a3t+v*(a2t+v*a1t))/(a2+v*(2.*a1+3.*v)); 
} 
/*------------------------------------------------------------*/
/* FUNCTION: RKEOS_Cp_ideal_gas */ 
/* Returns ideal gas specific heat given T */ 
/*------------------------------------------------------------*/ 
double RKEOS_Cp_ideal_gas(double temp) 
{ 
 return (CC1+temp*(CC2+temp*(CC3+temp*(CC4+temp*CC5)))); 
} 
/*------------------------------------------------------------*/ 
/* FUNCTION: RKEOS_H_ideal_gas */ 
/* Returns ideal gas specific enthalpy given T */ 
/*------------------------------------------------------------*/ 
double RKEOS_H_ideal_gas(double temp) 
{ 
 return temp*(CC1+temp*(0.5*CC2+temp*(0.333333*CC3+ 
 temp*(0.25*CC4+temp*0.2*CC5)))); 
} 
/*------------------------------------------------------------*/ 
/* FUNCTION: RKEOS_specific_heat */ 
/* Returns specific heat given T and rho */ 
/*------------------------------------------------------------*/ 
double RKEOS_specific_heat(cell_t cell, Thread *thread, double temp, double density, double P, double yi[]) 
{ 
 double delta_Cp,press,v,dvdt,dadt; 
 double afun = a0*pow(TCRIT/temp,NRK); 
 press = RKEOS_pressure(temp, density); 
 v = 1./density; 
 dvdt = RKEOS_dvdt(temp, density); 
 dadt = -NRK*afun/temp; 
 delta_Cp = press*dvdt-rgas-dadt*(1.+NRK)/b0*log((v+b0)/v) 
 + afun*(1.+NRK)*dvdt/(v*(v+b0)); 
 return RKEOS_Cp_ideal_gas(temp)+delta_Cp; /* (J/Kg-K) */ 
}
/*------------------------------------------------------------*/ 
/* FUNCTION: RKEOS_enthalpy */ 
/* Returns specific enthalpy given T and rho */ 
/*------------------------------------------------------------*/ 
double RKEOS_enthalpy(cell_t cell, Thread *thread, double temp, double density, double P, double yi[]) 
{ 
 double delta_h,press, v; 
 double afun = a0*pow(TCRIT/temp,NRK); 
 press = RKEOS_pressure(temp, density); 
 v = 1./density; 
 delta_h = press*v-rgas*temp-afun*(1+NRK)/b0*log((v+b0)/v); 
 return H_REF+RKEOS_H_ideal_gas(temp)+delta_h; /* (J/Kg) */ 
} 
/*------------------------------------------------------------*/ 
/* FUNCTION: RKEOS_entropy */ 
/* Returns entropy given T and rho */ 
/*------------------------------------------------------------*/ 
double RKEOS_entropy(cell_t cell, Thread *thread, double temp, double density, double P, double yi[]) 
{ 
 double delta_s,v,v0,dadt,cp_integral; 
 double afun = a0*pow(TCRIT/temp,NRK); 
 cp_integral = CC1*log(temp)+temp*(CC2+temp*(0.5*CC3+ 
 temp*(0.333333*CC4+0.25*CC5*temp))) 
 - cp_int_ref; 
 v = 1./density; 
 v0 = rgas*temp/P_REF; 
 dadt = -NRK*afun/temp; 
 delta_s = rgas*log((v-bb)/v0)+dadt/b0*log((v+b0)/v); 
 return S_REF+cp_integral+delta_s; /* (J/Kg-K) */ 
} 
/*------------------------------------------------------------*/ 
/* FUNCTION: RKEOS_mw
/* Returns molecular weight */ 
/*------------------------------------------------------------*/ 
double RKEOS_mw(double yi[]) 
{ 
 return MWT; /* (Kg/Kmol) */ 
} 
/*------------------------------------------------------------*/ 
/* FUNCTION: RKEOS_speed_of_sound */ 
/* Returns s.o.s given T and rho */ 
/*------------------------------------------------------------*/ 
double RKEOS_speed_of_sound(cell_t cell, Thread *thread, double temp, double density, double P, 
double yi[]) 
{ 
 double cp = RKEOS_specific_heat(cell, thread, temp, density, P, yi); 
 double dvdt = RKEOS_dvdt(temp, density); 
 double dvdp = RKEOS_dvdp(temp, density); 
 double v = 1./density; 
 double delta_c = -temp*dvdt*dvdt/dvdp; 
 return sqrt(cp/((delta_c-cp)*dvdp))*v; /* m/s */ 
} 
/*------------------------------------------------------------*/ 
/* FUNCTION: RKEOS_rho_t */ 
/*------------------------------------------------------------*/ 
double RKEOS_rho_t(cell_t cell, Thread *thread, double temp, double density, double P, double yi[]) 
{ 
 return -density*density*RKEOS_dvdt(temp, density); 
} 
/*------------------------------------------------------------*/ 
/* FUNCTION: RKEOS_rho_p */ 
/*------------------------------------------------------------*/ 
double RKEOS_rho_p(cell_t cell, Thread *thread, double temp, double density, double P, double yi[]) 
{ 
 return -density*density*RKEOS_dvdp(temp, density); 
} 
/*------------------------------------------------------------*/ 
/* FUNCTION: RKEOS_enthalpy_t */ 
/*------------------------------------------------------------*/ 
double RKEOS_enthalpy_t(cell_t cell, Thread *thread, double temp, double density, double P, double yi[]) 
{ 
 return RKEOS_specific_heat(cell, thread, temp, density, P, yi); 
} 
/*------------------------------------------------------------*/ 
/* FUNCTION: RKEOS_enthalpy_p */ 
/*------------------------------------------------------------*/ 
double RKEOS_enthalpy_p(cell_t cell, Thread *thread, double temp, double density, double P, double yi[]) 
{ 
 double v = 1./density; 
 double dvdt = RKEOS_dvdt(temp, density); 
 return v-temp*dvdt; 
} 
/*------------------------------------------------------------*/ 
/* FUNCTION: RKEOS_viscosity */ 
/*------------------------------------------------------------*/ 
double RKEOS_viscosity(cell_t cell, Thread *thread, double temp, double density, double P, double yi[]) 
{ 
 double mu,tr,tc,pcatm; 
 tr = temp/TCRIT; 
 tc = TCRIT; 
 pcatm = PCRIT/101325.; 
 mu = 6.3e-7*sqrt(MWT)*pow(pcatm,0.6666)/pow(tc,0.16666)* 
 (pow(tr,1.5)/(tr+0.8)); 
 return mu;
} 
/*------------------------------------------------------------*/ 
/* FUNCTION: RKEOS_thermal_conductivity */ 
/*------------------------------------------------------------*/ 
double RKEOS_thermal_conductivity(cell_t cell, Thread *thread, double temp, 
 double density, double P, double yi[]) 
{ 
 double cp, mu; 
 cp = RKEOS_Cp_ideal_gas(temp); 
 mu = RKEOS_viscosity(cell, thread, temp, density, P, yi); 
 return (cp+1.25*rgas)*mu; 
} 
/* Export Real Gas Functions to Solver */ 
UDF_EXPORT RGAS_Functions RealGasFunctionList = 
{ 
 RKEOS_Setup, /* initialize */ 
 RKEOS_density, /* density */ 
 RKEOS_enthalpy, /* enthalpy */ 
 RKEOS_entropy, /* entropy */ 
 RKEOS_specific_heat, /* specific_heat */ 
 RKEOS_mw, /* molecular_weight */ 
 RKEOS_speed_of_sound, /* speed_of_sound */ 
 RKEOS_viscosity, /* viscosity */ 
 RKEOS_thermal_conductivity, /* thermal_conductivity */ 
 RKEOS_rho_t, /* drho/dT |const p */ 
 RKEOS_rho_p, /* drho/dp |const T */ 
 RKEOS_enthalpy_t, /* dh/dT |const p */ 
 RKEOS_enthalpy_p /* dh/dp |const T */ 
};




#include<fenv.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<stddef.h>

long SEED;

int nx, ny, checking_time_count;

double delta_x, delta_t, end_time;

double *conc, *psi;

double relax_coeff, mobility;

double Tolerance, alloycomp;

double total, err, COMPERR;

double A, B, P, omega, ceq_liquid;

double ceq_alpha, ceq_beta, K_c, K_psi;

double del_f;

int system_size, IP_Flag, layer_thickness;

int lamellar_width;

FILE *fpout;
 

#include"Eutectic.h"

void get_input_eutectic (char *fnin, char *fnout) {

FILE *fpin, *fpcout;
char param[200];
setvbuf(stdout, NULL, _IONBF, 0);

if (!(fpcout = fopen (fnout, "w"))) {
printf("File: %s could not be opened\n.", fnout);
exit(1);
}
 
fprintf(fpcout, "The name of the file is: %s\n", fnout);
fprintf(fpcout, "Input is from          : %s\n", fnin);

if (!(fpin = fopen (fnin, "r"))) {
printf("FIle: %s could not be opened\n.", fnin);
exit(1);
}

if(fscanf (fpin, "%s%d", param, &nx));
if(fscanf (fpin, "%s%d", param, &ny));
if(fscanf (fpin, "%s%lf", param, &delta_x));
if(fscanf (fpin, "%s%lf", param, &delta_t));
if(fscanf (fpin, "%s%lf", param, &end_time));
if(fscanf (fpin, "%s%lf", param, &relax_coeff));
if(fscanf (fpin, "%s%lf", param, &mobility));
if(fscanf (fpin, "%s%lf", param, &A));
if(fscanf (fpin, "%s%lf", param, &B));
if(fscanf (fpin, "%s%lf", param, &P));
if(fscanf (fpin, "%s%lf", param, &omega));
if(fscanf (fpin, "%s%lf", param, &ceq_alpha));
if(fscanf (fpin, "%s%lf", param, &ceq_beta));
if(fscanf (fpin, "%s%lf", param, &del_f));
if(fscanf (fpin, "%s%lf", param, &K_c));
if(fscanf (fpin, "%s%lf", param, &K_psi));
if(fscanf (fpin, "%s%lf", param, &ceq_liquid));
if(fscanf (fpin, "%s%d", param, &checking_time_count));
if(fscanf (fpin, "%s%d", param, &IP_Flag));
if(fscanf (fpin, "%s%d", param, &layer_thickness));
if(fscanf (fpin, "%s%d", param, &lamellar_width));
if(fscanf (fpin, "%s%le", param, &Tolerance));
fclose (fpin);

printf ("nx = %d\n", nx);
printf ("ny = %d\n", ny);
printf ("delta_x = %lf\n", delta_x);
printf ("delta_t = %lf\n", delta_t);
printf ("end_time = %lf\n", end_time);
printf ("relaxation coefficient = %lf\n", relax_coeff);
printf ("mobility = %lf\n", mobility);
printf ("A = %lf\n", A);
printf ("B = %lf\n", B);
printf ("P = %lf\n", P);
printf ("omega = %lf\n", omega);
printf ("c_alpha = %lf\n", ceq_alpha);
printf ("c_beta = %lf\n", ceq_beta);
printf ("Undercooling = %lf\n", del_f);
printf ("K_c = %lf\n", K_c);
printf ("K_psi = %lf\n", K_psi);
printf ("Equillibrium Liquid composition = %lf\n", ceq_liquid);
printf ("checking time count = %d\n", checking_time_count);
printf ("Intial Profile Flag = %d\n", IP_Flag);
printf ("Layer thickness = %d\n", layer_thickness);
printf ("Lamella Width = %d\n", lamellar_width);
printf ("Tolerance = %le\n", Tolerance);

fprintf (fpcout, "nx = %d\n", nx);
fprintf (fpcout, "ny = %d\n", ny);
fprintf (fpcout, "delta_x = %lf\n", delta_x);
fprintf (fpcout, "delta_t = %lf\n", delta_t);
fprintf (fpcout, "end_time = %lf\n", end_time);
fprintf (fpcout, "Relaxation coefficient = %lf\n", relax_coeff);
fprintf (fpcout, "Mobility = %lf\n", mobility);
fprintf (fpcout, "A = %lf\n", A);
fprintf (fpcout, "B = %lf\n", B);
fprintf (fpcout, "P = %lf\n", P);
fprintf (fpcout, "Omega = %lf\n", omega);
fprintf (fpcout, "C_alpha = %lf\n", ceq_alpha);
fprintf (fpcout, "C_beta = %lf\n", ceq_beta);
fprintf (fpcout, "Undercooling = %lf\n", del_f);
fprintf (fpcout, "K_c = %lf\n", K_c);
fprintf (fpcout, "K_psi = %lf\n", K_psi);
fprintf (fpcout, "Equillibrium Liquid composition = %lf\n", ceq_liquid);
fprintf (fpcout, "checking time count = %d\n", checking_time_count);
fprintf (fpcout, "Intial Profile Flag = %d\n", IP_Flag);
fprintf (fpcout, "Layer thickness = %d\n", layer_thickness);
fprintf (fpcout, "Lamella width = %d\n", lamellar_width);
fprintf (fpcout, "Tolerance = %le\n", Tolerance);

fclose (fpcout);

}

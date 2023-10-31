#include"Eutectic.h"

void out_conf(int steps) {

	FILE *fpc;
	FILE *fpp;
	int i, j;
	char fn1[100];
	char fn2[100];

	sprintf(fn1, "Final_Conc_Profile.%08d", steps);
	sprintf(fn2, "Final_Psi_Profile.%08d", steps);

	fpc = fopen(fn1, "w");
	fpp = fopen(fn2, "w");
	for(i = 0; i < nx; i++) {
		for(j = 0; j < ny; j++) {
		fprintf(fpc, "%d\t%d\t%lf\n", i, j, conc[j + i * ny]);
		fprintf(fpp, "%d\t%d\t%lf\n", i, j, psi[j + i * ny]);
		}
		fprintf(fpc, "\n");
		fprintf(fpp, "\n");
	}
	fclose(fpc);

}

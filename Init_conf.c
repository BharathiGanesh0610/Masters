#include"Eutectic.h"

void init_conf() {

	float ran(long *idum);
        double *random_num;
        int i, j; // coordinate control variable
        int rep, off_A1, off_A2, off_B1, off_B2;
        double sum, mean, epsilon;

        system_size = nx * ny;

        rep = nx / (2 * lamellar_width);

        random_num = (double*)malloc(sizeof(double) * system_size);
        
        sum = 0.0;

//      Intial Profile

        if(IP_Flag == 0) {

//      FOR RANDOM NOISE ALL OVER THE DOMAIN

        for(i = 0; i < nx; i++) {
                for(j = 0; j < ny; j++) {

                // GENERATING A 2D ARRAY OF RANDOM NUMBERS FROM -1/2 TO 1/2
                random_num[j + i * ny] = ran(&SEED);
                random_num[j + i * ny] = (2.0 * random_num[j + i * ny]) - 1.0;
                random_num[j + i * ny] = random_num[j + i * ny] * 0.5;
                sum += random_num[j + i * ny];

                }
        }

        mean = sum / (double)system_size;

        for(i = 0; i < nx; i++) {
                for(j = 0; j < ny; j++) {

                epsilon = mean - random_num[j + i * ny];
                conc[j + i * ny] = ceq_liquid + epsilon;
                psi[j + i * ny] = epsilon;

                }
        }
        
	}

        if(IP_Flag == 1) {

//      SOLID LAYER AT THE BOTTOM WITH ALTERNATE LAMELLA
         
        for(i = 0; i < nx; i++) {
                for(j = 0; j < ny; j++) {
                conc[j + i * ny] = ceq_liquid;
                psi[j + i * ny] = 0.0;
                }
        }
        for(i = 0; i < nx; i++) {
                for(j = 0; j <= layer_thickness; j++) {
                conc[j + i * ny] = ceq_alpha;
                psi[j + i * ny] = 1.0;
                }
        }
        for (int m = 1; m <= rep; m++) {
        off_A1 = (lamellar_width / 2) + ((m - 1) * 2.0 * lamellar_width);
        off_A2 = (lamellar_width / 2) + (m * lamellar_width) + ((m - 1) * lamellar_width);
        for (int i = off_A1; i <= off_A2; i++) {
                for (int j = 0; j <= layer_thickness; j++) {
                conc[j + i * ny] = ceq_beta;
                psi[j + i * ny] = 1.0;
                }
        }
        }
        for (int m = 1; m < rep; m++) {
        off_B1 = (lamellar_width / 2) + (m * lamellar_width) + ((m - 1) * lamellar_width);
        off_B2 = (lamellar_width / 2) + (m * 2.0 * lamellar_width);
        for (int i = off_B1; i <= off_B2; i++) {
                for (int j = 0; j <= layer_thickness; j++) {
                conc[j + i * ny] = ceq_alpha;
                psi[j + i * ny] = 1.0;
                }
        }
        }

        }

        if(IP_Flag == 2) {

//      SOLID LAYER AT THE BOTTOM

        for(i = 0; i < nx; i++) {
                for(j = 0; j < ny; j++) {
                        if(j <= layer_thickness) {
                        conc[j + i * ny] = ceq_liquid;
                        psi[j + i * ny] = 1.0;
                        } else {
                        conc[j + i * ny] = ceq_liquid;
                        psi[j + i * ny] = 0.0;
			}
		}
	}
	
	}

	alloycomp = 0.0;

	for(i = 0; i < nx; i++) {
		for(j = 0; j < ny; j++) {
		alloycomp += conc[j + i * ny];
		}
	}

	alloycomp = alloycomp / (double)system_size;

free(random_num);

}


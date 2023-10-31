/*
**********************************************************
SOLVER FOR EUTECTIC GROWTH WITH ISOSTRUCTURAL SOLID PHASES
**********************************************************
*/

#include "Eutectic.h"


void evolve() {

void out_conf (int steps);

double *mu, *rhs_psi, *tempreal, *grad_mux, *grad_muy;
double df_dc, df_dpsi, h_prime, g_prime, h_psi, g_psi;
double rconc, rpsi, fl, fs, dfl_dc, dfs_dc;
double Ga_l, Ga_s, Gb_l, Gb_s, net_flux; 
double c_lapla, psi_lapla, rconc_new, rpsi_new;
int i, j, N, E, W, S; // coordinate control variable
int n; // time coordinate control variable
double sum, mean, error, maxerror;
int loop_condition;
		
	system_size = nx * ny;
	
	tempreal = (double*)malloc(sizeof(double) * system_size);
	mu = (double*)malloc(sizeof(double) * system_size);
	rhs_psi = (double*)malloc(sizeof(double) * system_size);
	grad_mux = (double*)malloc(sizeof(double) * system_size);
	grad_muy = (double*)malloc(sizeof(double) * system_size);
	
	sum = 0.0;
	COMPERR = 0.0001;
	rconc_new = 0.0; rpsi_new = 0.0;
	Ga_l = 4.06484; Gb_l = 4.06484; Ga_s = -0.01; Gb_s = -0.01;

	// UNCOMMENT TO DISPLAY AVERAGE COMPOSITION OF THE SYSTEM
	/*	
	for(i = 0; i < nx; i++) {
		for(j = 0; j < ny; j++) {
		 sum += conc[j + i * ny];
		}
	}
	double avg = sum / (double)(nx * ny);
	printf("%le\n", avg);
       	*/

	for (i = 0; i < nx; i++) {
		for (j = 0; j < nx; j++) {
		tempreal[j + i * ny] = conc[j + i * ny];
		}
	}

	loop_condition = 1;

	for(n = 0; n <= (int)(end_time/delta_t); n++) {	
	
                if (n % checking_time_count == 0) {

                out_conf(n);

                }

                if (loop_condition == 0) {

                out_conf(n);
                break;

                }
				
		for(i = 0; i < nx; i++) {
                E = i + 1;
                W = i - 1;
			
		if(E == nx) E = 0; //Periodic BC
		if(W < 0) W = W + nx; //Periodic Bc

                	for(j = 0; j < ny; j++) {
			N = j + 1;
			S = j - 1;

			if(N == ny) N = S; //No flux
			if(S < 0) S = N;   //No flux
			
			rpsi = psi[j + i * ny];
			rconc = conc[j + i * ny];
			h_psi = rpsi * rpsi * (3.0 - 2.0 * rpsi);
			g_psi = rpsi * rpsi * (1.0 - rpsi) * (1.0 - rpsi);
			h_prime = 6.0 * rpsi * (1.0 - rpsi);
			g_prime = 2.0 * rpsi * (1.0 - 3.0 * rpsi + 2.0 * rpsi * rpsi);
			fl = rconc * Ga_l + (1.0 - rconc) * Gb_l + A * (rconc * log(rconc) + (1.0 - rconc) * log(1.0 - rconc)) + del_f;
			fs = rconc * Ga_s + (1.0 - rconc) * Gb_s + B * (rconc * log(rconc) + (1.0 - rconc) * log(1.0 - rconc)) + omega * rconc * (1.0 - rconc); 
			dfl_dc = Ga_l - Gb_l + A * (log(rconc) - log(1.0 - rconc));
			dfs_dc = Ga_s - Gb_s + B * (log(rconc) - log(1.0 - rconc)) + omega * (1.0 - 2.0 * rconc);

			df_dc = (1.0 - h_psi) * dfl_dc + h_psi * dfs_dc;
			df_dpsi = h_prime * (fs - fl) + P * g_prime; 
		
			c_lapla = (conc[N + i * ny] + conc[S + i * ny] + conc[j + E * ny] + conc[j + W * ny] - 4.0 * conc[j + i * ny]) / (delta_x * delta_x);
			psi_lapla = (psi[N + i * ny] + psi[S + i * ny] + psi[j + E * ny] + psi[j + W * ny] - 4.0 * psi[j + i * ny]) / (delta_x * delta_x);

			mu[j + i * ny] = df_dc - K_c * K_c * c_lapla;
			rhs_psi[j + i * ny] = df_dpsi - K_psi * K_psi * psi_lapla; 
	
			}
                }  

		for(i = 0; i < nx; i++) {
		E = i + 1;
		W = i - 1;

		if(E == nx) E = 0; //Periodic BC
		if(W < 0) W = W + nx; //Periodic BC

			for(j = 0; j < ny; j++) {
			N = j + 1;
			S = j - 1;

			if(N == ny) N = S; //No flux
			if(S < 0) S = N; //No flux

			grad_mux[j + i * ny] = (mu[j + E * ny] - mu[j + W * ny]) / (2.0 * delta_x);
			grad_muy[j + i * ny] = (mu[N + i * ny] - mu[S + i * ny]) / (2.0 * delta_x);

			}
		}
				
		for(i = 0; i < nx; i++) {
		E = i + 1;
		W = i - 1;

		if(E == nx) E = 0; //Periodic BC
		if(W < 0) W = W + nx; //Periodic BC

			for(j = 0; j < ny; j++) {
			N = j + 1;
			S = j - 1;
			
			if(N == ny) N = S; //No flux
			if(S < 0) S = N; //No flux
						
			rpsi = psi[j + i * ny];
			rpsi_new = rpsi - relax_coeff * delta_t * rhs_psi[j + i * ny];
			psi[j + i * ny] = rpsi_new;

			net_flux = grad_mux[j + E * ny] - grad_mux[j + W * ny] + grad_muy[N + i * ny] - grad_muy[S + i * ny];

			rconc = conc[j + i * ny];
			rconc_new = rconc + ((mobility * delta_t * net_flux) / delta_x);
			conc[j + i * ny] = rconc_new;
	
			}
		}

/* Check for conservation of mass */

		total = 0.0;
		for (i = 0; i < nx; i++) {
			for(j = 0; j < ny; j++) {
			total += conc[j + i * ny];
			}
		}
		total = total / (double)system_size; 
		err = fabs (total - alloycomp);
		if(err > COMPERR) {
		printf("Elements are not conserved...\n");
		printf("error = %lf\n", err);
		exit (0);
		}
/* Check for bounds */

  		for (int i = 0; i < nx; i++) {
   			for (int j = 0; j < ny; j++) {
    			if (conc[j + i * ny] < 0.0
        		|| conc[j + i * ny] > 1.0) {
     			printf ("Compositions out of bounds. Exiting\n");
     			exit (0);
    			}
   			}
  		}

/* Check for convergence */

  		maxerror = 0.0;

  		for (int i = 0; i < nx; i++) {
   			for (int j = 0; j < ny; j++) {
    			error = fabs (tempreal[j + i * ny] - conc[j + i * ny]);
    			if (error > maxerror)
     			maxerror = error;
   			}		
  		}

  		if (maxerror <= Tolerance) {
   		printf ("maxerror=%lf\tsteps=%d\n", maxerror, n);
   		loop_condition = 0;
  		}	

		for (int i = 0; i < nx; i++) {
   			for (int j = 0; j < ny; j++) {
    			tempreal[j + i * ny] = conc[j + i * ny];
   			}
  		}
		
	}

free(tempreal);
free(mu);
free(rhs_psi);
free(grad_mux);
free(grad_muy);
	
}


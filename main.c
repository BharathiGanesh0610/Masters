#include"Eutectic.h"

int main(void) {

void get_input_eutectic(char *fnin, char *fnout);
void init_conf();
void evolve();

char finput[20] = "EutecticSolve";
char fnin[30], fnout[30];

FILE *fp, *fpstr;

unsigned FLAG;

if (!(fp = fopen (finput, "r"))) {
printf("File:%s could not be opened\n", finput);
exit(EXIT_FAILURE);
} 

if (fscanf (fp, "%s", fnin) == 1) {
printf("Filename:%s\n", fnin);
}

if (fscanf (fp, "%s", fnout) == 1) {
printf("Filename: %s\n", fnout);
}

if (!(fpout = fopen (fnout, "w"))) {
printf("File:%s could not be opened\n", fnout);
exit(EXIT_FAILURE);
}

fclose(fp);

get_input_eutectic (fnin, fnout);

system_size = nx * ny;

psi = (double*)malloc(sizeof(double) * system_size);
conc = (double*)malloc(sizeof(double) * system_size);

init_conf();

evolve();

fclose(fpout);

free(psi);
free(conc);

return (0);

}

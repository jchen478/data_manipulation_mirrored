#include <stdlib.h>
#include <stdio.h>

int main()
{
	int nfib, nseg, frames, config_write; 
	float dt, strain, dum; 
	float *q0, *q1, *q2, *q3; 
	float *rcmx, *rcmy, *rcmz;
	FILE *Parameters, *center_mass;
	FILE *q0file, *q1file, *q2file, *q3file;
	FILE *Centers_of_Mass, *Euler_Parameters; 

	int step, m, i, mi, idum; 

	Parameters = fopen("Parameters.in", "r"); 
	center_mass = fopen("center_mass.txt", "rb");
	q0file = fopen("q0.txt", "rb");
	q1file = fopen("q1.txt", "rb");
	q2file = fopen("q2.txt", "rb");
	q3file = fopen("q3.txt", "rb");
	Centers_of_Mass = fopen("Centers_of_Mass.in", "w"); 
	Euler_Parameters = fopen("Euler_Parameters.in", "w"); 

	fscanf(Parameters, "%d", &nfib);
	fscanf(Parameters, "%*[^\n]%d", &nseg);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dt);
	fscanf(Parameters, "%*[^\n]%f", &strain);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%f", &dum);
	fscanf(Parameters, "%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%d", &config_write);
	fclose(Parameters);


	printf("nfib %4d\nnseg %4d\ndt %6f\nstrain %6f\nconfig_write %4d\n",
		nfib, nseg, dt, strain, config_write); 

	rcmx = (float*)malloc(nfib*sizeof(float)); 
	rcmy = (float*)malloc(nfib*sizeof(float));
	rcmz = (float*)malloc(nfib*sizeof(float));
	q0 = (float*)malloc(nfib*nseg*sizeof(float)); 
	q1 = (float*)malloc(nfib*nseg*sizeof(float));
	q2 = (float*)malloc(nfib*nseg*sizeof(float));
	q3 = (float*)malloc(nfib*nseg*sizeof(float));

	frames = int(strain / dt) / config_write + 1; 

	printf("frames %4d\n", frames); 

	for (step = 0; step < frames; step++){
		fread(&dum, sizeof(float), 1, center_mass);
		fread(&dum, sizeof(float), 1, q0file);
		fread(&dum, sizeof(float), 1, q1file);
		fread(&dum, sizeof(float), 1, q2file);
		fread(&dum, sizeof(float), 1, q3file);
		fread(rcmx, sizeof(float), nfib, center_mass);
		fread(rcmy, sizeof(float), nfib, center_mass);
		fread(rcmz, sizeof(float), nfib, center_mass);
		fread(q0, sizeof(float), nfib*nseg, q0file);
		fread(q1, sizeof(float), nfib*nseg, q1file);
		fread(q2, sizeof(float), nfib*nseg, q2file);
		fread(q3, sizeof(float), nfib*nseg, q3file);
		if (step == frames - 1){
			for (m = 0; m < nfib; m++){
				fprintf(Centers_of_Mass, "%4d%17.8E%17.8E%17.8E\n",
					m + 1, rcmx[m], rcmy[m], rcmz[m]);
				for (i = 0; i < nseg; i++){
					mi = m*nseg + i;
					fprintf(Euler_Parameters, "%6d%4d%17.8E%17.8E%17.8E%17.8E\n",
						m + 1, i + 1, q0[mi], q1[mi], q2[mi], q3[mi]);
				}
			} 
		}
	}
	
	fclose(center_mass); fclose(Centers_of_Mass); fclose(Euler_Parameters); 
	fclose(q0file); fclose(q1file); fclose(q2file); fclose(q3file);  

	free(rcmx); free(rcmy); free(rcmz); 
	free(q0); free(q1); free(q2); free(q3); 

    return 0;
}

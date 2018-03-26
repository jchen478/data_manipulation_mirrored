#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std; 

int main(){

	////////////////////////////////////////
	//        input and output files      //
	////////////////////////////////////////
	FILE *Parameters, *center_mass;
	FILE *q0file, *q1file, *q2file, *q3file;
	FILE *rcmAscii, *qAscii; 
	FILE *pxfile, *pyfile, *pzfile, *pAscii; 
	FILE *uxfile, *uyfile, *uzfile, *uAscii; 
	FILE *wxfile, *wyfile, *wzfile, *wAscii; 
	FILE *rxfile, *ryfile, *rzfile, *rAscii; 

	Parameters = fopen("Parameters.in", "r"); 
	center_mass = fopen("center_mass.txt", "rb");
	q0file = fopen("q0.txt", "rb");
	q1file = fopen("q1.txt", "rb");
	q2file = fopen("q2.txt", "rb");
	q3file = fopen("q3.txt", "rb");
	pxfile = fopen("px.txt", "rb");
	pyfile = fopen("py.txt", "rb");
	pzfile = fopen("pz.txt", "rb");
	uxfile = fopen("ux.txt", "rb");
	uyfile = fopen("uy.txt", "rb");
	uzfile = fopen("uz.txt", "rb");
	wxfile = fopen("wx.txt", "rb");
	wyfile = fopen("wy.txt", "rb");
	wzfile = fopen("wz.txt", "rb");
	rxfile = fopen("rx.txt", "rb");
	ryfile = fopen("ry.txt", "rb");
	rzfile = fopen("rz.txt", "rb");
	rcmAscii = fopen("rcmAscii.in", "w"); 
	qAscii = fopen("qAscii.in", "w"); 
	pAscii = fopen("pAscii.in", "w"); 
	uAscii = fopen("uAscii.in", "w"); 
	wAscii = fopen("wAscii.in", "w"); 
	rAscii = fopen("rAscii.in", "w"); 

	if (Parameters == NULL || center_mass == NULL || pAscii == NULL || 
		pxfile == NULL || pyfile == NULL || pzfile == NULL ||
		q0file == NULL || q1file == NULL || q2file == NULL ||
		q3file == NULL || rcmAscii == NULL || qAscii == NULL){
		perror("Error");
	}
	// open files //
	//Parameters = fopen("Parameters.in", "r");
	//center_mass = fopen("center_mass.txt", "rb");

	//if (Parameters == NULL || center_mass == NULL) {
	//	perror("Error");
	//}

	////////////////////////////////////////
	//               variables            //
	////////////////////////////////////////
	int nfib, nseg, config_write;
	int nstep, step, nstart, frames;
	float dt, t, strain, tstart;
	
	float *rcmx, *rcmy, *rcmz;
  	float *q0, *q1, *q2, *q3; 	
	float *px, *py, *pz; 
	float *ux, *uy, *uz; 
	float *wx, *wy, *wz; 
	float *rx, *ry, *rz; 
	int idum, m, n, i, mi;
	float dum;

	float pi = 3.141592654;


	// Read in Parameters.in //
	fscanf(Parameters, "%d", &nfib);
	fscanf(Parameters, "%*[^\n]%d", &nseg);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &idum);
	fscanf(Parameters, "%*[^\n]%f", &idum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dt);
	fscanf(Parameters, "%*[^\n]%f", &strain);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, " %f", &dum);
	fscanf(Parameters, " %f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%d", &config_write);
	fscanf(Parameters, "%*[^\n]%d", &idum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%d", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%d", &idum);
	fscanf(Parameters, "%*[^\n]%d", &idum);
	fscanf(Parameters, "%*[^\n]%d", &idum);
	fscanf(Parameters, "%*[^\n]%d", &idum);
	fscanf(Parameters, "%*[^\n]%d", &idum);
	fscanf(Parameters, "%*[^\n]%d", &idum);
	fscanf(Parameters, "%*[^\n]%d", &idum);
	fscanf(Parameters, "%*[^\n]%d", &idum);
	fscanf(Parameters, "%*[^\n]%d", &idum);
	fscanf(Parameters, "%*[^\n]%d", &idum);
	fscanf(Parameters, "%*[^\n]%d", &idum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &tstart);

	printf("nfib nseg %4d %4d\n", nfib, nseg);
	printf("config_write %4d\n", config_write);
	printf("dt strain %6f %6f\n", dt, strain);

	//cout << "Enter strain to start converting to ASCII: " << endl;
	//cin >> tstart; 



	rcmx = (float*)malloc(nfib*sizeof(float)); 
	rcmy = (float*)malloc(nfib*sizeof(float));
	rcmz = (float*)malloc(nfib*sizeof(float));
	q0 = (float*)malloc(nfib*nseg*sizeof(float)); 
	q1 = (float*)malloc(nfib*nseg*sizeof(float));
	q2 = (float*)malloc(nfib*nseg*sizeof(float));
	q3 = (float*)malloc(nfib*nseg*sizeof(float));
	px = (float*)malloc(nfib*nseg*sizeof(float)); 
	py = (float*)malloc(nfib*nseg*sizeof(float)); 
	pz = (float*)malloc(nfib*nseg*sizeof(float)); 
	ux = (float*)malloc(nfib*nseg*sizeof(float)); 
	uy = (float*)malloc(nfib*nseg*sizeof(float)); 
	uz = (float*)malloc(nfib*nseg*sizeof(float)); 
	wx = (float*)malloc(nfib*nseg*sizeof(float)); 
	wy = (float*)malloc(nfib*nseg*sizeof(float)); 
	wz = (float*)malloc(nfib*nseg*sizeof(float)); 
	rx = (float*)malloc(nfib*nseg*sizeof(float)); 
	ry = (float*)malloc(nfib*nseg*sizeof(float)); 
	rz = (float*)malloc(nfib*nseg*sizeof(float)); 
	
	frames = int(strain / dt) / config_write + 1; 
	nstart = int(tstart / dt) / config_write;
	
	for (step = 0; step < frames; step++){
		fread(&t, sizeof(float), 1, center_mass);
		fread(&t, sizeof(float), 1, q0file);
		fread(&t, sizeof(float), 1, q1file);
		fread(&t, sizeof(float), 1, q2file);
		fread(&t, sizeof(float), 1, q3file);
		fread(&t, sizeof(float), 1, pxfile);
		fread(&t, sizeof(float), 1, pyfile);
		fread(&t, sizeof(float), 1, pzfile);
		fread(&t, sizeof(float), 1, uxfile);
		fread(&t, sizeof(float), 1, uyfile);
		fread(&t, sizeof(float), 1, uzfile);
		fread(&t, sizeof(float), 1, wxfile);
		fread(&t, sizeof(float), 1, wyfile);
		fread(&t, sizeof(float), 1, wzfile);
		fread(&t, sizeof(float), 1, rxfile);
		fread(&t, sizeof(float), 1, ryfile);
		fread(&t, sizeof(float), 1, rzfile);
		fread(rcmx, sizeof(float), nfib, center_mass);
		fread(rcmy, sizeof(float), nfib, center_mass);
		fread(rcmz, sizeof(float), nfib, center_mass);
		fread(q0, sizeof(float), nfib*nseg, q0file);
		fread(q1, sizeof(float), nfib*nseg, q1file);
		fread(q2, sizeof(float), nfib*nseg, q2file);
		fread(q3, sizeof(float), nfib*nseg, q3file);
		fread(px, sizeof(float), nfib*nseg, pxfile);
		fread(py, sizeof(float), nfib*nseg, pyfile);
		fread(pz, sizeof(float), nfib*nseg, pzfile);
		fread(ux, sizeof(float), nfib*nseg, uxfile);
		fread(uy, sizeof(float), nfib*nseg, uyfile);
		fread(uz, sizeof(float), nfib*nseg, uzfile);
		fread(wx, sizeof(float), nfib*nseg, wxfile);
		fread(wy, sizeof(float), nfib*nseg, wyfile);
		fread(wz, sizeof(float), nfib*nseg, wzfile);
		fread(rx, sizeof(float), nfib*nseg, rxfile);
		fread(ry, sizeof(float), nfib*nseg, ryfile);
		fread(rz, sizeof(float), nfib*nseg, rzfile);
		
		if (step >= nstart){
			fprintf(rcmAscii, "%.6f\n", t);
			fprintf(qAscii, "%.6f\n", t);
			fprintf(pAscii, "%.6f\n", t);
			fprintf(uAscii, "%.6f\n", t);
			fprintf(wAscii, "%.6f\n", t);
			fprintf(rAscii, "%.6f\n", t);
			for (m = 0; m < nfib; m++){
				fprintf(rcmAscii, "%4d%17.8E%17.8E%17.8E\n",
					m + 1, rcmx[m], rcmy[m], rcmz[m]);
				for (i = 0; i < nseg; i++){
					mi = m*nseg + i;
					fprintf(qAscii, "%4d%2d%17.8E%17.8E%17.8E%17.8E\n",
						m + 1, i + 1, q0[mi], q1[mi], q2[mi], q3[mi]);
					fprintf(pAscii, "%4d%2d%17.8f%17.8f%17.8f\n",
						m + 1, i + 1, px[mi], py[mi], pz[mi]);
					fprintf(uAscii, "%4d%2d%17.8f%17.8f%17.8f\n",
						m + 1, i + 1, ux[mi], uy[mi], uz[mi]);
					fprintf(wAscii, "%4d%2d%17.8f%17.8f%17.8f\n",
						m + 1, i + 1, wx[mi], wy[mi], wz[mi]);
					fprintf(rAscii, "%4d%2d%17.8f%17.8f%17.8f\n",
						m + 1, i + 1, rx[mi], ry[mi], rz[mi]);
				}
			} 
		}
	}

	free(rcmx); free(rcmy); free(rcmz);
	free(q0); free(q1); free(q2); free(q3); 
	free(px); free(py); free(pz); 	
	free(ux); free(uy); free(uz); 	
	free(wx); free(wy); free(wz); 	
	free(rx); free(ry); free(rz); 	

	fclose(Parameters);
	fclose(rcmAscii); fclose(qAscii); 
	fclose(center_mass);
	fclose(q0file); fclose(q1file); fclose(q2file); fclose(q3file); 
	fclose(pxfile); fclose(pyfile); fclose(pzfile); fclose(pAscii);
	fclose(uxfile); fclose(uyfile); fclose(uzfile); fclose(uAscii);
	fclose(wxfile); fclose(wyfile); fclose(wzfile); fclose(wAscii);
	fclose(rxfile); fclose(ryfile); fclose(rzfile); fclose(rAscii);
	return 0;
}

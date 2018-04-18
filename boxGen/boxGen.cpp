#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
using namespace std;

int main(){

	// read input parameters
	FILE *input;
	input = fopen("box.gen", "r");

	float sidex, sidey, sidez, a, dt, rate; 
	float gamma_init, gamma_high, gamma_low;
	int box_write;

	fscanf(input, "%f", &sidex);
	fscanf(input, "%*[^\n]%f", &sidey);
	fscanf(input, "%*[^\n]%f", &sidez);
	fscanf(input, "%*[^\n]%f", &a);
	fscanf(input, "%*[^\n]%d", &box_write);
	fscanf(input, "%*[^\n]%f", &dt);
	fscanf(input, "%*[^\n]%f", &rate);
	fscanf(input, "%*[^\n]%f", &gamma_init);
	fscanf(input, "%*[^\n]%f", &gamma_high);
	fscanf(input, "%*[^\n]%f", &gamma_low);
	fclose(input); 

	float N;
	float region1, region2, region3, region4, region5, gammaTot;
	// N = number of concentrating/redispersing steps
	// region1 = shearing before concetrating
	// region2 = concentrating
	// region3 = shearing at high concentration
	// region4 = redispersing
	// region5 = shearing at low concentration
	// gammaTot = total strain required to finish cycle

	N = ceil(-logf(a) / logf(1.0 - rate)*dt*float(box_write));
	region1 = gamma_init;
	region2 = region1 + N; 
	region3 = region2 + gamma_high;
	region4 = region3 + N; 
	region5 = region4 + gamma_low;
	gammaTot = region5; 

	int ind; 
	int nStep = gammaTot / (dt*box_write) + 1; 
	float power, n; 
	float *gamma = (float*)malloc(nStep*sizeof(float)); 
	float *Lx = (float*)malloc(nStep*sizeof(float)); 
	float *Ly = (float*)malloc(nStep*sizeof(float));
	float *Lz = (float*)malloc(nStep*sizeof(float));

	n = 0.0; 
	for (int step = 0; step < nStep; step++){
		gamma[step] = dt*float(step*box_write);
		if (step <= region1 / (dt*box_write)){
			Lx[step] = sidex; 
			Ly[step] = sidey;
			Lz[step] = sidez;
			ind = step; 
			n = 1.0; 
			continue;
		}
		if (step < region2 / (dt*box_write)){
			power = 1.0 / 3.0*n;
			Lx[step] = sidex*powf(1.0 - rate, power);
			Ly[step] = sidey*powf(1.0 - rate, power);
			Lz[step] = sidez*powf(1.0 - rate, power);
			n += 1.0; 
			continue;
		}
		if (step < region3 / (dt*box_write)){
			Lx[step] = Lx[step - 1]; 
			Ly[step] = Ly[step - 1];
			Lz[step] = Lz[step - 1];
			ind = step;
			n = 1.0; 
			continue;
		}
		if (step < region4 / (dt*box_write)){
			power = -1.0 / 3.0 *n; 
			Lx[step] = Lx[ind] * powf(1.0 - rate, power); 
			Ly[step] = Ly[ind] * powf(1.0 - rate, power);
			Lz[step] = Lz[ind] * powf(1.0 - rate, power);
			n += 1.0;
			continue;
		}
		if (step < region5 / (dt*box_write)){
			Lx[step] = sidex;
			Ly[step] = sidey;
			Lz[step] = sidez;
			continue;
		}
	}

	FILE *Box;
	Box = fopen("Lbox.txt", "w"); 
	// print to file
	for (int step = 0; step < nStep; step++){
		fprintf(Box, "%8.4f %10.6f %10.6f %10.6f %10.6f\n",
			gamma[step], Lx[step], Ly[step], Lz[step], Lx[step] * Ly[step] * Lz[step]/(sidex*sidey*sidez));
	}
	fclose(Box); 
	free(gamma); free(Lx); free(Ly); free(Lz); 

	return 0; 
}

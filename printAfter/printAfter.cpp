#include <stdlib.h>
#include <stdio.h>

int main(){

	////////////////////////////////////////
	//        input and output files      //
	////////////////////////////////////////
	FILE *Parameters; 
	FILE *rxfile, *ryfile, *rzfile;
	FILE *rxfileTmp, *ryfileTmp, *rzfileTmp;
	FILE *pxfile, *pyfile, *pzfile;
	FILE *pxfileTmp, *pyfileTmp, *pzfileTmp;
	FILE *uxfile, *uyfile, *uzfile;
	FILE *uxfileTmp, *uyfileTmp, *uzfileTmp;
	FILE *wxfile, *wyfile, *wzfile;
	FILE *wxfileTmp, *wyfileTmp, *wzfileTmp;
	FILE *q0file, *q1file, *q2file, *q3file;
	FILE *q0fileTmp, *q1fileTmp, *q2fileTmp, *q3fileTmp;
	FILE *Stress_tensor, *Stress_tensorTmp;
	FILE *center_mass, *center_massTmp; 
	FILE *NC, *NCTmp;

	// open files //
	Stress_tensor = fopen("Stress_tensor.txt", "r");
	Stress_tensorTmp = fopen("Stress_tensorTmp.txt", "w");
	Parameters = fopen("Parameters.in", "r");

	// nc
	NC = fopen("Number_of_Contacts.txt", "r");
	NCTmp = fopen("Number_of_ContactsTmp.txt", "w");
	
	// rcm
	center_mass = fopen("center_mass.txt", "rb");
	center_massTmp = fopen("center_massTmp.txt", "wb");

	// r
	rxfile = fopen("rx.txt", "rb");
	ryfile = fopen("ry.txt", "rb");
	rzfile = fopen("rz.txt", "rb");
	rxfileTmp = fopen("rxTmp.txt", "wb");
	ryfileTmp = fopen("ryTmp.txt", "wb");
	rzfileTmp = fopen("rzTmp.txt", "wb");
	// p
	pxfile = fopen("px.txt", "rb");
	pyfile = fopen("py.txt", "rb");
	pzfile = fopen("pz.txt", "rb");
	pxfileTmp = fopen("pxTmp.txt", "wb");
	pyfileTmp = fopen("pyTmp.txt", "wb");
	pzfileTmp = fopen("pzTmp.txt", "wb");
	// u
	uxfile = fopen("ux.txt", "rb");
	uyfile = fopen("uy.txt", "rb");
	uzfile = fopen("uz.txt", "rb");
	uxfileTmp = fopen("uxTmp.txt", "wb");
	uyfileTmp = fopen("uyTmp.txt", "wb");
	uzfileTmp = fopen("uzTmp.txt", "wb");
	// w
	wxfile = fopen("wx.txt", "rb");
	wyfile = fopen("wy.txt", "rb");
	wzfile = fopen("wz.txt", "rb");
	wxfileTmp = fopen("wxTmp.txt", "wb");
	wyfileTmp = fopen("wyTmp.txt", "wb");
	wzfileTmp = fopen("wzTmp.txt", "wb");
	// q
	q0file = fopen("q0.txt", "rb");
	q1file = fopen("q1.txt", "rb");
	q2file = fopen("q2.txt", "rb");
	q3file = fopen("q3.txt", "rb");
	q0fileTmp = fopen("q0Tmp.txt", "wb");
	q1fileTmp = fopen("q1Tmp.txt", "wb");
	q2fileTmp = fopen("q2Tmp.txt", "wb");
	q3fileTmp = fopen("q3Tmp.txt", "wb");

	int nfib, nseg, config_write, stress_write, contact_write, idum;
	float dt, strain, start_printAfter, dum;

	// Read in Parameters.in //
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
	fscanf(Parameters, " %f", &dum);
	fscanf(Parameters, " %f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%d", &config_write);
	fscanf(Parameters, "%*[^\n]%d", &contact_write);
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
	fscanf(Parameters, "%*[^\n]%d", &idum);
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
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%d", &stress_write);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%d", &idum);
	fscanf(Parameters, "%*[^\n]%d", &idum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%d", &idum);
	fscanf(Parameters, "%*[^\n]%d", &idum);
	fscanf(Parameters, "%*[^\n]%d", &idum);
	fscanf(Parameters, "%*[^\n]%d", &idum);
	fscanf(Parameters, "%*[^\n]%d", &idum);
	fscanf(Parameters, "%*[^\n]%d", &idum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%d", &idum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &dum);
	fscanf(Parameters, "%*[^\n]%f", &start_printAfter);

	int step, nStress, nConfig, nContact;
	int stepStress, stepConfig, stepContact;
	float dum1, dum2, dum3, dum4, dum5, dum6, dum7; 
	int idum1, idum2, idum3;
	float *r, *rc; 

	nStress = int(strain / dt / float(stress_write)); 
	nConfig = int(strain / dt / float(config_write));
	nContact = int(strain / dt / float(contact_write));
	stepStress = int(start_printAfter / dt / float(stress_write)); 
	stepConfig = int(start_printAfter / dt / float(config_write));
	stepContact = int(start_printAfter / dt / float(contact_write));

	r = (float*)malloc(nfib*nseg*sizeof(float)); 
	rc = (float*)malloc(nfib*sizeof(float));

	// reprint contact file
	for (step = 0; step < nContact; step++){
		fscanf(NC, "%f %d %d %f %d",
			&dum1, &idum1, &idum2, &dum2, &idum3);
		if (step >= stepContact) fprintf(NCTmp, 
			"%8.5f %6d %6d %6.3f %5d\n",
			dum1, idum1, idum2, dum2, idum3);
	}
	// reprint stress file
	for (step = 0; step < nStress; step++){
		fscanf(Stress_tensor, "%f %f %f %f %f %f %f",
			&dum1, &dum2, &dum3, &dum4, &dum5, &dum6, &dum7);
		if (step >= stepStress) fprintf(Stress_tensorTmp, 
			"%10.4f %10.6f %10.6f %10.6f %10.6f %10.6f %10.6f\n",
			dum1, dum2, dum3, dum4, dum5, dum6, dum7);
	}
	// reprint configuration files
	for (step = 0; step < nConfig + 1; step++){
		
		// rc
		fread(&dum, sizeof(float), 1, center_mass);
		if (step >= stepConfig) fwrite(&dum, sizeof(float), 1, center_massTmp);
		if (step >= stepConfig) printf("dum %f\n", dum); 
		fread(rc, sizeof(float), nfib, center_mass);
		if(step >= stepConfig) fwrite(rc, sizeof(float), nfib, center_massTmp);
		fread(rc, sizeof(float), nfib, center_mass);
		if(step >= stepConfig) fwrite(rc, sizeof(float), nfib, center_massTmp);
		fread(rc, sizeof(float), nfib, center_mass);
		if(step >= stepConfig) fwrite(rc, sizeof(float), nfib, center_massTmp);
		// rx
		fread(&dum, sizeof(float), 1, rxfile);
		fread(r, sizeof(float), nfib*nseg, rxfile);
		if(step >= stepConfig) fwrite(&dum, sizeof(float), 1, rxfileTmp); 
		if(step >= stepConfig) fwrite(r, sizeof(float), nfib*nseg, rxfileTmp);
		// ry
		fread(&dum, sizeof(float), 1, ryfile);
		fread(r, sizeof(float), nfib*nseg, ryfile);
		if(step >= stepConfig) fwrite(&dum, sizeof(float), 1, ryfileTmp);
		if(step >= stepConfig) fwrite(r, sizeof(float), nfib*nseg, ryfileTmp);
		// rz
		fread(&dum, sizeof(float), 1, rzfile);
		fread(r, sizeof(float), nfib*nseg, rzfile);
		if(step >= stepConfig) fwrite(&dum, sizeof(float), 1, rzfileTmp);
		if(step >= stepConfig) fwrite(r, sizeof(float), nfib*nseg, rzfileTmp);
		// px 
		fread(&dum, sizeof(float), 1, pxfile);
		fread(r, sizeof(float), nfib*nseg, pxfile);
		if(step >= stepConfig) fwrite(&dum, sizeof(float), 1, pxfileTmp);
		if(step >= stepConfig) fwrite(r, sizeof(float), nfib*nseg, pxfileTmp);
		// py
		fread(&dum, sizeof(float), 1, pyfile);
		fread(r, sizeof(float), nfib*nseg, pyfile);
		if(step >= stepConfig) fwrite(&dum, sizeof(float), 1, pyfileTmp);
		if(step >= stepConfig) fwrite(r, sizeof(float), nfib*nseg, pyfileTmp);
		// pz
		fread(&dum, sizeof(float), 1, pzfile);
		fread(r, sizeof(float), nfib*nseg, pzfile);
		if(step >= stepConfig) fwrite(&dum, sizeof(float), 1, pzfileTmp);
		if(step >= stepConfig) fwrite(r, sizeof(float), nfib*nseg, pzfileTmp);
		// ux 
		fread(&dum, sizeof(float), 1, uxfile);
		fread(r, sizeof(float), nfib*nseg, uxfile);
		if(step >= stepConfig) fwrite(&dum, sizeof(float), 1, uxfileTmp);
		if(step >= stepConfig) fwrite(r, sizeof(float), nfib*nseg, uxfileTmp);
		// uy 
		fread(&dum, sizeof(float), 1, uyfile);
		fread(r, sizeof(float), nfib*nseg, uyfile);
		if(step >= stepConfig) fwrite(&dum, sizeof(float), 1, uyfileTmp);
		if(step >= stepConfig) fwrite(r, sizeof(float), nfib*nseg, uyfileTmp);
		// uy 
		fread(&dum, sizeof(float), 1, uzfile);
		fread(r, sizeof(float), nfib*nseg, uzfile);
		if(step >= stepConfig) fwrite(&dum, sizeof(float), 1, uzfileTmp);
		if(step >= stepConfig) fwrite(r, sizeof(float), nfib*nseg, uzfileTmp);
		// wx 
		fread(&dum, sizeof(float), 1, wxfile);
		fread(r, sizeof(float), nfib*nseg, wxfile);
		if(step >= stepConfig) fwrite(&dum, sizeof(float), 1, wxfileTmp);
		if(step >= stepConfig) fwrite(r, sizeof(float), nfib*nseg, wxfileTmp);
		// wy
		fread(&dum, sizeof(float), 1, wyfile);
		fread(r, sizeof(float), nfib*nseg, wyfile);
		if(step >= stepConfig) fwrite(&dum, sizeof(float), 1, wyfileTmp);
		if(step >= stepConfig) fwrite(r, sizeof(float), nfib*nseg, wyfileTmp);
		// wz
		fread(&dum, sizeof(float), 1, wzfile);
		fread(r, sizeof(float), nfib*nseg, wzfile);
		if(step >= stepConfig) fwrite(&dum, sizeof(float), 1, wzfileTmp);
		if(step >= stepConfig) fwrite(r, sizeof(float), nfib*nseg, wzfileTmp);
		// q0
		fread(&dum, sizeof(float), 1, q0file);
		fread(r, sizeof(float), nfib*nseg, q0file);
		if(step >= stepConfig) fwrite(&dum, sizeof(float), 1, q0fileTmp);
		if(step >= stepConfig) fwrite(r, sizeof(float), nfib*nseg, q0fileTmp);
		// q1
		fread(&dum, sizeof(float), 1, q1file);
		fread(r, sizeof(float), nfib*nseg, q1file);
		if(step >= stepConfig) fwrite(&dum, sizeof(float), 1, q1fileTmp);
		if(step >= stepConfig) fwrite(r, sizeof(float), nfib*nseg, q1fileTmp);
		// q2
		fread(&dum, sizeof(float), 1, q2file);
		fread(r, sizeof(float), nfib*nseg, q2file);
		if(step >= stepConfig) fwrite(&dum, sizeof(float), 1, q2fileTmp);
		if(step >= stepConfig) fwrite(r, sizeof(float), nfib*nseg, q2fileTmp);
		// q3
		fread(&dum, sizeof(float), 1, q3file);
		fread(r, sizeof(float), nfib*nseg, q3file);
		if(step >= stepConfig) fwrite(&dum, sizeof(float), 1, q3fileTmp);
		if(step >= stepConfig) fwrite(r, sizeof(float), nfib*nseg, q3fileTmp);
	}



	free(r); free(rc); 


	fclose(Parameters); 

	fclose(NC); fclose(NCTmp); 	

	fclose(rxfile); fclose(ryfile); fclose(rzfile);
	fclose(rxfileTmp); fclose(ryfileTmp); fclose(rzfileTmp);

	fclose(pxfile); fclose(pyfile); fclose(pzfile);
	fclose(pxfileTmp); fclose(pyfileTmp); fclose(pzfileTmp);

	fclose(uxfile); fclose(uyfile); fclose(uzfile);
	fclose(uxfileTmp); fclose(uyfileTmp); fclose(uzfileTmp);

	fclose(wxfile); fclose(wyfile); fclose(wzfile);
	fclose(wxfileTmp); fclose(wyfileTmp); fclose(wzfileTmp);

	fclose(q0file); fclose(q1file); fclose(q2file); fclose(q3file);
	fclose(q0fileTmp); fclose(q1fileTmp); fclose(q2fileTmp); fclose(q3fileTmp);

	fclose(Stress_tensor); fclose(Stress_tensorTmp);

	fclose(center_mass); fclose(center_massTmp); 

	// rename files
	remove("Number_of_Contacts.txt"); 
	rename("Number_of_ContactsTmp.txt", "Number_of_Contacts.txt"); 

	remove("center_mass.txt"); 
	rename("center_massTmp.txt", "center_mass.txt"); 

	remove("Stress_tensor.txt");
	rename("Stress_tensorTmp.txt", "Stress_tensor.txt");

	remove("rx.txt");
	rename("rxTmp.txt", "rx.txt");
	remove("ry.txt");
	rename("ryTmp.txt", "ry.txt");
	remove("rz.txt");
	rename("rzTmp.txt", "rz.txt");

	remove("px.txt");
	rename("pxTmp.txt", "px.txt");
	remove("py.txt");
	rename("pyTmp.txt", "py.txt");
	remove("pz.txt");
	rename("pzTmp.txt", "pz.txt");

	remove("ux.txt");
	rename("uxTmp.txt", "ux.txt");
	remove("uy.txt");
	rename("uyTmp.txt", "uy.txt");
	remove("uz.txt");
	rename("uzTmp.txt", "uz.txt");

	remove("wx.txt");
	rename("wxTmp.txt", "wx.txt");
	remove("wy.txt");
	rename("wyTmp.txt", "wy.txt");
	remove("wz.txt");
	rename("wzTmp.txt", "wz.txt");


	remove("q0.txt");
	rename("q0Tmp.txt", "q0.txt");
	remove("q1.txt");
	rename("q1Tmp.txt", "q1.txt");
	remove("q2.txt");
	rename("q2Tmp.txt", "q2.txt");
	remove("q3.txt");
	rename("q3Tmp.txt", "q3.txt");

	return 0; 
}

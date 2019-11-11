/************************************************************************
Programma pelaths	: AirportManagement.c
Syggrafeas			: 
Skopos				: skeleton main for askhsh 3
*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include "TSEvr.h"
#include "TSDDA.h"
#include "Evretirio.h"

int InsertData(FILE *fp, EvrPtr E);
int InsertRoutes(EvrPtr E,FILE *routes,int *airfound,int *airnotfound);


int main(int argc, char *argv[]){ 
	EvrPtr E;
	FILE *fp,*fp1,*routes,*routes1,*out,*out1;
	int counter=0,airfound=0,airnotfound=0,countroutes;
	LARGE_INTEGER t1,t2,t3,t4;
	LARGE_INTEGER frequency;
	double elapsedTime,elapsedTime1;
	
	E=EvrConstruct(7200);
	
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&t1);
	
	fp=fopen(".\\Windows\\airportsSimpleWinRandomANSI.txt","r");
	if(fp==NULL){
		printf("Error.Cannot find file!\n");
		EvrDestruct(&E);
		return 0;
	}
	InsertData(fp,E);	
		
	QueryPerformanceCounter(&t3);
	countroutes=InsertRoutes(E,routes,&airfound,&airnotfound);
	QueryPerformanceCounter(&t4);
	elapsedTime1=(t4.QuadPart-t3.QuadPart)*1000.0 / frequency.QuadPart;

	out=fopen(".\\Windows\\OUTPUTRandomBST.txt","w");
	
	fprintf(out,"Routes:%d,Airports found:%d,Airports not found:%d\n",countroutes,airfound,airnotfound);
	Evr_PrintAll(E,out, &counter);
	QueryPerformanceCounter(&t2);
	elapsedTime=(t2.QuadPart-t1.QuadPart)*1000.0 / frequency.QuadPart;
	printf("Plithos stoixewn pou ektypwthikan %d in time %lf\n",counter,elapsedTime);
    fprintf(out,"Plithos stoixewn pou ektypwthikan %d in time %lf\n",counter,elapsedTime);
    fprintf(out,"Mesos oros anazhthshs  %lf\n",elapsedTime1/counter);
  
	fclose(out);
	EvrDestruct(&E);
	E=NULL;
	fclose(fp);
	
	
/*	E=EvrConstruct(7200);
	
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&t1);
	
	fp1=fopen(".\\Windows\\airportsSimpleWinSortedANSI.txt","r");
		if(fp1==NULL){
		printf("Error.Cannot find file!\n");
		EvrDestruct(&E);
		return 0;
	}
	InsertData(fp1,E);		
	airfound=0;
	airnotfound=0;
	QueryPerformanceCounter(&t3);
	countroutes=InsertRoutes(E,routes1,&airfound,&airnotfound);
	QueryPerformanceCounter(&t4);
	elapsedTime1=(t4.QuadPart-t3.QuadPart)*1000.0 / frequency.QuadPart;

	
	
	out1=fopen(".\\Windows\\OUTPUTSortedBST.txt","w");
	fprintf(out1,"Routes:%d,Airports found:%d,Airports not found:%d\n",countroutes,airfound,airnotfound);
	counter=0;
	Evr_PrintAll(E,out1, &counter);
	
	QueryPerformanceCounter(&t2);
	elapsedTime=(t2.QuadPart-t1.QuadPart)*1000.0 / frequency.QuadPart;
	printf("Plithos stoixewn pou ektypwthikan %d in time %lf\n",counter,elapsedTime);
    fprintf(out1,"Plithos stoixewn pou ektypwthikan %d in time %lf\n",counter,elapsedTime);
    fprintf(out1,"Mesos oros anazhthshs  %lf\n",elapsedTime1/counter);
  
    fclose(fp1);
	fclose(out1);
	EvrDestruct(&E);*/

		
	return 0;
}




int InsertData(FILE *fp, EvrPtr E){
	LARGE_INTEGER t1,t2;
	LARGE_INTEGER frequency;
	double elapsedTime;
	int countinsert=0,i,error=1;
	
	

	
	TStoixeiouEvr Data;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&t1);
	while(!feof(fp)){
		error=TSEvr_readValue (fp, &Data);
		if(error==1) Evr_Insert(E, Data);
		countinsert++;
		for(i=9;i<=12;i++)
		{
		
			if(countinsert==(int)pow(2,i))
			{
				QueryPerformanceCounter(&t2);
				elapsedTime=(t2.QuadPart-t1.QuadPart)*1000.0 / frequency.QuadPart;
				printf("Plithos stoixeiwn inserted %d in time %lf\n",countinsert,elapsedTime);
			}
		}
	}
	QueryPerformanceCounter(&t2);
	elapsedTime=(t2.QuadPart-t1.QuadPart)*1000.0 / frequency.QuadPart;
	printf("Synoliko plithos stoixeiwn inserted %d in time %lf\n",countinsert,elapsedTime);
		
 
	
	
}



int InsertRoutes(EvrPtr E,FILE *routes,int *airfound,int *airnotfound){
	char num1[100],num2[100];
	char c;
	int i,j,SourceID,DestinationID,key;
	int found=0;
	int InOut=0;
	int countroutes=0;
	
	routes=fopen(".\\Windows\\routesWin.txt","r");
	
	if(routes==NULL){
		printf("Error.Cannot find file!\n");
		EvrDestruct(&E);
		return 0;
	}
	
	while(!feof(routes)){	
		i=0;
		
		for(j=1;j<=3;j++){
			if(!feof(routes)) c=fgetc(routes);
			while(c!=';'){
				if(!feof(routes)) c=fgetc(routes);
				else break;
			}
		}
	
		if(!feof(routes)) c=fgetc(routes);
		while(c!=';'){
			num1[i]=c;
			i++;
			if(!feof(routes)) c=fgetc(routes);
			else break;
		}
		num1[i]='\0';
    	SourceID=atoi(num1);
    	key=SourceID;
    	InOut=1;
    	EvrSearch(E, key, InOut, &found);
    	if(found)
    	{
    		(*airfound)++;
		}
		else (*airnotfound)++;
    	if(!feof(routes)) c=fgetc(routes);
		while(c!=';'){
			if(!feof(routes)) c=fgetc(routes);
			else break;
		}
	
		i=0;
		if(!feof(routes)) c=fgetc(routes);
		while(c!=';'){
			num2[i]=c;
			i++;
			if(!feof(routes)) c=fgetc(routes);
			else break;
		}
		num2[i]='\0';
    	DestinationID=atoi(num2);
    	key=DestinationID;
    	countroutes++;
    	InOut=0;
    	
    	EvrSearch(E, key, InOut, &found);
    	
    	if(found)
    	{
    		(*airfound)++;
		}
		else (*airnotfound)++;
    	if (!feof(routes)) c=fgetc(routes);
    	while(c!='\n'){
    		if (!feof(routes)) c=fgetc(routes);
    		else break;
		}
	
	}

		fclose(routes);
		return countroutes;
}



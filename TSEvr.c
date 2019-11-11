#include "TSEvr.h"
#include <string.h>



int TSEvr_setValue (TStoixeiouEvr *target, TStoixeiouEvr source){
	if(target==NULL) return 0;
	target->AirportID=source.AirportID;
	target->Arrivals=source.Arrivals;
	target->Departures=source.Departures;
	strcpy(target->City,source.City);
	strcpy(target->Country,source.Country);
	strcpy(target->IATA,source.IATA);
	strcpy(target->Name,source.Name);
	return 1;
}

int TSEvr_readValue (FILE *from,  TStoixeiouEvr *Elem){
	char num[100];
	char c;
	int i;
	if(from==NULL)
	{
		printf("Error.Cannot find file!\n");
		return 0;
	}
	Elem->AirportID=-1;
	c=fgetc(from);
	if(!feof(from)){
		i=0;
		while(c!=';'){
			num[i]=c;
			i++;
			if(!feof(from)) c=fgetc(from);
			else break;
		}
		num[i]='\0';
		Elem->AirportID=atoi(num);
		
		if(!feof(from)) c=fgetc(from);
		i=0;
		while(c!=';'){
			Elem->Name[i]=c;
			i++;
			if(!feof(from))	c=fgetc(from);
			else break;
		}
		Elem->Name[i]='\0';
		
		if(!feof(from)) c=fgetc(from);
		i=0;
		while(c!=';'){
			Elem->City[i]=c;
			i++;
			if(!feof(from))	c=fgetc(from);
			else break;
		}
		Elem->City[i]='\0';
		
		if(!feof(from) )c=fgetc(from);
		i=0;
		while(c!=';'){
			Elem->Country[i]=c;
			i++;
			if(!feof(from))	c=fgetc(from);
			else break;
		}
		Elem->Country[i]='\0';
		
		if(!feof(from)) c=fgetc(from);
		i=0;
		while(c!=';'){
			Elem->IATA[i]=c;
			i++;
			if(!feof(from) )	c=fgetc(from);
			else break;
		}
		Elem->IATA[i]='\0';
		
		if(!feof(from)) c=fgetc(from);
		i=0;
		while(c!='\n' ){
			Elem->ICAO[i]=c;
			i++;
			if(!feof(from)) c=fgetc(from);
			else break;
		}
		Elem->ICAO[i]='\0';
		
	}
	Elem->Departures=0;
	Elem->Arrivals=0;
	if(Elem->AirportID==-1) return 0;
	return 1;
}

int TSEvr_writeValue(FILE *to, TStoixeiouEvr Elem){
	int c;
	printf("begin");
	printf("key %d\n",Elem.AirportID);
	c=fprintf(to,"%d;%d;%d\n",Elem.AirportID,Elem.Departures,Elem.Arrivals);
	printf("%d end\n",c);
}


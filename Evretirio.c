#include "Evretirio.h"

#define Simple 1 /* 0 for AVL - any Evr integer for Simple  */

/* Oi diafores tvn ylopoihsevn Simple kai AVL einai mikres - mporeite na xrhsimopoihsete 
   thn  domh #if ... #else ...#endif gia na diaforopihsete tis dyo ylopoihseis  */
   
#if (Simple)
#include "BST/ch8_BSTpointer.h" /* gia Simple Ylopoihsh */
#else
#include "AVL/ch8_AVLpointer.h" /* gia AVL Ylopoihsh */
#endif


struct EvrNode{
       TStoixeiouEvr *DataArray; /* array of size MaxSize */
       int Index;              /* index of first available element in array */
       typos_deikti TreeRoot;     /* Root of DDA */
} EvrNode;

EvrPtr EvrConstruct(int MaxSize){
	
   typos_deikti TreeRoot;

	
	EvrPtr E=(EvrPtr)malloc(sizeof(struct EvrNode));
	E->DataArray=(TStoixeiouEvr *)malloc(MaxSize*sizeof(TStoixeiouEvr));
	#if (Simple)
	printf("use simple BST\n");
	Tree_dimiourgia(&(E->TreeRoot));
	#else   
    printf("use AVL BST\n");
    AVLTree_dimiourgia(&(E->TreeRoot));
	#endif		
	E->Index=0;
	return E;
}

int Evr_Insert(EvrPtr E, TStoixeiouEvr Data){ 
	int error=0;
	TStoixeiouDDA Node;
	TSEvr_setValue (&(E->DataArray[E->Index]),Data); 
	TSDDA_setKey(&(Node.key), Data.AirportID); 
	TSDDA_setIndex(&(Node.arrayIndex), E->Index);
	E->Index=(E->Index)+1;
	
	#if (Simple)
	Tree_eisagogi(&(E->TreeRoot), Node, &error);
	#else
	AVLTree_eisagogi(&(E->TreeRoot),Node,&ypsilotero,&error);
	#endif
	
	if (error==1){
		printf("Error in insert!\n");
	}
	return error;
}

int EvrSearch(EvrPtr E, keyType key, int InOut, int * found){
	typos_deikti deiktis;
	TStoixeiouDDA periexomeno,temp;
	int k;
	TSDDA_setKey(&(temp.key), key); 
	
	#if (Simple)
	Tree_anazitisi(E->TreeRoot,temp, &deiktis,found);
	#else
	AVLTree_anazitisi(E->TreeRoot, temp, &deiktis, found);
	#endif
	
	if(*found)
	{
		#if(Simple)
		Tree_periexomeno(deiktis, &periexomeno);
		#else
		AVLTree_periexomeno(deiktis,&periexomeno);
		#endif
		
		k=TSDDA_getIndex(periexomeno);
		if (InOut==0){
			E->DataArray[k].Arrivals=(E->DataArray[k].Arrivals)+1;
		}
		else if(InOut==1){
			E->DataArray[k].Departures=(E->DataArray[k].Departures)+1;
		}
		return 1;
	}
	return 0;
}

void endodiataksi(EvrPtr E,typos_deikti a,FILE *out, int * counter)
{
	typos_deikti b,c;
	TStoixeiouDDA temp;		
	int index;
	if(a==NULL) return;
	#if (Simple)
    	b=Tree_apaidi(a);
    	c=Tree_dpaidi(a);
    	
	#else   
    	b=AVLTree_apaidi(a);
    	c=AVLTree_dpaidi(a);
	#endif
	
	endodiataksi(E,b,out,counter);
	#if (Simple)
	Tree_periexomeno(a, &temp);			
	#else
	AVLTree_periexomeno(a, &temp);	
	#endif
	
	index=TSDDA_getIndex(temp);			
	TSEvr_writeValue(out, E->DataArray[index]);
	
	(*counter)++;
	endodiataksi(E,c,out,counter);
}
int Evr_PrintAll(EvrPtr E, FILE *out, int * counter){
	
	typos_deikti a=E->TreeRoot;
	if(a==NULL) return 0;
	endodiataksi(E,a,out,counter);
	return 1;
}

int EvrDestruct(EvrPtr *E){
	if(E== NULL) return 0;
	if((*E)->DataArray==NULL) return 0;
	free((*E)->DataArray);
	(*E)->Index=0;
	
	#if(Simple)
	Tree_katastrofi(&((*E)->TreeRoot));
	#else
	AVLTree_katastrofi(&((*E)->TreeRoot));
	#endif
	
	if((*E)->TreeRoot!=NULL) return 0;
	free(*E);
	return 1;
}

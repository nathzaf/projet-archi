#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define V_MAX 200000
#define C_MAX 10000

typedef struct instruction{
    char* code;
    char* dest;
    char* src1;
    char imm;
    char* src2;
} Instruction;
 
typedef struct instructionavecvaleur{
    int codebis;
    char* destbis;
    char* val1;
    char* val2;
} Instructionbis;


int recupLinks(char fileName[V_MAX], char* result[V_MAX]){ //cette fonction permet d'ouvrir et lire un fichier texte, et de placer chaque ligne de ce ficher dans un tableau de chaine de caracteres
	int nbLignes = 0;
	FILE * links;
	links = fopen(fileName, "r");
	if(links == NULL) return 0;
	
	int i = 0;
	while((fgets(result[i], C_MAX, links) != NULL) && (i < V_MAX)){
		i+=1;
		nbLignes += 1;
	}
	
	fclose(links);
	return nbLignes;
}

void createFile(const int nbLines, char* instr[V_MAX], const char fileName[100]){  // met dans le fichier "filename" toutes les chaines de caracteres de "instr"
	FILE * file;
	file = fopen(fileName, "w");
	for(int i=0; i<nbLines; i++) fprintf(file, "%s\n", instr[i]);
	fclose(file);
}

void init_eti(char** etiquette, int nbLignes, char** result){  // initialise le tableau d'etiquettes
	char* s = malloc(100*sizeof(char));
	char* copie_result = malloc(100*sizeof(char));
	for(int i=0;i<nbLignes;i++){
		copie_result = strdup(result[i]);
		if(strstr(copie_result,":")!=NULL){
				s=strtok(copie_result,":");
				etiquette[i]=s; //à la ligne i+1 (car les lignes commencent à 1 et nous à 0), il y a une etiquette 
		}
	}
}

char* hexToBin(char* hexLine, int size){ // Fonction qui traduit une chaine de caractères en hexa de taille "size" et renvoie la version en binaire 
             char** Binary = malloc(size*sizeof(char*));
             for(int i=0; i<size; i++) Binary[i] = malloc(4*sizeof(char));
 
             for(int i=0;i<size;i++){
                              if(hexLine[i]=='0'){
                                           Binary[i] = "0000";
                              }
                              else if(hexLine[i]=='1'){
                                                     Binary[i] = "0001";
                              }
                              else if(hexLine[i]=='2'){
                                           Binary[i] = "0010";
                              }
                              else if(hexLine[i]=='3'){
                                           Binary[i] = "0011";
                              }
                              else if(hexLine[i]=='4'){
                                           Binary[i] = "0100";
                              }
                              else if(hexLine[i]=='5'){
                                           Binary[i] = "0101";
                              }
                              else if(hexLine[i]=='6'){
                                           Binary[i] = "0110";
                              }
                              else if(hexLine[i]=='7'){
                                           Binary[i] = "0111";
                              }
                              else if(hexLine[i]=='8'){
                                           Binary[i] = "1000";
                              }
                              else if(hexLine[i]=='9'){
                                           Binary[i] = "1001";
                              }
                              else if(hexLine[i]=='A'){
                                           Binary[i] = "1010";
                              }
                              else if(hexLine[i]=='B'){
                                           Binary[i] = "1011";
                              }
                              else if(hexLine[i]=='C'){
                                           Binary[i] = "1100";
                              }
                              else if(hexLine[i]=='D'){
                                           Binary[i] = "1101";
                              }
                              else if(hexLine[i]=='E'){
                                           Binary[i] = "1110";
                              }
                              else if(hexLine[i]=='F'){
                                           Binary[i] = "1111";
                              }
             }
             char* Binaire = malloc(size*4*sizeof(char));
             for(int i=0; i<size; i++) strcat(Binaire, Binary[i]);
             return Binaire;
}


char* andBinaire(char* bin1, char* bin2, int size){ // et binaire 
    char* resultat = malloc(size*sizeof(char)); 
    for(int i=0;i<size;i++){
            if((bin1[i]=='1')&&(bin2[i]=='1')) resultat[i]='1';
            else resultat[i]='0'; 
        }
    return resultat;    
}

char* orBinaire(char* bin1, char* bin2, int size){ // ou binaire 
    char* resultat = malloc(size*sizeof(char)); 
    for(int i=0;i<size;i++){
            if((bin1[i]=='1')||(bin2[i]=='1')) resultat[i]='1';
            else resultat[i]='0'; 
        }
    return resultat;    
}

char* xorBinaire(char* bin1, char* bin2, int size){ // ou-exclusif binaire 
    char* resultat = malloc(size*sizeof(char)); 
    for(int i=0;i<size;i++){
            if((bin1[i]=='1')^(bin2[i]=='1')) resultat[i]='1';
            else resultat[i]='0'; 
        }
    return resultat;    
}

int powbis(int x, int y){ // renvoie x à la puissance y 
    int resultat = 1;
    for(int i=0;i<y;i++){
   	 resultat = resultat * x;
    }
    return resultat;
}

int binaireCOMP2decimal(char*str, int size){ //traduit du binaire (en complement à 2) en décimal 
	int x=0;
	for(int i=1; i<size; i++){
    	if(str[i]=='1'){
        	x = x + powbis(2,size-1-i);	
    	}
	}
	if(str[0]=='1'){
        x = x - powbis(2,size-1);
    }
	return x;
}

int binaire2decimal(char*str, int size){ //traduit du binaire (pas en complement à 2) en décimal
	int x=0;
	for(int i=0; i<size; i++){
    	if(str[i]=='1'){
        	x = x + powbis(2,size-1-i);	
    	}
	}
	return x;
}

char* deciaml2hexa(int x){  // prend un nombre decimal entre 0 et 15 et renvoie le caractere hexadecimal associé
    
	if(x<10){
    	char*str = malloc(sizeof(char));
    	snprintf(str,20,"%d",x);
    	return str;
	}
	switch(x){
    	case 10:
        	return "A";
        	break;
    	case 11:
        	return "B";
        	break;
    	case 12:
        	return "C";
        	break;
    	case 13:
        	return "D";
        	break;
    	case 14:
        	return "E";
        	break;
    	case 15:
        	return "F";
        	break;
	}
	return "";    //la fonction n'arrivera jamais à cette ligne
}

char* binaire2hexa(char* str){   // traduit binaire en hexadecimal, fonctionne uniquement avec les binaires de 32 charctères 
	char* hexa = malloc(8*sizeof(char));
	for(int i=0; i<8; i++){
    	char*temp = malloc(4*sizeof(char));
    	temp[0] = str[4*i];
    	temp[1] = str[4*i+1];
    	temp[2] = str[4*i+2];
    	temp[3] = str[4*i+3];
   	 
    	strcat(hexa,deciaml2hexa(binaire2decimal(temp,4)));
	}
	return hexa;
}

char* shr(char* val1, int shift, int size, char* retenue){   // decale un nombre binanire vers la gauche (si shift positif) et vers la droite (si shift negatif) 
    char* temp = strdup(val1);
    char* tempbis = strdup(val1);
    if(shift>0){
        for(int i=0; i<size-shift; i++) temp[i] = temp[i+shift];
        for(int i=size-shift; i<size; i++) temp[i] = '0';
        tempbis = strdup(temp);
        *retenue = val1[shift-1];
    } else if(shift<0){
        for(int i=(-shift); i<size; i++) tempbis[i]=temp[i+shift];
        for(int i=0; i<(-shift); i++) tempbis[i] = '0';
        *retenue = val1[size+shift];
    }
    return tempbis;
}


char demiAdd(char bin1, char bin2, char* retenue){ // demi additionneur de 2 bits
    if((bin1=='1')^(bin2=='1')){
        *retenue = '0';
        return '1';
    }
    else if((bin1=='0')&&(bin2=='0')){
        *retenue = '0';
        return '0';
    }
    else{
        *retenue = '1';
        return '0';
    }
}

char addComplet(char bin1, char bin2, char *retenue){  // additionneur complet de 2 bits et une retenue
    char r2 = '0';
    char r1 = '0';
    char s1 = demiAdd(bin1, bin2, &r1);
    char s2 = demiAdd(s1, *retenue, &r2);
    if((r1=='1')||(r2=='1')) *retenue = '1';
    else *retenue = '0';
    return s2;
}

char* add2binaires(char* bin1, char* bin2, int size, char* retenue){ // addition de 2 nombres binaires avec retenue en entré
    char* temp = malloc(size*sizeof(char));
    for(int i=size-1; i>=0; i--){
        temp[i] = addComplet(bin1[i], bin2[i], retenue);
    }
    return temp;
}

char* decToBin(int d, int size){  // convertit du decimal en binaire, faire attention à l'intervalle 
	char* bin = malloc(size*sizeof(char));
	for(int i=0; i<size; i++){
		if(d%2==0) bin[size-1-i]='0';
		else if(d%2==1) bin[size-1-i]='1';
		d=d/2;
	}
	return bin;
}

char* inversionDesBits(char* bin, int size){  // inverse tous les bits
    char* temp = malloc(size*sizeof(char));
    for(int i=0; i<size; i++){
        if(bin[i]=='1'){
            temp[i]= '0';
        }
        if(bin[i]=='0'){
            temp[i]='1'; 
            
        } 
    }
    return temp;
}

char* completerBinUn(char* bin, int taille){  // on rajoute juste des zeros devant le chiffre pour avoir la bonne taille 
    int size = taille-strlen(bin);
    char* binbis = strdup(bin);
    char* temp = malloc(size*sizeof(char));
    for(int i=0; i<size; i++) temp[i] = '1';
    strcat(temp,binbis);
    return temp;
}


char* ajout1(char* bin, int size){ // ajoute 1 à un nombre binaire 
    char* un = malloc(size*sizeof(char));
    for(int i=0; i<size-1; i++){
        strcat(un,"0");
    }
    strcat(un,"1");
    char* r = malloc(sizeof(char));
    *r = 48;
    return add2binaires(bin, un, size, r);
}

char* decimal2binaireCOMP(int x, int size){  // convertit du decimal en binaire (en complément à 2) ATTENTION faire bien attention à l'intervalle des possibilité, adapter size en consequence 
    if(x>=0) return decToBin(x, size);
    else{
        char* comp = malloc(size*sizeof(char));
        comp = decToBin(-x,size);
        comp = inversionDesBits(comp,size);
        comp = ajout1(comp,size);
        return comp;
    }
}

char* decalage(char* bin, int shift){  // decale bin vers la gauche, le shift doit etre positif
    int size = (strlen(bin)+shift);
    char* temp = malloc(size*sizeof(char));
    for(int i=0; i<size-shift; i++) temp[i] = bin[i];
    for(int j=size-shift; j<size; j++) temp[j] = '0';
    return temp;
    
}

char* completerBin(char* bin, int taille){  // rajoute des zeros devant le chiffre pour avoir la bonne taille 
    int size = taille-strlen(bin);
    char* binbis = strdup(bin);
    char* temp = malloc(size*sizeof(char));
    for(int i=0; i<size; i++) temp[i] = '0';
    strcat(temp,binbis);
    return temp;
}

char* multiplication(char* bin1, char* bin2, char* retenue){  // prend 2 nombre binaire de 16 bits et renvoie leur multiplacation en 32 bits 
    char* temp1 = "00000000000000000000000000000000";
    char* temp2 = malloc(32*sizeof(char));
    if((bin1[0]=='1')^(bin2[0]=='1')){
        if(bin1[0]=='1'){
            bin1 = inversionDesBits(bin1,16);
            bin1 = ajout1(bin1,16);
        }
        if(bin2[0]=='1'){
            bin2 = inversionDesBits(bin2,16);
            bin2 = ajout1(bin2,16);
        }
        for(int i=15; i>=0; i--){
            if(bin2[i]=='1'){
                temp2 = decalage(bin1, 15-i);
                temp2 = completerBin(temp2,32);
                temp1 = add2binaires(temp1,temp2,32,retenue);
            }
        }
        temp1 = inversionDesBits(temp1,32);
        temp1 = ajout1(temp1,32);
    }
    else if((bin1[0]=='1')&&(bin2[0]=='1')){
        bin1 = inversionDesBits(bin1,16);
        bin1 = ajout1(bin1,16);
        char* bin1bis = strdup(bin1);
        bin2 = inversionDesBits(bin2,16);
        bin2 = ajout1(bin2,16);
        for(int i=15; i>=0; i--){
            if(bin2[i]=='1'){
                temp2 = decalage(bin1bis, 15-i);
                temp2 = completerBin(temp2,32);
                temp1 = add2binaires(temp1,temp2,32,retenue);
            }
        }
    }
    else{
        for(int i=15; i>=0; i--){
            if(bin2[i]=='1'){
                temp2 = decalage(bin1, 15-i);
                temp2 = completerBin(temp2,32);
                temp1 = add2binaires(temp1,temp2,32,retenue);
            }
        }
    }
    return temp1;
}


char* sub2binaires(char* bin1, char* bin2, int size, char* retenue){ // soustraction de deux nombres binaires,  a-b = a+(-b) 
    char* inversBin2 = strdup(bin2);
    inversBin2 = inversionDesBits(inversBin2,size);
    inversBin2 = ajout1(inversBin2,size);
    return add2binaires(bin1,inversBin2,size,retenue);
}


char* divisionBinaire(char* bin1, char* bin2, int size){  // division binaire de 2 nombres binaire de taille size 
    int quotient = 0;
    char* retenue = malloc(sizeof(char));
    char* sub = malloc(size*sizeof(char));
    int cas;    // cas permet de verifier si le resultat final sera positif ou negatif
    
    if((bin1[0]=='0')&&(bin2[0]=='0')){
        cas = 1;
    }
    else if((bin1[0]=='1')&&(bin2[0]=='0')){
        bin1 = strdup(inversionDesBits(bin1,size));
        bin1 = strdup(ajout1(bin1,size));
        cas = 2;
    }
    else if((bin1[0]=='0')&&(bin2[0]=='1')){
        bin2 = strdup(inversionDesBits(bin2,size));
        bin2 = strdup(ajout1(bin2,size));
        cas = 2;
    }
    else {
        cas = 3;
        bin1 = strdup(inversionDesBits(bin1,size));
        bin1 = strdup(ajout1(bin1,size));
        bin2 = strdup(inversionDesBits(bin2,size));
        bin2 = strdup(ajout1(bin2,size));
    }
    
    while (binaireCOMP2decimal(bin1,size)>=binaireCOMP2decimal(bin2,size)){
        *retenue = 48;
        sub = malloc(size*sizeof(char));
        sub = strdup(sub2binaires(bin1,bin2,size,retenue));
        bin1 = strdup(sub);
        quotient += 1;
    }
    
    if((cas==1)||(cas==3)) return decimal2binaireCOMP(quotient,size);  // si on etait dans le cas ou les deux entrées sont positives ou les 2 negatives on renvoie le quotien positif
    else return decimal2binaireCOMP(-quotient,size); //sinon on renvoie l'inverse du quotient
}



char* completerBinDroite(char* bin, int taille){  // rajoute des zeros à droite du nombre binaire pour avoir la bonne taille size
    int size = taille-strlen(bin);
    char* binbis = strdup(bin);
    char* temp = malloc(size*sizeof(char));
    for(int i=0; i<size; i++) temp[i] = '0';
    char* tempbis = strdup(temp);
    strcat(binbis,tempbis);
    return binbis;
}



int pos(char *s,char *etiquette[V_MAX],int nbLignes){ 
	for(int i=0;i<nbLignes;i++){
		if(strcmp(etiquette[i],s)==0){
			return 4*i;
		}
	}
	return -1;
}

//result : instructions ligne par ligne

void trad(char *result[V_MAX], char *machine[V_MAX], char *etiquette[V_MAX], int nbLignes,int *temoin){
	int cpt,val,transfert;
	char *s=malloc(50*sizeof(char));
	char *bis=malloc(50*sizeof(char));
	char* hash=malloc(sizeof(char));
	char* bisbis = malloc(32*sizeof(char));
	char *temp=malloc(50*sizeof(char));
	char *temp2=malloc(5*sizeof(char));
	for(int i=0;i<nbLignes;i++){
		bis=strdup("");
		bisbis=strdup("");
		hash = strstr(result[i],"#");
		cpt=0; //si cpt=0, on regarde le code d'instruction. Si cpt=1, on regarde le numero du premier registre (etc)
		val=0;
		transfert=0;
		if(strstr(result[i],":")!=NULL){
			s=strtok(result[i],":");
			s=strtok(NULL, ": , \t()#\n"); 
		}
		else{
			s=strtok(result[i]," , \t()#\n");
		}
		while(s!=NULL){
			if(cpt==3 && transfert>=1){
				if(hash!=NULL){
					strcat(bis,"1");
					bisbis=strdup(bis);
					strcat(bisbis,strdup(decimal2binaireCOMP(atoi(s),16)));
					bis = strdup(bisbis);
				}
				else if(strstr(result[i],"#h")!=NULL){
					strcat(bis,"1");
					bisbis=strdup(bis);
					strcat(bisbis,strdup(hexToBin(s,16)));
					bis = strdup(bisbis);
				}
			}
			
			
			if(cpt==3 && hash!=NULL && transfert == 0){
				strcat(bis,"1");
				bisbis=strdup(bis);
				strcat(bisbis,strdup(decimal2binaireCOMP(atoi(s),16)));
				bis = strdup(bisbis);
			}
			else if(cpt==3 && hash==NULL){
				strcat(bis,"000000000000");
			}
			
			if(strcmp(s,"and")==0){
				strcat(bis,"00000");
				val=4;
			}
			else if(strcmp(s,"or")==0){
				strcat(bis,"00001");
				val=4;
			} 
			else if(strcmp(s,"xor")==0){
				strcat(bis,"00010");
				val=4;
			}
			else if(strcmp(s,"mul")==0){
				strcat(bis,"00011");
				val=4;
			}
			else if(strcmp(s,"div")==0){
				strcat(bis,"00100");
				val=4;
			}
			else if(strcmp(s,"add")==0){
				strcat(bis,"00101");
				val=4;
			}
			else if(strcmp(s,"sub")==0){
				strcat(bis,"00110");
				val=4;
			}
			else if(strcmp(s,"shr")==0){
				strcat(bis,"00111");
				val=4;
			}
			else if(strcmp(s,"ldb")==0){
				strcat(bis,"01000");
				val=4;
				transfert=1;
				
			}
			else if(strcmp(s,"ldh")==0){
				strcat(bis,"01001");
				val=4;
				transfert=1;
			}
			else if(strcmp(s,"ldw")==0){
				strcat(bis,"01010");
				val=4;
				transfert=1;
			}
			else if(strcmp(s,"stb")==0){
				strcat(bis,"01011");
				val=4;
				transfert=2;
				
			}
			else if(strcmp(s,"sth")==0){
				strcat(bis,"01100");
				val=4;
				transfert=2;
			}
			else if(strcmp(s,"stw")==0){
				strcat(bis,"01101");
				val=4;
				transfert=2;
			}
			else if(strcmp(s,"jmp")==0){
				strcat(bis,"01110");
				val=2;
			}
			else if(strcmp(s,"jzs")==0){
				strcat(bis,"01111");
				val=2;
			}
			else if(strcmp(s,"jzc")==0){
				strcat(bis,"10000");
				val=2;
			}
			else if(strcmp(s,"jcs")==0){
				strcat(bis,"10001");
				val=2;
			}
			else if(strcmp(s,"jcc")==0){
				strcat(bis,"10010");
				val=2;
			}
			else if(strcmp(s,"jns")==0){
				strcat(bis,"10011");
				val=2;
			}
			else if(strcmp(s,"jnc")==0){
				strcat(bis,"10100");
				val=2;
			}
			else if(strcmp(s,"in")==0){
				strcat(bis,"10101");
				val=2;
			}
			else if(strcmp(s,"out")==0){
				strcat(bis,"10110");
				val=2;
			}
			else if(strcmp(s,"rnd")==0){
				strcat(bis,"10111");
				val=4;
			}
			else if(strcmp(s,"hlt")==0){
				strcat(bis,"11111");
				val=1;
			}//fin des instructions
			
			else if(strcmp(s,"r0")==0){
				strcat(bis,"00000");
			}
			else if(strcmp(s,"r1")==0){
				strcat(bis,"00001");
			}
			else if(strcmp(s,"r2")==0){
				strcat(bis,"00010");
			}
			else if(strcmp(s,"r3")==0){
				strcat(bis,"00011");
			}
			else if(strcmp(s,"r4")==0){
				strcat(bis,"00100");
			}
			else if(strcmp(s,"r5")==0){
				strcat(bis,"00101");
			}
			else if(strcmp(s,"r6")==0){
				strcat(bis,"00110");
			}
			else if(strcmp(s,"r7")==0){
				strcat(bis,"00111");
			}
			else if(strcmp(s,"r8")==0){
				strcat(bis,"01000");
			}
			else if(strcmp(s,"r9")==0){
				strcat(bis,"01001");
			}
			else if(strcmp(s,"r10")==0){
				strcat(bis,"01010");
			}
			else if(strcmp(s,"r11")==0){
				strcat(bis,"01011");
			}
			else if(strcmp(s,"r12")==0){
				strcat(bis,"01100");
			}
			else if(strcmp(s,"r13")==0){
				strcat(bis,"01101");
			}
			else if(strcmp(s,"r14")==0){
				strcat(bis,"01110");
			}
			else if(strcmp(s,"r15")==0){
				strcat(bis,"01111");
			}
			else if(strcmp(s,"r16")==0){
				strcat(bis,"10000");
			}
			else if(strcmp(s,"r17")==0){
				strcat(bis,"10001");
			}
			else if(strcmp(s,"r18")==0){
				strcat(bis,"10010");
			}
			else if(strcmp(s,"r19")==0){
				strcat(bis,"10011");
			}
			else if(strcmp(s,"r20")==0){
				strcat(bis,"10100");
			}
			else if(strcmp(s,"r21")==0){
				strcat(bis,"10101");
			}
			else if(strcmp(s,"r22")==0){
				strcat(bis,"10110");
			}
			else if(strcmp(s,"r23")==0){
				strcat(bis,"10111");
			}
			else if(strcmp(s,"r24")==0){
				strcat(bis,"11000");
			}
			else if(strcmp(s,"r25")==0){
				strcat(bis,"11001");
			}
			else if(strcmp(s,"r26")==0){
				strcat(bis,"11010");
			}
			else if(strcmp(s,"r27")==0){
				strcat(bis,"11011");
			}
			else if(strcmp(s,"r28")==0){
				strcat(bis,"11100");
			}
			else if(strcmp(s,"r29")==0){
				strcat(bis,"11101");
			}
			else if(strcmp(s,"r30")==0){
				strcat(bis,"11110");
			}
			else if(strcmp(s,"r31")==0){
				strcat(bis,"11111");
			}
			else if(cpt==1){
				strcat(bis,"0000000000");
				if(hash!=NULL){
					strcat(bis,"1");
					bisbis=strdup(bis);
					strcat(bisbis,strdup(decimal2binaireCOMP(atoi(s),16)));
					bis = strdup(bisbis);
				}
				else if(strstr(result[i],"#h")!=NULL){
					strcat(bis,"1");
					bisbis=strdup(bis);
					strcat(bisbis,strdup(hexToBin(s,16)));
					bis = strdup(bisbis);
				}
				else if(strlen(bis)==10){ //cas ou la destination est un registre
					temp=strdup(bis);
					strncpy(temp,bis,5);
					bis=strdup(temp);
					strcat(bis,"00000000000"); // le bit IMM et onze 0 car numero du registre sur 5 bits
					if(strcmp(s,"r0")==0){
						strcat(bis,"00000");
					}
					else if(strcmp(s,"r1")==0){
						strcat(bis,"00001");
					}
					else if(strcmp(s,"r2")==0){
						strcat(bis,"00010");
					}
					else if(strcmp(s,"r3")==0){
						strcat(bis,"00011");
					}
					else if(strcmp(s,"r4")==0){
						strcat(bis,"00100");
					}
					else if(strcmp(s,"r5")==0){
						strcat(bis,"00101");
					}
					else if(strcmp(s,"r6")==0){
						strcat(bis,"00110");
					}
					else if(strcmp(s,"r7")==0){
						strcat(bis,"00111");
					}
					else if(strcmp(s,"r8")==0){
						strcat(bis,"01000");
					}
					else if(strcmp(s,"r9")==0){
						strcat(bis,"01001");
					}
					else if(strcmp(s,"r10")==0){
						strcat(bis,"01010");
					}
					else if(strcmp(s,"r11")==0){
						strcat(bis,"01011");
					}
					else if(strcmp(s,"r12")==0){
						strcat(bis,"01100");
					}
					else if(strcmp(s,"r13")==0){
						strcat(bis,"01101");
					}
					else if(strcmp(s,"r14")==0){
						strcat(bis,"01110");
					}
					else if(strcmp(s,"r15")==0){
						strcat(bis,"01111");
					}
					else if(strcmp(s,"r16")==0){
						strcat(bis,"10000");
					}
					else if(strcmp(s,"r17")==0){
						strcat(bis,"10001");
					}
					else if(strcmp(s,"r18")==0){
						strcat(bis,"10010");
					}
					else if(strcmp(s,"r19")==0){
						strcat(bis,"10011");
					}
					else if(strcmp(s,"r20")==0){
						strcat(bis,"10100");
					}
					else if(strcmp(s,"r21")==0){
						strcat(bis,"10101");
					}
					else if(strcmp(s,"r22")==0){
						strcat(bis,"10110");
					}
					else if(strcmp(s,"r23")==0){
						strcat(bis,"10111");
					}
					else if(strcmp(s,"r24")==0){
						strcat(bis,"11000");
					}
					else if(strcmp(s,"r25")==0){
						strcat(bis,"11001");
					}
					else if(strcmp(s,"r26")==0){
						strcat(bis,"11010");
					}
					else if(strcmp(s,"r27")==0){
						strcat(bis,"11011");
					}
					else if(strcmp(s,"r28")==0){
						strcat(bis,"11100");
					}
					else if(strcmp(s,"r29")==0){
						strcat(bis,"11101");
					}
					else if(strcmp(s,"r30")==0){
						strcat(bis,"11110");
					}
					else if(strcmp(s,"r31")==0){
						strcat(bis,"11111");
					}
					
				} else { //cas où la destination est une etiquette
					strcat(bis,"1");
					if(pos(s,etiquette,nbLignes)==-1){
						printf("Erreur : cette etiquette n'existe pas\n");
						*temoin+=1;
			
					}else strcat(bis,strdup(decToBin(pos(s,etiquette,nbLignes),16))); 		
					
				}
			}
			cpt=cpt+1;
			s=strtok(NULL, ",  \t()#\n");
		}
		
		if(cpt!=val){
			bis="ERROR";
		}
		
		char *ter = strdup(completerBinDroite(bis, 32));
		
		if((transfert==2)&&(hash==NULL)){  // pour inverser rn et S que dans le cas st* 
			temp2[0] = ter[27];
			temp2[1] = ter[28];
			temp2[2] = ter[29];
			temp2[3] = ter[30];
			temp2[4] = ter[31];
			
			ter[27] = ter[10];
			ter[28] = ter[11];
			ter[29] = ter[12];
			ter[30] = ter[13];
			ter[31] = ter[14];
			
			ter[10] = temp2[0];
			ter[11] = temp2[1];
			ter[12] = temp2[2];
			ter[13] = temp2[3];
			ter[14] = temp2[4];
		}
		
		machine[i]=strdup(ter);
		
	}
}


 
int getLines(const char fileName[100], char* file_lines[V_MAX]){ //Cette fonction permet d'ouvrir et lire un fichier texte, et de placer chaque ligne de ce ficher dans un tableau de chaine de caracteres. De plus elle renvoie le nombre de lignes
	FILE * file;
	file = fopen(fileName, "r");
	if(file == NULL) return 0;
	int i = 0;
	while((fgets(file_lines[i], V_MAX, file) != NULL) && (i++ < V_MAX)); // recupere la ligne dans file_line[i] et increment le compteur de ligne
	fclose(file);
	return i;
}
 

Instruction* split(char* inst){ // Fonction qui prend une instruction en binaire et la place dans la structure instruction
	Instruction* Instr= malloc(sizeof(Instruction));
   
	char* code=malloc(5*sizeof(char));
	for(int i=0; i<5; i++) code[i]=inst[i];
	Instr->code = strdup(code);
   
	char* dest=malloc(5*sizeof(char));
	for(int i=0; i<5; i++) dest[i]=inst[i+5];
	Instr->dest = strdup(dest);
   
	char* src1=malloc(5*sizeof(char));
	for(int i=0; i<5; i++) src1[i]=inst[i+10];
	Instr->src1 = strdup(src1);
   
	Instr->imm = inst[15];
   
	char* src2=malloc(16*sizeof(char));
	for(int i=0; i<16; i++) src2[i]=inst[i+16];
	Instr->src2 = strdup(src2);
   
	return Instr;
}
 
void initRegistres(char** Registres, char* RegistreEtat){ // Fonction initialisant tous les registres a 0
	for(int i=0; i<32; i++) Registres[i]="00000000000000000000000000000000";
	for(int j=0; j<3; j++) RegistreEtat[j] = '0';
}
 

void initMemory(char** Memoire, int i, char* charInstr){ // initialise la mémoire
	for(int k=0; k<4; k++){
		for(int j=0; j<8; j++){
			Memoire[k+4*i][j]=charInstr[8*k+j];
		}
	}
}

 

 
int executer(Instructionbis* PCbis, Instruction** PC, Instruction** All, char* RE, char** Registres, int* CPC, char* retenue, char** Memoire){
    const char* zeroBin = "00000000000000000000000000000000";
    char* val1 = PCbis->val1;
    char* val2 = PCbis->val2;
    int saut = 0; // Si ce temoin est mis a 1 alors un saut aura ete effectue (par jmp) et donc pas de +1 a PC à la fin
   
    switch(PCbis->codebis){
       
        case 0: // AND
            PCbis->destbis = strdup(andBinaire(val1, val2, 32));
            if(strcmp(PCbis->destbis ,zeroBin)==0) RE[0] = '1';
            else RE[0] = '0';
            RE[1]='0';
            RE[2] = PCbis->destbis[0];
            break;
           
        case 1: // OR
            PCbis->destbis = strdup(orBinaire(val1, val2, 32));
            if(strcmp(PCbis->destbis,zeroBin)==0) RE[0] = '1';
            else RE[0] = '0';
            RE[1]='0';
            RE[2] = PCbis->destbis[0];
            break;
       
        case 2: // XOR
			PCbis->destbis = strdup(xorBinaire(val1, val2, 32));
            if(strcmp(PCbis->destbis,zeroBin)==0) RE[0] = '1';
            else RE[0] = '0';
            RE[1]='0';
            RE[2] = PCbis->destbis[0];
            break;
              
        case 3: // MUL
            PCbis->destbis = strdup(multiplication(val1, val2, retenue));
            if(strcmp(PCbis->destbis,zeroBin)==0) RE[0] = '1';
            else RE[0] = '0';
            if(*retenue=='1') RE[1] = '1';
            else RE[1] = '0'; 
            RE[2] = PCbis->destbis[0];
            break;
           
        case 4: // DIV
        	PCbis->destbis = divisionBinaire(val1, val2, 32);
        	if(strcmp(PCbis->destbis,zeroBin)==0) RE[0] = '1';
            else RE[0] = '0';
            RE[1]='0';
            break;
           
        case 5: // ADD
			PCbis->destbis = strdup(add2binaires(val1, val2, 32, retenue));
            if(strcmp(PCbis->destbis,zeroBin)==0) RE[0] = '1';
            else RE[0] = '0';
            if(*retenue=='1') RE[1] = '1';
            else RE[1] = '0';
            RE[2] = PCbis->destbis[0];
            break;
            
        case 6: // SUB
            PCbis->destbis = strdup(sub2binaires(val1, val2, 32, retenue));
            if(strcmp(PCbis->destbis,zeroBin)==0) RE[0] = '1';
            else RE[0] = '0';
            if(*retenue=='1') RE[1] = '1';
            else RE[1] = '0';
            RE[2] = PCbis->destbis[0];
            break;
        
        case 7:{ // SHR
            int shift = binaireCOMP2decimal(val2, 32);
            PCbis->destbis = strdup(shr(val1, shift, 32, retenue));
            if(strcmp(PCbis->destbis,zeroBin)==0) RE[0] = '1';
            else RE[0] = '0';
            if(*retenue=='1') RE[1] = '1';
            else RE[1]='0';
            RE[2] = PCbis->destbis[0];
            break;
        }
        case 8:{ // LDB
        	char* rnS = add2binaires(val1, val2, 32, retenue);
        	char* templdb = Memoire[binaire2decimal(rnS, 32)];
        	PCbis->destbis = strdup(completerBin(templdb, 32));
        	if(strcmp(PCbis->destbis,zeroBin)==0) RE[0] = '1';
            else RE[0] = '0';
        	RE[1]='0';
        	RE[2] = PCbis->destbis[0];
        	break;}
        	
        case 9:{ // LDH
        	char* rnS = add2binaires(val1, val2, 32, retenue);
        	char* templdh = strdup(Memoire[binaire2decimal(rnS, 32)]);
        	char* templdhbis = strdup(Memoire[binaire2decimal(rnS, 32)+1]);
        	strcat(templdhbis, templdh);
        	PCbis->destbis = strdup(completerBin(templdhbis, 32));
        	if(strcmp(PCbis->destbis,zeroBin)==0) RE[0] = '1';
            else RE[0] = '0';
        	RE[1]='0';
        	RE[2] = PCbis->destbis[0];
        	break;}
        	
        case 10:{ // LDW
        	char* rnS = add2binaires(val1, val2, 32, retenue);
        	char* templdw = strdup(Memoire[binaire2decimal(rnS, 32)]);
        	char* templdwbis = strdup(Memoire[binaire2decimal(rnS, 32)+1]);
        	char* templdwter = strdup(Memoire[binaire2decimal(rnS, 32)+2]);
        	char* templdwquad = strdup(Memoire[binaire2decimal(rnS, 32)+3]);
        	strcat(templdwquad, templdwter);
        	strcat(templdwquad, templdwbis);
        	strcat(templdwquad, templdw);
        	PCbis->destbis = strdup(completerBin(templdwquad, 32));
        	if(strcmp(PCbis->destbis,zeroBin)==0) RE[0] = '1';
            else RE[0] = '0';
        	RE[1]='0';
        	RE[2] = PCbis->destbis[0];
        	break;}
        	
        case 11:{ // STB
        	char* rnS = strdup(add2binaires(PCbis->destbis, val2, 32, retenue));
        	char* temp = strdup(Registres[binaire2decimal(val1, strlen(val1))]);
        	char* temp_oct = malloc(8*sizeof(char));
        	
        	for(int i=0; i<8; i++) temp_oct[i]=temp[i+24];
        	
        	Memoire[binaire2decimal(rnS, 32)] = strdup(temp_oct);
        	if(strcmp(temp_oct, "00000000")==0) RE[0]='1';
        	else RE[0] = '0';
        	RE[1]='0';
        	break;}
        	
        case 12: { // STH
        	char* rnS = strdup(add2binaires(PCbis->destbis, val2, 32, retenue));
        	char* temp = strdup(Registres[binaire2decimal(val1, strlen(val1))]);
        	char* temp_oct = malloc(8*sizeof(char));
        	char* temp_oct_bis =  malloc(8*sizeof(char));
        	
        	for(int i=0; i<8; i++) temp_oct[i]=temp[i+24];
        	for(int i=0; i<8; i++) temp_oct_bis[i]=temp[i+16];
        	
        	Memoire[binaire2decimal(rnS, 32)] = strdup(temp_oct);
        	Memoire[binaire2decimal(rnS, 32)+1] = strdup(temp_oct_bis);
        	if(strcmp(temp_oct, "00000000")==0 && strcmp(temp_oct_bis, "00000000")==0) RE[0]='1';
        	else RE[0] = '0';
        	RE[1]='0';
        	break;}
        	
        case 13:{ // STW
        	char* rnS = strdup(add2binaires(PCbis->destbis, val2, 32, retenue));
        	char* temp = strdup(Registres[binaire2decimal(val1, strlen(val1))]);
        	char* temp_oct = malloc(8*sizeof(char));
        	char* temp_oct_bis = malloc(8*sizeof(char));
        	char* temp_oct_ter = malloc(8*sizeof(char));
        	char* temp_oct_quad = malloc(8*sizeof(char));
        	
        	for(int i=0; i<8; i++) temp_oct[i]=temp[i+24];
        	for(int i=0; i<8; i++) temp_oct_bis[i]=temp[i+16];
        	for(int i=0; i<8; i++) temp_oct_ter[i]=temp[i+8];
        	for(int i=0; i<8; i++) temp_oct_quad[i]=temp[i];
        	
        	Memoire[binaire2decimal(rnS, 32)] = strdup(temp_oct);
        	Memoire[binaire2decimal(rnS, 32)+1] = strdup(temp_oct_bis);
        	Memoire[binaire2decimal(rnS, 32)+2] = strdup(temp_oct_ter);
        	Memoire[binaire2decimal(rnS, 32)+3] = strdup(temp_oct_quad);
        	if(strcmp(temp_oct, "00000000")==0 && strcmp(temp_oct_bis, "00000000")==0 && strcmp(temp_oct_ter, "00000000")==0 && strcmp(temp_oct_quad, "00000000")==0) RE[0]='1';
        	else RE[0] = '0';
        	RE[1]='0';
        	break;}
       
        case 14: // JMP 
            *CPC = binaire2decimal(val2, strlen(val2))/4;
            *PC = All[*CPC];
            saut = 1;
            break;
                              
        case 15: // JZS
            if(RE[0]=='1'){
				*CPC = binaire2decimal(val2, strlen(val2))/4;
				*PC = All[*CPC];
				saut = 1;
            }
            break;
            
        case 16: // JZC
            if(RE[0]=='0'){
                *CPC = binaire2decimal(val2, strlen(val2))/4;
                *PC = All[*CPC];
                saut = 1;
            }
            break;
            
        case 17: // JCS
            if(RE[1]=='1'){
                *CPC = binaire2decimal(val2, strlen(val2))/4;
                *PC = All[*CPC];
                saut = 1;
            }
            break;
           
        case 18: // JCC
            if(RE[1]=='0'){
                *CPC = binaire2decimal(val2, strlen(val2))/4;
                *PC = All[*CPC];
                saut = 1;
            }
            break;
           
        case 19: // JNS
            if(RE[2]=='1'){
                *CPC = binaire2decimal(val2, strlen(val2))/4;
                *PC = All[*CPC];
                saut = 1;
                }
            break;
           
        case 20: // JNC
            if(RE[2]=='0'){
                *CPC = binaire2decimal(val2, strlen(val2))/4;
                *PC = All[*CPC];
                saut = 1;
            }
            break;
           
        case 21:{ // IN
            int* userInputDec = malloc(sizeof(int));
            printf("Entrez une valeur : ");
            scanf("%d", userInputDec);
            PCbis->destbis = strdup(decimal2binaireCOMP(*userInputDec,32));
        	if(strcmp(PCbis->destbis,zeroBin)==0) RE[0] = '1';
        	else RE[0]='0';
        	RE[1]='0';
        	RE[2] = PCbis->destbis[0];
            break;
        }
       
        case 22: // OUT
            printf("Valeur dans le registre %d : %d\n", binaire2decimal((*PC)->dest, 5), binaireCOMP2decimal(PCbis->destbis, 32));
            if(strcmp(PCbis->destbis,zeroBin)==0) RE[0] = '1';
            else RE[0] = '0';
            RE[1]='0';
            RE[2] = PCbis->destbis[0];
            break;
           
        case 23:{ // RND
        	int diff = (binaireCOMP2decimal(val2, 32)-1) - binaireCOMP2decimal(val1, 32);
			int randomValue = rand()%diff; // On prend la valeur random sur le bon nombres de valeurs (par exemple si [-1; 3] 5 valeurs possibles)
			randomValue += binaireCOMP2decimal(val1, 32); // Puis on rajoute le min, car la ca a donné [0;4] donc on fait -1 pour [-1;3]
            PCbis->destbis = decToBin(randomValue,32);
            if(strcmp(PCbis->destbis,zeroBin)==0) RE[0] = '1';
            else RE[0] = '0';
            RE[1]='0';
            RE[2] = PCbis->destbis[0];        
            break;
            
            }
    }
    if(strcmp(PCbis->destbis, "")!=0 || PCbis->codebis==11 || PCbis->codebis==12 || PCbis->codebis==13) Registres[binaire2decimal((*PC)->dest, 5)] = PCbis->destbis; // MODIFIATION DES REGISTRES QUE SI DEST A UNE VALEUR ET QUE NON ST*
    return saut;
              
}

	



int main(int argc, char* argv[]){
	char* resultat[V_MAX];
	char* machine[V_MAX];
	char* etiquette[V_MAX];
	int nbLignes;
	int temoin=0;
	
	for(int i=0; i<V_MAX; i++){ 
		resultat[i] = malloc(V_MAX*sizeof(char)); //Cette ligne permet pour chaque chaines de caracteres du tableau de reserver la place pour 10 000 caracteres, une definition par macro provoquant seg fault
		machine[i]=malloc(32*sizeof(char));
		machine[i]="";
		etiquette[i]=malloc(V_MAX*sizeof(char));
		if(resultat[i]==NULL){
			printf("Erreur d'allocation memoire \n");
			return 1;	
		}
	}
	
	nbLignes = recupLinks(argv[1], resultat);
	
	init_eti(etiquette, nbLignes, resultat);
	
	trad(resultat,machine,etiquette,nbLignes,&temoin);
	if(temoin!=0){
		printf("erreur fatale : etiquette inexistante");
	}
	
	char* hexa[nbLignes];
	
	for(int i=0; i<nbLignes; i++){
		hexa[i]=binaire2hexa(machine[i]);
	}

	
	createFile(nbLignes, hexa, "hexaquad.txt");
	
	
	////////////////////////////////////////////////////////////////////
	
	char* retenue = malloc(sizeof(char));
	*retenue = '0';
	
    srand(time(NULL));
	char* file_lines[V_MAX]; // Creation d'un tableau de chaines de caracteres qui va contenir toutes les lignes du fichier assembleur
	int nbLines;
	for(int i=0; i<V_MAX; i++){ 
		file_lines[i] = malloc(V_MAX*sizeof(char));
		if(file_lines[i]==NULL) return 1;	
	}
	
	char** Memoire = malloc(65536*sizeof(char*)); // Creation de la memoire adressee de 0 a 65535
	for(int i=0; i<65536; i++) Memoire[i] = malloc(8*sizeof(char)); // Reservation d'un octet pour chaque emplacement, on stockera les valeurs binaires
	
	nbLines = getLines("hexaquad.txt", file_lines);
	char** charInstr = malloc(nbLines*sizeof(char*));
	for(int i=0; i<nbLines; i++){
		charInstr[i] = malloc(32*sizeof(char));
		charInstr[i] = hexToBin(file_lines[i], 8);
	}
	
	for(int i=0; i<nbLines; i++) initMemory(Memoire, i, charInstr[i]);
	
	Instruction** All = malloc(nbLines*sizeof(Instruction*));
	
	for(int i=0; i<nbLines; i++) All[i] = split(charInstr[i]);
	
	char** Registres = malloc(32*sizeof(char*)); 
	char* RegistresEtat = malloc(3*sizeof(char)); // On pose que RE[0]=Z ; RE[1]=C ; RE[2]=N
	initRegistres(Registres, RegistresEtat);
	
    int currentPC = 0;
    Instruction* PC = All[currentPC];
    Instructionbis* PCbis = malloc(sizeof(Instructionbis));
    int saut;
    
    while(strcmp(PC->code, "11111")!=0){ //Correspond a hlt qui est la fin du programme
    	PCbis->codebis = binaire2decimal(PC->code, 5);
    	
    	PCbis->destbis = malloc(32*sizeof(char)); 
    	
    	if(strcmp(PC->code, "10110")==0 || strcmp(PC->code, "01011")==0 || strcmp(PC->code, "01100")==0 || strcmp(PC->code, "01101")==0) PCbis->destbis = strdup(Registres[binaire2decimal(PC->dest, 5)]); // Exception ou l'instruction rd a besoin de la valeur de dest pour out, st*
    	
    	PCbis->val1 = strdup(Registres[binaire2decimal(PC->src1, 5)]);
    	
    	if(PC->imm=='0'){
    		PCbis->val2 = strdup(Registres[binaire2decimal(PC->src2, 16)]);
    	}
    	
    	else if(PC->imm=='1'){
    		if(PC->src2[0]=='0'){
    			PCbis->val2 = strdup(completerBin(PC->src2, 32));
    		} else if(PC->src2[0]=='1'){
    			PCbis->val2 = strdup(completerBinUn(PC->src2, 32));
    		}
    	}
    	
    	
    	saut = executer(PCbis, &PC, All, RegistresEtat, Registres, &currentPC, retenue, Memoire); // simulation du programme que l'on a traduit

		if(saut == 0){
			PC = All[++currentPC];
		}
		Registres[0] = decToBin(0, 32); // Le registre 0 est toujours egal 0
        }
    printf("Fin du programme \n");
	
	return 0;
}
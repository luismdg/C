# include <string.h>
# include <stdio.h>
# include <conio.h>
# include <fstream>

using namespace std;

class Archivo {
	public:
		char id[10], nom[16], ap[16], am[16];
		int cal;	
	public:
		Archivo(char p_id[10],char p_nom[16], char p_ap[16], char p_am[16],int p_cal){
			strcpy(id,p_id);
			strcpy(nom,p_nom);
			strcpy(ap,p_ap);
			strcpy(am,p_am);
			cal=p_cal;
		}
		
		Archivo(){
		
		}
		
		void graba(){
			ofstream arch;
			arch.open("ProyectoFinal.csv", ios::app);
			arch <<id<<","<<nom<<","<<ap<<","<<am<<","<<cal<<"\n";
			arch.close();	
		}
		
	void busca_rec(char *buf, char id[10]){
		bool existe;
		ifstream arch;
		arch.open("ProyectoFinal.csv",ios::in);
		existe=false;
		while (!arch.eof()){
			arch>>buf;
			if (strnicmp(buf,id,9)==0){
				existe=true;
				break;
			}
		}
		if (!existe) strcpy(buf,"XXX");
	}
	
	void listado(){
		char cad[100], *token, id[10], nom[16], ap[16], am[16], cal[4];
		for (int i=0;i<=40;i++) printf("\n");
		printf("Matricula Nombre 	  Ap. Paterno 	  Ap. Materno 	  Calificacion\n");
		printf("----------------------------------------------------------------------\n");
			//	123457890 123456789012345 123456789012345 123456789012345 1234
		ifstream arch;
		arch.open("ProyectoFinal.csv",ios::in);
		while (!arch.eof()){
			arch >>cad;
			if (!arch.eof()){
				token=strtok(cad,","); strcpy(id,token);
				token=strtok(NULL,","); strcpy(nom,token);
				token=strtok(NULL,","); strcpy(ap,token);
				token=strtok(NULL,","); strcpy(am,token);
				token=strtok(NULL,","); strcpy(cal,token);
				printf("%s ",id);
				for (int i=0;i<strlen(nom);i++) if (nom[i]=='_') nom[i]=' ';
				printf("%-15s ",nom);
				printf("%-15s ",ap);
				printf("%-15s ",am);
				printf("%s\n",cal);
			}
		}
		arch.close();
		getche();
	}	
};

void alta(){
	char cad[100], id[10], nom[16], ap[16], am[16];
	int cal;
	for(int i=0; i<=40; i++) printf("\n");
	while (true){
		printf("ID del alumno	: \n"); gets(id);
		strupr(id);
		if ((strlen(id)!=9) || (id[0]!='A') || (id[1]!='0')){
			printf("Usa el formato A01122334 \n \n");	
		}
		else{
			Archivo obj;
			obj.busca_rec(cad, id);
			
    		if (strcmp(cad, "XXX")!=0) {
       			printf("Matricula ya existente \n");
  			}
			else break;
    	}
	}
	
	
	while(true){
		printf("Nombre del alumno	: \n"); gets(nom);
		if ((strlen(nom)<1) || (strlen(nom)>15) || (!isupper(nom[0]))) {
			printf("Usa el formato correcto: Luis \n");
		}
		else break;
	}
	for(int i=0; i<=40; i++) printf("\n");
	while(true){
		printf("Ap. Paterno del alumno	: \n"); gets(ap);
		if ((strlen(ap)<1) || (strlen(ap)>15) || (!isupper(ap[0]))) {
			printf("Usa el formato correcto: Lopez \n");
		}
		else break;
	}
	for(int i=0; i<=40; i++) printf("\n");
	while(true){
		printf("Ap. Materno del alumno	: \n"); gets(am);
		if ((strlen(am)<1) || (strlen(am)>15) || (!isupper(am[0]))) {
			printf("Usa el formato correcto: Lopez \n");
		}
		else break;
	}
	for(int i=0; i<=40; i++) printf("\n");
	while(true){
		printf("Calificacion del alumno	: \n"); scanf("%d", &cal);
		if ((cal<0) || (cal>100)) {
			printf("Formato -/100 \n");
		}
		else break;
	}
	
	for (int i=0;i<strlen(nom);i++) if (nom[i]==' ') nom[i]='_';
	for (int i=0;i<strlen(ap);i++) if (ap[i]==' ') ap[i]='_';
	for (int i=0;i<strlen(am);i++) if (am[i]==' ') am[i]='_';
	Archivo obj(id,nom,ap,am,cal);
	obj.graba();
}

void consulta(){
	char cad[100], id[10];
	char *token, nom[16], ap[16], am[16], cal[4];
	
	printf("Ingresa la matricula a consultar : "); gets(id);
	Archivo obj;
	obj.busca_rec(cad,id);
	if(strcmp(cad,"XXX")==0){
		printf("Matricula no existente \n");
		getche();
	}
	else{
		token=strtok(cad,",");
		token=strtok(NULL,","); strcpy(nom,token);
		token=strtok(NULL,","); strcpy(ap,token);
		token=strtok(NULL,","); strcpy(am,token);
		token=strtok(NULL,","); strcpy(cal,token);
		for (int i=0;i<strlen(nom);i++) if (nom[i]=='_') nom[i]=' ';
		printf("Nombre 	= %s\n",nom);
		printf("Ap. Paterno = %s\n",ap);
		printf("Ap. Paterno = %s\n",am);
		printf("Calificacion= %s\n",cal);
		getche();
	}
}


void menu(){
	int op;
	char falso[2];
	while (op!=4){
		for(int i=0; i<=40; i++) printf("\n");
		printf("1) Alta de matriculas \n");
		printf("2) Consulta de matriculas \n");
		printf("3) Lista de alumnos \n");
		printf("4) Fin del proceso \n \n \n");
		printf("Opcion a elegir 	 :\n"); scanf("%d", &op); gets(falso);
		if (op==1) alta();
		if (op==2) consulta();
		if (op==3){
		Archivo obj;
		obj.listado();
		}
	}			
}

main(){
	menu();
}

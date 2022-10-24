#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <string.h >

using namespace std;

const char *archivo2 = "palabras.dat";


struct Palabras{
	char nuevas[20];
	char espanol[20];
	char descripcion[300];
};

struct Traducir{
	char letras[500];
	
	
	
};

void abrir();
void nueva();
void cambiar();
void traduccion();
void borrar();


// MODIFICAR LINEA 75

// ERROR EN 268

int main(){
	
	
	// MENU PRINCIPAL
    int elegir;
    
        system("cls");        
        
        cout<<""<<endl<<endl;
        cout << "\033[1;32m                                                        MENU PRINCIPAL \033[0m\n"<< endl;
        cout << "                  1) Ver Lista de Palabras" << endl;
        cout << "                  2) Ingresar Palabra" << endl;
        cout << "                  3) Actualizar Palabra" << endl;
        cout << "                  4) Traducirir Codigo" << endl;
        cout << "                  \033[1;31m5) Eliminar \033[0m\n";
        cout << "                  6) Salir" << endl;
        
        cout << "\n                  Ingrese una opcion: ";
        cin >> elegir;

        switch (elegir) {
            case 1:
                
                system("cls");
                abrir();
                break;
                
            case 2:
                
                system("cls");
                nueva();
                break;
                
            case 3:
                
                system("cls");
				cambiar();  
                break;
                
            case 4:
                
                system("cls");
				traduccion();  
                break;
			    
            case 5:
                
                system("cls");
				borrar();    
                break;
                
            case 6:
                
                system("cls");
				return 0;
				   
        }     
           
    return 0;
}

// ABRIR EL ARCHIVO DE LAS PALABRAS

void abrir(){
	system("cls");
	FILE* archivo = fopen(archivo2, "rb");
	if(!archivo) {
		archivo = fopen(archivo2, "w+b");
	}
	Palabras palabras;
	int grabar=1;
	fread ( &palabras, sizeof(Palabras), 1, archivo );
	do{
	
	//cout << "\033[1;32m a \033[0m\n";
	
	cout<<"___________________________________________"<<endl<<endl;
	cout<<"  No."<<"  Palabra espanol   "<<"Traducircion   "<<endl;
	cout<<"___________________________________________"<<endl;
	cout<<""<<endl;
	cout<<"   "<<grabar<<"   "<<palabras.nuevas<<"              "<<palabras.espanol<<endl<<endl;
	cout<<"              Descripcion"<<endl<<endl;
	cout<<palabras.descripcion<<endl<<endl;
	
	fread ( &palabras, sizeof(Palabras), 1, archivo );
		grabar += 1;	
		} while (feof( archivo ) == 0);
		
    cout<<endl;    
	fclose(archivo);
	
	_getch();
	main();
}

// AGREGAR OTRAS PALABRAS

void nueva(){
	
	char continuar;
	FILE* archivo = fopen(archivo2, "ab");
	if(!archivo) {
		archivo = fopen(archivo2, "w+b");
	}
	
		Palabras palabras;
		string nuevas,espanol,descripcion;
		system("cls");
		
		do{
			fflush(stdin);
			
		cout<<"Ingrese palabra en ingles: ";
		getline(cin,nuevas);
        strcpy(palabras.nuevas, nuevas.c_str());
        cout<<""<<endl<<endl;
        
		cout<<"Ingrese palabra en espanol: ";
		getline(cin,espanol);
    	strcpy(palabras.espanol, espanol.c_str()); 
    	cout<<""<<endl<<endl;
    	
		cout<<"Ingrese definicion: ";
		getline(cin,descripcion);
    	strcpy(palabras.descripcion, descripcion.c_str()); 
		cout<<""<<endl<<endl;
		
		fwrite( &palabras, sizeof(Palabras), 1, archivo );
		
		cout<<"Desea agregar otra palabra (s/n): ";
		cin>>continuar;
		}
		while((continuar=='s') || (continuar=='S'));
		
		
		fclose(archivo);
		
	_getch();
	main();
}

// MODIFICA LAS PALABRAS

void cambiar(){
	system("cls");
	
	FILE* archivo = fopen(archivo2, "r+b");
	int id;
		
    	Palabras palabras;
		string nuevas,espanol,descripcion;
    	
    	cout << "Ingrese el \033[1;31mid\033[0m que desea Modificar: ";
    	cin >> id;
    	id=id-1;
    	fseek ( archivo, id * sizeof(Palabras), SEEK_SET );
    	cout<<""<<endl;
		
		
		getline(cin,nuevas);
        strcpy(palabras.nuevas, nuevas.c_str());
        cout<<""<<endl;
		
		cout<<"Ingrese palabra en ingles: ";
		getline(cin,nuevas);
        strcpy(palabras.nuevas, nuevas.c_str());
        cout<<""<<endl<<endl;
        
		cout<<"Ingrese palabra en espanol: ";
		getline(cin,espanol);
    	strcpy(palabras.espanol, espanol.c_str());
		cout<<""<<endl<<endl; 
    	
		cout<<"Ingrese definicion: ";
		getline(cin,descripcion);
    	strcpy(palabras.descripcion, descripcion.c_str());
    	cout<<""<<endl<<endl;
    	
    	fwrite( &palabras, sizeof(Palabras), 1, archivo );
		fclose(archivo);
		
	_getch();
	main();	
}

void traducir(string& listapal, string buscar,string rempl){
	int pos= listapal.find(buscar);
	while (pos != -1){
		listapal.replace(pos,buscar.size(),rempl);
		pos = listapal.find(buscar, pos + rempl.size());
	}
}

// TRADUCIR EL CODIGO

void traduccion(){
	system("cls");
	
	FILE* archivo = fopen(archivo2, "rb");
	string listapal;
	Palabras palabras;
	cout<<"Por favor ingrese el codigo para traducir"<<endl<<endl;
	cout<<"Para terminar ingrese punto y coma '\033[1;31m;\033[0m' "<<endl<<endl;
	getline(cin,listapal,';');
	
	fread(&palabras,sizeof(Palabras),1,archivo);	
	do{
		
		traducir(listapal, palabras.nuevas, palabras.espanol);
		fread ( &palabras, sizeof(Palabras), 1, archivo );
	} while (feof( archivo ) == 0);
	cout<<"\n\nTraduccion del codigo: "<<endl;
	
	
	cout<<listapal<<endl;
	fclose(archivo);
	
	_getch();
	main();
}


// BORRAR LAS PALABRAS

void borrar(){
	system("cls");
	
	const char *nombre_temp = "temp.dat";
	int aux=0;
	char borrar[20];
	
	Palabras palabras;

	FILE* archivo = fopen(archivo2, "rb");
	FILE* temp = fopen(nombre_temp, "wb");
	cout<<"ingrese la \033[1;31mpalabra en ingles\033[0m que desea borrar: ";
	cin>>borrar;
	
	while (fread(&palabras,sizeof(Palabras),1,archivo) != NULL) {
		if (strcmp (borrar, palabras.nuevas) == 0) {
			cout<<""<<endl;
			cout<<"\033[1;31mPalabra eliminada\033[0m\n"<<endl;
			aux=1;
		} else {
			fwrite(&palabras, sizeof(Palabras), 1, temp);
		}
	}

	fclose(archivo);
	fclose(temp);

	remove("palabras.dat");
	rename("temp.dat", "palabras.dat");
	 
	
	_getch();
	main();
}



/*
Grupo:  Francisco Muñoz
        Jorge Valdivia
Ramo: Sistemas Operativos
Fecha: 21-04-22
*/

//Libreria para entrada de teclado
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Librerias para la llamada al sistema read()
#include <fcntl.h>
#include <unistd.h>
//Libreria para mkdir
#include <sys/types.h>
#include <sys/stat.h>

//Declaracion de funciones que contendran las llamadas al sistema.
void crearDirectorio();
void reaad();
void createNewFork();

int main(){
    //String que contendrá el comando que ingrese el usuario.
    char comando[20];
    //Ciclo do-while que finaliza cuando el usuario ingrese el comando $salir.
    do{
        //Lectura de entrada del usuario
        printf(">");
        scanf("%s",&comando);
        //Limpiamos el buffer.
        fflush(stdin);

        if(strcmp(comando, "Salir") == 0){
            printf("Saliendo...\n");
        }else if(strcmp(comando, "limpiarPantalla") == 0){
            system("clear");
        }else if(strcmp(comando, "listDir") == 0){
            system("ls -l");
        }else if(strcmp(comando, "crearDirectorio") == 0){
            crearDirectorio();
        }else if(strcmp(comando, "leerArchivo") == 0){
            reaad();
        }else if(strcmp(comando, "crearFork") == 0){
            createNewFork();
        }else if(strcmp(comando, "verificarFork") == 0){
            system("ps -fe");
        }else{
            printf("Comando no reconocido por la bash.\n");
        }
        
    }while(strcmp(comando,"Salir"));
    //fin de la ejecucion de la bash.
    return 0;
}

void crearDirectorio(){
    //Nos servira para verificar si el directorio esta creado o no.
    int verificarCreado;
    //String que contendra el nombre del directorio
    char dir[30];

    printf("Ingrese el nombre del directorio (Máx 30 caracteres) \n");
    printf(">");
    scanf("%s",&dir);
    //Limpiar Buffer
    fflush(stdin);

    verificarCreado = mkdir(dir,0777);

    //Verificamos si el directorio pudo ser creado o no
    if(!verificarCreado){
        printf("Directorio creado :) \n");
    }else{
        printf("No se ha podido crear el directorio (DIRECTORIO YA EXISTE) \n");
        exit(1);
    }
}
//funcion para llamada al sistema read()
void reaad(){
    //Variable para ver si el directorio a seleccionar existe o no
    int directorioCheck;
    char buffer[50];
    ssize_t numBytes;
    //string que contendra el nombre o ruta del archivo a leer
    char rutaArchivo[100];

    printf("Ingrese la ruta o el nombre del archivo\n");
    scanf("%s",&rutaArchivo);

    directorioCheck = open(rutaArchivo, O_RDONLY);

    //Verificacion si el archivo esta creado, vacio o un error al abrirlo
    if(!directorioCheck){
        printf("ERROR AL ABRIR ARCHIVO\n");
    }else{
        //llamada al sistema read()
        numBytes = read(directorioCheck,buffer,20);
        close(directorioCheck);
        if(numBytes == 0){
            printf("El archivo se encuentra vacio\n");
        }else{
            printf("El numero de caracteres es %zd y el contenido es %s \n",numBytes,buffer);
        }
    }
}

void createNewFork(){
    int pid;
    pid = fork();

    switch(pid){
        case 0 :
            printf("Proceso hijo %d padre %d\n",getpid(), getppid());
            while(1);
        break;
        case 1 :
            printf("Proceso padre %d padre del proceso: %d \n",getpid(),getppid());
        break;
        default:
            printf("ERROR(1) \n");
            exit(1);
        break;
    }
}
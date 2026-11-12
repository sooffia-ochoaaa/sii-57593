#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "DatosMemCOmpartida.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc,char* argv[])
{
	int i;
	DatosMemCOmpartida* dat;
	char *direccion;
	int fd;
	
	fd=open("fichero_memoria",O_RDWR);
	if (fd == -1)
	{
		perror("Error al abrir el archivo"); 
		return 1;
	}
	direccion= (char*)mmap(NULL, sizeof(DatosMemCOmpartida), PROT_READ | PROT_WRITE, MAP_SHARED, fd,0);
	if (direccion == MAP_FAILED)
	{
		perror("Error en la proyeccion mmap"); 
		close(fd);
		return 1;
	}
	close(fd);
	dat=(DatosMemCOmpartida*)direccion;

	while(1)
	{
		usleep(25000);
		// X3 Completar la lógica
		// dat->jugador, por ejemplo, accede al identificador del jugador
		float raquetaY=(dat->raqueta1.y1 +dat->raqueta1.y2)/2.0f;
		if (dat->esfera.centro.y > raquetaY){
		dat->accion=1; //Arriba
		} 
		else if (dat->esfera.centro.y < raquetaY)
		{
		dat->accion=-1; //Abajo
		}
		else {
		dat->accion=0; //Nada
		}
	}
	return 0;
}

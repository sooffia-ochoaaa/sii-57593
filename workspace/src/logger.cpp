#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int main(int argc, char **argv) {
    int fd;
    char buffer[1024];

    // borrar FIFO por si existiera previamente
    unlink("/tmp/tenis_fifo");

    /* crear el FIFO */
    if (mkfifo("/tmp/tenis_fifo", 0666)<0) {
        perror("No puede crearse el FIFO");
        return(1);
    }
    /* Abrir el FIFO */
    if (fd=open("/tmp/tenis_fifo", O_RDONLY)<0) {
        perror("No puede abrirse el FIFO");
        return(1);
    }
    /* Leer de la FIFO */
    while (1) {//Este es el bucle infinito
	// X5: Imprimir el texto en la pantalla
	int bytes_leidos=read(fd, buffer, sizeof(buffer)-1);

	if (bytes_leidos>0){
		buffer[bytes_leidos]='\0';//indica donde termina el texto leido
		printf("%s",buffer);//esto es lo que imprime por pantalla
		}
	else if(bytes_leidos==0){
		break;
		}
	else{
		perror("Error al leer");
		break;
		}
		}

   
    close(fd);
    unlink("/tmp/tenis_fifo");
    return(0);
}

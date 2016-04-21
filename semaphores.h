/*

*/

#ifndef SEMAPHORE_H
#define SEMAPHORE_H

/*Estructura para el control de semanforos*/
struct semaphore_p
{
  int cant[3]; //Cantidad de elementos que cuenta este semaforo(Semaforo de conteo)
              //total-restante-consumido
  struct pcbCtrl_p *blocked; //Elementos en cola(bloqueados) esperando para ocupar el recurso
};

#endif

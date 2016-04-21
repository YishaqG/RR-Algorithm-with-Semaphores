/*

*/

#ifndef CRITIC_ZONES_H
#define CRITIC_ZONES_H

/*Estructura para control de zonas criticas*/
struct cz_p
{
  int start; //Tiempo en donde incia la zona crítica
  int end; //Tiempo donde finaliza la zona crítica
  int dif; //Dado por la diferencía entre fin e inicio
  int numResource; //Esta variable sirve para saber si el proceso esta en el recurso o no
  struct resource_p *resource; //Rercurso asignado
};

#endif

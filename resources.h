/*


*/

#ifndef RESOURCES_H
#define RESOURCES_H

//Estructura para el manejo de los recursos.
struct resources_p
{
  char n[TAM_BUFF]; //Nombre del recurso.
  int id; // Id del recurso.
  semaphore_p sem; //Número de recursos.
  struct resourcesMov_p *resourSense;//
};

struct resourcesMov_p
{
  struct resource_p *prev;
  struct resource_p *next;
}

struct resourcesCtrl_p
{
  struct resources_p *front;
  struct resources_p *rear;
}

#endif

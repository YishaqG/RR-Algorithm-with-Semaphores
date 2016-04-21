/*


*/

#ifndef RESOURCES_H
#define RESOURCES_H

//Estructura para el manejo de los recursos.
struct resources_p
{
  char n[TAM_BUFF]; //Nombre del recurso.
  int id; // Id del recurso.
  struct semaphore_p *sem; //Controlador de recursos.
  struct resourcesMov_p *resourSense;//
};

struct resourcesMov_p
{
  struct resources_p *prev;
  struct resources_p *next;
};

struct resourcesCtrl_p
{
  struct resources_p *front;
  struct resources_p *rear;
};

#endif

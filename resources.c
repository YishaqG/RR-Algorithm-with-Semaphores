/*

*/
resources* create_resourse_mem();
int repeat_resource(resources *front,char *name);
int check_resource(resources *front,char*name);
int next_resource(resources **aux,resources *f);//Para desplazarse.
int prev_resource(resources **aux,resources *r);
void create_resource(resourcesCtrl *ctrlR); //Crea un recurso.
void add_resource(resourcesCtrl *ctrlR);//Aumenta el numero de instancias disponibles de un recurso.
resources* show_resources(resourcesCtrl *ctrlR); //Muestra los recursos.
resources* find_resource(char* opc); //Busca el nombre del recurso a imprimir
void delete_resource(resourcesCtrl *ctrlR); //Elimina un recurso.

void show_Tresources(resources *front);  //Muestra las instancias totales por tipo.
void show_Sresources(resources *front);  //Muestra las instancias disponibles por tipo.

resources* create_resourse_mem()
{
  resources *temp;
  temp = (resources *)malloc(sizeof(resources));

  temp = (semaphore *)malloc(sizeof(semaphore));
  temp->sem->blocked =(pcbCtl *)malloc(sizeof(pcbCtrl));
  temp->sem->blocked->front = NULL;
  temp->sem->blocked->rear = NULL;
  temp->resourSense->next = NULL;
  temp->resourSense->rear = NULL;
  temp->id = -1;
  strcpy(temp->n," ");

  return temp;
}

/*0_Sig_resource*/
int next_resource(resources **aux,resources *f)
{
  int b = 0;
  if(((**aux).resourSense->next != NULL) || (**aux).resourSense->next != f))
    *aux = (**aux).resourSense->next; //Desplazamiento al siguiente elemento
  else
    b = ERROR;

  return b;
}
/*1_Sig_recurso*/

/*0_prev_resource*/
int prev_resource(resources **aux,resources *r)
{
  int b = 0;
  if(((**aux).resourSense->prev != NULL) || (**aux).resourSense->prev != r))
    *aux = (**aux).resourSense->prev; //Desplazamiento al siguiente elemento
  else
    b = ERROR;

  return b;
}
/*1_prev_recurso*/

/*Evalua si el id de un usuario ha sido repetido y de ser
asi pregunta por otro o cancela la creacion del proceso*/
int set_idR(resources *front)
{
  int idR,flag = 0;
  resources *f = front;
  if(front == NULL)
    idR = set_int("el id del nuevo recurso",0);
  else
  {
    idR = set_int("el id del nuevo usuario",0);
    do
    {
      if(idR == f->idR)
      {
        flag = FAIL;
        break;
      }
    }while(next_resource(&f,front) != FAIL);
    if(flag == FAIL)
    {
      printf("%s\n",REP_FAIL);
      if(cancel("creacion del recurso") == 0)
        idR = set_idR(front);
      else
        idR = FAIL;
    }
  }

  return idR;
}
/**/

int repeat_resource(resources *front,char *name)
{
  int flag = 0;
  resources *f = front;
  if(front != NULL)
  {
    do
    {
      if(strcmp(f->n,name) == 0)
      {
        flag = FAIL;
        break;
      }
    }while(next_resource(&f,front) != FAIL);
  }

  return flag;
}

int check_resource(resources *front,char*name)
{
  int flag = 0;
  do
  {
    if(set_name(name,"recurso") >= 0)
    {
      if(repeat_resource(front,name) == 0)
        break;
      else
      {
        printf("%s\n",REP_FAIL);
        printf("Si desea añadir una instancia a un
        recurso existente, porfavor vaya al menu
        principal\n", );
        if(cancel("creacion del recurso") == 0)
        {
          check_resource(front,name);
          break;
        }
        else
        {
          flag = FAIL;
          break;
        }
      }
    }
    else
    {
      flag = FAIL;
      break;
    }
  }while(1);

  return flag;
}

//*_0 Crear recurso
void create_resource(resourcesCtrl *ctrlR)
{
  int id;
  char *name = create_string_mem(TAM_BUFF); //Variable temporal para validar longitud del nombre
  int nSem; //Variable temporal para validar el num de recursos del tipo.

  if((id = set_idR(ctrlR->front)) > 0)
  {
    if(check_resource(name,"recurso") == 0)
    {
      if(((nsem = set_int("el numero de %s disponibles",name)) > 0) || (nSem <= TAM_REC))
      {
        if(ctrlR->front == NULL)
        {
          ctrlR->front = create_resourse_mem();
          if(ctrlR->front != NULL)
          {
            ctrlR->front->id = idR;
            strcpy(ctrlR->front->n, name); //Asignación del nombre del nuevo recurso
            //Al principio son iguales los recursos libres y totales, siendo los ocupados 0.
            ctrlR->front->sem.cant[0] = nSem;
            ctrlR->front->sem.cant[1] = nSem;
            ctrlR->front->sem.cant[2] = 0;
            free(name);
          }
          else printf("%s",MEM_FAIL);
        }
        else
        {
          ctrlR->rear->resourSense->next = create_resourse_mem();
          if(ctrlR->rear->resourSense->next != NULL)
          {
            ctrlR->rear->resourSense->next->resourSense->prev = ctrlR->rear; //?
            ctrlR->rear = ctrlR->rear->resourSense->next;

            strcpy(ctrlR->rear->n, name);
            ctrlR->rear->idR = idR;

            ctrlR->rear->resourSense->next = ctrlR->front;
            ctrlR->front->resourSense->prev = ctrlR->rear;
            free(name);
          }
          else printf("%s",MEM_FAIL);
        }
      }
    }
  }

}
//*_1 Crear recurso

//*_0 Agregar recurso
void add_resource(resourcesCtrl *ctrlR)
{
  if(ctrlR->front != NULL)
  {
    int id;
    resources *aux;
    printf("%s para elegir un recurso.\n",SELEC);
    show_resources(ctrlR);
    scanf("%i",&id);
    getchar();

    aux = find_resource(id,ctrlR);
    if(aux != NULL)
    {
      a->sem.cant[0]++;
      b->sem.cant[1]++;
    }
    else
      printf("Error, no se ha podido aumentar las instancias de %s\n",aux->n);
  }
  printf("No se han creado recursos.\n");
}
//*_1 Agregar recurso

/*1_show_recurso
Esta funcion no recibe nada como parametro, retorna el id del recurso seleccionado.
Su funcion es mostrar la informacion de los recursos, y leer el id seleccionado*/
void show_resources(resourcesCtrl *ctrlR)
{
  resources *f;
  if(ctrlR->front != NULL)
  {
    f = ctrlR->front;

  printf("\t\t\tRECURSOS EXISTENTES\n");
    printf("|%7s|%15s|%8s|%11s|%8s|\n","ID","Descripcion","Totales","Disponibles","Ocupados");
    printf("=========================\n");
    do
    {
      printf("|(%5i)|%15s|%8i|%11i|%8i|\n",
      f->id,f->n,f->sem[0],f->sem[1],f->sem[2]);
    }while(next_resource(&f,ctrlR->front) != FAIL);
    printf("\n");
  }
  else
    printf("No se han creado recursos.\n");
}
/*0_show_recurso*/

/*0_Recorrido para buscar un recurso por id*/
resources* find_resource(int id, resources *front)
{
  resources *chosen,*aux = front;
  chosen = NULL;
  do
  {
    if(id == aux->id)
    {
      chosen = aux;
      break;
    }
  }while(next_resource(&aux,front) != FAIL);
  return chosen;
}
/*0_*/

/*0_eliminar_recurso*/
void delete_resource(resourcesCtrl *ctrlR)
{
  int op, id_res;
  printf("%s\n el recurso que desea elegir:\n", SELEC);
  show_resources();
  scanf("%i", &id_res);
  resources *x = find_resource(id_res, ctrlR->front);
  if(x != NULL){
    printf("Elija una opcion para continuar:\n");
    printf("\t(1) Disminuir instancias de recurso.\n");
    printf("\t(2) Eliminar recurso e instancias.\n");
    scanf("%i",&op);
    getchar();
    switch(op){
      case 1:
        if( (x->sem.cant[2] == 0 )
        {
          x->sem.cant[0]--;
          x->sem.cant[1]--;
        }
        else
          printf("Hay %d instancias de %s ocupadas, imposible eliminar resource.\n",x->sem.cant[2],x->n);
        break;
      case 2:
        if(x->sem.cant[2] == 0)
        {
          if(ctrlR->front == ctrlR->rear)
            ctrlR->rear = ctrlR->front = NULL;
          else
            if(ctrlR->front == x)
            {
              ctrlR->front = ctrlR->front->resourSense->next;
              ctrlR->front->resourSense->prev = ctrlR->rear;
            }
            else
              if(ctrlR->rear == x)
              {
                ctrlR->rear = ctrlR->rear->resourSense->prev;
                ctrlR->front->resourSense->prev = ctrlR->rear;
              }
              else
              {
                x->resourSense->next->resourSense->prev = x->resourSense->prev;
                x->resourSense->prev->resourSense->next = x->resourSense->next;
              }

          free(x);
        }
        else
          printf("Hay %d instancias de %s ocupadas, imposible eliminar recurso.\n",x->sem.cant[2], x->n);
        break;
      default:
        puts(FIND_FAIL);
        printf("\n");
    }
  }
  else{
    puts(FIND_FAIL);
    printf("\n");
  }
}
/*1_eliminar_recurso*/

int set_resource(resourcesCtrl *ctrlR,pcb **aux)
{
  int id,flag = 0;
  do
  {
    printf("%s el recurso que se desea utilizar.\n",SELEC);
    show_resources(ctrlR);
    printf(">");
    scanf("%i",&id);
    getchar();
    *aux->critic_zones[i].resource = find_resource(id,ctrlR->front);
    if(aux->critic_zones[i].resource != NULL)
      break;
    else
    {
      printf("%s\n",FIND_FAIL);
      if(cancel("creacion del proceso") == 1)
      {
        flag = FAIL;
        break;
      }
      else
        flag = set_resource(ctrlR,*aux);
    }
  }while(1);
}

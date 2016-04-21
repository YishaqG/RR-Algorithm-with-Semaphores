/*

*/
int val_res(semaphore *aux);
void block_pcss(semaphore *aux, pcb *elm);
void up(semaphore *elm);
int down(semaphore *elm, pcb*aux);


/*1_solic_rec
Esta función verifica si hay espacio para que el proceso disponga
del recurso y sea ejecutado.*/
int val_res(semaphore *aux)
{
  int ban;
  if(aux->cant[1] == 0)
  {
    printf("Error al intentar acceder al recurso.\n");
    printf("Recursos agotados.\n");
    ban = FAIL;
  }
  else
    ban = aux->cant[1];

  aux = NULL;

  return ban;
}
/*0_solic_rec*/

/*1_add_pcsSQ
Esta función agrega un elemento a la lista ade bloqueados del semaphore
void block_pcss(semaphore *aux, pcb *elm)
{
  /*1_Refront variables*/
  //elm->state->front = NULL;
//  elm->state->prev = NULL;
  /*0_Refront variables*/
/*
  if(aux->blocked->front == NULL) //Formando
    aux->blocked->rear = aux->blocked->front = elm;
  else
  {
      aux->blocked->rear->state->next = elm; //Elemento anterior
      aux->blocked->rear = aux->blocked->rear->state->next;  //Elemento siguiete
  }

  aux = NULL;
  elm = NULL;
}
/*0_add_pcsSQ*/

/*1_inc_sem*/
void up(semaphore *elm)
{
  if(elm->blocked != NULL)
  {
    asig_EjecList(elm->blocked->front);
    if(elm->blocked->front->semSense->next != NULL)
      elm->blocked->front = elm->blocked->front->semSense->next;
    else
      elm->blocked->front = NULL;
  }
  else
  {
    elm->cant[1]++;
    elm->cant[2]--;
  }

  elm = NULL;
}
/*0_inc_sem*

/*1_dec_sem
Retorna FAIL si el proceso es bloqueado*/
int down(semaphore *elm, pcb*aux)
{
  int ban = 0;
    if(solic_rec(elm) != FAIL)
  {
    elm->cant[1]--;
    elm->cant[2]++;
    printf("Acceso al recurso concedido.\n");
  }
  else
  {
    printf("Bloqueado proceso...\n");
    add_pcsSQ(elm, aux);
    elmPcs_QLis(aux);
    printf("Proceso bloqueado.\n");
    ban = FAIL;
  }
  elm = NULL;
  aux = NULL;

  return ban;
}
/*0_dec_sem*/

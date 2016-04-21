/*

*/
int create_critic_zone(pcb *aux,resourcesCtrl *ctrlR);
int check_zc(int ncz, int i, int duration, zc *aux);
void show_zc(zc *aux, int elm);
int val_nextZC(pcb *aux);
int execute_cz(int t,pcb *readys);

int create_critic_zone(pcb *aux,resourcesCtrl *ctrlR)
{
  int nz,v,start,end,flag = 0;

  char str[45];
  if((nz = set_int("las zonas criticas del proceso",0)) > 0)
  {
    aux->nzc[0] = nz;
    aux->nzc[1] = nz;
    aux->critic_zones = (zc *) malloc(aux->nzc[0] * sizeof(zc)); //Para almacenar las zc
    if(aux->critic_zones != NULL)
    {
      for(i = 0;i < nz;)
      {
        strcpy(str,"el segundo en el que inicia la zona critica %i",i);
        if((start = set_int(str,0)) > 0)
        {
          strcpy(str,"el segundo en el que termina la zona critica %i",i);
          if((end = set_int(str,0)) > 0)
          {
            v = val_zc(aux->nzc[0],i,aux->tim->[0],aux->critic_zones)
            switch(v)
            {
              case FAIL:
                printf("Error hay zonas criticas que se traslapan o el incio y el fin son iguales.\n");
                if(cancel(CANCEL_PCSS) == 0)
                  flag = FAIL;
                else continue;
                break;
              case FATAL_FAIL:
                printf("La distribución de zonas criticas implementada, ha dejado zonas criticas sin poder ser asignadas.\n");
                if(cancel(CANCEL_PCSS) == 0)
                  flag = FAIL;
                else
                {
                  i = 0;
                  continue;
                }
                break;
              default:
                break;
            }
            if(flag == 0)
            {
              if(set_resource(ctrlR,&aux) != FAIL)
              {
                aux->critic_zones[i].wr = 0;
                aux->critic_zones[i].dif = aux->critic_zones[i].end - aux->critic_zones.start;
                i++;
              }
            }
            else break;
          }
        }

      }
    }
    else printf("%s\n",MEM_FAIL);
  }
  else
  {
    if(cancel("creacion del proceso") == 0)
      nz = create_critic_zone(*aux);
    else
      nz = FAIL;
  }
  return nz;
}


/*1_check_zc
Esta función valida las zc*/
int check_zc(int ncz, int i, int duration, zc *critic_zones)
{
  if( critic_zones[i].fin == duration ) //Verificando si el t final del elemento es igual a total.
    if(i < ncz - 1) //Verificando que no sobren zc
      i = FATAL_FAIL;  //flagdera de que sobraron zc

  if(i != FATAL_FAIL)
    if( critic_zones[i].fin <= duration ) //Verificando el t máximo
      if(critic_zones[i].front < critic_zones[i].fin) //Verificando que el front sea menor al final
        if(i > 0)  //Si hay más de una zc creada
          if( critic_zones[i - 1].front < critic_zones[i].front )
            if( critic_zones[i - 1].fin > critic_zones[i].fin )
              i = FAIL;
          else
            i = FAIL;
      else
        i = FAIL;

    return i;
}
/*0_check_zc*/

/*1_mostar_zc
Esta funcion muestra las zonas criticas creadas
Recibe el arreglo de zc y el número de zc totales*/
void show_zc(zc *aux, int elm)
{
  printf("Zonas criticas creadas:\n");
  printf("%7s | %7s | %8s |\n", "ID", "Inicia", "Finaliza");

  if(elm > 0)
  {
    int i;

    for(i = 0; i < elm; i++)
      printf("%d | %d | %d |\n", i+1 , aux[i].front, aux[i].fin);
  }
  else
    printf("%7s | %7s | %8s |\n", "-", "-", "-");
}
/*0_mostar_zc*/

int val_nextZC(pcb *aux)
{
  int flag = 0;
  if(aux->t[2] == aux->critic_zones[ aux->nzc[2] ].start)
    flag = FAIL;

  return flag;
}

int execute_cz(int t,pcb *readys)
{
    if(readys->front->critic_zones[ readys->front->nzc[2] ].dif > t)
      readys->front->critic_zones[ readys->front->nzc[2] ].dif -= t;
    else
    {
      printf("Liberando recurso...\n");
      t = readys->front->critic_zones[ readys->front->nzc[2] ].dif;
      readys->front->critic_zones[ readys->front->nzc[2] ].dif = 0;
      up( &readys->front->critic_zones[ readys->front->nzc[2] ].recurso->sem );
      readys->front->nzc[1]--;
      readys->front->nzc[2]++;
      printf("Recurso liberado.\n");
    }
  return t;
}

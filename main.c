#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define max 5

pthread_mutex_t talheres[max];

void pensar(int id);
void comer(int id);
void pegar_talher(int id);
void guardar_talher(int id);

void* filosofos_acao(void* arg){
    int id = *(int *)arg;
    
    while(1){
        pensar(id);
        pegar_talher(id);
        comer(id);
        guardar_talher(id);
    }
    
    return NULL;
}
int main()
{
    pthread_t filosofos[max];
    int ids[max];
    int i;
    
    for(i=0;i<max;i++){
        pthread_mutex_init(&talheres[i], NULL);
        ids[i] = i;
    }
    
    for(i=0;i<max;i++){
        pthread_create(&filosofos[i], NULL, filosofos_acao, &ids[i]);   
    }
    
    for(i=0;i<max;i++){
        pthread_join(filosofos[i], NULL);   
    }
    
    for(i=0;i<max;i++){
        pthread_mutex_destroy(&talheres[i]);   
    }

    return 0;
}

void pensar(int id){
    printf("o filosofo %d esta pensando. \n", id);
    int cinco = 5;
    sleep(cinco);
}

void comer(int id){
    printf("o filosofo %d esta comendo. \n", id);
    int um = 1;
    sleep(um);
}

void pegar_talher(int id){
    if(id % 2 == 0){
        pthread_mutex_lock(&talheres[id]);
        pthread_mutex_lock(&talheres[(id + 1) % max]);
    }else{
        pthread_mutex_lock(&talheres[(id + 1) % max]);
        pthread_mutex_lock(&talheres[id]);
    }
}
void guardar_talher(int id){
    pthread_mutex_unlock(&talheres[id]);
    pthread_mutex_unlock(&talheres[(id + 1) % max]);
}

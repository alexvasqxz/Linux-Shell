 //
 //  thread_Mutex.c
 //
 //  This program written in C when run on terminal
 //  creates a selling algorithm that distributes
 //  an equal amount of objects (in this case bottles)
 //  to n number of sellers who can only sell (total/n)
 //  amount of bottles in a day, the use of mutex is crucial
 //  in this algorithm when it comes to keepin track of
 //  how many objects has each seller sold
 //
 //   Created on 10/23/20
 //   Copyright © 2020 Gustavo Vasquez. All rights reserved
 //
 //     __________________________________________________
 //    / Let's sell some Milk! Don't forget to consume    \
 //    \  local and/or organic if you are not vegan <3    /
 //    /   And if you are vegan thank you <3              \
 //    ----------------------------------------------------
 //                     \   ^__^
 //                      \  (oo)\_______
 //                         (__)\       )\/\
 //                             ||----w |
 //                             ||     ||
 // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  #include <stdio.h>
  #include <stdlib.h>
  #include <pthread.h>
  #include <unistd.h>
  #include <stdint.h>
  #include <time.h>

  pthread_mutex_t mutex;
  int milkBottles = 1000;
  int sellers = 5;
  int sellerBottles[5] = {200,200,200,200,200};
  int countSeller[5] = {1,1,1,1,1};
  int num = 0;

 void *sellMilk(void *i){
     intptr_t t_id = (intptr_t) i;
     
     for (;;){

         if (milkBottles > 0 && countSeller[t_id] <= 5){
             int upper = sellerBottles[t_id];
             num = (rand() % (upper - 0 + 1));
             
             sellerBottles[t_id] -= num;
             milkBottles -= num;
             
             printf("Seller %zd just sold %d bottles. There are %d total bottles remaining\n", t_id+1, num, milkBottles);
             countSeller[t_id] += 1;
             
             pthread_mutex_unlock(&mutex);
         }
         else{
             printf("Seller %zd has no more bottles to seel today, come back tomorrow\n", t_id+1);
             pthread_mutex_unlock(&mutex);
             pthread_exit(NULL);
         }
     }
 }

 int main(void){
     pthread_mutex_init(&mutex,NULL);
     pthread_t thread[sellers];

     for (int k = 0; k < sellers; k++){
         pthread_create(&thread[k], NULL, sellMilk, (void*) (intptr_t) (k));
     }
     
     for (int j = 0; j < sellers; j++){
         pthread_join(thread[j], NULL);
     }
     
     for (int i = 0; i < sellers; i++){
         printf("Seller %d sold a total of %d\n", i+1, 200 - sellerBottles[i]);
     }
     
     printf("Total bottles reamining after today: %d. Thank You!\n", milkBottles);
 }

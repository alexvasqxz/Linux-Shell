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

 pthread_mutex_t mutex;
 int milkBottles = 30;
 int sellers = 5;
 int miniSellers = 5;
int bottles1 = 6;
int bottles2 = 6;
int bottles3 = 6;
int bottles4 = 6;
int bottles5 = 6;

 /*
 *   Calls sellmilk(), and activate/desactivate mutex whenever there is someone selling
 */
 void *threadfunc(void *i){
     intptr_t t_id = (intptr_t) i;
     
     for(;;){
         if (t_id == 1){
             pthread_mutex_lock(&mutex);
             if (bottles1 > 0){
                 milkBottles--;
                 bottles1--;
                 printf("Thread %zd SOLD! New total amount is: %d\n" ,t_id, milkBottles);
                 pthread_mutex_unlock(&mutex);
             }
             else{
                 pthread_mutex_unlock(&mutex);
                 pthread_exit(NULL);
             }
         }
         
         if (t_id == 2){
             pthread_mutex_lock(&mutex);
             if (bottles2 > 0){
                 milkBottles--;
                 bottles2--;
                 printf("Thread %zd SOLD! New total amount is: %d\n" ,t_id, milkBottles);
                 pthread_mutex_unlock(&mutex);
             }
             else{
                 pthread_mutex_unlock(&mutex);
                 pthread_exit(NULL);
             }
         }
         
         if (t_id == 3){
             pthread_mutex_lock(&mutex);
             if (bottles3 > 0){
                 milkBottles--;
                 bottles3--;
                 printf("Thread %zd SOLD! New total amount is: %d\n" ,t_id, milkBottles);
                 pthread_mutex_unlock(&mutex);
             }
             else{
                 pthread_mutex_unlock(&mutex);
                 pthread_exit(NULL);
             }
         }
         
         if (t_id == 4){
             pthread_mutex_lock(&mutex);
             if (bottles4 > 0){
                 milkBottles--;
                 bottles4--;
                 printf("Thread %zd SOLD! New total amount is: %d\n" ,t_id, milkBottles);
                 pthread_mutex_unlock(&mutex);
             }
             else{
                 pthread_mutex_unlock(&mutex);
                 pthread_exit(NULL);
             }
         }
         
         if (t_id == 5){
             pthread_mutex_lock(&mutex);
             if (bottles5 > 0){
                 milkBottles--;
                 bottles5--;
                 printf("Thread %zd SOLD! New total amount is: %d\n" ,t_id, milkBottles);
                 pthread_mutex_unlock(&mutex);
             }
             else{
                 pthread_mutex_unlock(&mutex);
                 pthread_exit(NULL);
             }
         }
     }
 }

 int main(void){
     pthread_mutex_init(&mutex, NULL);                               /* Initialize mutex with no attr, see more in man pthread_mutex_destoy */
     pthread_t thread[sellers];

     int i;
     for(i = 0; i < sellers; i++){
         pthread_create(&thread[i], NULL, threadfunc, (void *) (intptr_t) (i+1));
     }
     
     for(i = 0; i < sellers; i++){
         pthread_join(thread[i], NULL);
     }
 }



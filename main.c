
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<string.h>

     int nbr_collab;
    int y, m, d;
    time_t t;
    struct tm date;

   void initialize_time(){
    t = time(NULL);
    date = *localtime(&t);
    y = date.tm_year + 1900;
    m = date.tm_mon + 1;
    d = date.tm_mday;
}


  typedef struct {
   char nom[30];
   char prenom[30];
   char email[50];
}collaborateur;

  typedef struct{
    int annee;
    int mois;
    int jour;
}Deadline;


typedef struct {
int id;
char titre[30];
char description [100];
char status [30];
Deadline deadline;
Deadline Date_creation;
//Deadline Date_creation;
collaborateur collab[100];
}tache;

tache T[1000];
int c=0;
int s=0;
int m=0;
tache tmp;
int d,index=-1;

int date_valide(int annee, int mois, int jour) {
    if (mois < 1 || mois > 12 || jour < 1 || jour > 31) return 0;
    if (mois == 2) {
        if (annee % 4 == 0 && (annee % 100 != 0 || annee % 400 == 0)) {
            if (jour > 29) return 0;
        } else {
            if (jour > 28) return 0;
        }
    } else if (mois == 4 || mois == 6 || mois == 9 || mois == 11) {
        if (jour > 30) return 0;
    }
    return 1;
}

void ajouter_tache(){
    printf("Saisir L'ID de Tache : ");
    scanf("%d",&d);
    for(int i =0;i<c;i++){
        while(d==T[i].id){
            printf("Le ID que vous aves saisir est un ID d'une Tache existe.");
            printf("Entrer un autre ID :");
            scanf("%d",&d);
        }
    }

    T[c].id=d;
    printf("Saisir le Titre de tache : ");
    scanf("%s",T[c].titre);

    printf("Saisir la description de tache : ");
    scanf("%s",T[c].description);

       do{
        printf("Saisir la status de tache : 1- realiser. 2- en cours de realisation. 3- finaliser. ");
        scanf("%d",&s);

        if(s==1){
           strcpy(T[c].status, "realiser");
        }
        else if(s==2){
           strcpy(T[c].status, "en cours de realisation" );
        }
        else if(s==3){
            strcpy(T[c].status, "finaliser");
        }
        else{
            printf("\nle nombre que vous aves saisir est incorrect. sairir 1 ou 2 ou 3 !\n");
        }

      }while(s != 1 && s != 2 && s != 3);


      do{
            printf("enter l'annee de tach : ");
            scanf("%d",&T[c].deadline.annee);

            if(T[c].deadline.annee < 2024){
            printf("\nl'annee que vous aves saisir est incorrect.\nEntrer une annee supperieur ou egale 2024 !\n");
             }
      }while (T[c].deadline.annee < 2024);

      do{
            printf("enter le mois de tach : ");
            scanf("%d",&T[c].deadline.mois);

            if(T[c].deadline.mois < 1 || T[c].deadline.mois > 12){
            printf("\nle mois que vous aves saisir est incorrect.\nEntrer un mois entre 1 et 12 !\n");
             }
      }while (T[c].deadline.mois < 1 || T[c].deadline.mois > 12);

     do {
        printf("Entrer le jour de la tache : ");
        scanf("%d", &T[c].deadline.jour);

        if (date_valide(T[c].deadline.annee, T[c].deadline.mois, T[c].deadline.jour) == 0) {
        printf("Le jour est incorrect. entrer un jour valide.\n");
        }
    }while (date_valide(T[c].deadline.annee, T[c].deadline.mois, T[c].deadline.jour)==0);


      // Add Collaborateur
      printf("Combien de collaborateur dans cette tache\n");
      scanf("%d",&nbr_collab);
      for(int i=0;i<nbr_collab;i++){

        printf("Entrer le nom de collaborateur : %d\n",i+1);
        scanf(" %s", T[c].collab[i].nom);
        printf("Entrer le prenom de collaborateur : %d\n",i+1);
        scanf(" %s", T[c].collab[i].prenom);
        printf("Entrer l'email de collaborateur : %d\n",i+1);
        scanf(" %s", T[c].collab[i].email);

      }
    initialize_time();
    T[c].Date_creation.annee = y;
    T[c].Date_creation.mois = m;
    T[c].Date_creation.jour = d;

      c++;
}

void ajouter_multi_tache(int m){
      for(int i=0;i<m;i++){
        printf("Ajouter la Tache : %d\n", i+1);
        ajouter_tache(y,m,d);
        printf("\n");
      }
}

void affiche_une_seule_tache(int index){
       if(c>0){
        printf("\ninformation de tache %d \n", index+1);
        printf("ID de tache : %d\n", T[index].id);
        printf("Titre de tache : %s\n", T[index].titre);
        printf("La description de tache : %s\n", T[index].description);
        printf("La status de tache : %s\n", T[index].status);
        printf("Deadline de tache : %d-%d-%d \n", T[index].deadline.annee,T[index].deadline.mois,T[index].deadline.jour);
       }else{
          printf("la liste des taches est vide !\n");
       }
}

void afficher_taches(){
     for(int i =0;i<c;i++){
            affiche_une_seule_tache(i);
     }
}

void trier_alphabet(){
      for(int i=0;i<c-1;i++){
            for(int j=i+1;j<c;j++){
                 if(strcmp(T[i].titre,T[j].titre)>0){
                    tmp=T[i];
                    T[i]=T[j];
                    T[j]=tmp;
                 }
            }
      }
}
void trier_deadline(){
for(int i=0;i<c-1;i++){
            for(int j=i+1;j<c;j++){
               if(T[i].deadline.annee>T[j].deadline.annee || T[i].deadline.mois>T[j].deadline.mois || T[i].deadline.jour>T[j].deadline.jour){
                tmp=T[i];
                T[i]=T[j];
                T[j]=tmp;
               }
       }
    }
}

void afficher_deadline_3jours(){
        for(int i=0;i<c;i++){
            if(T[i].deadline.annee==y && T[i].deadline.mois == m && d<=T[i].deadline.jour<=d+3){
                printf("\ninformation de tache de deadline de 3 jours:\n");
                affiche_une_seule_tache(i);
            }
        }
}

int recherche_indice(int l){
      for(int i;i<c;i++){
        if(T[i].id==l){
        return i;
      }
  }
  printf(" Introuvable Tache !\n");
}

void recherche_id(int id_rechercher){
     affiche_une_seule_tache(recherche_indice(id_rechercher));
}

void recherche_titre(char titre_rechercher[]){
     for(int i=0;i<c;i++){
            if(strcmp(T[i].id,titre_rechercher)==0){
                 affiche_une_seule_tache(i);
                 printf("/n");
               }
     }
}

void modifier_description(int id,char new_description[]){
         strcpy(T[recherche_indice(id)].description,new_description);
}

void modifier_status(int id, char new_status){
        strcpy(T[recherche_indice(id)].status,new_status);
}

void modifier_deadline(int x,int new_y, int new_m, int new_d){
       T[recherche_indice(x)].deadline.annee=new_y;
       T[recherche_indice(x)].deadline.mois=new_m;
       T[recherche_indice(x)].deadline.jour=new_d;
}

void supprimer_tache(int id){
   for(int i=recherche_indice(id);i<c;i++){
       T[recherche_indice(id)]=T[recherche_indice(id)+1];
 }
 c--;
}

 void afficher_nbr_tache(){
     if(c>0){
        printf(" le nombre total des taches est : %d\n",c);
     }
     else{
         printf(" la liste des taches est vide !\n");
     }
 }

void afficherTache_complete_incomplete(){
     int cc=0,ci=0;
     for(int i=0;i<c;i++){
        if (strcmp(T[i].status, "realiser") == 0 || strcmp(T[i].status, "en cours de realisation") == 0) {
        ci = ci + 1;
      }
        if(strcmp(T[i].status, "finaliser") == 0){
        cc = cc + 1;
        }
}
       printf("le nombre des taches incompletes est %d\n",ci);
       printf("le nombre des taches completes est %d\n",cc);
}

int est_date_bissextile(int annee) {
    return (annee % 4 == 0 && (annee % 100 != 0 || annee % 400 == 0));
}

void afficher_jours_restants(int annee_actuelle, int mois_actuel, int jour_actuel) {
    int jours_restants = 0;
    int jours_par_mois[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    for (int i = 0; i < c; i++) {

        if (est_date_bissextile(annee_actuelle)) {
            jours_par_mois[1] = 29;
        }


        if (T[i].deadline.annee == annee_actuelle) {
           if (T[i].deadline.mois == mois_actuel) {

                jours_restants = T[i].deadline.jour - jour_actuel;

            } else {

                  jours_restants += jours_par_mois[mois_actuel - 1] - jour_actuel;

                for (int mois = mois_actuel; mois < T[i].deadline.mois - 1; mois++) {
                    jours_restants += jours_par_mois[mois];
                }
                jours_restants += T[i].deadline.jour;
            }
        } else {

            jours_restants += jours_par_mois[mois_actuel - 1] - jour_actuel;


            for (int mois = mois_actuel; mois < 12; mois++) {
                jours_restants += jours_par_mois[mois];
            }


            if (T[i].deadline.annee == annee_actuelle + 1) {

                if (est_date_bissextile(T[i].deadline.annee)) {
                    jours_par_mois[1] = 29;
                }

                for (int mois = 0; mois < T[i].deadline.mois - 1; mois++) {
                    jours_restants += jours_par_mois[mois];
                }
                jours_restants += T[i].deadline.jour;

            } else {

                for (int annee = annee_actuelle + 1; annee < T[i].deadline.annee; annee++) {
                    if (est_date_bissextile(annee)) {
                        jours_restants += 366;
                    } else {
                        jours_restants += 365;
                    }
                }

                if (est_date_bissextile(T[i].deadline.annee)) {
                    jours_par_mois[1] = 29;
                }

                for (int mois = 0; mois < T[i].deadline.mois - 1; mois++) {
                    jours_restants += jours_par_mois[mois];
                }
                jours_restants += T[i].deadline.jour;
            }
        }

        printf("Le nombre de jours restants pour la tache %d est : %d\n", T[i].id, jours_restants);
    }
}

void affiche_collaborateur_finaliser(){
    for(int i = 0; i < c; i++){
        printf("Tache %d\n", i + 1);
        for (int j = 0; j < nbr_collab; j++){
            if(strcmp(T[i].status,"finaliser")==0) {
                printf("Collaborateur Finaliser %d\n", j + 1);
                printf("Nom : %s\n", T[i].collab[j].nom);
                printf("Prenom : %s\n", T[i].collab[j].prenom);
                printf("Email : %s\n", T[i].collab[j].email);
            }
        }
    }
}
// FILE **************

void sauvegarder_taches(const char* taches) {
    FILE* file = fopen(taches, "a");
    if (file == NULL) {
        printf("Erreur d ouverture du fichier.\n");
        return;
    }


    for (int i = 0; i < c; i++) {
        fprintf(file, "L'ID : %d\n", T[i].id);
        fprintf(file, "Titre de la tache : %s\n", T[i].titre);
        fprintf(file, "Description de la tache : %s\n", T[i].description);
        fprintf(file, "Statut de la tache : %s\n", T[i].status);
        fprintf(file, "Deadline de la tache : %d - %d - %d\n", T[i].deadline.annee, T[i].deadline.mois, T[i].deadline.jour);
        fprintf(file, "Date de creation de la tache : %d - %d - %d\n", T[i].Date_creation.annee, T[i].Date_creation.mois, T[i].Date_creation.jour);

        for (int j = 0; j < nbr_collab; j++) {
            fprintf(file, "Collaborateur %d :\n", j + 1);
            fprintf(file, "Nom : %s\n", T[i].collab[j].nom);
            fprintf(file, "Prenom : %s\n", T[i].collab[j].prenom);
            fprintf(file, "Email : %s\n", T[i].collab[j].email);
        }
    }

    fclose(file);
}


void supprimercmd(){
   system("pause");
   system("cls");
}
int main()
{

    int choix,ch,id,new_y,new_m,new_d,id_rechercher;
    // Currencury time

    char new_description[50],titre_rechercher[50],new_status[50];
    do {
        printf("\n===================================\n");
        printf("1-  Les Fonction D'ajoute.\n");
        printf("2-  Les Fonctions D'affichage\n");
        printf("3-  Les Focntion de Trie\n");
        printf("4-  Les Fonction de Modification\n");
        printf("5-  Fonction de Supprimer une tache par identifiant.\n");
        printf("6-  Les Fonction de Triage.\n");
        printf("7-  Les Fonctions de Triage.\n");
        printf("8-  Rechercher une tache par son Titre.\n");
        printf("0-  Quitter\n");
        printf("===================================\n");
        scanf("%d", &choix);
        switch (choix) {
        case 1 :
            printf("1-  Ajouter une seule Tache.\n");
            printf("2-  Ajouter plusieurs nouvelles taches.\n");
            scanf("%d",&ch);
            switch(ch){
            case 1 :
                  ajouter_tache();
              break;
            case 2 :
                  printf("Combien de Taches vous voulez ajouter : ");
                  scanf("%d",&m);
                  ajouter_multi_tache(m);
            break;
            }
            break;
            case 2 :
            printf("1-  Afficher Tout les Taches.\n");
            printf("2-  Afficher une seule Tache.\n");
            printf("3-  Afficher le nombre total des Taches.\n");
            printf("4-  Afficher le nombre de taches completes et incompletes.\n");
            printf("5-  Afficher les taches dont le deadline est dans 3 jours ou moins.\n");
            printf("6-  Afficher le nombre de jours restants jusqu'au delai de chaque tache.\n");
            printf("7-  Afficher les collaborateur Qui finisait les taches.\n");
            printf("8-  Afficher la date de creation.\n");
            scanf("%d",&ch);
            switch(ch){

            case 1 :
                if(c>0){
               afficher_taches();
               }else{
                printf("Aucune Tache dans la memoire !\n");
                }
            break;
            case 2 :
                printf("Entrer l'ID de la tache");
                int l ;
                scanf("%d",&l);
                affiche_une_seule_tache(recherche_indice(l));
            break;
            case 3 :
                afficher_nbr_tache();
            break;

            case 4 :
                afficherTache_complete_incomplete();
            break;

            case 5 :
                afficher_deadline_3jours();
            break;
            case 6 :
                initialize_time();
                afficher_jours_restants(y,m,d);
            break;
            case 7 :
                affiche_collaborateur_finaliser();
                break;
            case 8 :
                for(int i=0;i<c;i++){
                    printf("Date de Creation est : %d - %d - %d\n",T[i].Date_creation.annee,T[i].Date_creation.mois,T[i].Date_creation.jour);
                }
            }
             break;
            case 3 :
            printf("1- Trier les taches par deadline.\n");
            printf("2- Trier les taches par ordre alphabetique.\n");
            scanf("%d",&ch);
             switch(ch){
             case 1 :
               trier_deadline();
               break;
             case 2 :
                trier_alphabet();
                break;
             }
             break;
           case 4 :
              printf("1- Modifier la status de la tache.\n");
              printf("2- Modifier la description de la tache.\n");
              printf("3- Modifier Deadline\n");
              scanf("%d",&ch);
              switch(ch){
           case 1 :
                  printf("Entrer ID de la tache : ");
                  scanf("%d",&id);
                do{
                  printf("Saisir la status de tache : 1- realiser. 2- en cours de realisation. 3- finaliser. ");
                  scanf("%d",&s);
                if(s==1){
                  strcpy(new_status, "realiser");
                  modifier_status(id,new_status);
                 }
                else if(s==2){
                   strcpy(new_status, "en cours de realisation" );
                   modifier_status(id,new_status);
                   }
                else if(s==3){
                   strcpy(new_status, "finaliser");
                   modifier_status(id,new_status);
                   }
                  else{
                   printf("\nle nombre que vous aves saisir est incorrect. sairir 1 ou 2 ou 3 !\n");
                    }
                    }while(s != 1 && s != 2 && s != 3);
                    break;
           case 2 :
                  printf("Entrer ID de la tache : ");
                  scanf("%d",&id);
                  printf("\nEntrer la nouvelle description : ");
                  scanf("%s",new_description);
                  modifier_description(id,new_description);
                  break;
           case 3 :
                   printf("Entrer ID de la tache : ");
                   scanf("%d",&id);
                   printf("Entrer le nouvelle annee: ");
                   scanf("%d",&new_y);
                   printf("Entrer le nouveau mois : ");
                   scanf("%d",&new_m);
                   printf("Entrer le nouveau jour : ");
                   scanf("%d",&new_d);
                   modifier_deadline(id,new_y,new_m,new_d);
             }
             break;
           case 5 :
                   printf("Entrer ID de la tache : ");
                   scanf("%d",&id);
                   supprimer_tache(id);
             break;

           case 6 :
                  printf("1- Trier les taches par deadline.\n");
                  printf("2- Trier les taches par ordre alphabetique.\n");
                  scanf("%d",&ch);
                  switch(ch){
              case 1 :
                  trier_deadline();
                break;
              case 2 :
                  trier_alphabet();
                break;
                }

          case 7 :
                  printf("1- Rechercher une tache par son Identifiant.\n");
                  printf("2- Rechercher une tache par son Titre.\n");
                  scanf("%d",&ch);
                  switch(ch){
              case 1 :
                  printf("Entrer ID de la tache : ");
                  scanf("%d",&id);
                  recherche_id(id);
                  break;
              case 2 :
                   printf("Entrer le titre de la tache : ");
                   scanf("%s",titre_rechercher);
                   recherche_titre(titre_rechercher);
                   break;
                  }
                  break;
           case 0 :
               sauvegarder_taches("taches.txt");
            break;
        default :
            printf("Choix introuvable  saisir un autre choix !");
        }
        supprimercmd();
    }while(choix != 0);

    return 0;
}



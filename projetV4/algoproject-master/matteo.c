#include "projet.h"



/*
Titre : rechercheAdherent
Finalité : Recherche dans la liste Adherent l'adherent correspondant au nom et prenom
Paramètres : lAd - Liste chaînée adherent de type ListeAD
	        nom -chaîne de caractères pour le nom de l'adherent recherché
	        prenom -chaîne de caractères pour le prenom de l'adherent recherché
*/
ListeAD rechercheAdherent(ListeAD lAd,char nom[],char prenom[]){
    if(lAd==NULL)return NULL;
    if(strcmp(lAd->a.nom,nom) == 0 && strcmp(lAd->a.prenom,prenom) == 0)return lAd;
    return rechercheAdherent(lAd->suiv,nom,prenom);
}

/*
Titre : rechercheAdherentID
Finalité : Recherche dans la liste Adherent l'adherent correspondant a l'id
Paramètres : lAd - Liste chaînée adherent de type ListeAD
	        id -chaîne de caractères pour l'id de l'adherent recherché
*/
ListeAD rechercheAdherentID(ListeAD lAd,char id[]){
    if(lAd==NULL)return NULL;
    if(strcmp(lAd->a.idad,id) == 0)return lAd;
    return rechercheAdherentID(lAd->suiv,id);
}

/*
Titre : retourJeux
Finalité : Fonction qui permet la possibilité de retourner un jeux
Paramètres : tabJeux - Tableaux de pointeurs statique de jeux
	        nb -taille logique de tabJeux
            lAd -Liste chaînée des adherents
            lEmp -Liste chaînée des emprunts
            lResa -Liste chaînée des réservations
            nbEmp -nombre emprunt
*/
ListeResa retourJeux(Jeux *tabJeux[], int nb,ListeAD lAd,ListeEmp lEmp, ListeResa lResa,int *nbEmp){
    char c='n';
    char nom[20], prenom[20], jeu[20];
    int i,trouve,choixM=6;
    while(c!='o'){
        system("clear");
        AffichageMenuPrincipal();
        printf("    Votre choix : 6\n");
        printf("\n\n\tVeuillez renseigner votre nom : ");
        fgets(nom,20,stdin);
        nom[strlen(nom)-1]='\0';
        printf("\n\tVeuillez renseigner votre prénom : ");
        fgets(prenom,20,stdin);
        prenom[strlen(prenom)-1]='\0';    
        printf("\n\n    Validez vous ces informations ?");
        printf("\n\n\to/n (Oui ou Non) : ");
        scanf("%c%*c",&c);
    }

    ListeAD adRetour=rechercheAdherent(lAd,nom,prenom);
    if(adRetour==NULL){
        printf("\n\n    L'adérents %s %s n'existe pas !", nom, prenom);
        printf("\n    Veuillez vérifier l'orthographe de votre nom et prénom.\n");
    }
    else{
        printf("\n\n    Le nom du jeu que vous souhaitez rendre : ");
        fgets(jeu,20,stdin);
        jeu[strlen(jeu)-1]='\0';

        i=RechercheJeux(tabJeux,nb,jeu,&trouve);
        while(trouve==-1){
            reAffichage(nom,prenom,choixM);
            printf("\n\n    Le jeu \n%s\n n'existe pas !", jeu);
            printf("\n\n    Le nom du jeu : ");
            fgets(jeu,20,stdin);
            jeu[strlen(jeu)-1]='\0';
            i=RechercheJeux(tabJeux,nb,jeu,&trouve);
        }  

        ListeEmp emprunt=rechercheEmprunt(lEmp,tabJeux[i]->idjeux,adRetour->a.idad);

        if(emprunt==NULL)
            printf("\n\tVous n'avez pas d'emprunt pour ce jeux.\n");
        else{
            printf("\n\tVotre emprunt a été supprimé.");

            lResa=verifResa(lAd,lEmp,lResa,tabJeux,emprunt->e.idjeux,i,nbEmp);
            lEmp=suppEmprunt(lEmp,emprunt);
        }
    }
    printf("\n\n    Tapez une touche pour revenir au menu...");
    getchar();
    return lResa;
}

/*
Titre : rechercheEmprunt
Finalité : Recherche dans la liste Emprunt correspondant à l'id de jeux et à l'id adherent
Paramètres : lEmp - Liste chaînée emprunt de type ListeEmp
	        idJeux -chaîne de caractères pour l'id de jeux recherché
	        idAd -chaîne de caractères pour l'id d'adherent recherché
*/
ListeEmp rechercheEmprunt(ListeEmp lEmp,char idJeux[],char idAd[]){
    if(lEmp==NULL)return NULL;
    if(strcmp(lEmp->e.idad,idAd) ==0 && strcmp(lEmp->e.idjeux,idJeux)==0)return lEmp;
    return rechercheEmprunt(lEmp->suiv,idJeux,idAd);
}

/*
Titre : suppEmprunt
Finalité : Supprime un Emprunt de la listeEmprunt
Paramètres : lEmp - Liste chaînée des emprunts
	     emprunt -emprunt à supprimer
Variables : n -emprunt actuel
	    prec -emprunt précedent
*/
ListeEmp suppEmprunt(ListeEmp lEmp, ListeEmp emprunt){
    ListeEmp n,prec;
    if(lEmp==NULL)return NULL;
    if(lEmp==emprunt){
        n=lEmp;
        lEmp=lEmp->suiv;
        free(n);
    }else
    {
        prec=lEmp;
        n=lEmp->suiv;
        while(n != NULL){
            if(n==emprunt){
                prec->suiv=n->suiv;
                free(n);
                break;
            }
            prec=n;
            n=n->suiv;
        }
    }
    return lEmp;
}

/*
Titre : rechercheResa
Finalité : Recherche d'un réservation dans la liste de réservation grâce a l'id du jeux
Paramètres : lResa - Liste chaînée des résérvations
	        idJeux -chaîne de caractères pour l'id du jeu recherché
*/
ListeResa rechercheResa(ListeResa lResa,char idJeux[]){
    if(lResa==NULL)return NULL;
    if(strcmp(lResa->r.idjeux,idJeux)==0 )return lResa;
    return rechercheResa(lResa->suiv,idJeux);
}

/*
Titre : verifResa
Finalité : Vérifie s'il y a une réservation disponible pour un jeux
Paramètres : lAd - Liste chaînée des adhérents
	     lEmp -Liste chaînée des emprunts
         lResa -Liste chaînée des réservations
         tabJeux -Tableaux de pointeur statique des Jeux
         idJeux -Id du Jeux réservations
         i -Position du jeux dans le tableau de pointeur
         *nbEmp -Nombre emprunt
Variables : resa -Reservation trouvé
	    adResa -Adherent trouvé pour la réservation
*/
ListeResa verifResa(ListeAD lAd,ListeEmp lEmp, ListeResa lResa, Jeux *tabJeux[], char idJeux[],int i,int *nbEmp){
    ListeResa resa;
    ListeAD adResa;
    int nb;
    resa = rechercheResa(lResa,idJeux);
    if(resa!=NULL){
        adResa= rechercheAdherentID(lAd,resa->r.idad);
        printf("\n\tVous pouvez informer : %s %s que ca réservation est disponible.\n",adResa->a.nom,adResa->a.prenom);
        lResa=suppResa(lResa,resa);
        (*nbEmp)--;
             
        nb=nombreEmprunts(lAd,adResa->a.nom,adResa->a.prenom,lEmp);
        if(nb<3){ 
            lEmp=nouvelEmprunt(i,tabJeux,lAd,adResa->a.nom,adResa->a.prenom,lEmp,nbEmp);
            (*nbEmp)++;
        }
        else
            printf("\n\tMais il doit avant rendre au moins 1 jeux.\n");              
    }
    else
        printf("\n\tIl n'y a pas actuellement de réservation pour ce jeux.\n");

    return lResa;
}

/*
Titre : suppResa
Finalité : Supprime une réservation de la listeRéservation
Paramètres : lEmp - Liste chaînée des réservations
	     emprunt -Réservation a supprimer
Variables : n -Reservation actuel
	    prec -Reservation précedente
*/
ListeResa suppResa(ListeResa lEmp, ListeResa emprunt){
    ListeResa n,prec;
    /*
    n=(ListeResa)malloc(sizeof(ListeResa));
    if(n==NULL){
        printf("Problème malloc\n");
        return lEmp;
    }
    */
    if(lEmp==NULL)return NULL;
    if(lEmp==emprunt){
        n=lEmp;
        lEmp=lEmp->suiv;
        free(n);
    }else
    {
        prec=lEmp;
        n=lEmp->suiv;
        while(n != NULL){
            if(n==emprunt){
                prec->suiv=n->suiv;
                free(n);
                break;
            }
            prec=n;
            n=n->suiv;
        }
    }
    return lEmp;
}

/*
Titre : triejeux
Finalité : Trie le tableaux jeux par ordre alphabétique (les categories de jeux + les noms de jeux)
Paramètres : tabJeux - tableau de pointeurs statique de type Jeux
            nb - Taille maximale du tableau de Jeux
*/
void triejeux(Jeux *tabJeux[], int nb)
{
	for (int i = 0; i < nb; i++)
		for (int j = 0; j < nb; j++)
			if (strcmp(tabJeux[i]->typejeux, tabJeux[j]->typejeux) < 0)
			{
				echange(tabJeux,i,j);
			}

	for (int i = 0; i < nb; i++)
		for (int j = 0; j < nb; j++)
			if (strcmp(tabJeux[i]->nomjeux, tabJeux[j]->nomjeux) < 0 && strcmp(tabJeux[i]->typejeux, tabJeux[j]->typejeux) == 0)
			{
				echange(tabJeux,i,j);
			}
}

/*
Titre : echange
Finalité : Echange 2 cellule du tableau Jeux
Paramètres : tabJeux - tableau de pointeurs statique de type Jeux
            i - Position du tableau Jeux
            j - Position tableau Jeux +1
*/
void echange(Jeux *tabJeux[], int i,int j)
{
    	Jeux *modif;
	modif = tabJeux[i];
	tabJeux[i] = tabJeux[j];
	tabJeux[j] = modif;
}

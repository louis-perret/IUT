#include "projet.h"



//Partie fichier jeux//



/*
Titre : lireJeux
Finalité : Lit des éléments du fichier jeux.txt pour les insérer dans une structure Jeux puis retourne la structure
Paramètre : Le flot vers le fichier jeux.txt
Variables : j -variable de type Jeux
*/

Jeux lireJeux(FILE *flot)
{
	Jeux j;
	fscanf(flot,"%s%*c",j.idjeux);	
	fscanf(flot,"%s%*c%d%*c",j.typejeux,&j.nb);
	fgets(j.nomjeux,20,flot);
	j.nomjeux[strlen(j.nomjeux)-1]='\0';	
	return j;
}

/*
Titre : chargementJeux
Finalité : Charger en mémoire le fichier jeux.txt dans un tableau de pointeur statique puis retourne la taille logique de ce dernier
Paramètres : tabJeux - tableau de pointeur statique de type Jeux
	     nomFichier -chaîne de caractères pour le nom du fichier
	     taillemax -taille physique de tabJeux
Variables : j -structure jeux
	    i -entier retourné par la fonction
*/

int chargementJeux(Jeux *tabJeux[], char nomFichier[], int taillemax)
{
	FILE *flot;
	Jeux j;
	int i=0;
	flot=fopen(nomFichier,"r");
	if(flot==NULL)
	{
		printf("Problème d'ouverture du fichier\n");
		return -1;
	}
	j=lireJeux(flot);
	while(!feof(flot))
	{
		if(i>=taillemax)
		{
			printf("Tableau plein\n");
			fclose(flot);
			return -1;
		}
		tabJeux[i]=(Jeux*)malloc(sizeof(Jeux));
		if(tabJeux[i]==NULL)
		{
			printf("Problème malloc\n");
			fclose(flot);
			return -1;
		}
		*tabJeux[i]=j;
		i=i+1;
		j=lireJeux(flot);
	}
	fclose(flot);
	triejeux(tabJeux, i);
	return i;
}

/*
Titre : affichageJeux
Finalité : Afficher le contenu du tableau tabJeux
Paramètres : tabJeux - tableau de pointeur statique de type Jeux
	     nb -taille logique de tabJeux
Variable : i -entier servant d'index
*/

void affichageJeux(Jeux *tabJeux[], int nb)
{
	int i;
	printf("ID Jeux\t Type\t Nb exemplaire\t Nom\n");
	for(i=0;i<nb;i++)
		printf("%s\t%s\t\t%d\t%s\n",tabJeux[i]->idjeux,tabJeux[i]->typejeux,tabJeux[i]->nb,tabJeux[i]->nomjeux);
}

/*
Titre : sauvegardeJeux
Finalité : Sauvegarder les données concernant les jeux dans le fichier jeu.txt puis renvoie un entier pour vérifier si ça a marché
Paramètres : tabJeux - tableau de pointeur statique de type Jeux
	     nomFichier -chaîne de caractères pour le nom du fichier
	     nb -taille logique de tabJeux
Variable : i -entier servant d'index
*/

int sauvegardeJeux(Jeux *tabJeux[], char nomFichier[], int nb)
{
	FILE *flot;
	int i;
	flot=fopen(nomFichier,"w");
	if(flot==NULL)
	{
		printf("Problème dans l'ouverture du fichier %s !", nomFichier);
		return -1;
	}
	for(i=0;i<nb;i++)
		fprintf(flot,"%s\n%s\n%d\n%s\n",tabJeux[i]->idjeux,tabJeux[i]->typejeux,tabJeux[i]->nb,tabJeux[i]->nomjeux);
	fprintf(flot,"\n\n");
	fclose(flot);
	return 0;
}

//Partie fichier adhérent//

/*
Titre : lireAD
Finalité :  Lit des éléments du fichier adherents.txt pour les insérer dans une structure Adherent puis retourne la structure
Paramètre : flot vers le fichier adherents.txt
Variables : ad - variable de type Adherent
*/

Adherent lireAD(FILE* flot)
{
	Adherent ad;
	fscanf(flot,"%s%*c%s%*c",ad.idad,ad.civil);
	fgets(ad.nom,30,flot);
	ad.nom[strlen(ad.nom)-1]='\0';
	fgets(ad.prenom,30,flot);
	ad.prenom[strlen(ad.prenom)-1]='\0';
	fscanf(flot,"%s%*c",ad.date);
	return ad;
}

/*
Titre : listevideAD
Finalité : Initialise la liste à NULL puis la retourne
Paramètre : aucun
Variable : liste -liste chaînée de type ListeAD
*/

ListeAD listevideAD(void)
{
	ListeAD liste;
	liste=NULL;
	return liste;
}

/*
Titre videAD
Finalité : Renvoie vrai si la liste est vide, faux dans le cas contraire
Paramètre : lAd -liste de chaînée type ListeAD à vérifier
Variable : Aucune
*/

Booleen videAD(ListeAD lAd)
{
	if(lAd==NULL)
		return vrai;
	return faux;
}

/*
Titre insertionEnTeteAD
Finalité : Insérer à la première position d'une liste, puis renvoie la liste
Paramètres : lAd -Liste chaînée de type lAd
	     ad -variable de type Adherent à ajouter
Variable : adherent -Pointeur sur un maillon de type MaillonAD
*/

ListeAD insertionEnTeteAD(ListeAD lAd, Adherent ad)
{
	MaillonAD *adherent;
	adherent=(MaillonAD *)malloc(sizeof(MaillonAD));
	if(adherent==NULL)
	{
		printf("Problème malloc");
		exit(-1);
	}
	adherent->a=ad;
	adherent->suiv=lAd;
	return adherent;
}

/*
Titre ajouterAdherent
Finalité : Ajouter un adhérent dans la liste des adhérents puis retourne la liste
Paramètres : lAd -Liste chaînée de type Adherent
	     ad -variable de type Adherent à ajouter
Variables : Aucune
*/

ListeAD ajouterAdherent(ListeAD lAd, Adherent ad)
{
	if(lAd==NULL)
		return insertionEnTeteAD(lAd,ad);
	if(strcmp(ad.idad,lAd->a.idad)<0)
		return insertionEnTeteAD(lAd,ad);
	if(strcmp(ad.idad,lAd->a.idad)==0)
		return lAd;
	lAd->suiv=ajouterAdherent(lAd->suiv,ad);
	return lAd;
}

/*
Titre : chargerListeAdherent
Finalité : Charger en mémoire le fichier adherents.txt dans la liste des adhérents puis retourne la liste
Paramètres : lAd -Liste chaînée de type Adherent
	     nomFichier -chaîne de caractères contenant le nom du fichier à charger
Variables : ad -variable de type Adherent à ajouter
*/

ListeAD chargerListeAdherent(ListeAD lAd, char nomFichier[],int *nbAd)
{
	FILE *flot;
	Adherent ad;
	lAd=listevideAD();
	flot=fopen(nomFichier,"r");
	if(flot==NULL)
	{
		printf("Problème dans l'ouverture du fichier\n");
		return lAd;
	}
	ad=lireAD(flot);
	while(!feof(flot))
	{
		lAd=ajouterAdherent(lAd,ad);
		*nbAd=*nbAd+1;
		ad=lireAD(flot);
	}
	fclose(flot);
	return lAd;
}

/*
Titre affichageListeAdherent
Finalité : Afficher la liste des adhérents
Paramètres : lAd -Liste chaînée de type Adherent
Variable : aucune
*/

void affichageListeAdherent(ListeAD lAd)
{
	printf("{\n");
	while(!videAD(lAd))
	{
		printf(" %s\t%s\t%s  %s  %s\t\n",lAd->a.idad,lAd->a.civil,lAd->a.nom,lAd->a.prenom,lAd->a.date);
		lAd=lAd->suiv;
	}
	printf("}\n");
}

/*
Titre : sauvegardeAdherents
Finalité : Sauvegarder la liste des adhérents dans le fichier adherents.txt
Paramètres : lAd -Liste chaînée de type Adherent
	     nomFichier -chaîne de caractères contenant le nom du fichier pour sauvegarder
*/

int sauvegardeAdherents(ListeAD lAd, char nomFichier[])
{
	FILE *flot;
	flot=fopen(nomFichier,"w");
	if(flot==NULL)
	{
		printf("Problème d'ouverture du fichier\n");
		return -1;
	}
	if(videAD(lAd))
	{
		printf("\n\tListe adhérents vide, veuillez la remplir avant de sauvegarder\n");
		return -1;
	}
	while(!videAD(lAd))
	{
		fprintf(flot,"%s\n%s\n%s\n%s\n%s\n",lAd->a.idad,lAd->a.civil,lAd->a.nom,lAd->a.prenom,lAd->a.date);
		lAd=lAd->suiv;
	}
	fprintf(flot,"\n");
	fclose(flot);
	return 0;
}

//Partie fichier emprunt//

/*
Titre : lireEmp
Finalité :  Lit des éléments du fichier emprunts.txt pour les insérer dans une structure Emprunt puis retourne la structure
Paramètre : flot vers le fichier adherents.txt
Variables : emp - variable de type Emprunt
*/

Emprunt lireEmp(FILE* flot)
{
	Emprunt emp;
	fscanf(flot,"%s%s%s%s",emp.idemp,emp.idjeux,emp.idad,emp.dateEmp);
	return emp;
}

/*
Titre : listevideEmp
Finalité : Initialise la liste à NULL puis la retourne
Paramètre : aucun
Variable : liste -liste chaînée de type ListeEmp
*/

ListeEmp listevideEmp(void)
{
	ListeEmp liste;
	liste=NULL;
	return liste;
}

/*
Titre videEmp
Finalité : Renvoie vrai si la liste est vide, faux dans le cas contraire
Paramètre : lEmp -liste chaînée de type ListeEmp à vérifier
Variable : Aucune
*/

Booleen videEmp(ListeEmp lEmp)
{
	if(lEmp==NULL)
		return vrai;
	return faux;
}

/*
Titre insertionEnTeteEmp
Finalité : Insérer à la première position d'une liste, puis renvoie la liste
Paramètres : lEmp -Liste chaînée de type Emprunt
	     emp -variable de type Emprunt à ajouter
Variable : emprunt -Pointeur sur un maillon de type MaillonEmp
*/

ListeEmp insertionEnTeteEmp(ListeEmp lEmp, Emprunt emp)
{
	MaillonEmp *emprunt;
	emprunt=(MaillonEmp *)malloc(sizeof(MaillonEmp));
	if(emprunt==NULL)
	{
		printf("Problème malloc");
		exit(-1);
	}
	emprunt->e=emp;
	emprunt->suiv=lEmp;
	return emprunt;
}

/*
Titre ajouterEmprunt
Finalité : Ajouter un emprunt dans la liste des emprunts puis retourne la liste
Paramètres : lEmp -Liste chaînée de type Emprunt
	     emp -variable de type Emprunt à ajouter
Variables : Aucune
*/

ListeEmp ajouterEmprunt(ListeEmp lEmp, Emprunt emp)
{
	if(lEmp==NULL)
		return insertionEnTeteEmp(lEmp,emp);
	if(strcmp(emp.dateEmp,lEmp->e.dateEmp)<=0)
		return insertionEnTeteEmp(lEmp,emp);
	lEmp->suiv=ajouterEmprunt(lEmp->suiv,emp);
	return lEmp;
}

/*
Titre : chargerListeEmprunt
Finalité : Charger en mémoire le fichier emprunts.txt dans la liste des emprunts puis retourne la liste
Paramètres : lEmp -Liste chaînée de type Emprunt
	     nomFichier -chaîne de caractères contenant le nom du fichier à charger
Variables : emp -variable de type Emprunt à ajouter
*/

ListeEmp chargerListeEmprunt(ListeEmp lEmp, char nomFichier[],int *nbAd)
{
	FILE *flot;
	Emprunt emp;
	lEmp=listevideEmp();
	flot=fopen(nomFichier,"r");
	if(flot==NULL)
	{
		printf("Problème dans l'ouverture du fichier\n");
		return lEmp;
	}
	emp=lireEmp(flot);
	while(!feof(flot))
	{
		lEmp=ajouterEmprunt(lEmp,emp);
		*nbAd=*nbAd+1;
		emp=lireEmp(flot);
	}
	fclose(flot);
	return lEmp;
}

/*
Titre affichageListeEmprunt
Finalité : Afficher la liste des emprunts
Paramètres : lEmp -Liste chaînée de type Emprunt
Variable : aucune
*/

void affichageListeEmprunt(ListeEmp lEmp)
{
	printf("{\n");
	while(!videEmp(lEmp))
	{
		printf(" %s\t%s\t%s  %s\n",lEmp->e.idemp,lEmp->e.idjeux,lEmp->e.idad,lEmp->e.dateEmp);
		lEmp=lEmp->suiv;
	}
	printf("}\n");
}

/*
Titre : sauvegardeEmprunts
Finalité : Sauvegarder la liste des emprunts dans le fichier emprunts.txt
Paramètres : lEmp -Liste chaînée de type Emprunt
	     nomFichier -chaîne de caractères contenant le nom du fichier pour sauvegarder
*/

int sauvegardeEmprunts(ListeEmp lEmp, char nomFichier[])
{
	FILE *flot;
	flot=fopen(nomFichier,"w");
	if(flot==NULL)
	{
		printf("Problème d'ouverture du fichier\n");
		return -1;
	}
	if(videEmp(lEmp))
	{
		printf("\n\tListe emprunts vide, veuillez la remplir avant de sauvegarder\n");
		return -1;
	}
	while(!videEmp(lEmp))
	{
		fprintf(flot,"%s\t%s\t%s  %s\n",lEmp->e.idemp,lEmp->e.idjeux,lEmp->e.idad,lEmp->e.dateEmp);
		lEmp=lEmp->suiv;
	}
	fprintf(flot,"\n");
	fclose(flot);
	return 0;
}

//Partie fichier réservation//

/*
Titre : lireResa
Finalité :  Lit des éléments du fichier reservations.txt pour les insérer dans une structure Reservation puis retourne la structure
Paramètre : flot vers le fichier reservations.txt
Variables : resa - variable de type Reservation
*/

Reservation lireResa(FILE* flot)
{
	Reservation resa;
	fscanf(flot,"%s%s%s%s",resa.idresa,resa.idad,resa.idjeux,resa.dateResa);
	return resa;
}

/*
Titre : listevideResa
Finalité : Initialise la liste à NULL puis la retourne
Paramètre : aucun
Variable : liste -liste chaînée de type ListeResa
*/

ListeResa listevideResa(void)
{
	ListeResa liste;
	liste=NULL;
	return liste;
}

/*
Titre videResa
Finalité : Renvoie vrai si la liste est vide, faux dans le cas contraire
Paramètre : lResa -liste chaînée de type ListeResa à vérifier
Variable : Aucune
*/

Booleen videResa(ListeResa lResa)
{
	if(lResa==NULL)
		return vrai;
	return faux;
}

/*
Titre insertionEnTeteResa
Finalité : Insérer à la première position d'une liste, puis renvoie la liste
Paramètres : lResa -Liste chaînée de type Reservation
	     resa -variable de type Reservation à ajouter
Variable : reservation -Pointeur sur un maillon de type MaillonResa
*/

ListeResa insertionEnTeteResa(ListeResa lResa, Reservation resa)
{
	MaillonResa *reservation;
	reservation=(MaillonResa *)malloc(sizeof(MaillonResa));
	if(reservation==NULL)
	{
		printf("Problème malloc");
		exit(-1);
	}
	reservation->r=resa;
	reservation->suiv=lResa;
	return reservation;
}

/*
Titre ajouterReservation
Finalité : Ajouter une reservation dans la liste des reservations puis retourne la liste
Paramètres : lResa -Liste chaînée de type Reservation
	     resa -variable de type Reservation à ajouter
Variables : Aucune
*/

ListeResa ajouterReservation(ListeResa lResa, Reservation resa)
{
	if(lResa==NULL)
		return insertionEnTeteResa(lResa,resa);
	if(strcmp(resa.dateResa,lResa->r.dateResa)<=0)
		return insertionEnTeteResa(lResa,resa);
	lResa->suiv=ajouterReservation(lResa->suiv,resa);
	return lResa;
}

/*
Titre : chargerListeReservation
Finalité : Charger en mémoire le fichier reservations.txt dans la liste des reservations puis retourne la liste
Paramètres : lResa -Liste chaînée de type Reservation
	     nomFichier -chaîne de caractères contenant le nom du fichier à charger
Variables : resa -variable de type Reservation à ajouter
*/

ListeResa chargerListeReservation(ListeResa lResa, char nomFichier[],int *nbResa)
{
	FILE *flot;
	Reservation resa;
	lResa=listevideResa();
	flot=fopen(nomFichier,"r");
	if(flot==NULL)
	{
		printf("Problème dans l'ouverture du fichier\n");
		return lResa;
	}
	resa=lireResa(flot);
	while(!feof(flot))
	{
		lResa=ajouterReservation(lResa,resa);
		*nbResa=*nbResa+1;
		resa=lireResa(flot);
	}
	fclose(flot);
	return lResa;
}

/*
Titre affichageListeReservation
Finalité : Afficher la liste des reservations
Paramètres : lResa -Liste chaînée de type reservation
Variable : aucune
*/

void affichageListeReservation(ListeResa lResa)
{
	printf("{\n");
	while(!videResa(lResa))
	{
		printf("%s\t%s\t%s  %s\n",lResa->r.idresa,lResa->r.idad,lResa->r.idjeux,lResa->r.dateResa);
		lResa=lResa->suiv;
	}
	printf("}\n");
}

/*
Titre : sauvegardeReservation
Finalité : Sauvegarder la liste des reservations dans le fichier reservations.txt
Paramètres : lResa -Liste chaînée de type Reservation
	     nomFichier -chaîne de caractères contenant le nom du fichier pour sauvegarder
*/

int sauvegardeReservation(ListeResa lResa, char nomFichier[])
{
	FILE *flot;
	flot=fopen(nomFichier,"w");
	if(flot==NULL)
	{
		printf("Problème d'ouverture du fichier\n");
		return -1;
	}
	if(videResa(lResa))
	{
		printf("\n\tListe réservations vide, veuillez la remplir avant de sauvegarder\n");
		return -1;
	}
	while(!videResa(lResa))
	{
		fprintf(flot,"%s\t%s\t%s  %s\n",lResa->r.idresa,lResa->r.idad,lResa->r.idjeux,lResa->r.dateResa);
		lResa=lResa->suiv;
	}
	fprintf(flot,"\n");
	fclose(flot);
	return 0;
}



/*Titre : RechercheJeux
Finalité : Rechercher dans tabJeux, le jeu désiré
Paramètres : tabJeux -Tableau de pointeur de type Jeux
	     nb -taille logique de tabJeux
	     jeux -chaîne de caractères 
	     trouve -pointeur de type entier
Variables :  i -entier 
*/

int RechercheJeux(Jeux *tabJeux[], int nb, char jeux[], int *trouve)
{
	int i;
	for(i=0;i<nb;i++)
		if(strcmp(jeux,tabJeux[i]->nomjeux)==0)
		{
			*trouve=0;
			return i;
		}
	*trouve=-1;
	return i;
}

/*
Titre : affichageReservationJeux
Finalité : Afficher la liste des réservations pour un jeu donné
Paramètres : tabJeux -Tableau de pointeur de type Jeux
	     nb -taille logique de tabJeux
	     lResa -Liste chaînée de reservation de type ListeResa
Variables : jeux -chaîne de caractère
	    c -caractère
	    i -entier
	    j -entier
*/

void affichageReservationJeux(Jeux *tabJeux[], int nb, ListeResa lResa)
{
	char jeux[20], c;
	int i, trouve,j=0;
	printf("\n\n\tJeux désiré : ");
	fgets(jeux,20,stdin);
	jeux[strlen(jeux)-1]='\0';
	i=RechercheJeux(tabJeux,nb, jeux, &trouve);
	if(trouve==-1)
	{
		printf("\n\tLe jeux n'existe pas\n");
		printf("\n\n    Tapez une touche pour revenir au menu...");
    		c=getchar();
		return;
	}
	printf("\n\tLe jeux désiré possède comme identifiant : %s\n\n",tabJeux[i]->idjeux);
	while(!videResa(lResa))
	{
		if(strcmp(tabJeux[i]->idjeux,(lResa->r).idjeux)==0)
		{
			printf("\t%s\t%s\t%s\t%s\n",(lResa->r).idresa,(lResa->r).idad,(lResa->r).idjeux,(lResa->r).dateResa);
			j++;
		}
		lResa=lResa->suiv;
	}
	if(j==0)
		printf("\tAucune réservation pour ce jeux\n\n");
	printf("\n\n    Tapez une touche pour revenir au menu...");
    	c=getchar();
}

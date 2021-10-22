#include "projet.h"
#include "time.h"   // Nécessaire pour la création de la date (adhérents,emprunts,réservations)


// Valentin's part
// Dans l'ordre : Sauvegarde globale, Menus, Affichages(1 et 2), Création(adhérents, emprunts, réservations), Annulation réservation.



/*
Titre : 	sauvegardeGlobale
Finalité :  Sauvegarder dans les fichiers de stockage, le contenu des différentes listes et tableaux de données.
        	Renvoyer une confirmation ou une erreur si la sauvegarde ne s'est pas bien déroulée.
Paramètres :tabJeux -Tableau de pointeur statique de type Jeux
        	lAd -Liste chainée des adhérents de type ListeAD
        	lEmp -Liste des emprunts de type ListeEmp
        	lResa -Liste des réservations de type ListeResa
        	nomFichierJeux -Chaîne de caractères
        	nomFichierAd -Chaîne de caractères
        	nomFichierEmp -Chaîne de caractères
        	nomFichierRe -Chaîne de caractères
        	nb - int,taille logique de tabJeux
Variables : v1 - Caractère
        	v2 - Caractère
        	v3 - Caractère
        	v4 - Caractère
        	c - Caractère
*/
void sauvegardeGlobale(Jeux *tabJeux[], char nomFichierJeux[], int nb, ListeAD lAd, char nomFichierAd[], ListeEmp lEmp, char nomFichierEmp[], ListeResa lResa, char nomFichierRe[]){
	int v1, v2, v3, v4;
	char c;

	v1=sauvegardeJeux(tabJeux,nomFichierJeux,nb);
	v2=sauvegardeAdherents(lAd,nomFichierAd);
	v3=sauvegardeEmprunts(lEmp,nomFichierEmp);
	v4=sauvegardeReservation(lResa,nomFichierRe);

	if(v1==0 && v2==0 && v3==0 && v4==0)
    	printf("\n\n\tSauvegarde des données effectuée.\n");
	else
    	printf("\n\n\tProblème dans la sauvegarde des données !\n");

	printf("\n\n    Tapez une touche...");
	c=getchar();
}



/*
Titre : 	quitterSansSauvegarder
Finalité :  Demande à l'utilisateur s'il souhaite enregistrer avant de quitter.
Paramètres :tabJeux -Tableau de pointeurs statique de type Jeux
        	lAd -Liste chainée des adhérents de type ListeAD
        	lEmp -Liste chaînée des emprunts de type ListeEmp
        	lResa -Liste chaînée des réservations de type ListeResa
        	nomFichierJeux -Chaîne de caractères
        	nomFichierAd -Chaîne de caractères
        	nomFichierEmp -Chaîne de caractères
        	nomFichierRe -Chaîne de caractères
        	nb - int,taille logique de tabJeux
Variable :  c - Caractère
*/
void quitterSansSauvegarder(Jeux *tabJeux[], char nomFichierJeux[], int nb, ListeAD lAd, char nomFichierAd[], ListeEmp lEmp, char nomFichierEmp[], ListeResa lResa, char nomFichierRe[]){
	char c;
	printf("\n\n\tVoulez vous sauvegarder avant de quitter ?\n");
	printf("\n\t\to/n (Oui ou Non) : ");
	scanf("%c%*c", &c);

	if(c=='o'){
    	sauvegardeGlobale(tabJeux,nomFichierJeux,nb,lAd,nomFichierAd,lEmp,nomFichierEmp,lResa,nomFichierRe);
    	system("clear");
    	exit(1);
	}
	else{
    	system("clear");
    	exit(1);
	}
}



/*
Titre : 	MenuPrincipal
Finalité :  Envoyer dans les différentes fonctions du programme les listes et tableaux requis.
        	Appeler les fonctions de choix et d'affichage afin de mener sa tâche.
Paramètre : Aucun
Variable :  tabJeux -Tableau de pointeurs statique de type Jeux
        	lAd -Liste chainée des adhérents de type ListeAD
        	lEmp -Liste chaînée des emprunts de type ListeEmp
        	lResa -Liste chaînée des réservations de type ListeResa
        	nomFichierJeux -Chaîne de caractères
        	nomFichierAd -Chaîne de caractères
        	nomFichierEmp -Chaîne de caractères
        	nomFichierRe -Chaîne de caractères
        	nb -int,taille logique de tabJeux
        	nbAd -int, nombre d'adhérents
        	nbEmp -int, nombre d'emprunts
        	nbResa -int, nombre de réservations
        	choix -char
        	c -char
*/
void MenuPrincipal(){
	Jeux *tabJeux[100];
	ListeAD lAd;
	ListeEmp lEmp;
	ListeResa lResa;
	char nomFichierJeux[30],nomFichierAd[30],nomFichierEmp[30],nomFichierRe[30];
	char choix, c;
	int nb,nbAd=0,nbEmp=0,nbResa=0;

	system("clear");

	printf("\n    Voulez vous utiliser les noms de fichiers par défaut ?\n\n");
	printf("\to/n (Oui ou Non) : ");
	scanf("%c%*c",&c);

	if(c=='o'){
    	strcpy(nomFichierJeux,"jeux.txt");
    	strcpy(nomFichierAd,"adherents.txt");
    	strcpy(nomFichierEmp,"emprunts.txt");
    	strcpy(nomFichierRe,"reservations.txt");
	}
	else{
    	printf("    Nom des fichiers :\n");

    	printf("\n\tNom du fichier Jeux : ");
    	scanf("%s%*c",nomFichierJeux);  

    	printf("\n\tNom du fichier Adhérents : ");
    	scanf("%s%*c",nomFichierAd);

    	printf("\n\tNom du fichier Emprunts : ");
    	scanf("%s%*c",nomFichierEmp);

    	printf("\n\tNom du fichier Reservations : ");
    	scanf("%s%*c",nomFichierRe);
    	}

	nb=chargementJeux(tabJeux,nomFichierJeux,100);
	if(nb==-1){
        	printf("Problème dans le chargement du tableau\n");
        	return;
        }
	lAd=chargerListeAdherent(lAd,nomFichierAd,&nbAd);
	lEmp=chargerListeEmprunt(lEmp,nomFichierEmp,&nbEmp);
	lResa=chargerListeReservation(lResa,nomFichierRe,&nbResa);

// ## Sert juste à vérifier que tout se passe bien
	printf("\n\n");
	printf("    Voulez vous afficher le contenu des fichiers ?\n");
	printf("\n\to/n ? (Oui ou Non) ");
	scanf("%c%*c", &c);

	if(c=='o'){
    	printf("\n\n");
    	affichageJeux(tabJeux,nb);
    	affichageListeAdherent(lAd);
    	affichageListeEmprunt(lEmp);
    	affichageListeReservation(lResa);
	}
// ## Fin de la partie

	printf("\n\n    Tapez une touche pour accéder au menu..." );
	c=getchar();

	choix = choixMenuPrincipal();
	while(choix != '0'){
    	switch(choix){
        	case '1': MenuAffichage(tabJeux,nomFichierJeux,nb,lAd,nomFichierAd,lEmp,nomFichierEmp,lResa,nomFichierRe); break;
        	case '2': lAd=creationNouvelAdherent(lAd,&nbAd); break;
        	case '3': lEmp=creationNouvelEmprunt(tabJeux,nb,lAd,lEmp,&nbEmp); break;
        	case '4': lResa=creationNouvelleReservation(tabJeux,nb,lAd,lEmp,lResa,&nbResa); break;
        	case '5': lResa=annulationReservation(tabJeux,nb,lAd,lResa); break;
        	case '6': lResa=retourJeux(tabJeux,nb,lAd,lEmp,lResa,&nbEmp); break;
        	case '7': sauvegardeGlobale(tabJeux,nomFichierJeux,nb,lAd,nomFichierAd,lEmp,nomFichierEmp,lResa,nomFichierRe); break;
        	case '9': quitterSansSauvegarder(tabJeux,nomFichierJeux,nb,lAd,nomFichierAd,lEmp,nomFichierEmp,lResa,nomFichierRe); break;
    	}
	choix = choixMenuPrincipal();
	}
	system("clear");
}


/*
Titre : 	MenuAffichage
Finalité :  Envoyer dans les différentes fonctions de programme les listes et tableaux requis.
        	Appeler les fonctions de choix et d'affichage afin de mener sa tâche.
Paramètres :tabJeux -Tableau de pointeur statique de type Jeux
        	lAd -Liste chainée des adhérents de type ListeAD
        	lEmp -Liste chaînée des emprunts de type ListeEmp
        	lResa -Liste chaînée des réservations de type ListeResa
        	nomFichierJeux -Chaîne de caractères
        	nomFichierAd -Chaîne de caractères
        	nomFichierEmp -Chaîne de caractères
        	nomFichierRe -Chaîne de caractères
        	nb -int,taille logique de tabJeux
Variables : choix - Caractère
*/
void MenuAffichage(Jeux *tabJeux[], char nomFichierJeux[], int nb, ListeAD lAd, char nomFichierAd[], ListeEmp lEmp, char nomFichierEmp[], ListeResa lResa, char nomFichierRe[]){
	char choix;
	choix = choixMenuAffichage();
	while(choix != '8'){
    	switch(choix){
   		case '1': affichageListeJeuxDisponibles(tabJeux, nb); break;
        	case '2': affichageEmpruntEnCours(tabJeux, nb, lEmp, lAd); break;
        	case '3': affichageReservationJeux(tabJeux, nb, lResa); break;
        	case '9': quitterSansSauvegarder(tabJeux,nomFichierJeux,nb,lAd,nomFichierAd,lEmp,nomFichierEmp,lResa,nomFichierRe); break;
    	}
	choix = choixMenuAffichage();
	}
	system("clear");
}



/*
Titre : 	choixMenuPrincipal
Finalité :  Récuperer le choix fait par l'utilisateur et le renvoyer à la fonction principale du menu.
        	Vérifier que le choix rentre bien dans les critères du menu.
        	Appeler l'affichage du menu principal.
Paramètre : Aucun
Variables :  c - Caractère
        	choix - Caractère
*/
char choixMenuPrincipal(void){
	char c, choix;
	AffichageMenuPrincipal();
	printf("    Votre choix : ");
	scanf("%c%*c",&choix);
	while((choix != '0') && (choix != '1') && (choix != '2') && (choix != '3') && (choix != '4') && (choix != '5') && (choix != '6') && (choix != '7') && (choix != '9')){   	 
    	printf("\n\tChoix incorrect\n");
    	printf("\tTapez une touche pour revenir au menu...");
    	c=getchar();
    	AffichageMenuPrincipal();
    	printf("    Votre choix : ");
    	scanf("%c%*c",&choix);
	}
	return choix;
}



/*
Titre : 	choixMenuAffichage
Finalité :  Récuperer le choix fait par l'utilisateur et le renvoyer à la fonction principale du menu.
        	Vérifier que le choix rentre bien dans les critères du menu.
        	Appeler l'affichage du sous menu affichage.
Paramètre : Aucun
Variable :  c - Caractère
        	choix - Caractère
*/
char choixMenuAffichage(void){
	char c, choix;
	AffichageMenuAffichage();
	printf("    Votre choix : ");
	scanf("%c%*c",&choix);
	while((choix != '1') && (choix != '2') && (choix != '3') && (choix != '8') && (choix != '9')){
    	printf("\n\tChoix incorrect\n");
    	printf("\tTapez une touche pour revenir au menu...");
    	c=getchar();
    	AffichageMenuAffichage();
    	printf("    Votre choix : ");
    	scanf("%c%*c",&choix);
	}
	return choix;
}



/*
Titre : 	AfichageMenuPrincipal
Finalité :  Afficher le menu principal
Paramètre : Aucun
Variable :  Aucune
*/
void AffichageMenuPrincipal(void){
	system("clear");
	printf("|***********************************************|\n");
	printf("|    Programme de gestion de la ludothèque :\t|\n");
	printf("|\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t|\n");
	printf("|\t1. Affichages\t\t\t\t|\n");
	printf("|\t2. Nouvel adhérent\t\t\t|\n");
	printf("|\t3. Nouvel emprunt\t\t\t|\n");
	printf("|\t4. Nouvelle réservation\t\t\t|\n");
	printf("|\t5. Annulation d'une réservation\t\t|\n");
	printf("|\t6. Retour d'un jeu\t\t\t|\n");
	printf("|\t7. Sauvegarder\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t|\n");
	printf("|\t9. Quitter\t\t\t\t|\n");
	//printf("|\t|\t|\t|\t|\t|\t|\n");
	printf("|\t\t\t\t\t\t|\n");
	printf("|***********************************************|\n\n");
}



/*
Titre : 	AffichagemenuAffichage
Finalité :  Afficher le sous menu affichage
Paramètre : Aucun
Variable :  Aucune
*/
void AffichageMenuAffichage(void){
	system("clear");
	printf("|***********************************************|\n");
	printf("|    Affichages :\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t|\n");
	printf("|\t1. Liste des Jeux disponibles\t\t|\n");
	printf("|\t2. Emprunts en cours\t\t\t|\n");
	printf("|\t3. Liste des réservations\t\t|\n");
	printf("|\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t|\n");
	printf("|\t8. Retour au menu Principal\t\t|\n");
	printf("|\t9. Quitter\t\t\t\t|\n");
	//printf("|\t|\t|\t|\t|\t|\t|\n");
	printf("|\t\t\t\t\t\t|\n");
	printf("|***********************************************|\n\n");
}



/*
Titre : 	Modifier
Finalité :  Servir de bouche trou
Paramètre : Aucun
Variable :  c - Caractère
*/
void Modifier(void){    	// Inutile depuis que toutes les fonctionnalités ont été ajouté.
	char c;
	printf("\n\tA modifier/compléter\n");

	printf("\n\n    Tapez une touche pour revenir au menu...");
	c=getchar();
}



/*
Titre : 	affichageEmpruntsEnCours
Finalité :  Afficher les emprunts en cours
Paramètres :tabJeux -Tableau de pointeurs statique de type Jeux
        	lAd -Liste chainée des adhérents de type ListeAD
        	lEmp -Liste chaînée des emprunts de type ListeEmp
        	nb -int,taille logique de tabJeux
Variable :  c -Caractère
        	i -int
*/
void affichageEmpruntEnCours(Jeux *tabJeux[], int nb, ListeEmp lEmp, ListeAD lAd){
	char c;
	int i;
	
    if(lEmp==NULL)
        printf("\n\n\tIl n'y a pas d'emprunts en cours.\n");
    else{
        printf("\n\n    Emprunts en cours :\n\n");
        printf("\tNom du jeu\tIdentité de l'emprunteur\tDate de l'emprunt\n\n");
    }
        
	while(!videEmp(lEmp)){
  	  i=0;
  	  while(strcmp(lEmp->e.idjeux, tabJeux[i]->idjeux) != 0){
  		  if(i>nb)
  			  printf("Le jeu n'existe pas !\n");  	 
  		  i++;
  	  }
 	if(strlen(tabJeux[i]->nomjeux)<8)
  	 	printf("\t%s\t",tabJeux[i]->nomjeux);
	else
    	printf("\t%s",tabJeux[i]->nomjeux);

  	  affichageIdentite(lEmp, lAd);

  	  printf("%s\n",lEmp->e.dateEmp);
  	  lEmp=lEmp->suiv;

	}
	printf("\n\n    Tapez une touche pour revenir au menu...");
	c=getchar();
}



/*
Titre : 	affichageIdentité
Finalité :  Afficher l'identité d'une personne (civilité, nom, prénom)
Paramètres :lAd -Liste chainée des adhérents de type ListeAD
        	lEmp -Liste chaînée des emprunts de type ListeEmp
Variable :  Aucune
*/
void affichageIdentite(ListeEmp lEmp, ListeAD lAd){
	while(strcmp(lEmp->e.idad, lAd->a.idad) != 0){
  		 if(lAd->suiv==NULL){
  			 printf("\tL'adhérents n'existe pas !\n");
  			 break;
  	  }
  	  lAd=lAd->suiv;    
	}
	if(strlen(lAd->a.civil) > 2)
   	 printf("\t%s", lAd->a.civil);
	else
   	 printf("\t%s ", lAd->a.civil);

	printf(" %s\t",lAd->a.nom);

	if(strlen(lAd->a.prenom) > 7)
   	 printf("%s\t",lAd->a.prenom);
	else
   	 printf("%s\t\t",lAd->a.prenom);
}



/*
Titre : 	affichageListeJeuxDisponibles
Finalité :  Afficher la liste des jeux disponibles (supposés triés)
Paramètres :tabJeux -Tableau de pointeurs statique de type Jeux
        	nb - int,taille logique de tabJeux  
Variable :  c - Caractère
        	i - Entier
*/
void affichageListeJeuxDisponibles(Jeux *tabJeux[], int nb){
	char c;
	int i;

	printf("\n\n    Jeux disponibles :\n\n");
    
	printf("\tType de jeu\tNom du jeu\n\n");

    for(i=0;i<nb;i++)
   	 if(tabJeux[i]->nb > 0)
   		 if(strlen(tabJeux[i]->typejeux) > 7)
   			 printf("\t%s\t%s\n",tabJeux[i]->typejeux,tabJeux[i]->nomjeux);
   		 else
   			 printf("\t%s\t\t%s\n",tabJeux[i]->typejeux,tabJeux[i]->nomjeux);

	printf("\n\n    Tapez une touche pour revenir au menu...");
	c=getchar();
}



/*
Titre : 	creationNouvelAdherent
Finalité :  Récolter et vérifier les informations nécessaires pour créer un adhérent.
Paramètres :lAd -Liste chainée des adhérents de type ListeAD
        	nbAd -pointeur sur un entier
Variables : c -char
        	genre -char
        	nom -Chaîne de caractères
        	prenom -Chaîne de caractères
*/
ListeAD creationNouvelAdherent(ListeAD lAd, int *nbAd){
    	char c='n', genre;
    	char nom[20], prenom[20];

    	while(c!='o'){
        	system("clear");
        	AffichageMenuPrincipal();
        	printf("    Votre choix : 2\n");

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

    	ListeAD rechAd=rechercheAdherent(lAd,nom,prenom);

    	if(!rechAd){
        	printf("\n\n    Etes vous un homme ?");
        	printf("\n\n\to/n (Oui ou Non) : ");
        	scanf("%c%*c", &genre);

        	lAd=nouvelAdherent(nom,prenom,genre,lAd,nbAd);
        	if(lAd==NULL){
            	printf("Problème dans la création de l'adhérent\n");
            	exit(1);
        	}
        	else
            	printf("\n\n    Création de l'adhérent réussite.\n");
    	}
    	else{
        	printf("\n\n    L'Adhérent existe déja !");
        	printf("\n    Création de l'adhérent annulé !\n");
    	}
    	printf("\n\n    Tapez une touche pour revenir au menu...");
    	c=getchar();
    	return lAd;
}



/*
Titre : 	creationNouvelEmprunt
Finalité :  Récolter et vérifier les informations nécessaires pour créer un emprunt.
Paramètres :lEmp -Liste chainée des emprunts de type ListeEmp
        	lAd -Liste chainée des adhérents de type ListeAD
        	nbEmp -pointeur sur un entier
Variables : c -char
        	nom -Chaîne de caractères
        	prenom -Chaîne de caractères
        	jeu -Chaîne de caractères
        	trouve -int
        	choixM -int
        	nbEmpP -int
        	pos -int
*/
ListeEmp creationNouvelEmprunt(Jeux *tabJeux[], int nb, ListeAD lAd, ListeEmp lEmp, int *nbEmp){
	char c='n';
	char nom[20], prenom[20], jeu[20];
	int trouve=0, choixM=3, nbEmpP=0, pos;

	while(c!='o'){
    	system("clear");
    	AffichageMenuPrincipal();
    	printf("    Votre choix : 3\n");

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
	ListeAD rechAd=rechercheAdherent(lAd,nom,prenom);

	if(!rechAd){
    	printf("\n\n    L'Adhérent %s %s n'existe pas !", nom, prenom);
    	printf("\n    Veuillez le créer avant de faire un emprunt.\n");
	}
	else{
    	nbEmpP=nombreEmprunts(lAd,nom,prenom,lEmp);
    	if(nbEmpP>=3){
        	printf("\n\n\tVous avez dépassé le nombre de 3 emprunts maximum.");
        	printf("\n\tVous devez d'abord rendre un jeu avant de pouvoir en emprunter un nouveau.\n");
    	}
    	else{
        	printf("\n\n    Nom du jeu à emprunter : ");
        	fgets(jeu,20,stdin);
        	jeu[strlen(jeu)-1]='\0';
        	pos=RechercheJeux(tabJeux,nb,jeu,&trouve);

        	while(trouve==-1){
            	reAffichage(nom,prenom,choixM);

            	printf("\n\n\n\tLe jeu \"%s\" n'existe pas !",jeu);
            	printf("\n\n   Nom du jeu à emprunter : ");
            	fgets(jeu,20,stdin);
            	jeu[strlen(jeu)-1]='\0';
            	pos=RechercheJeux(tabJeux,nb,jeu,&trouve);
        	}
        	if(tabJeux[pos]->nb>0){
            	lEmp=nouvelEmprunt(pos,tabJeux,lAd,nom,prenom,lEmp,nbEmp);
            	if(lAd==NULL){
                	printf("Problème dans la création de l'emprunt\n");
                	exit(1);
            	}
            	else
                	printf("\n\tEmprunt accordé.\n");
        	}
        	else{
            	printf("\n\n    Le jeu que vous désirez est actuellement indisponible.");
            	printf("\n    Veuillez utiliser la fonction \"Nouvelle réservation\".\n");
        	}
    	}
	}
	printf("\n\n    Tapez une touche pour revenir au menu...");
	c=getchar();
	return lEmp;
}



/*
Titre : 	creationNouvelleReservation
Finalité :  Récolter et vérifier les informations nécessaires pour créer une réservation.
Paramètres :lResa -Liste chainée des adhérents de type ListeResa
        	lEmp -Liste chainée des adhérents de type ListeEmp
        	lAd -Liste chainée des adhérents de type ListeAd
        	nbResa -pointeur sur un entier
Variables : c -char
        	nom -Chaîne de caractères
        	prenom -Chaîne de caractères
        	jeu -Chaîne de caractères
        	trouve -int
        	choixM -int
        	nbEmpP -int
        	pos -int
*/
ListeResa creationNouvelleReservation(Jeux *tabJeux[], int nb, ListeAD lAd, ListeEmp lEmp, ListeResa lResa, int *nbResa){
	char c='n';
	char nom[20], prenom[20], jeu[20];
	int trouve=0, choixM=4, nbEmpP=0, pos;

	while(c!='o'){
    	system("clear");
    	AffichageMenuPrincipal();
    	printf("    Votre choix : 4\n");
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
	ListeAD rechAd=rechercheAdherent(lAd,nom,prenom);

	if(!rechAd){
    	printf("\n\n    L'Adhérent %s %s n'existe pas !", nom, prenom);
    	printf("\n    Veuillez le créer avant de faire un emprunt.\n");
	}
	else{
    	nbEmpP=nombreEmprunts(lAd,nom,prenom,lEmp);

    	if(nbEmpP>=3){
        	printf("\n\n\tVous avez dépassé le nombre de 3 emprunts maximum.");
        	printf("\n\tVous devez d'abord rendre un jeu avant de pouvoir en emprunter un nouveau.\n");
    	}
    	else{
        	printf("\n\n    Nom du jeu à réserver : ");
        	fgets(jeu,20,stdin);
        	jeu[strlen(jeu)-1]='\0';

        	pos=RechercheJeux(tabJeux,nb,jeu,&trouve);

        	while(trouve==-1){
            	reAffichage(nom,prenom,choixM);

            	printf("\n\n\n\tLe jeu \"%s\" n'existe pas !",jeu);
            	printf("\n\n    Nom du jeu à réserver : ");
            	fgets(jeu,20,stdin);
            	jeu[strlen(jeu)-1]='\0';
            	pos=RechercheJeux(tabJeux,nb,jeu,&trouve);
        	}    
        	lResa=nouvelleReservation(pos,tabJeux,lAd,nom,prenom,lResa,nbResa);
        	if(lResa==NULL){
            	printf("Problème dans la création de la réservation\n");
            	exit(1);
        	}
        	else
            	printf("\n\tRéservation effectuée.\n");
    	}
	}
	printf("\n\n    Tapez une touche pour revenir au menu...");
	c=getchar();
	return lResa;
}



/*
Titre : 	reAffichage
Finalité :  Permettre un affichage plus compacte en terme de lignes de code.
Paramètres :nom -Chaîne de caractères
        	prenom -Chaîne de caractères
        	choixM -int
Variable :  Aucune
*/
void reAffichage(char nom[], char prenom[], int choixM){
	system("clear");
	AffichageMenuPrincipal();
	printf("    Votre choix : %d", choixM);
	printf("\n\n\n\tVeuillez renseigner votre nom : %s",nom);
	printf("\n\n\tVeuillez renseigner votre prénom : %s",prenom);
	printf("\n\n\n    Validez vous ces informations ?");
	printf("\n\n\to/n (Oui ou Non) : o");
}



/*
Titre : 	nouvelAdherent
Finalité :  Créer un nouvel adhérent.
Paramètres :lAd -Liste chainée des adhérents de type ListeAD
        	nom -Chaîne de caractères
        	prenom -Chaîne de caractères
        	genre -char
        	nbAd -pointeur sur un entier
Variable :  Adhérent a -Maillon de type Adhérent
*/
ListeAD nouvelAdherent(char nom[] , char prenom[] , char genre, ListeAD lAd, int *nbAd){
	Adherent a;

	if(*nbAd/100>=1){
    	char Ad[3]={"AD"};
    	char nbr[4]="";
    	sprintf(nbr, "%d", *nbAd+1);
    	strcat(Ad, nbr);
    	strcpy(a.idad, Ad);
	}
	else if(*nbAd/10>=1){
    	char Ad[4]={"AD0"};
    	char nbr[3]="";
    	sprintf(nbr, "%d", *nbAd+1);
    	strcat(Ad, nbr);
    	strcpy(a.idad, Ad);
	}
	else{
    	char Ad[5]={"AD00"};
    	char nbr[2]="";
    	sprintf(nbr, "%d", *nbAd+1);
    	strcat(Ad, nbr);
    	strcpy(a.idad, Ad); 	 
	}  

	if(genre=='o')
    	strcpy(a.civil, "Mr");
	else
    	strcpy(a.civil, "Mme");
 
	strcpy(a.nom, nom);

	strcpy(a.prenom, prenom);
    
	char date[64];
	time_t timestamp = time(NULL);
	strftime(date, sizeof(date), "%d/%m/%Y", localtime(&timestamp));

	strcpy(a.date, date);
    
	lAd=ajouterAdherent(lAd,a);
	(*nbAd)++;
	return lAd;
}



/*
Titre : 	nombreEmprunts
Finalité :  Retourner le nombre d'emprunts d'un adhérent.
Paramètres :lAd -Liste chainée des adhérents de type ListeAD
        	lEmp -Liste chaînée des emprunts de type ListeEmp      	 
        	nom -Chaîne de caractères
        	prenom -Chaîne de caractères
Variables : nb -int
        	id -Chaîne de caractères
*/
int nombreEmprunts(ListeAD lAd, char nom[], char prenom[], ListeEmp lEmp){
	int nb=0;
	char id[6];
 
	while(strcmp(lAd->a.nom, nom) != 0 && strcmp(lAd->a.prenom, prenom) != 0)
    	lAd=lAd->suiv;

	strcpy(id, lAd->a.idad);

	while(!videEmp(lEmp)){
    	if(strcmp(id, lEmp->e.idad)==0)
        	nb++;
    	lEmp=lEmp->suiv;
	}
	return nb;
}



/*
Titre : 	nouvelEmprunt
Finalité :  Créer un nouvel emprunt.
Paramètres :tabJeux -Tableau de pointeurs statique de type Jeux
        	lAd -Liste chainée des adhérents de type ListeAD
        	lEmp -Liste chaînée des emprunts de type ListeEmp
        	nom -Chaîne de caractères
        	prenom -Chaîne de caractères
        	pos -int
        	nbEmp -pointeur sur un entier
Variable :  Emprunt e -Maillon de type Emprunt
*/
ListeEmp nouvelEmprunt(int pos, Jeux *tabJeux[], ListeAD lAd, char nom[], char prenom[], ListeEmp lEmp, int *nbEmp){
	Emprunt e;

	if(*nbEmp/100>=1){
    	char Emp[3]={"EM"};
    	char nbr[4]="";
    	sprintf(nbr, "%d", *nbEmp+1);
    	strcat(Emp, nbr);
    	strcpy(e.idemp, Emp);
	}
	else if(*nbEmp/10>=1){
    	char Emp[4]={"EM0"};
    	char nbr[3]="";
    	sprintf(nbr, "%d", *nbEmp+1);
    	strcat(Emp, nbr);
    	strcpy(e.idemp, Emp);
	}
	else{
    	char Emp[5]={"EM00"};
    	char nbr[2]="";
    	sprintf(nbr, "%d", *nbEmp+1);
    	strcat(Emp, nbr);
    	strcpy(e.idemp, Emp); 	 
	}

	strcpy(e.idjeux, tabJeux[pos]->idjeux);	 

	while(strcmp(lAd->a.nom, nom) != 0 && strcmp(lAd->a.prenom, prenom) != 0)
    	lAd=lAd->suiv;
	strcpy(e.idad, lAd->a.idad);

	char date[64];
	time_t timestamp = time(NULL);
	strftime(date, sizeof(date), "%d/%m/%Y", localtime(&timestamp));

	strcpy(e.dateEmp, date);

	lEmp=ajouterEmprunt(lEmp,e);
	(tabJeux[pos]->nb)--;
	(*nbEmp)++;
	return lEmp;
}



/*
Titre : 	nouvelleReservation
Finalité :  Créer une nouvelle réservation.
Paramètres :tabJeux -Tableau de pointeurs statique de type Jeux
        	lAd -Liste chainée des adhérents de type ListeAD
        	lResa -Liste chaînée des réservations de type ListeResa
        	nom -Chaîne de caractères
        	prenom -Chaîne de caractères
        	pos -int  
        	nbResa -pointeur sur un entier
Variable :  Reservation r -Maillon de type Reservation
*/
ListeResa nouvelleReservation(int pos, Jeux *tabJeux[], ListeAD lAd, char nom[], char prenom[], ListeResa lResa, int *nbResa){
	Reservation r;

	if(*nbResa/100>=1){
    	char Resa[3]={"RE"};
    	char nbr[4]="";
    	sprintf(nbr, "%d", *nbResa+1);
    	strcat(Resa, nbr);
    	strcpy(r.idresa, Resa);
	}
	else if(*nbResa/10>=1){
    	char Resa[4]={"RE0"};
    	char nbr[3]="";
    	sprintf(nbr, "%d", *nbResa+1);
    	strcat(Resa, nbr);
    	strcpy(r.idresa, Resa);
	}
	else{
    	char Resa[5]={"RE00"};
    	char nbr[2]="";
    	sprintf(nbr, "%d", *nbResa+1);
    	strcat(Resa, nbr);
    	strcpy(r.idresa, Resa); 	 
	}

	while(strcmp(lAd->a.nom, nom) != 0 && strcmp(lAd->a.prenom, prenom) != 0)
    	lAd=lAd->suiv;
	strcpy(r.idad, lAd->a.idad);

	strcpy(r.idjeux, tabJeux[pos]->idjeux);	 

	char date[64];
	time_t timestamp = time(NULL);
	strftime(date, sizeof(date), "%d/%m/%Y", localtime(&timestamp));

	strcpy(r.dateResa, date);

	lResa=ajouterReservation(lResa,r);
	(*nbResa)++;
	return lResa;
}



/*
Titre :     annulationReservation
Finalité :  Récolter et vérifier les informations pour annuler une réservation.
Paramètre :
Variables : nom -Chaîne de caractères
            prenom -Chaîne de caractères
            jeu -Chaîne de caractères
            choixM -int
            trouve -int
            pos -int
*/
ListeResa annulationReservation(Jeux *tabJeux[], int nb, ListeAD lAd, ListeResa lResa){
	char c='n', genre;
	char nom[20], prenom[20], jeu[20];
	int choixM=5, trouve, pos;

	while(c!='o'){
    	system("clear");
    	AffichageMenuPrincipal();
    	printf("    Votre choix : 5\n");

    	printf("\n\n\tVeuillez renseigner votre nom : ");
    	fgets(nom,20,stdin);
    	nom[strlen(nom)-1]='\0';
    	printf("\n\tVeuillez renseigner votre prénom : ");
    	fgets(prenom,20,stdin);
    	prenom[strlen(prenom)-1]='\0';
    	printf("\n\n    Validez vous ces informations ?");
    	printf("\n\n\to/n (Oui ou Non) : ");
    	scanf("%c%*c",&c);

    	ListeAD rechAd=rechercheAdherent(lAd,nom,prenom);

    	if(c=='o' && !rechAd){
        	printf("\n\n\tLes inforamtions que vous avez communiqué sont incorrectes !");
        	printf("\n\tVeuillez entrer des informations exactes.");
        	printf("\n\n    Tapez une touche pour recommencer...");
        	c=getchar();
    	}

	reAffichage(nom,prenom,choixM);

	printf("\n\n\n\tVotre réservation porte sur le jeu : ");
	fgets(jeu,20,stdin);
	jeu[strlen(jeu)-1]='\0';

	pos=RechercheJeux(tabJeux,nb,jeu,&trouve);

	while(trouve==-1){
    	reAffichage(nom,prenom,choixM);

    	printf("\n\n\n\tLe jeu \"%s\" n'existe pas !",jeu);
    	printf("\n\n    Nom correct du jeu : ");
    	fgets(jeu,20,stdin);
    	jeu[strlen(jeu)-1]='\0';
   	 
    	pos=RechercheJeux(tabJeux,nb,jeu,&trouve);
    	}                  
	}
    ListeResa rech=rechercheResaAnnulation(lResa,lAd,nom,prenom,tabJeux,pos);

    if(rech==NULL)
        printf("\n\n    Vous n'avez pas de réservation pour ce jeux.\n");
    else{
        lResa=suppResa(lResa,rech);
        printf("\n\n    Votre réservation a été annulée.\n");
    }
	printf("\n\n    Tapez une touche pour revenir au menu...");
	c=getchar();
    return lResa;
}



/*
Titre :     recherResaAnnulation
Finalité :  Recherche une réservation selon plusieurs critères.
Paramètres :tabJeux -Tableau de pointeur statique de type Jeux
            lAd -Liste chainée des adhérents de type ListeAD
            lResa -Liste chaînée des réservations de type ListeResa
            nom -Chaîne de caractères
            prenom -Chaîne de caractères
            pos -int
Variable :  recherAd -Maillon de type ListeAD
*/
ListeResa rechercheResaAnnulation(ListeResa lResa, ListeAD lAd, char nom[], char prenom[], Jeux *tabjeux[], int pos){
    if(lResa==NULL)return NULL;
    ListeAD recherAd=rechercheAdherentID(lAd,lResa->r.idad);
    if(strcmp(recherAd->a.nom, nom)==0 && strcmp(recherAd->a.prenom, prenom)==0 && strcmp(tabjeux[pos]->idjeux, lResa->r.idjeux)==0)return lResa;
    return rechercheResaAnnulation(lResa->suiv,lAd,nom,prenom,tabjeux,pos);
}

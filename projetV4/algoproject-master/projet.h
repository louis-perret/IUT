#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void Projet(void);



/*--Structure--*/

//--Stucture étudiant--//
typedef struct
{
	char idjeux[6];
	char typejeux[13];
	int nb;
	char nomjeux[20];
}Jeux;
//--Stucture adhérent--//
typedef struct
{
	char idad[6];
	char civil[4];
	char nom[30];
	char prenom[30];
	char date[11];
}Adherent;

//--Structure du maillon et de liste sur la structure Adherent--//
typedef struct maillonAD
{
	Adherent a;
	struct maillonAD* suiv;
} MaillonAD, *ListeAD;

//--Stucture emprunt--//
typedef struct
{
	char idemp[6];
	char idjeux[6];
	char idad[6];
	char dateEmp[11];
}Emprunt;

//--Structure du maillon et de liste sur la structure Emprunt--//
typedef struct maillonEmp
{
	Emprunt e;
	struct maillonEmp* suiv;
} MaillonEmp, *ListeEmp;

//--Stucture reservation--//

typedef struct
{
	char idresa[6];
	char idad[6];
	char idjeux[6];
	char dateResa[11];
}Reservation;

//--Structure du maillon et de liste sur la structure Reservation--//
typedef struct maillonResa
{
	Reservation r;
	struct maillonResa* suiv;
} MaillonResa, *ListeResa;

//--Définition du type booleen--//
typedef enum{faux,vrai} Booleen;

/*--Prototype des fonctions--*/

// Partie de Louis //

// chargement du fichier jeux.txt
Jeux lireJeux(FILE *flot);
int chargementJeux(Jeux *tabJeux[], char nomFichier[], int taillemax);
void affichageJeux(Jeux *tabJeux[], int nb);
int sauvegardeJeux(Jeux *tabJeux[], char nomFichier[], int nb);

// chargement du fichier adherents.txt
Adherent lireAD(FILE* flot);
ListeAD listevide(void);
Booleen videAD(ListeAD lAd);
ListeAD insertionEnTete(ListeAD lAd, Adherent ad);
ListeAD ajouterAdherent(ListeAD lAd, Adherent ad);
ListeAD chargerListeAdherent(ListeAD lAd, char nomFichier[],int *nbAd);
void affichageListeAdherent(ListeAD lAd);
int sauvegardeAdherents(ListeAD lAd, char nomFichierAd[]);

// chargement du fichier emprunts.txt
Emprunt lireEmp(FILE* flot);
ListeEmp listevideEmp(void);
Booleen videEmp(ListeEmp lEmp);
ListeEmp insertionEnTeteEmp(ListeEmp lEmp, Emprunt emp);
ListeEmp ajouterEmprunt(ListeEmp lEmp, Emprunt emp);
ListeEmp chargerListeEmprunt(ListeEmp lEmp, char nomFichier[],int *nbEmp);
void affichageListeEmprunt(ListeEmp lEmp);
int sauvegardeEmprunts(ListeEmp lEmp, char nomFichier[]);

// chargement du fichier reservations.txt
Reservation lireResa(FILE* flot);
ListeResa listevideResa(void);
Booleen videResa(ListeResa lResa);
ListeResa insertionEnTeteResa(ListeResa lResa, Reservation resa);
ListeResa ajouterReservation(ListeResa lResa, Reservation Resa);
ListeResa chargerListeReservation(ListeResa lResa, char nomFichier[],int *nbResa);
void affichageListeReservation(ListeResa lResa);
int sauvegardeReservation(ListeResa lResa, char nomFichier[]);

// affichage des réservations pour un jeu donné
int RechercheJeux(Jeux *tabJeux[], int nb, char jeux[], int *trouve);
void affichageReservationJeux(Jeux *tabJeux[], int nb, ListeResa lResa);





// Valentin's part 
// Dans l'ordre : Sauvegarde globale, Menus, Affichages(1 et 2), Création(adhérents, emprunts, réservations), Annulation réservation.


// Fonction de sauvegarde générale (nécessite celles de Louis)
void sauvegardeGlobale(Jeux *tabJeux[], char nomFichierJeux[], int nb, ListeAD lAd, char nomFichierAd[], ListeEmp lEmp, char nomFichierEmp[], ListeResa lResa, char nomFichierRe[]);
void quitterSansSauvegarder(Jeux *tabJeux[], char nomFichierJeux[], int nb, ListeAD lAd, char nomFichierAd[], ListeEmp lEmp, char nomFichierEmp[], ListeResa lResa, char nomFichierRe[]);

// Menu (Principal, affichage et choix)
void MenuPrincipal();
void MenuAffichage(Jeux *tabJeux[], char nomFichierJeux[], int nb, ListeAD lAd, char nomFichierAd[], ListeEmp lEmp, char nomFichierEmp[], ListeResa lResa, char nomFichierRe[]);

void AffichageMenuPrincipal(void);
void AffichageMenuAffichage(void);

char choixMenuPrincipal(void);
char choixMenuAffichage(void);


// Affichage des emprunts en cours ainsi que des jeux disponibles (suposés triés)
void affichageEmpruntEnCours(Jeux *tabJeux[], int nb, ListeEmp lEmp, ListeAD lAd);
void affichageIdentite(ListeEmp lEmp, ListeAD lAd);
void affichageListeJeuxDisponibles(Jeux *tabJeux[], int nb);


// Bouche trou en attendant de tout compléter
void Modifier(void);	// Inutile


// Création adhérent/emprunt/réservation
ListeAD creationNouvelAdherent(ListeAD lAd, int *nbAd);
ListeEmp creationNouvelEmprunt(Jeux *tabJeux[], int nb, ListeAD lAd, ListeEmp lEmp, int *nbEmp);
ListeResa creationNouvelleReservation(Jeux *tabJeux[], int nb, ListeAD lAd, ListeEmp lEmp, ListeResa lResa, int *nbResa);

ListeAD nouvelAdherent(char nom[] , char prenom[] , char genre, ListeAD lAd, int *nbAd);
ListeEmp nouvelEmprunt(int pos, Jeux *tabJeux[], ListeAD lAd, char nom[],char prenom[], ListeEmp lEmp, int *nbEmp);
ListeResa nouvelleReservation(int pos, Jeux *tabJeux[], ListeAD lAd, char nom[], char prenom[], ListeResa lResa, int *nbResa);

// Fonctions nécessaires à la création (adhérent/emprunt/réservation)
int nombreEmprunts(ListeAD lAd, char nom[], char prenom[], ListeEmp lEmp);
void reAffichage(char nom[],char prenom[], int choixM);


// Annulation d'une réservation
ListeResa annulationReservation(Jeux *tabJeux[], int nb, ListeAD lAd, ListeResa lResa);
ListeResa rechercheResaAnnulation(ListeResa lResa, ListeAD lAd, char nom[], char prenom[], Jeux *tabjeux[], int pos);





// Matteo's part
ListeAD rechercheAdherent(ListeAD lAd,char nom[],char prenom[]);
ListeAD rechercheAdherentID(ListeAD lAd,char id[]);

ListeEmp rechercheEmprunt(ListeEmp lEp,char idJeux[],char idAd[]);
ListeEmp suppEmprunt(ListeEmp lEmp, ListeEmp emprunt);

ListeResa rechercheResa(ListeResa lResa,char idJeux[]);
ListeResa suppResa(ListeResa lEmp, ListeResa emprunt);
ListeResa verifResa(ListeAD lAd,ListeEmp lEmp, ListeResa lResa, Jeux *tabJeux[], char idJeux[],int i,int *nbEmp);

ListeResa retourJeux(Jeux *tabJeux[], int nb,ListeAD lAd,ListeEmp lEmp, ListeResa lResa,int *nbEmp);

void echange(Jeux *tabJeux[], int i,int j);
void triejeux(Jeux *tabJeux[], int nb);

#include <stdio.h>
#include <stdbool.h>



// Structure pour représenter une date
typedef struct {
    int jour;
    int mois;
    int annee;
} Date;

// Structure pour représenter un film
typedef struct {
    char titre[100];
    Date dateSortie;
    int identificateur;
    float budgetProduction;
} Film;

// Tableau de films et nombre maximum de films
Film TFilm[100];
int nbFilms = 0;

// Procédure pour ajouter un film dans le tableau TFilm
void Ajouter() {
    // Vérifier si le tableau est plein
    if (nbFilms >= 100) {
        printf("Le tableau est plein, impossible d'ajouter plus de films.\n");
        return;
    }

    // Saisie des informations sur le film
    printf("Entrez le titre du film : ");
    scanf("%s", TFilm[nbFilms].titre);
    printf("Entrez la date de sortie (jour mois annee) : ");
    scanf("%d %d %d", &TFilm[nbFilms].dateSortie.jour, &TFilm[nbFilms].dateSortie.mois, &TFilm[nbFilms].dateSortie.annee);
    printf("Entrez l'identificateur du film : ");
    scanf("%d", &TFilm[nbFilms].identificateur);
    printf("Entrez le budget de production : ");
    scanf("%f", &TFilm[nbFilms].budgetProduction);

    // Incrémenter le nombre de films
    nbFilms++;
}

// Procédure pour modifier un film dans le tableau TFilm
void Modifier() {
    int id;
    printf("Entrez l'identificateur du film a modifier : ");
    scanf("%d", &id);

    int i;
    bool found = false;
    for (i = 0; i < nbFilms; i++) {
        if (TFilm[i].identificateur == id) {
            printf("Entrez le nouveau budget de production : ");
            scanf("%f", &TFilm[i].budgetProduction);

            printf("Entrez la nouvelle date de sortie (jour mois annee) : ");
            scanf("%d %d %d", &TFilm[i].dateSortie.jour, &TFilm[i].dateSortie.mois, &TFilm[i].dateSortie.annee);

            found = true;
            break;
        }
    }

    if (!found) {
        printf("Aucun film ne correspond a l'identificateur saisi.\n");
    }
}

// Procédure pour supprimer un film depuis le tableau TFilm
void Supprimer() {
    int id;
    printf("Entrez l'identificateur du film a supprimer : ");
    scanf("%d", &id);

    int i, j;
    bool found = false;
    for (i = 0; i < nbFilms; i++) {
        if (TFilm[i].identificateur == id) {
            // Décaler les films suivants vers la gauche
            for (j = i; j < nbFilms - 1; j++) {
                TFilm[j] = TFilm[j + 1];
            }
            nbFilms--;
            found = true;
            break;
        }
    }

    if (!found) {
        printf("Aucun film ne correspond a l'identificateur saisi.\n");
    }
}

// Fonction récursive pour rechercher un film dans le tableau TFilm
int Rechercher(int id, int index) {
    if (index >= nbFilms) {
        return -1;
    }

    if (TFilm[index].identificateur == id) {
        return index;
    }

    return Rechercher(id, index + 1);
}

// Procédure pour lister les films dont la date est supérieure à une date saisie
void Lister() {
    int jour, mois, annee;
    printf("Entrez la date de reference (jour mois annee) : ");
    scanf("%d %d %d", &jour, &mois, &annee);

    // Vérifier si la date saisie est valide
    if (jour < 1 || jour > 31 || mois < 1 || mois > 12 || annee < 1920 || annee > 2120) {
        printf("Date saisie invalide.\n");
        return;
    }

    printf("Films sortis apres la date %d/%d/%d :\n", jour, mois, annee);
    for (int i = 0; i < nbFilms; i++) {
        if (TFilm[i].dateSortie.annee > annee || 
            (TFilm[i].dateSortie.annee == annee && TFilm[i].dateSortie.mois > mois) ||
            (TFilm[i].dateSortie.annee == annee && TFilm[i].dateSortie.mois == mois && TFilm[i].dateSortie.jour > jour)) {
            printf("- Titre : %s, Date de sortie : %d/%d/%d, Budget de production : %.2f\n", 
                TFilm[i].titre, TFilm[i].dateSortie.jour, TFilm[i].dateSortie.mois, TFilm[i].dateSortie.annee, TFilm[i].budgetProduction);
        }
    }
}

// Programme principal
int main() {
    int choix;
    do {
        // Affichage du menu
        printf("\nMenu\n");
        printf("1. Ajouter un nouveau film : \n");
        printf("2. Modifier un film : \n");
        printf("3. Supprimer un film : \n");
        printf("4. Rechercher un film : \n");
        printf("5. Lister les films existants : \n");
        printf("6. Quitter Programme \n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                Ajouter();
                break;
            case 2:
                Modifier();
                break;
            case 3:
                Supprimer();
                break;
            case 4: {
                int id;
                printf("Entrez l'identificateur du film a rechercher : ");
                scanf("%d", &id);
                int position = Rechercher(id, 0);
                if (position == -1) {
                    printf("Aucun film ne correspond a l'identificateur saisi.\n");
                } else {
                    printf("Le film est a la position %d dans le tableau.\n", position);
                }
                break;
            }
            case 5:
                Lister();
                break;
            case 6:
                printf("Programme termine.\n");
                break;
            default:
                printf("Choix invalide. Veuillez saisir un nombre entre 1 et 6.\n");
        }
    } while (choix != 6);

    return 0;
}

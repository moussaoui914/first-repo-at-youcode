#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ANIMAUX 200
#define TAILLE_NOM 50
#define TAILLE_HABITAT 30
#define TAILLE_ESPECE 50
#define TAILLE_DATE 11

typedef struct Animal{
    int id;
    char nom[TAILLE_NOM];
    char espece[TAILLE_ESPECE];
    int age;
    char habitat[TAILLE_HABITAT];
    float poids;
    char typeAlimentation[20];
    char dateArrivee[TAILLE_DATE];
    int estOccupe;
} Animal;

Animal zoo[MAX_ANIMAUX];
int nbAnimaux = 0;
int idCourant = 1;

void viderBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void getDateActuelle(char* date){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}

void determinerTypeAlimentation(const char* espece, char* typeAlim) {
    if (strcmp(espece, "Lion") == 0 || strcmp(espece, "Tigre") == 0 || 
        strcmp(espece, "Chien sauvage") == 0 || strcmp(espece, "Serpent") == 0) {
        strcpy(typeAlim, "Carnivore");
    } else if (strcmp(espece, "Zebre") == 0 || strcmp(espece, "Girafe") == 0 || 
               strcmp(espece, "Elephant") == 0 || strcmp(espece, "Phacochere") == 0 ||
               strcmp(espece, "Hippopotame") == 0 || strcmp(espece, "Tortue") == 0) {
        strcpy(typeAlim, "Herbivore");
    } else {
        strcpy(typeAlim, "Omnivore");
    }
}

int verifierAgeCritique(Animal a) {
    int ageCritique = 0;
    
    if (strcmp(a.espece, "Lion") == 0 || strcmp(a.espece, "Tigre") == 0) {
        ageCritique = 20;
    } else if (strcmp(a.espece, "Elephant") == 0) {
        ageCritique = 50;
    } else if (strcmp(a.espece, "Ours") == 0) {
        ageCritique = 30;
    } else if (strcmp(a.espece, "Girafe") == 0) {
        ageCritique = 25;
    } else {
        ageCritique = 15;
    }
    
    if (a.age > ageCritique) {
        printf("ALERTE: %s (%s) a depasse l'age critique de %d ans!\n", 
               a.nom, a.espece, ageCritique);
        return 1;
    }
    return 0;
}

void initialiserAnimaux() {
    Animal a[] = {
        {1, "Simba", "Lion", 5, "Savane", 190.5, "", "2020-01-15", 1},
        {2, "Nala", "Lion", 4, "Savane", 175, "", "2021-03-20", 1},
        {3, "ShereKhan", "Tigre", 8, "Jungle", 220.3, "", "2017-11-10", 1},
        {4, "Baloo", "Ours", 12, "Foret", 310, "", "2013-05-25", 1},
        {5, "Raja", "Elephant", 15, "Savane", 540.7, "", "2010-08-30", 1},
        {6, "Marty", "Zebre", 6, "Savane", 300.2, "", "2019-02-14", 1},
        {7, "Gloria", "Hippopotame", 10, "Riviere", 450, "", "2015-07-08", 1},
        {8, "Alex", "Lion", 7, "Savane", 200, "", "2018-09-12", 1},
        {9, "Julien", "Lemurien", 3, "Jungle", 12.5, "", "2022-04-05", 1},
        {10, "Melman", "Girafe", 9, "Savane", 390.8, "", "2016-06-18", 1},
        {11, "Timon", "Suricate", 2, "Desert", 1.2, "", "2023-01-22", 1},
        {12, "Pumbaa", "Phacochere", 5, "Savane", 120, "", "2020-10-15", 1},
        {13, "Scar", "Lion", 11, "Savane", 210.4, "", "2014-12-03", 1},
        {14, "Kaa", "Serpent", 6, "Jungle", 45, "", "2019-03-28", 1},
        {15, "Iko", "Perroquet", 4, "Jungle", 2.1, "", "2021-07-19", 1},
        {16, "Dumbo", "Elephant", 3, "Savane", 320, "", "2022-11-11", 1},
        {17, "Kiki", "Chien sauvage", 7, "Savane", 25, "", "2018-08-07", 1},
        {18, "Donatello", "Tortue", 40, "Riviere", 90.5, "", "1985-09-15", 1},
        {19, "Polly", "Oiseau", 5, "Jungle", 1.5, "", "2020-05-30", 1},
        {20, "Kong", "Gorille", 13, "Jungle", 180, "", "2012-04-22", 1}
    };

    int total = sizeof(a) / sizeof(a[0]);
    for (int i = 0; i < total && nbAnimaux < MAX_ANIMAUX; i++) {
        determinerTypeAlimentation(a[i].espece, a[i].typeAlimentation);
        zoo[nbAnimaux++] = a[i];
        idCourant = a[i].id + 1;
    }
    printf("%d animaux initialises avec succes!\n", total);
}

void sauvegarderDonnees() {
    FILE *fichier = fopen("C:\\Users\\HP\\Desktop\\zoo_data.txt", "w");
    if (fichier == NULL) {
        printf("Erreur lors de la creation du fichier de sauvegarde.\n");
        return;
    }
    
    int animauxSauvegardes = 0;
    for (int i = 0; i < nbAnimaux; i++) {
        if (zoo[i].estOccupe) {
            fprintf(fichier, "%d;%s;%s;%d;%s;%.2f;%s;%s\n",
                   zoo[i].id, zoo[i].nom, zoo[i].espece, zoo[i].age,
                   zoo[i].habitat, zoo[i].poids, zoo[i].typeAlimentation,
                   zoo[i].dateArrivee);
            animauxSauvegardes++;
        }
    }
    
    fflush(fichier);
    fclose(fichier);
    
    printf("SUCCES: %d animaux sauvegardes sur le Bureau!\n", animauxSauvegardes);
    printf("Ouvrez le fichier zoo_data.txt avec le Bloc Notes pour voir les donnees.\n");
}

void ajouterAnimal() {
    if (nbAnimaux >= MAX_ANIMAUX) {
        printf("Le zoo est plein! Impossible d'ajouter plus d'animaux.\n");
        return;
    }
    
    int n;
    printf("Combien d'animaux voulez-vous ajouter ? ");
    scanf("%d", &n);
    viderBuffer();

    if (n <= 0) {
        printf("Nombre invalide.\n");
        return;
    }

    for (int i = 0; i < n && nbAnimaux < MAX_ANIMAUX; i++) {
        Animal a;
        a.id = idCourant++;
        a.estOccupe = 1;

        printf("\n--- Animal %d ---\n", i + 1);
        
        printf("Nom : ");
        fgets(a.nom, TAILLE_NOM, stdin);
        a.nom[strcspn(a.nom, "\n")] = 0;

        printf("Espece : ");
        fgets(a.espece, TAILLE_ESPECE, stdin);
        a.espece[strcspn(a.espece, "\n")] = 0;

        printf("Age : ");
        scanf("%d", &a.age);
        viderBuffer();

        printf("Habitat : ");
        fgets(a.habitat, TAILLE_HABITAT, stdin);
        a.habitat[strcspn(a.habitat, "\n")] = 0;

        printf("Poids (kg) : ");
        scanf("%f", &a.poids);
        viderBuffer();

        determinerTypeAlimentation(a.espece, a.typeAlimentation);
        getDateActuelle(a.dateArrivee);

        zoo[nbAnimaux++] = a;
        printf("Animal '%s' ajoute avec succes (ID: %d)!\n", a.nom, a.id);
        verifierAgeCritique(a);
    }
    
    sauvegarderDonnees();
}

void afficherAnimal(Animal a) {
    if (!a.estOccupe) return;
    printf("ID: %d | Nom: %-12s | Espece: %-15s | Age: %2d | Habitat: %-10s | Poids: %6.1f kg | Type: %-10s | Arrivee: %s\n",
           a.id, a.nom, a.espece, a.age, a.habitat, a.poids, a.typeAlimentation, a.dateArrivee);
}

void afficherTousAnimaux() {
    printf("\n=== LISTE COMPLETE DES ANIMAUX (%d animaux) ===\n", nbAnimaux);
    for (int i = 0; i < nbAnimaux; i++) {
        if (zoo[i].estOccupe)
            afficherAnimal(zoo[i]);
    }
}

void trierParNomBulle(Animal arr[], int n) {
    int i, j;
    Animal temp;
    
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (strcmp(arr[j].nom, arr[j+1].nom) > 0) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void afficherTriesParNom() {
    Animal copie[MAX_ANIMAUX];
    int count = 0;
    
    for (int i = 0; i < nbAnimaux; i++) {   
        if (zoo[i].estOccupe) {
            copie[count] = zoo[i];
            count++;
        }
    }
    
    trierParNomBulle(copie, count);
    
    printf("\n=== ANIMAUX TRIES PAR NOM (TRI A BULLES) ===\n");
    for (int i = 0; i < count; i++) {
        afficherAnimal(copie[i]);
    }
}

void trierParAgeBulle(Animal arr[], int n) {
    int i, j;
    Animal temp;
    
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j].age > arr[j+1].age) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void afficherTriesParAge() {
    Animal copie[MAX_ANIMAUX];
    int count = 0;
    
    for (int i = 0; i < nbAnimaux; i++) {
        if (zoo[i].estOccupe) {
            copie[count] = zoo[i];
            count++;
        }
    }
    
    trierParAgeBulle(copie, count);
    
    printf("\n=== ANIMAUX TRIES PAR AGE (TRI A BULLES) ===\n");
    for (int i = 0; i < count; i++) {
        afficherAnimal(copie[i]);
    }
}

void trierParEspeceBulle(Animal arr[], int n) {
    int i, j;
    Animal temp;
    
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (strcmp(arr[j].espece, arr[j+1].espece) > 0) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void afficherTriesParEspece() {
    Animal copie[MAX_ANIMAUX];
    int count = 0;
    
    for (int i = 0; i < nbAnimaux; i++) {
        if (zoo[i].estOccupe) {
            copie[count] = zoo[i];
            count++;
        }
    }
    
    trierParEspeceBulle(copie, count);
    
    printf("\n=== ANIMAUX TRIES PAR ESPECE (TRI A BULLES) ===\n");
    for (int i = 0; i < count; i++) {
        afficherAnimal(copie[i]);
    }
}

void trierParHabitatBulle(Animal arr[], int n) {
    int i, j;
    Animal temp;
    
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (strcmp(arr[j].habitat, arr[j+1].habitat) > 0) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void afficherTriesParHabitat() {
    Animal copie[MAX_ANIMAUX];
    int count = 0;
    
    for (int i = 0; i < nbAnimaux; i++) {
        if (zoo[i].estOccupe) {
            copie[count] = zoo[i];
            count++;
        }
    }
    
    trierParHabitatBulle(copie, count);
    
    printf("\n=== ANIMAUX TRIES PAR HABITAT (TRI A BULLES) ===\n");
    for (int i = 0; i < count; i++) {
        afficherAnimal(copie[i]);
    }
}

void afficherParHabitat() {
    char habitat[TAILLE_HABITAT];
    printf("Entrez l'habitat a filtrer : ");
    fgets(habitat, TAILLE_HABITAT, stdin);
    habitat[strcspn(habitat, "\n")] = 0;

    printf("\n=== ANIMAUX DE L'HABITAT '%s' ===\n", habitat);
    int trouve = 0;
    for (int i = 0; i < nbAnimaux; i++) {
        if (zoo[i].estOccupe && strcmp(zoo[i].habitat, habitat) == 0) {
            afficherAnimal(zoo[i]);
            trouve = 1;
        }
    }
    if (!trouve) printf("Aucun animal trouve dans cet habitat.\n");
}

void modifierAnimal() {
    int id;
    printf("Entrez l'ID de l'animal a modifier : ");
    scanf("%d", &id);
    viderBuffer();

    for (int i = 0; i < nbAnimaux; i++) {
        if (zoo[i].id == id && zoo[i].estOccupe) {
            printf("\nAnimal trouve : ");
            afficherAnimal(zoo[i]);
            
            printf("\nQue voulez-vous modifier ?\n");
            printf("1. Modifier l'habitat\n");
            printf("2. Modifier l'age\n");
            printf("3. Modifier le poids\n");
            printf("4. Deplacer vers un autre habitat\n");
            printf("Choix : ");
            
            int choix;
            scanf("%d", &choix);
            viderBuffer();

            switch (choix) {
                case 1:
                    printf("Nouvel habitat : ");
                    fgets(zoo[i].habitat, TAILLE_HABITAT, stdin);
                    zoo[i].habitat[strcspn(zoo[i].habitat, "\n")] = 0;
                    printf("Habitat mis a jour.\n");
                    break;
                case 2:
                    printf("Nouvel age : ");
                    scanf("%d", &zoo[i].age);
                    viderBuffer();
                    verifierAgeCritique(zoo[i]);
                    printf("Age mis a jour.\n");
                    break;
                case 3:
                    printf("Nouveau poids : ");
                    scanf("%f", &zoo[i].poids);
                    viderBuffer();
                    printf("Poids mis a jour.\n");
                    break;
                case 4:
                    printf("Nouvel habitat : ");
                    fgets(zoo[i].habitat, TAILLE_HABITAT, stdin);
                    zoo[i].habitat[strcspn(zoo[i].habitat, "\n")] = 0;
                    printf("Animal deplace vers '%s'.\n", zoo[i].habitat);
                    break;
                default:
                    printf("Choix invalide.\n");
                    return;
            }
            
            sauvegarderDonnees();
            return;
        }
    }

    printf("Animal non trouve.\n");
}

void supprimerAnimal() {
    int id;
    printf("Entrez l'ID de l'animal a supprimer : ");
    scanf("%d", &id);
    viderBuffer();

    for (int i = 0; i < nbAnimaux; i++) {
        if (zoo[i].id == id && zoo[i].estOccupe) {
            printf("Etes-vous sûr de vouloir supprimer %s (ID: %d) ? (o/n) : ", zoo[i].nom, id);
            char confirmation;
            scanf("%c", &confirmation);
            viderBuffer();
            
            if (confirmation == 'o' || confirmation == 'O') {
                zoo[i].estOccupe = 0;
                printf("Animal supprime.\n");
                sauvegarderDonnees();
            } else {
                printf("Suppression annulee.\n");
            }
            return;
        }
    }

    printf("Animal non trouve.\n");
}

void rechercherParId() {
    int id;
    printf("Entrez l'ID a rechercher : ");
    scanf("%d", &id);
    viderBuffer();

    for (int i = 0; i < nbAnimaux; i++) {
        if (zoo[i].id == id && zoo[i].estOccupe) {
            printf("\n=== ANIMAL TROUVE ===\n");
            afficherAnimal(zoo[i]);
            return;
        }
    }
    printf("Aucun animal trouve avec l'ID %d.\n", id);
}

void rechercherParNom() {
    char nom[TAILLE_NOM];
    printf("Entrez le nom a rechercher : ");
    fgets(nom, TAILLE_NOM, stdin);
    nom[strcspn(nom, "\n")] = 0;

    printf("\n=== RESULTATS DE LA RECHERCHE POUR '%s' ===\n", nom);
    int trouve = 0;
    for (int i = 0; i < nbAnimaux; i++) {
        if (zoo[i].estOccupe && strstr(zoo[i].nom, nom) != NULL) {
            afficherAnimal(zoo[i]);
            trouve = 1;
        }
    }
    if (!trouve) printf("Aucun animal trouve avec ce nom.\n");
}

void rechercherParEspece() {
    char espece[TAILLE_ESPECE];
    printf("Entrez l'espece a rechercher : ");
    fgets(espece, TAILLE_ESPECE, stdin);
    espece[strcspn(espece, "\n")] = 0;

    printf("\n=== ANIMAUX DE L'ESPECE '%s' ===\n", espece);
    int trouve = 0;
    for (int i = 0; i < nbAnimaux; i++) {
        if (zoo[i].estOccupe && strstr(zoo[i].espece, espece) != NULL) {
            afficherAnimal(zoo[i]);
            trouve = 1;
        }
    }
    if (!trouve) printf("Aucun animal trouve de cette espece.\n");
}

void afficherStatistiques() {
    if (nbAnimaux == 0) {
        printf("Aucun animal dans le zoo.\n");
        return;
    }

    int total = 0;
    int sommeAges = 0;
    int ageMin = 1000, ageMax = 0;
    Animal plusJeune, plusVieux;
    
    char especes[MAX_ANIMAUX][TAILLE_ESPECE];
    int compteurEspeces[MAX_ANIMAUX] = {0};
    int nbEspeces = 0;
  
    for (int i = 0; i < nbAnimaux; i++){
        if (zoo[i].estOccupe) {
            total++;
            sommeAges += zoo[i].age;
            
            if (zoo[i].age < ageMin){
                ageMin = zoo[i].age;
                plusJeune = zoo[i];
            }
            if (zoo[i].age > ageMax){
                ageMax = zoo[i].age;
                plusVieux = zoo[i];
            }
            
            int especeTrouvee = 0;
            for (int j = 0; j < nbEspeces; j++) {
                if (strcmp(especes[j], zoo[i].espece) == 0) {
                    compteurEspeces[j]++;
                    especeTrouvee = 1;
                    break;
                }
            }
            if (!especeTrouvee) {
                strcpy(especes[nbEspeces], zoo[i].espece);
                compteurEspeces[nbEspeces] = 1;
                nbEspeces++;
            }
        }
    }

    float ageMoyen = (float)sommeAges / total;

    printf("\n=== STATISTIQUES DU ZOO ===\n");
    printf("Nombre total d'animaux : %d\n", total);
    printf("Age moyen des animaux : %.1f ans\n", ageMoyen);
    printf("\nPlus jeune animal : %s (%s, %d ans)\n", plusJeune.nom, plusJeune.espece, plusJeune.age);
    printf("Plus vieux animal : %s (%s, %d ans)\n", plusVieux.nom, plusVieux.espece, plusVieux.age);
    
    printf("\n=== REPARTITION PAR ESPECE ===\n");
    for (int i = 0; i < nbEspeces; i++) {
        printf("%-15s : %d animal(s)\n", especes[i], compteurEspeces[i]);
    }
    
    printf("\n=== ALERTES AGE CRITIQUE ===\n");
    int alertes = 0;
    for (int i = 0; i < nbAnimaux; i++) {
        if (zoo[i].estOccupe) {
            if (verifierAgeCritique(zoo[i])) {
                alertes++;
            }
        }
    }
    if (alertes == 0) printf("Aucune alerte d'age critique.\n");
}

void menu() {
    int choix;
    do {
        printf("\n=========================================\n");
        printf("          GESTIONNAIRE DU ZOO\n");
        printf("=========================================\n");
        printf("1. Ajouter un animal\n");
        printf("2. Afficher les animaux\n");
        printf("3. Modifier un animal\n");
        printf("4. Supprimer un animal\n");
        printf("5. Rechercher un animal\n");
        printf("6. Statistiques\n");
        printf("7. Sauvegarder les donnees\n");
        printf("8. Quitter\n");
        printf("=========================================\n");
        printf("Choix : ");
        
        if (scanf("%d", &choix) != 1) {
            printf("Entree invalide.\n");
            viderBuffer();
            continue;
        }
        viderBuffer();

        switch (choix) {
            case 1:
                ajouterAnimal();
                break;
            case 2: {
                int sc;
                printf("\n--- AFFICHAGE ---\n");
                printf("1. Liste complete\n");
                printf("2. Trier par nom (Tri a bulles)\n");
                printf("3. Trier par age (Tri a bulles)\n");
                printf("4. Trier par espece (Tri a bulles)\n");
                printf("5. Trier par habitat (Tri a bulles)\n");
                printf("6. Afficher par habitat\n");
                printf("Choix : ");
                scanf("%d", &sc);
                viderBuffer();

                if (sc == 1) afficherTousAnimaux();
                else if (sc == 2) afficherTriesParNom();
                else if (sc == 3) afficherTriesParAge();
                else if (sc == 4) afficherTriesParEspece();
                else if (sc == 5) afficherTriesParHabitat();
                else if (sc == 6) afficherParHabitat();
                else printf("Choix invalide\n");
                break;
            }
            case 3:
                modifierAnimal();
                break;
            case 4:
                supprimerAnimal();
                break;
            case 5: {
                int rc;
                printf("\n--- RECHERCHE ---\n");
                printf("1. Par ID\n");
                printf("2. Par nom\n");
                printf("3. Par espece\n");
                printf("Choix : ");
                scanf("%d", &rc);
                viderBuffer();

                if (rc == 1) rechercherParId();
                else if (rc == 2) rechercherParNom();
                else if (rc == 3) rechercherParEspece();
                else printf("Choix invalide\n");
                break;
            }
            case 6:
                afficherStatistiques();
                break;
            case 7:
                sauvegarderDonnees();
                break;
            case 8:
                printf("\nAu revoir ! Merci d'avoir utilise le gestionnaire du zoo.\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
        
        if (choix != 8) {
            printf("\nAppuyez sur Entree pour continuer...");
            getchar();
        }
    } while (choix != 8);
}

int main() {
    printf("Initialisation du gestionnaire de zoo...\n");
    initialiserAnimaux();
    menu();
    return 0;
}
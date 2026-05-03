#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

char* voyelles = "aeiouy";
char* consonnes = "bcdfghjklmnpqrstvwxz";

void afficher_lettres(char* m, char* tab, bool* vus){
    printf(" | ");
    for (int i = 0; i<strlen(tab);i++){
        if (vus[tab[i]-97]){
            printf("\033[32m");
        }
        else{
            printf("\033[00m");
        }
        printf("%c ", tab[i]);
        printf("\033[00m");
    }
}
void affiche(int* jsp, char* mot, bool* vus){
    for(int i = 0; i<5;i++){
        if (jsp[i] == -1){
            printf("\033[31m"); //jaune?
        }
        if (jsp[i] == 0){
            printf("\033[37m"); //rouge
        }
        if (jsp[i] == 1){
            printf("\033[32m"); //vert
        }
        printf("%c", mot[i]);
    }
    printf("\033[00m");
    afficher_lettres(mot, voyelles, vus);
    afficher_lettres(mot, consonnes, vus);
    printf("\n");
    return;
}

bool exist(char* w, FILE* f){
    rewind(f);
    bool res = false;
    for(int i = 0; i<1804; i++){
        char tmp[6];
        fscanf(f, "%s", tmp);
        if (tmp[0] == w[0] && tmp[1] == w[1] && tmp[2] == w[2] && tmp[3] == w[3] && tmp[4] == w[4]){
            res = true;
        }
    }
    return res;
}

void update_v(char* w, bool* vus){
    for (int i = 0; i<5;i++){
        vus[w[i]-97] = true;
    }
}

void play(){
    bool win = false;
    srand(time( NULL ));
    int n = 1804;
    int n_word = rand() % 1804;
    bool vus[26];
    for(int i = 0; i<26;i++){
        vus[i] = false;
    }
    char word[5];
    FILE* f = fopen("words.txt", "r");
    for (int i = 0; i < n_word; i++){
        fscanf(f, "%s", word);
    }

    for (int essai = 0; essai<6;essai++){
        char word_u[6];
        scanf("%s",word_u);
        while (!exist(word_u,f)){
            printf("Ce mot n'existe pas (du moins dans mon dictionnaire)\n");
            scanf("%s",word_u);
        }
        int correct = 0;
        int jsp[5] = {0,0,0,0,0};

        for (int i = 0; i<5;i++){
            if (word_u[i] == word[i]){
                correct++;
                jsp[i] = 1;
            }
            else if (word_u[i] == word[(i+1)%5] || word_u[i] == word[(i+2)%5] || word_u[i] == word[(i+3)%5] || word_u[i] == word[(i+4)%5]){
                jsp[i] = -1;
            }
        }
        update_v(word_u, vus);
        affiche(jsp, word_u, vus);
        if (correct == 5){
            win = true;
            break;
        }
    }
    if (win){
        printf("BRAVOOOOO OOO OO O OO !!!\n");
    }
    else{
        printf("le looser, le mot était ...");
        printf("%c%c%c%c%c \n", word[0], word[1], word[2], word[3], word[4]);
    }
    return;
}

int main() {
    printf("}--- Bienvenue dans le Wordl de la hess ---{\n");
    int nb_game = 0;
    int still = 1;
    while (still){
        nb_game++;
        printf("La partie n°%d commence :\n", nb_game);
        play();
        printf("On fait une autre partie ? (Non : 0 / Oui : Anything else) : ");
        scanf("%d",&still);
    }
    printf("Tu vas me manquer.. On s'amusait bien ensemble pourtant :(\n");
    return EXIT_SUCCESS;
}

/**
 * AUTEUR : FOLLY Yao Hippolyte & amayes DJERMOUNE
*/
#ifndef  __CALC__H__
#define  __CALC__H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define TAILLE_MAX_ENTREE 100

/* Définition des structures de données*/

// Analyse lexicale
// Structure pour les transitions
typedef struct {
    char start;
    char element;
    char end;
} Transition;
// Structure pour l'automate fini déterministe
typedef struct {
    char *alphabet;
    char *states;
    char start_state;
    char *end_states;
    Transition* transitions;
} AFD;

// Analyse sémantique
// Structure de l'analyseur sémantique pour suivre les jetons consommés
typedef struct AnalyseurSyntaxique {
    char* jetons;
    int nJetons;
    int position;
} AnalyseurSyntaxique;

// Structure de l'arbre d'expression pour contenir notre expression
typedef struct ArbreExpression {
    char type;
    double valeur;
    struct ArbreExpression* gauche;
    struct ArbreExpression* droite;
} ArbreExpression;

/* Déclration des fonctions utilisées*/
// Analye lexicale

char verify_digit(char element);

char verify_op(char element);

char do_transition(char current_state, const Transition *t, char item);

char *lexical_analysis(const AFD afd, char *words);

int contans (const char *chaine, char caractere);

// Analyse Syntaxique
// Déclarations importantes de fonctions

char* tokenizer(char*);

ArbreExpression* analyser(AnalyseurSyntaxique*);

double calculer(ArbreExpression*);

void afficherResultat(double resultat);

// Fonctions d'analyse syntaxique auxiliaires
void libererArbreExpression(ArbreExpression*);

ArbreExpression* creerArbreExpression(char, double, ArbreExpression*, ArbreExpression*);

ArbreExpression* analyserExpressionAdditive(AnalyseurSyntaxique* analyseur);

ArbreExpression* analyserExpressionMultiplicative(AnalyseurSyntaxique* analyseur);

ArbreExpression* analyserExpressionAtomique(AnalyseurSyntaxique* analyseur);

ArbreExpression* analyserNombre(AnalyseurSyntaxique* analyseur);

#endif

#include "calc.h"
#define JETONS_VALIDES "+-*/^0123456789.()eE"
#include <math.h>

/* Analyser les jetons en un arbre d'expression basé sur la grammaire */
ArbreExpression* analyser(AnalyseurSyntaxique* analyseur) {
    // Calculer l'expression en commençant par l'analyse des jetons en commençant par la priorité la plus basse
    return analyserExpressionAdditive(analyseur);
}

double calculer(ArbreExpression* expression) {
    if (expression->type == 'n') {
        return expression->valeur;
    }

    double gauche = calculer(expression->gauche);
    double droite = calculer(expression->droite);

    switch (expression->type) {
        case '+':
            return gauche + droite;
        case '-':
            return gauche - droite;
        case '*':
            return gauche * droite;
        case '/':
            return gauche / droite;
        case '^':
            return pow(gauche, droite);
        default:
            return 0.0;
    }
}

void afficherResultat(double resultat) {
    // Afficher le résultat en fonction de son type
    if (resultat == (int)resultat) {
        // Si le résultat est un entier, je l'affiche comme un entier
        printf("%d\n", (int)resultat);
    } else {
        // Sinon, je l'affiche comme un nombre à virgule flottante
        printf("%g\n", resultat);
    }
}

ArbreExpression* analyserExpressionAdditive(AnalyseurSyntaxique* analyseur) {
    // Une expression additive est composée d'abord d'une expression multiplicative
    ArbreExpression* expression = analyserExpressionMultiplicative(analyseur);

    // Après l'expression multiplicative, une expression additive peut trouver 0 ou plusieurs (+ ou -)
    while (analyseur->position < analyseur->nJetons &&
           (analyseur->jetons[analyseur->position] == '+' || analyseur->jetons[analyseur->position] == '-')) {
        // Définir le type d'expression comme une addition ou une soustraction
        char type = analyseur->jetons[analyseur->position];

        // Consommer le jeton d'addition ou de soustraction
        analyseur->position++;

        // Analyser une expression multiplicative qui doit venir immédiatement après (+ ou -)
        ArbreExpression* expressionDroite = analyserExpressionMultiplicative(analyseur);

        // Créer une nouvelle expression avec ...
        expression = creerArbreExpression(type, 0.0, expression, expressionDroite);
    }

    return expression;
}

ArbreExpression* analyserExpressionMultiplicative(AnalyseurSyntaxique* analyseur) {
    // Une expression multiplicative est composée d'abord d'une expression atomique
    ArbreExpression* expression = analyserExpressionAtomique(analyseur);

    // Une expression multiplicative peut trouver 0 ou plusieurs (* ou /)
    while (analyseur->position < analyseur->nJetons &&
           (analyseur->jetons[analyseur->position] == '*' || analyseur->jetons[analyseur->position] == '/')) {
        // Définir le type d'expression comme une multiplication ou une division
        char type = analyseur->jetons[analyseur->position];

        // Consommer le jeton de multiplication ou de division
        analyseur->position++;

        // Analyser une expression atomique qui doit venir immédiatement après (* ou /)
        ArbreExpression* expressionDroite = analyserExpressionAtomique(analyseur);

        // Créer une nouvelle expression avec ...
        expression = creerArbreExpression(type, 0.0, expression, expressionDroite);
    }

    return expression;
}

ArbreExpression* analyserExpressionAtomique(AnalyseurSyntaxique* analyseur) {
    // Si nous trouvons des parenthèses, nous lisons une expression additive comme une expression atomique
    if (analyseur->jetons[analyseur->position] == '(') {
        analyseur->position++; // Consommer la parenthèse

        // Analyser l'expression additive qui doit venir entre parenthèses
        ArbreExpression* expression = analyserExpressionAdditive(analyseur);

        // Consommer la parenthèse de fermeture
        if (analyseur->jetons[analyseur->position] == ')') {
            analyseur->position++;
        } else {
            // Erreur s'il n'y en a pas
            fprintf(stderr, "Erreur 404 : Entrée Invalide\n");
            exit(1);
        }

        return expression;

    } else {
        // C'est la règle de production alternative - une expression atomique peut être simplement un nombre
        return analyserNombre(analyseur);
    }
}

ArbreExpression* analyserNombre(AnalyseurSyntaxique* analyseur) {
    // Nous allons lire les nombres consécutifs dans un tableau de caractères
    char nombre[TAILLE_MAX_ENTREE];
    int longueurNombre = 0;

    while (strchr("0123456789", analyseur->jetons[analyseur->position]) && analyseur->position < analyseur->nJetons) {
        nombre[longueurNombre++] = analyseur->jetons[analyseur->position];
        analyseur->position++;
    }

    // Vérifier s'il y a une partie décimale
    if (analyseur->jetons[analyseur->position] == '.') {
        nombre[longueurNombre++] = analyseur->jetons[analyseur->position];
        analyseur->position++;

        // Vérifier s'il y a d'autres chiffres après le point décimal
        if (!strchr("0123456789", analyseur->jetons[analyseur->position])) {
            fprintf(stderr, "Erreur 404 : Entrée Invalide\n");
            exit(1);
        }

        while (strchr("0123456789", analyseur->jetons[analyseur->position]) && analyseur->position < analyseur->nJetons) {
            nombre[longueurNombre++] = analyseur->jetons[analyseur->position];
            analyseur->position++;
        }
    }

    // Vérifier la notation scientifique
    if (strchr("eE", analyseur->jetons[analyseur->position]) && analyseur->position < analyseur->nJetons) {
        nombre[longueurNombre++] = analyseur->jetons[analyseur->position];
        analyseur->position++;

        // Vérifier la présence d'un signe facultatif
        if ((analyseur->jetons[analyseur->position] == '+' || analyseur->jetons[analyseur->position] == '-') &&
            analyseur->position < analyseur->nJetons) {
            nombre[longueurNombre++] = analyseur->jetons[analyseur->position];
            analyseur->position++;
        }

        // Vérifier s'il y a des chiffres après 'e'
        if (!strchr("0123456789", analyseur->jetons[analyseur->position])) {
            fprintf(stderr, "Erreur 404 : Entrée Invalide\n");
            exit(1);
        }

        while (strchr("0123456789", analyseur->jetons[analyseur->position]) && analyseur->position < analyseur->nJetons) {
            nombre[longueurNombre++] = analyseur->jetons[analyseur->position];
            analyseur->position++;
        }
    }

    nombre[longueurNombre] = '\0';

    // Lorsqu'aucun caractère de nombre ne peut être trouvé
    if (longueurNombre == 0) {
        fprintf(stderr, "Erreur 404 : Entrée Invalide\n");
        exit(1);
    }

    // Convertir le tableau de caractères de nombre en double
    double valeur = atof(nombre);

    // Créer une expression de type 'n' avec la valeur définie comme la valeur du nombre
    return creerArbreExpression('n', valeur, NULL, NULL);
}

ArbreExpression* creerArbreExpression(char type, double valeur, ArbreExpression* gauche, ArbreExpression* droite) {
    // Allouer de la mémoire pour l'expression
    ArbreExpression* expression = malloc(sizeof(ArbreExpression));

    // Définir les valeurs pour l'expression
    expression->type = type;
    expression->valeur = valeur;
    expression->gauche = gauche;
    expression->droite = droite;

    return expression;
}

void libererArbreExpression(ArbreExpression* expression) {
    // Libérer récursivement l'expression
    if (expression) {
        libererArbreExpression(expression->gauche);
        libererArbreExpression(expression->droite);
        free(expression);
    }
}

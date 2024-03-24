# Analyseur et Évaluateur d'Expressions Mathématiques (Calculatrice)

## Introduction

Ce projet consiste en l'implémentation d'un analyseur lexical et d'un évaluateur d'expressions mathématiques basé sur un automate fini déterministe (AFD) et une analyse syntaxique basée sur les arbres d'expressions et les grammaires. 

## Contenu du Projet

### Fichiers Source

1. **calc.h et calc.c**:
   - Contient les déclarations de fonctions et les définitions de constantes utilisées dans le programme.
   - Les fonctions principales incluent `lexical_analysis`, `do_transition`, `verify_digit`, `verify_op`, et `contains`.

2. **lex.c**:
   - Représente l'analyseur lexical basé sur un AFD.
   - Structures de données : AFD Structure, Transition Structure.
   - Fonctions principales : `lexical_analysis` et `do_transition`.
   - Fonctions d'analyse auxiliaires : `verify_digit`, `verify_op`, et `contains`.

3. **syn.c**:
   - Représente l'analyse syntaxique et l'évaluation d'expressions mathématiques.
   - Structures de données : AnalyseurSyntaxique, ArbreExpression.
   - Fonctions principales : `tokenizer`, `analyser`, `calculer`, `afficherResultat`.
   - Fonctions d'analyse syntaxique auxiliaires : `analyserExpressionAdditive`, `analyserExpressionMultiplicative`, `analyserExpressionAtomique`, et `analyserNombre`.
   - Boucle principale (main) et fonctions de gestion de la mémoire (`creerArbreExpression` et `libererArbreExpression`).

### Program.txt : 

    - Fichier txt détaillant les explications de notre implémentation. 

### Makefile : 

    - Fichier de configuration pour la compilation du programme 


### Grammaires.txt

   - Fichier contenant la grammaire utilisée pour l'analyse syntaxique.

### README.md

   - Ce fichier README qui explique la structure du projet, les fichiers inclus, et donne une vue d'ensemble du fonctionnement du programme.


## Utilisation

Afin d'utiliser le programme en question, veuillez suivre les étapes suivantes : 

1. $> tar xvfz DJERMOUNE_HIPPOLYTE.tgz
2. $> cd DJERMOUNE_HIPPOLYTE
3. $> make
4. Insérez les expressions mathématiques à évaluer 
5. $> q  // Pour quitter la calculatrice 


## LICENCE 

Ce projet est sous licence MIT. Voir le fichier LICENSE.md pour plus de détails.


## Auteurs

- Amayes DJERMOUNE
- Yao Hippolyte FOLLY

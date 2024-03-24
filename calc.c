
/**
 * AUTEUR : FOLLY Yao Hippolyte & amayes DJERMOUNE
*/
#include <ctype.h>
#include "calc.h"

/* La fonction principale */
int main()
{
    unsigned int MAX = 100;
    char entree[MAX];
    char buf[MAX];
    // Définition de l'automate fini déterministe et de ses éléments
    AFD afd;
    afd.alphabet = "d.e+-*/()";
    afd.states = "ABCDEFGH";
    afd.start_state = afd.states[0];
    afd.end_states = "ABCEH";
    // L'ensemble des transitions
    Transition t[] = {
        {'A', 'd', 'B'},
        {'A', 'p', 'C'},
        {'C', 'p', 'C'},
        {'C', 'd', 'B'},
        {'B', 'd', 'B'},
        {'B', '.', 'D'},
        {'B', 'p', 'C'},
        {'D', 'd', 'E'},
        {'E', 'd', 'E'},
        {'E', 'p', 'C'},
        {'E', 'e', 'F'},
        {'F', '-', 'G'},
        {'F', '+', 'G'},
        {'G', 'd', 'H'},
        {'H', 'd', 'H'},
        {'H', 'p', 'C'},
    };
    afd.transitions = t;
    while (1)
    {
        int i = 0, j = 0;
        // 1. Obtenir l'entrée de l'utilisateur
        printf("> ");
        char *result = fgets(buf, MAX, stdin);

        if (result != NULL)
        {
            while (result[i] != '\n')
            {
                if (!isspace(result[i]))
                {
                    entree[j] = result[i];
                    j++;
                }
                i++;
            }
            entree[j] = '\0';
        }
        else
        {
            printf("Une erreur s'est produite.\n");
        }

        // Vérifier la commande de sortie
        if (strcmp(entree, "q") == 0 || strcmp(entree, "Q") == 0)
        {
            printf("$>\n");
            break;
        }

        //  2. Obtenir les jetons de la chaîne d'entrée
        char *jetons = lexical_analysis(afd, entree);
        if (jetons == NULL)
        {
            printf("Analyse lexicale : Entrée non valide \n");
        }
        else
        {
            // 3. Créer l'arbre d'expression à partir des jetons
            AnalyseurSyntaxique analyseur = {jetons, strlen(jetons), 0};
            ArbreExpression *expression = analyserExpressionAdditive(&analyseur);

            // 4. Calculer la valeur de l'expression
            double valeur = calculer(expression);

            // 5. Afficher le résultat
            afficherResultat(valeur);

            // 6. Libérer la mémoire allouée pour l'expression
            libererArbreExpression(expression);

        }
    }
    return 0;
}

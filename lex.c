/**
 * AUTEUR : FOLLY Yao Hippolyte
*/
#include "calc.h"
#define NB_TRANSITIONS 16
/**
 * Fonction permettant de retourner le token si l'entrée est validée par l'automate à  pile
 * @param AFD
 * @param char *
 * @return char *
*/
char *lexical_analysis(const AFD afd, char *words){
    int accept = 0, i = 0;
    int lenght = strlen(words);
    char current_state = afd.start_state;
    // Boucle pour éffectuer les transitions sur chaque caractère
    while(i< lenght){
       if(!isspace(words[i])){
        // Transition sur un caractère
        current_state = do_transition(current_state, afd.transitions, words[i]);
        
        if(current_state == '\0'){
            accept = -1;
            i = lenght;
        }
       }
       i ++;
    }
   
    if(accept == 0 && contans(afd.end_states, current_state) == 1){
        return words;
    }else{
        
        return '\0';
    }
}

/**
 * Fonction permettant d'effectuer la transition sur un caractère
 * @param char
 * @param const Transition
 * @param char
 * @return char
*/
char do_transition(char current_state, const Transition *t, char item){
    char follow_state = '\0';
    int i = 0;
    // Remplacer les chiffres de [0-9] par 'd' et {*,+,-,(,)} par p
    if(verify_digit(item) != '\0'){
        item = 'd';
    }else if ( verify_op(item) != '\0' && current_state != 'F' ){
        item = 'p';
    }

    while(i < NB_TRANSITIONS){
        Transition tmp = t[i];
        if((tmp.start == current_state) && tmp.element == item){
            follow_state = tmp.end;
            i = NB_TRANSITIONS;
        }else{
            i ++;
        }
    }
   

    return follow_state;
}
/**
 * Fonction permettant de remplacer les chiffres par d
 * @param char
 * @return char
*/

char verify_digit(char element){
    char tab_digit[] = "0123456789";
    return contans(tab_digit, element) == 1 ? 'd' : '\0';
}
/**
 * Fonction permettant de remplacer les opérations par p 
 * @param char
 * @return char
*/
char verify_op(char element){
    char tab_op[] = "+-*/()";
    return contans(tab_op, element) == 1  ? 'p' : '\0';
}
/**
 * Fonction permettant de vérifier si une chaine contient un caractère
 * @param char*
 * @param char
 * @return int
*/
int contans (const char *words, char caractar) {
    for (int i = 0; words[i] != '\0'; i++) {
        if (words[i] == caractar) {
            return 1;
        }
    }
    return 0;
}

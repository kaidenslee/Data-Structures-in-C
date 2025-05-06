/**
 * -------------------------------------
 * @file  mystring.c
 * -------------------------------------
 *
 * @version 2025-01-22
 *
 * -------------------------------------
 */

#include "mystring.h"

/**
 * Count the number words of given simple string. A word starts with an English charactor end with a charactor of space, tab, comma, or period.
 *
 * @param s - char pointer to a string
 * @return - return the number of words.
 */
int str_words(char *s){

	int count = 0;
	int in_word = 0;

	for(int i = 0; s[i] != '\0'; i++){
		if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')){
			if(!in_word){
				count++;
				in_word = 1;
			}
		}
		else if (s[i] == ' ' || s[i] == '\t' || s[i] == ',' || s[i] == '.'){
			in_word = 0;
		}
	}

	return count;
}



/**
 * Change every upper case English letter to its lower case of string passed by s
 *
 * @param s - char pointer to a string
 * @return - return the number of actual flips.
 */
int str_lower(char *s){

	int count = 0;

	for(int i = 0; s[i] != '\0'; i++){
		if (s[i] >= 'A' && s[i] <= 'Z'){
			s[i] = s[i] + 32;
			count++;
		}

	}

	return count;
}

/**
 * Remove unnecessary space characters in a simple string passed by `s`
 *
 * @param s - char pointer to a string
 */
void str_trim(char *s){

	int i = 0, j = 0;

	    while (s[i] == ' ') {
	        i++;
	    }

	    while (s[i] != '\0') {
	        if (!(s[i] == ' ' && (s[i + 1] == ' ' || s[i + 1] == '\0'))) {
	            s[j++] = s[i];
	        }
	        i++;
	    }

	    if (j > 0 && s[j - 1] == ' ') {
	        j--;
	    }

	    s[j] = '\0';
	}

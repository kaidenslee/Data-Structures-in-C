/**
 * -------------------------------------
 * @file  myword.c
 * -------------------------------------
 *
 * @version 2025-01-22
 *
 * -------------------------------------
 */

#include "myword.h"
#include "mystring.h"
#include <string.h>
#include <stdio.h>
#define DICTIONARY_MAX_SIZE 2000


/*
 * Load word data from file, and insert words a directory represented by char array.
 *
 * @param  FILE *fp -   file pointer to an opened text file
 * @param *dictionary - char pointer to a char array where dictionary words are stored.
 *                      It's up to your design on how to store words in the char array.
 * @return - the number of words added into the dictionary.
 */
int create_dictionary(FILE *fp, char *dictionary){
	char line[DICTIONARY_MAX_SIZE];
	    int count = 0;
	    int index = 0;

	    dictionary[0] = '\0';

	    while (fgets(line, sizeof(line), fp) != NULL) {
	        char *token = strtok(line, ",");
	        while (token != NULL) {
	            int len = strlen(token);


	            if (index + len + 2 >= DICTIONARY_MAX_SIZE) {
	                break;
	            }

	            strcpy(&dictionary[index], token);
	            index += len;
	            dictionary[index++] = ' ';
	            count++;

	            token = strtok(NULL, ",");
	        }
	    }

	    dictionary[index] = '\0';

	    return count;
	}
/*
 * Determine if a given word is contained in the given dictionary.
 *
 * @param *dictionary -  char pointer to a char array of given dictionary.
 * @param *word  -  pointer to a given word.
 *
 * @return - TRUE if the word is in the dictionary, FALSE otherwise.
 */
BOOLEAN contain_word(char *dictionary, char *word){
	int word_len = strlen(word);

	    for (int i = 0; dictionary[i] != '\0'; i++) {
	        if (strncmp(&dictionary[i], word, word_len) == 0 &&
	            (dictionary[i + word_len] == ' ' || dictionary[i + word_len] == '\0')) {
	            return TRUE;
	        }

	        while (dictionary[i] != ' ' && dictionary[i] != '\0') {
	            i++;
	            if (dictionary[i] == '\0') break;
	        }
	    }
	    return FALSE;
	}

/*
 * Process text data from a file for word statistic information of line count, word count, keyword count, and frequency of keyword.
 *
 * @param *fp -  FILE pointer of input text data file. .
 * @param *words  -  WORD array for keywords and their frequencies.
 * @param *dictionary  -  stop-word/common-word dictionary.
 *
 * @return - WORDSTATS value of processed word stats information.
 */
WORDSTATS process_words(FILE *fp, WORD *words, char *dictionary){
	WORDSTATS stats = {0, 0, 0};
	    char word[100];
	    char line[1000];

	    while (fgets(line, sizeof(line), fp) != NULL) {
	        stats.line_count++;

	        char *token = strtok(line, " \t\n");
	        while (token != NULL) {
	            str_lower(token);
	            str_trim(token);

	            stats.word_count++;

	            if (contain_word(dictionary, token)) {
	                token = strtok(NULL, " \t\n");
	                continue;
	            }

	            int found = 0;
	            for (int i = 0; i < stats.keyword_count; i++) {
	                if (strcmp(words[i].word, token) == 0) {
	                    words[i].count++;
	                    found = 1;
	                    break;
	                }
	            }

	            if (!found) {
	                strcpy(words[stats.keyword_count].word, token);
	                words[stats.keyword_count].count = 1;
	                stats.keyword_count++;
	            }

	            token = strtok(NULL, " \t\n");
	        }
	    }

	    return stats;
	}

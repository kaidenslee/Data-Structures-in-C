/**
 * -------------------------------------
 * @file  myrecord.c
 * -------------------------------------
 * @author Kaiden Lee, 169050073 leex5007@mylaurier.ca
 *
 * @version 2025-06-06
 *
 * -------------------------------------
 */

#include "myrecord.h"
#include "mysort.h"
#include <math.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

/*
 * Convert a percentage grade to letter grade defined by percentage ranges
 * A+=[90, 100], A=[85, 90), A-=[80, 85), B+=[77, 80), B=[73, 77) B=[70, 73),
 * C+=[67, 70), C=[63, 77), C-=[60, 63), D+=[57,60),D=[53,57),D=[50,53), F=[0,50).
 *
 * @param score -  percetage grade.
 *
 * @return - letter grade wrapped in GRADE structure type.
 */
GRADE grade(float score){
	GRADE g;

	if (score >= 90.0) strcpy(g.letter_grade, "A+");
	else if (score >= 85.0) strcpy(g.letter_grade, "A");
	    else if (score >= 80.0) strcpy(g.letter_grade, "A-");
	    else if (score >= 77.0) strcpy(g.letter_grade, "B+");
	    else if (score >= 73.0) strcpy(g.letter_grade, "B");
	    else if (score >= 70.0) strcpy(g.letter_grade, "B-");
	    else if (score >= 67.0) strcpy(g.letter_grade, "C+");
	    else if (score >= 63.0) strcpy(g.letter_grade, "C");
	    else if (score >= 60.0) strcpy(g.letter_grade, "C-");
	    else if (score >= 57.0) strcpy(g.letter_grade, "D+");
	    else if (score >= 53.0) strcpy(g.letter_grade, "D");
	    else if (score >= 50.0) strcpy(g.letter_grade, "D-");
	    else strcpy(g.letter_grade, "F");

	    return g;
	}



/*
 *  Import record data from file and store name and store all record entries
 *  in the RECORD array passed by records, return the number of record count.
 *
 *  @param *fp -  FILE pointer to intput file.
 *  @param dataset - array of RECODR type to store record data.
 *  @return   - number of records
 */
int import_data(FILE *fp, RECORD *dataset){
	int count = 0;

	while (fscanf(fp, "%19[^,],%f\n", dataset[count].name, &dataset[count].score) == 2){
		count++;
	}
	return count;
}

/*
 *  Take the RECORD data array as input, compute the average score, standard deviation,
 *  median of the score values of the record data, and returns the STATS type value.
 *
 *  @param dataset -  input record data array.
 *  @param count -  the number of data record in dataset array.
 *  @return  -  stats value in STATS type.
 */
STATS process_data(RECORD *dataset, int count){
	STATS stats;
	    stats.count = count;

	    if (count < 1) {
	        stats.mean = 0;
	        stats.stddev = 0;
	        stats.median = 0;
	        return stats;
	    }

	    float sum = 0, sum_sq = 0;

	    for (int i = 0; i < count; i++) {
	        sum += dataset[i].score;
	        sum_sq += dataset[i].score * dataset[i].score;
	    }

	    stats.mean = sum / count;
	    stats.stddev = sqrt((sum_sq / count) - (stats.mean * stats.mean));

	    void *pointers[stats.count];
	    for (int i = 0; i < stats.count; i++) {
	        pointers[i] = &dataset[i].score;
	    }
	    my_sort((void **)pointers, 0, stats.count - 1, cmp);

	    if (stats.count % 2 == 0) {
	        int mid = stats.count / 2;
	        stats.median = (*(float*)pointers[mid - 1] + *(float*)pointers[mid]) / 2.0;
	    } else {
	        stats.median = *(float*)pointers[stats.count / 2];
	    }

	    return stats;
	}


/*
 *  This function takes output file named outfilename, RECORD array records,
 *  and stats as inputs, prepare and write report of stats and grade to files.
 *  The records in report file are sorted in decreasing of scores.
 *
 *  @param *fp -  FILE pointer to output file.
 *  @param *dataset - pointer to dataset array.
 *  @param count - the number of data record in dataset array.
 *  @return - returns 1 if successful; 0 if count < 1
 */
int report_data(FILE *fp,  RECORD *dataset, STATS stats){
	if (stats.count < 1 || fp == NULL) {
	        return 0;
	    }

	    void *score_pointers[stats.count];
	    for (int i = 0; i < stats.count; i++) {
	        score_pointers[i] = &dataset[i].score;
	    }

	    my_sort(score_pointers, 0, stats.count - 1, cmp);

	    RECORD *sorted_records[stats.count];

	    for (int i = 0; i < stats.count; i++) {
	        for (int j = 0; j < stats.count; j++) {
	            if (&dataset[j].score == score_pointers[i]) {
	                sorted_records[i] = &dataset[j];
	                break;
	            }
	        }
	    }

	    for (int i = 0; i < stats.count / 2; i++) {
	        RECORD *temp = sorted_records[i];
	        sorted_records[i] = sorted_records[stats.count - i - 1];
	        sorted_records[stats.count - i - 1] = temp;
	    }

	    fprintf(fp, "stats:value\n");
	    fprintf(fp, "count:%d\n", stats.count);
	    fprintf(fp, "mean:%.1f\n", stats.mean);
	    fprintf(fp, "stddev:%.1f\n", stats.stddev);
	    fprintf(fp, "median:%.1f\n\n", stats.median);

	    fprintf(fp, "name:score,grade\n");
	    for (int i = 0; i < stats.count; i++) {
	        GRADE g = grade(sorted_records[i]->score);
	        fprintf(fp, "%s:%.1f,%s\n", sorted_records[i]->name, sorted_records[i]->score, g.letter_grade);
	    }

	    return 1;
	}


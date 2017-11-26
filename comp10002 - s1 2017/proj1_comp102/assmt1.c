/* 
	COMP10002 - FOUNDATIONS OF FUN
	ASSESSMENT 1
	Author: Naufal Fikri Setiawan (nsetiawan@student.unimelb.edu.au)
	Student Number: 844027

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DIV "==========" /* stage header */
/* stage numbers */
#define STAGE_NUM_ONE 1 
#define STAGE_NUM_TWO 2
#define STAGE_NUM_THREE 3
#define STAGE_NUM_FOUR 4
#define STAGE_NUM_FIVE 5

#define READ_OK 1 /* reading point succeeded */
#define READ_FAILED 0 /* reading point failed */

#define MAX_NUM_POINTS 99 /* maximum number of points */
#define MAX_NUM_DIMENSIONS 10 /* maximum number of dimensions */

/* my own constants */
#define SCALE_FACTOR 0.01

typedef double point_t[MAX_NUM_DIMENSIONS];

/* function prototypes */
void stage_one(point_t one_point, int *num_points, int num_dimensions);
void stage_two(point_t points[], int *num_points, int num_dimensions, 
	double *coordinate_sums);
void stage_three(double *coordinate_sums, int num_points);
void stage_four(point_t points[], int num_points, int num_dimensions);
void stage_five(point_t points[], int num_points, int num_dimensions);

void print_stage_heading(int stage);
int read_one_point(point_t one_point, int num_dimensions);

/* add your own function prototypes here */
double max_coordinate_sums(double *coordinate_sums, int num_points);
double sum_point(point_t point, int num_dimensions);
void point_copy(point_t src, point_t dest, int num_dimensions);
int max_index(double *coordinate_sums, int num_points);
int skyline(int index, point_t points[], int num_points, int num_dimensions);
void
output_point(point_t point, int num_dimensions);


/* main program binds it all together */
int
main(int argc, char *argv[]) {

	/* storage for the input data */
	int num_dimensions;
	point_t points[MAX_NUM_POINTS];
	
	/* storage for statistics */
	int num_points = 0; /* number of points read in */
	double coordinate_sums[MAX_NUM_POINTS]; /* coordinate sums of the points */
	
	/* read the first line - number of dimensions */
	scanf("%d", &num_dimensions);
	
	/* stage 1 */
	stage_one(points[0], &num_points, num_dimensions);

	/* stage 2 */
	stage_two(points, &num_points, num_dimensions, 
		coordinate_sums);
	

	/* stage 3 */
	stage_three(coordinate_sums, num_points);

	/* stage 4 */
	stage_four(points, num_points, num_dimensions);

	/* stage 5 */
	stage_five(points, num_points, num_dimensions);
	
	/* and done! */
	return 0;
}

/* print out a stage heading, with a prior blank line once the stage number
   goes plus one 
*/
void 
print_stage_heading(int stage) {
	/* main job is to print the stage number passed as an argument */
	if (stage > STAGE_NUM_ONE) {
		/* separate the stages */
		printf("\n");
	}
	printf("Stage %d\n%s\n", stage, DIV);
}

/* read the coordinates of one point, store them in one_point
*/
int 
read_one_point(point_t one_point, int num_dimensions) {
	int i = 0;
	
	/* keep reading until num_dimensions numbers have been obtained */
	while (i < num_dimensions) {
		if (scanf("%lf", one_point+i) != 1) {
			return READ_FAILED;
		}
		i++;
	}
	
	return READ_OK;
}

/* stage 1 - read in and print one point
*/
void 
stage_one(point_t one_point, int *num_points, int num_dimensions) {
	/* print stage heading for stage 1 */
	print_stage_heading(STAGE_NUM_ONE);
	
	/* add your code here for stage 1 */
	read_one_point(one_point, num_dimensions);

	printf("Point 01: ");
	output_point(one_point, num_dimensions);

	(*num_points)++;


}

/* stage 2 - read in the rest of the points and visualise them
*/
void 
stage_two(point_t points[], int *num_points, int num_dimensions, 
	double *coordinate_sums) {
	/* print stage heading for stage 2 */
	print_stage_heading(STAGE_NUM_TWO);
	
	point_t one_point;
	/* add your code here for stage 2 */
	
	/* copies each of the input lines (if they exist) to an array of points*/
	while (read_one_point(one_point, num_dimensions)) {
		point_copy(one_point, points[(*num_points)++], num_dimensions);
	}


	int i;
	for (i = 0; i < *num_points; i++) {

		double sum = sum_point(points[i],num_dimensions);
		coordinate_sums[i] = sum;
		double displayed_sum = sum*SCALE_FACTOR;

		
		printf("Point %02d, sum of coordinates (/100): %5.2f |", i + 1, displayed_sum);


		/*	Prints the tower */
		int j;
		for (j = 1; j <= (int)ceil(displayed_sum); j++) {
			printf("%c", j % 10 == 0 ? '+' : '-');
		}
		printf("\n");
	}
}

/* stage 3 - print statistics
*/
void 
stage_three(double *coordinate_sums, int num_points) {
	/* print stage heading for stage 3 */
	print_stage_heading(STAGE_NUM_THREE);
	
	/* add your code here for stage 3 */
	int i;
	int max_pos = max_index(coordinate_sums, num_points);
	double maxsum = coordinate_sums[max_pos];
	printf("Total: %d points\n", num_points);
	printf("Point of largest sum of coordinates: %02d\n", max_pos + 1);
	printf("Largest sum of coordinates: %5.2f\n", maxsum);

}

/* stage 4 - find and print the skyline points
*/
void 
stage_four(point_t points[], int num_points, int num_dimensions) {
	/* print stage heading for stage 4 */
	print_stage_heading(STAGE_NUM_FOUR);
	
	int i;
	printf("Skyline points:\n");
	for (i = 0; i < num_points; i++) {
		if (skyline(i,points,num_points,num_dimensions)) {
			printf("Point %02d: ", i + 1);
			output_point(points[i], num_dimensions);
		}
	}
	/* add your code here for stage 4 */

}

/* stage 5 - sort and print the skyline points by the number of points 
   they dominate
*/
void 
stage_five(point_t points[], int num_points, int num_dimensions) {
	/* print stage heading for stage 5 */
	print_stage_heading(STAGE_NUM_FIVE);
	
	/* add your code here for stage 5 */

}


/* custom functions */
double
sum_point(point_t one_point, int num_dimensions) {
	double total = 0;
	int i;
	for (i = 0; i < num_dimensions; i++) {
		total += one_point[i];
	} 
	return total;
}

void
point_copy(point_t src, point_t dest, int num_dimensions) {
	int i;
	for (i = 0; i < num_dimensions; i++) {
		dest[i] = src[i];
	}
}

int
max_index(double *coordinate_sums, int num_points) {
	double max = 0;
	int index = 0;
	int i;
	for (i = 0; i < num_points; i++) {
		if (coordinate_sums[i] > max) {
			max = coordinate_sums[i];
			index = i;
		}
	}
	return index;
}

double
max_value(double *coordinate_sums, int num_points) {
	double max = 0;
	int i;
	for (i = 0; i < num_points; i++) {
		if (coordinate_sums[i] > max) {
			max = coordinate_sums[i];
		}
	}
	return max;	
}

int
check_domination(point_t one_point, point_t opposing_point, int num_dimensions) {
	int i;
	for(i = 0; i < num_dimensions; i++) {
		if (opposing_point[i] > one_point[i]) {
			return 0;
		}
	}
	return 1;
}

int
skyline(int index, point_t points[], int num_points, int num_dimensions) {
	int i;
	for (i = 0; i < num_points; i++) {
		if (index == i) {
			continue;
		}
		int dominated;
		dominated = check_domination(points[i], points[index], num_dimensions);

		if (dominated) {
			return 0;
		}
	}
	return 1;
}

void
output_point(point_t point, int num_dimensions) {
	int i;
	for (i = 0; i < num_dimensions; i++) {
		printf(i == 0 ? "<" : " ");
		printf("%.2f", point[i]);
		printf(i == num_dimensions - 1 ? ">" : ",");
	}
	printf("\n");
}
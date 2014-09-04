#include <stdlib.h>
#include <stdio.h>

#define NUM_ROWS 7
#define NUM_COLS 7

/* Linked List Data Structure Declaration */
struct LL {
        int label;
        struct LL* parent;
        struct LL* next;
};

/* Search routine */
struct LL*
get_node_in_LL(struct LL *head, int label)
{
	struct LL *temp = head;
	while (temp) {
		if (temp->label == label) {
                        return temp;
                }
		temp = temp->next;
	}
        return temp;
}

/* Helper routine to get the non-zero minimum in the input array */
int
get_non_zero_min(int* array, int n)
{
        /* arrange zeroes to end of array */
	int i = 0, j = n-1;
	while (i < j) {
		while (array[i]) {
		 	i++;
                }

                while (!array[j]) {
			j--;
                }

                if (i < j) {
                        array[i] = array[j];
                        array[j]=0;
                } 
        }

        /* Find the non-zero minimum in the array */
	int min = array[0];
	for (i = 1; array[i] != 0; i++) {
		if (min > array[i]) {
			min=array[i];
                }
        }
	
	return min;
}

/*
 * label_image is the connected component matrix 
 */
int
get_min_and_store_parent_label(int label_image[NUM_ROWS][NUM_COLS], int i, int j, struct LL *head)
{
	int arr[4] = { label_image[i-1][j-1],
                       label_image[i-1][j],
                       label_image[i-1][j+1],
                       label_image[i][j-1] };

	int min_label = get_non_zero_min(arr, 4);
	struct LL *minLL, *LL1;
	
	minLL = get_node_in_LL(head, min_label);

        if (label_image[i-1][j-1] != min_label) {
                LL1 = get_node_in_LL(head, label_image[i-1][j-1]);
                LL1->parent = minLL->parent;
        }	
	if (label_image[i-1][j] != min_label) {
		LL1 = get_node_in_LL(head, label_image[i-1][j]);
                LL1->parent = minLL->parent;
        }	
	if (label_image[i-1][j+1] != min_label) {
		LL1 = get_node_in_LL(head, label_image[i-1][j+1]);
                LL1->parent = minLL->parent;
        }	
	if (label_image[i][j-1]!=min_label) {
		LL1 = get_node_in_LL(head, label_image[i][j-1]);
                LL1->parent = minLL->parent;
        }

        return min_label;
}

/* Main Function to be called for Connected Components Labelling
 * Inputs:
 * input_image  : binary image for which connected components has to be labelled
 * num_rows : number of rows in A
 * num_cols : number of columns in A
 *
 * Output:
 * label_image : Connected components label matrix
 */
void
get_connected_components(int input_image[NUM_ROWS][NUM_COLS], int num_rows, int num_cols, int label_image[NUM_ROWS][NUM_COLS])
{
        int i = 0, j = 0, prev_label = 0;
        struct LL* L1 = (struct LL*)malloc(sizeof(struct LL));
        struct LL* head = L1;

        /* Label 2nd to last row and 2nd to last column of image */
        for (i = 0; i < num_rows; i++) {
                for (j = 0; j < num_cols; j++) {
                        if (input_image[i][j]) {
                                if (input_image[i][j-1] ||
                                    input_image[i-1][j-1] ||
                                    input_image[i-1][j] ||
                                    input_image[i-1][j+1]) {
                                        label_image[i][j] = get_min_and_store_parent_label(label_image, i, j, head);
                                } else {
		         		L1->label = ++prev_label;
                                        label_image[i][j] = L1->label;
					L1->parent = L1;
					L1->next = (struct LL*)malloc(sizeof(struct LL));
                                        L1 = L1->next;
				}
                        }
                }
        }

        L1->next = NULL;

        /*
         * Scan through the Connected components label matrix and assign the
         * value of label of its parent
         */
        for (i = 0; i < num_rows; i++) {
                for (j = 0; j < num_cols; j++) {
                        if (label_image[i][j] > 0) {
                                L1 = get_node_in_LL(head, label_image[i][j]);
                                label_image[i][j] = L1->parent->label;
                        }
		}
        }

        return;
}

int
main(int argc, char **argv)
{
        /* All input images should be padded with zeroes on all four sides as a requirement */
        /*
        int input_image[NUM_ROWS][NUM_COLS] = {
                {0, 0, 0, 0, 0, 0, 0},
                {0, 0, 1, 0, 1, 1, 0},
                {0, 1, 1, 0, 0, 1, 0},
                {0, 0, 0, 1, 0, 1, 0},
                {0, 0, 1, 0, 1, 0, 0},
                {0, 0, 0, 1, 0, 1, 0},
                {0, 0, 0, 0, 0, 0, 0},
        };
        */

        int input_image[NUM_ROWS][NUM_COLS] = {
                {0, 0, 0, 0, 0, 0, 0},
                {0, 1, 0, 0, 0, 1, 0},
                {0, 1, 0, 1, 0, 1, 0},
                {0, 1, 0, 1, 0, 0, 0},
                {0, 1, 1, 1, 0, 1, 0},
                {0, 1, 0, 1, 1, 0, 0},
                {0, 0, 0, 0, 0, 0, 0},
        };

        /*
        int input_image[NUM_ROWS][NUM_COLS] = {
                {0, 0, 0, 0, 0, 0, 0},
                {0, 1, 0, 0, 0, 1, 0},
                {0, 0, 0, 1, 0, 0, 0},
                {0, 1, 0, 0, 0, 1, 0},
                {0, 0, 0, 1, 0, 0, 0},
                {0, 1, 0, 0, 0, 1, 0},
                {0, 0, 0, 0, 0, 0, 0},
        };
        */

        /*
        int input_image[NUM_ROWS][NUM_COLS] = {
                {0, 0, 0, 0, 0, 0, 0},
                {0, 1, 0, 1, 0, 1, 0},
                {0, 1, 0, 1, 0, 1, 0},
                {0, 0, 0, 0, 0, 0, 0},
                {0, 1, 1, 1, 1, 1, 0},
                {0, 1, 0, 0, 1, 0, 0},
                {0, 0, 0, 0, 0, 0, 0},
        };
        */

        int label_image[NUM_ROWS][NUM_COLS] = {0};

        printf("Printing input matrix\n");
        int i = 0;
        int j = 0;
        for (i = 0; i < NUM_ROWS; i++) {
                printf("{ ");
                for (j = 0; j < NUM_COLS; j++) {
                        printf("%d ", input_image[i][j]);
                }
                printf("}\n");
        }

        printf("Running the connected components program\n");

        get_connected_components(input_image, NUM_ROWS, NUM_COLS, label_image);

        printf("Printing connected components matrix\n");
        i = 0;
        j = 0;
        for (i = 0; i < NUM_ROWS; i++) {
                printf("{ ");
                for (j = 0; j < NUM_COLS; j++) {
                        printf("%d ", label_image[i][j]);
                }
                printf("}\n");
        }

        return 1;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int rand_int(int max){
	return(rand()%max);
}

int check_for_mine(int index, int array[]){
	if (array[index] == -1){
		return 1;
	}
	else{
		return 0;
	}
}

int * minesweeper_field(int num_of_buttons,int num_of_mines){
	int * arr = malloc((num_of_buttons * num_of_buttons)*sizeof(int));
	int count = 0;
	bool no_left = true;
	bool no_right = true;
	bool no_upper = true;
	bool no_lower = true;

	if ((num_of_buttons * num_of_buttons) < num_of_mines){
		perror("number of mines must not exceed field size\n");
	}
	while (count < num_of_mines){
		//randomly place mines
		int r = rand_int(num_of_buttons*num_of_buttons);
		if (arr[r] == 0){
			arr[0] = -1;
			count++;
		}
	}
	for (int i = 0; i < (num_of_buttons * num_of_buttons); i++){
		//calculate field 
		int num = 0;
		if ((i% num_of_buttons) != 0){
			//field has left neighbor
			num = num + check_for_mine(i - 1, arr);
			no_left = false;
		} 
		if ((i%num_of_buttons) != (num_of_buttons - 1)){
			//field has right neighbor
			num = num + check_for_mine(i + 1, arr);
			no_right = false;
		}
		if (i >= num_of_buttons){
			//field has upper neighbor
			num = num + check_for_mine(i - num_of_buttons, arr);
			no_upper = false;
		}
		if (i < (num_of_buttons * (num_of_buttons - 1))){
			//field has lower neighbor
			num = num + check_for_mine(i + num_of_buttons, arr);
			no_lower = false;
		}
		if (!no_left && !no_upper){
			//field has upper left neighbor
			num = num + check_for_mine(i - (num_of_buttons + 1), arr);
		}
		if (!no_upper && !no_right){
			//field has upper right neighbor
			num = num + check_for_mine(i - num_of_buttons + 1, arr);
		}
		if (!no_left && !no_lower){
			//field has lower left neighbor
			num = num + check_for_mine(i + (num_of_buttons - 1), arr);
		}
		if (!no_lower && !no_right){
			//field has lower right neighbor
			num = num + check_for_mine(i + num_of_buttons + 1, arr);
		}
		if (arr[i] != -1){
			arr[i] = num;
		}

	}
	return arr;

}

int main(void){
	
	for (int j = 0; j < 16; j ++){
		printf("%d\n", minesweeper_field(4, 4)[j]);
	}
}

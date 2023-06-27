#include <stdio.h>
#include <stdbool.h>

int main() {
    int array_size, water_units = 0, current_wall = 0, is_done = 0;
    scanf("%d", &array_size);
    int input_array[array_size];

    // Read the array elements from the user
    for (int i = 0; i < array_size; i++) {
        scanf("%d", &input_array[i]);
    }

    // Find the left and right walls of each block of buildings
    while (is_done != 1) {
        bool left_wall_found = false;
        bool right_wall_found = false;
        int left_wall;
        int right_wall;

        // Find the left wall of the current block
        for (int i = current_wall; i < array_size; i++) {
            if (left_wall_found == false) {
                if (input_array[i] != 0) {
                    left_wall = i;
                    left_wall_found = true;
                }
            }
        }

        // If no left wall is found, we are done
        if (left_wall_found == false) {
            is_done = 1;
        } 
        // Find the right wall of the current block
        else {
            bool is_all_zeroes = true;
            for (int i = left_wall + 1; i < array_size; i++) {
                if (input_array[i] != 0) {
                    is_all_zeroes = false;
                }
            }

            if (is_all_zeroes == true) {
                is_done = 1;
            } 
            else {  
                right_wall = left_wall;
                for (int i = left_wall + 1; i < array_size; i++) {
                    if (right_wall_found == false) {
                        if (input_array[i] >= input_array[right_wall]) {
                            right_wall = i;
                            right_wall_found = true;
                        }
                    }
                }

                // Calculate the amount of water trapped between the walls
                if (right_wall_found == true) {
                    int sum = 0;
                    for (int i = left_wall + 1; i < right_wall; i++) {
                        sum += input_array[i];
                    }
                    int width = right_wall - left_wall - 1;
                    water_units += input_array[left_wall] * width - sum;
                } 
                else {
                    right_wall = left_wall + 1;
                    for (int i = left_wall + 1; i < array_size; i++) {
                        if (input_array[i] > input_array[right_wall]) {
                            right_wall = i;
                        }
                    }
                    int sum = 0;
                    for (int i = left_wall + 1; i < right_wall; i++) {
                        sum += input_array[i];
                    }
                    int width = right_wall - left_wall - 1;
                    water_units += input_array[right_wall] * width - sum;
                }
            }
            current_wall = right_wall;
            if (right_wall == array_size - 1) {
                is_done = 1;
            }
        }
    }
    // Print the total amount of water trapped
    printf("%d", water_units);
    return 0;
}

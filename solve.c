#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 9
#define n 3

typedef int grid_t[N][N], (* restrict grid_rt)[N];
typedef const int (* restrict grid_crt)[N];

typedef struct {
	int row, column;
} box_t;

static void copy_grid(grid_crt src, grid_rt dest)
{
	memcpy(dest, src, sizeof(int) * N * N);
}

static int is_grid_full(grid_crt grid)
{
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (grid[i][j] == 0)
				return 0;
		}
	}

	return 1;
}

static int is_number_possible(grid_crt grid, box_t box, int number)
{
	for (int i = 0; i < N; ++i) {
		if (grid[i][box.column] == number)
			return 0;
	}

	for (int i = 0; i < N; ++i) {
		if (grid[box.row][i] == number)
			return 0;
	}

	for (int i = n * (box.row / n); i < n + n * (box.row / n); ++i) {
		for (int j = n * (box.column / n); j < n + n * (box.column / n); ++j) {
			if (grid[i][j] == number)
				return 0;
		}
	}

	return 1;
}

static int count_possible_numbers(grid_crt grid, box_t box)
{
	int cnt = 0;
	for (int i = 0; i < N; ++i) {
		if (is_number_possible(grid, box, i + 1))
			++cnt;
	}

	return cnt;
}

static box_t find_easiest_box(grid_crt grid)
{
	box_t box = {0, 0};
	int num_of_possible_numbers = 0;

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			box_t tmp = {i, j};
			int cnt;

			if (grid[i][j] == 0 && ((cnt = count_possible_numbers(grid, tmp)) < num_of_possible_numbers || num_of_possible_numbers == 0)) {
				box = tmp;
				num_of_possible_numbers = cnt;
			}
		}
	}

	return box;
}

static int *get_possible_numbers(grid_crt grid, box_t box, size_t *size)
{
	int *possible_numbers = malloc(sizeof(int) * N);
	*size = 0;

	for (int i = 0; i < N; ++i) {
		if (is_number_possible(grid, box, i + 1))
			possible_numbers[(*size)++] = i + 1;
	}

	return possible_numbers;
}

static int solve(grid_t grid)
{
	if (is_grid_full(grid)) //we solved it
		return 1;

	grid_t tmp;
	copy_grid(grid, tmp);

	box_t box = find_easiest_box(grid);

	size_t size;
	int *possible_numbers = get_possible_numbers(grid, box, &size);

	for (size_t i = 0; i < size; ++i) {
		grid[box.row][box.column] = possible_numbers[i];

		if (solve(grid)) {
			free(possible_numbers);
			return 1; //found solution
		}

		copy_grid(tmp, grid);
	}

	free(possible_numbers);
	return 0;
}

static void print_grid(grid_crt grid)
{
	for (int i = 0; i < N; ++i) {
		if (i % 3 == 0)
			printf("---------------------\n");

		for (int j = 0; j < N; ++j) {
			if (j % 3 == 0)
				printf("|");

			if (grid[i][j] != 0)
				printf("%d", grid[i][j]);
			else
				printf(" ");

			if (j < N - 1)
				printf(" ");
		}

		printf("|\n");
	}

	printf("---------------------\n");
}

int main(void)
{
	grid_t grid;

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j)
			if (!scanf("%1d", &grid[i][j])) {
				printf("Error!\n");
				return -1;
			}
	}

	printf("ORIGINAL\n");
	print_grid(grid);
	printf("\n");

	solve(grid);

	printf("SOLVED\n");
	print_grid(grid);

	return 0;
}

#ifndef READ_LINES_H
	#define READ_LINES_H

    #include <stdbool.h>
	#include <stdio.h>
    #include <stdlib.h>

	void read_lines(FILE* reader, char** *lines, int *num_lines);
	bool get_line(FILE* reader, char* *line, int *num_chars);

    void add_char(char* *arr, int *arr_len, char augment);
	void add_char_arr(char** *arr, int *arr_len, char* line, int line_len);

	void free_memory(char* *arr);

#endif

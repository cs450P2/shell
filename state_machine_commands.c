
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>




enum states {command, std_in, std_out, append, end_of_command, input_file, output_file, filler};


int firstNextState(int state)
{
	/*
	|	current state   |  							next states to check				|
	command				std_out, 		std_in, 		append,  end_of_command, command,
	std_out				output_file, 	filler, 		filler, filler, 		 filler,
	std_in				input_file, 	filler, 		filler, filler, 		 filler,
	append				output_file, 	filler, 		filler, filler, 		 filler,
	output_file			end_of_command, filler, 		filler, filler, 		 filler,
	input_file			std_out, 		end_of_command, append, filler, 		 filler,
	end_of_command		filler, 		filler, 		filler, filler, 		 filler,
	filler   			filler, 		filler, 		filler, filler, 		 filler,

		how the indexes of the next states table relates to a 1d array
	|current state |	indexes of the next states table |
	command					0  1  2  3  4
	std_out					5  6  7  8  9
	std_in					10 11 12 13 14
	append					15 16 17 18 19
	output_file				20 21 22 23 24
	input_file				25 26 27 28 29
	filler					30 31 32 33 34
	*/

	int location_of_first_next_state;

	switch (state)
	{
		case command:
			location_of_first_next_state = 0;
			break;
		case std_out:
			location_of_first_next_state = 5;
			break;
		case std_in:
			location_of_first_next_state = 10;
			break;
		case append:
			location_of_first_next_state = 15;
			break;

		case output_file:
			location_of_first_next_state = 20;
			break;


		case input_file:
			location_of_first_next_state = 25;
			break;

		case end_of_command:
			location_of_first_next_state = 30;
			break;
		case filler:
			location_of_first_next_state = 35;
			break;

		default:
			location_of_first_next_state = -2;
			break;
	}
	return location_of_first_next_state;
}

char* getEnum(int state)
{


	// returns the enumerated names
	switch (state)
	{
		case command:
			return "command";

		case std_in:
			return "std_in";


		case std_out:
			return "std_out";


		case append:
			return "append";


		case end_of_command:
			return "end_of_command";


		case input_file:
			return "input_file";


		case output_file:
			return "output_file";

		case filler:
			return "filler";


		default:
			return "no state";

	}

}
bool isEmpty(int* next_states)
{

	return next_states[0] == filler &&
		   next_states[1] == filler &&
		   next_states[2] == filler &&
		   next_states[3] == filler;
}
int main()
{











	int next_states[] = {
		/*command*/				std_out, 		std_in, 		append,  end_of_command, command,
		/*std_out*/				output_file, 	filler, 		filler, filler, 		filler,
		/*std_in*/				input_file, 	filler, 		filler, filler, 		filler,
		/*append*/				output_file, 	filler, 		filler, filler, 		filler,
		/*output_file*/			end_of_command, filler, 		filler, filler, 		filler,
		/*input_file*/			std_out, 		end_of_command, append, filler, 		filler,
		/*end_of_command*/		filler, 		filler, 		filler, filler, 		filler,
		/*filler*/   			filler, 		filler, 		filler, filler, 		filler,
	};
	char* a = "ps\0-u\0yourusername\0";

	char* b = "who\0";

	char* c = "ls\0/usr/bin\0";


	char* d = "wc\0-l\0<\0inputfile\0";

	char* e = "who\0>\0outputfile\0";

	char* f = "wc\0-l\0<\0inputfile\0>>\0outputfile\0";

	int size_of_command = 6;
	char** words = malloc(sizeof(char*) * size_of_command);

	// passes
	/*
	words[0] = &a[0];
	words[1] = &a[3];
	words[2] = &a[6];
	*/

	// passes
	/*
	words[0] = &b[0];
	*/

	// passes
	/*
	words[0] = &c[0];
	words[1] = &c[3];
	*/


	// passes
	/*
	words[0] = &d[0];
	words[1] = &d[3];
	words[2] = &d[6];
	words[3] = &d[8];
	*/

	// passes
	/*
	words[0] = &e[0];
	words[1] = &e[4];
	words[2] = &e[6];
	*/

	// passes
	words[0] = &f[0];
	words[1] = &f[3];
	words[2] = &f[6];
	words[3] = &f[8];
	words[4] = &f[18];
	words[5] = &f[21];








	/*
	all string examples above are recognized
	*/

	/*
	for(int i = 0; i < size_of_command; i++)

		printf("%s\n", words[i]);
	*/
	int max_index = size_of_command - 1;
	//printf("last index %i\n", max_index);
	// ideally the first time we are at this state we should run a state instead of getting the next state,
	// but the command state will happen at least 1 time for the process name(just who), so it doesn't matter.
	// we will get the next state that happens to be command and we will run command.

	printf("start machine\n\n");

	int state = command;
	int location_of_first_next_state = firstNextState(state);
	int* set_of_next_states = malloc(sizeof(int) * 5);

	memcpy(set_of_next_states, next_states + location_of_first_next_state, sizeof(int) * 5);

	int j = 0;
	int count = 0;
	int winning_state;

	// an instance of the command struct would be declared here.
	// the states will fill up parts of the struct
	// after this loop is over, the entire struct will be filld out
	while(!isEmpty(set_of_next_states))
	{

		/*
		if(count == 5)
		{
			printf("ran too long\n");
			exit(1);
		}
		*/
		// don't continue if j is out of range
		if (j > max_index || j < 0)
		{
			break;
		}
		bool state_changed = false;
		//printf("current state is %s\n", getEnum(winning_state));
		winning_state = 0;
		for(int i = 0; i < 5; i++)
		{
			//printf("	%s\n", getEnum(set_of_next_states[i]));


			if(set_of_next_states[i] == end_of_command)
			{
				if (j > max_index || j < 0)
				{

					winning_state = end_of_command;
					state_changed = true;

				}
			}
			else if(set_of_next_states[i] == command)
			{
				if(strcmp(words[j], ">") != 0 ||
				   strcmp(words[j], "<") != 0 ||
				   strcmp(words[j], ">>")!= 0)
				{
					printf("%s ", words[j]);
					j++;
					winning_state = command;
					state_changed = true;

				}

			}

			else if (set_of_next_states[i] == std_in)
			{
				if(strcmp(words[j], "<") == 0)
				{
					printf("%s ", words[j]);
					j++;
					winning_state = std_in;
					state_changed = true;

				}


			}
			else if(set_of_next_states[i] == std_out)
			{
				if(strcmp(words[j], ">") == 0)
				{
					printf("%s ", words[j]);
					j++;
					winning_state = std_out;
					state_changed = true;
				}


			}

			else if (set_of_next_states[i] == append)
			{
				if(strcmp(words[j], ">>") == 0)
				{
					printf("%s ", words[j]);
					j++;
					winning_state = append;
					state_changed = true;
				}


			}


			else if(set_of_next_states[i] == input_file)
			{
				if(strcmp(words[j], ">") != 0 ||
				   strcmp(words[j], "<") != 0 ||
				   strcmp(words[j], ">>")!= 0)
				{
					printf("%s ", words[j]);
					j++;
					winning_state = input_file;
					state_changed = true;

				}



			}
			else if(set_of_next_states[i] == output_file)
			{
				if(strcmp(words[j], ">") != 0 ||
				   strcmp(words[j], "<") != 0 ||
				   strcmp(words[j], ">>")!= 0)
				{
					printf("%s ", words[j]);
					j++;
					winning_state = output_file;
					state_changed = true;

				}



			}
			else if(set_of_next_states[i] == filler)
			{
				// this check is only here for completeness
				// this state doesn't do anything
			}


			if(state_changed)
			{
				break;
			}

		}
		if(!state_changed)
		{
			printf("state didn't change.  exiting program\n");
			// print current state, next states
			// exit program
			exit(1);
		}

		//printf("state = %s  %i  \n", getEnum(winning_state), j);

		if(state_changed)
		{
			location_of_first_next_state = firstNextState(winning_state);

			// want to start the copy at location next_states root address + the computed location of the first next state in the next_states array.  5 elements will be copied from next_states
			memcpy(set_of_next_states, next_states + location_of_first_next_state, sizeof(int) * 5);

		}
		//printf("\n");
		count++;
	}
	free(set_of_next_states);
	free(words);
	//printf("\n\nj = %i\n", j);
	printf("\n\ndone with machine\n");
	//(location_of_first_next_state + 2));

	return 0;

}


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>




enum states {command, std_in, std_out, append, end_of_command, input_file, output_file, filler};


int firstNextState(int state)
{
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
			return "input_files";


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
	//printf("here");
	return next_states[0] == filler && next_states[1] == filler && next_states[2] == filler && next_states[3] == filler;
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

	char** words = malloc(sizeof(char*) * 3);
	words[0] = &e[0];
	words[1] = &e[4];
	words[2] = &e[6];
	/*
	words[0] = &a[0];
	words[1] = &a[3];
	words[2] = &a[6];
	*/
	for(int i = 0; i < 3; i++)

		printf("%s\n", words[i]);

	int state = command;
	int location_of_first_next_state = firstNextState(state);
	printf("%i\n", location_of_first_next_state);
	int* set_of_next_states = malloc(sizeof(int) * 5);

	memcpy(set_of_next_states, next_states + location_of_first_next_state, sizeof(int) * 5);
	printf("new set of next states\n");
	for(int i = 0; i < 5; i++)
		printf("%s ", getEnum(set_of_next_states[i]));
	printf("%i\n", isEmpty(set_of_next_states));

	printf("start machine\n\n");
	int j = 0;
	int count = 0;
	int winning_state;
	int prev_state;
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
		bool state_changed = false;
		//printf("current state is %s\n", getEnum(winning_state));
		winning_state = 0;
		for(int i = 0; i < 5; i++)
		{
			//printf("	%s\n", getEnum(set_of_next_states[i]));

			//printf("i = %i\n", i);
			//printf("%s \n", getEnum(set_of_next_states[i]));

			//printf("got here%i\n", j);

			if(set_of_next_states[i] == end_of_command)
			{
				// we are
				if( j >= 3)
				{
					winning_state = end_of_command;
					state_changed = true;

				}
				//break;
			}
			else if(set_of_next_states[i] == command)
			{
				//printf("j final %i\n", j);
				//printf("	did state change %i\n", state_changed);

				if(j < 3)
				{

					if(strcmp(words[j], ">") != 0 ||  strcmp(words[j], "<") != 0 || strcmp(words[j], ">>") != 0)
					{
						printf("command %s", words[j]);
						//printf("case state %s\n", getEnum(prev_state));
						j++;
						winning_state = command;
						state_changed = true;

					}
				}
				//printf("did state change %i\n", state_changed);

				//break;
			}
			/*
			else if (set_of_next_states[i] == std_in)
			{
				state = std_in;
				state_changed = true;

				break;
			}*/
			else if(set_of_next_states[i] == std_out)
			{
				if (j < 3)
				{
					if(strcmp(words[j], ">") == 0)
					{
						printf("stdout %s", words[j]);
						j++;
						winning_state = std_out;
						state_changed = true;
					}
				}

				//break;
			}
			/*
			else if (set_of_next_states[i] == append)
			{
				state = append;
				state_changed = true;
				break;
			}

			else if(set_of_next_states[i] == input_file)
			{
				state = input_file;
				state_changed = true;
				break;
			}*/
			else if(set_of_next_states[i] == output_file)
			{
				if(j < 3)
				{
					if(strcmp(words[j], ">") != 0 ||  strcmp(words[j], "<") != 0 || strcmp(words[j], ">>") != 0)
					{
						printf("output_file %s", words[j]);
						j++;
						winning_state = output_file;
						state_changed = true;

					}

				}

				//break;
			}
			else if(set_of_next_states[i] == filler)
			{
				//state = filler;
				//state_changed = true;
				//break;
			}




			if(state_changed)
			{
				break;
			}

		}
		if(!state_changed)
		{
			printf("failed\n");
			// print current state, next states
			// exit program
		}

		//printf("state = %s  %i  \n", getEnum(winning_state), j);
		/*if (j < 3)
		{
			printf("%s\n", words[j]);
		}*/
		/*if (j >= 3)
		{
			// done with command;
			state = end_of_command;
			break;
		}*/
		if(state_changed)
		{
			//printf("got here, state changed status: %i, state that passed: %s\n", state_changed, getEnum(state));
			location_of_first_next_state = firstNextState(winning_state);
			prev_state = winning_state;
			//printf("next firstst states %i\n", location_of_first_next_state);
			//free(set_of_next_states);
			//set_of_next_states = malloc(sizeof(int) * 5);
			// want to start the copy at location next_states root address + the computed location of the first next state in the next_states array.  5 elements will be
			memcpy(set_of_next_states, next_states + location_of_first_next_state, sizeof(int) * 5);
			//printf("new set of next states\n");
			/*
			for(int i = 0; i < 5; i++)
				printf("%s ", getEnum(set_of_next_states[i]));
			*/
			//printf("%i", isEmpty(set_of_next_states));
			//exit(1);
			//break;
		}
		printf("\n");
		count++;
	}
	free(set_of_next_states);
	free(words);
	printf("j = %i\n", j);
	printf("done with machine\n");
	//(location_of_first_next_state + 2));

	return 0;

}

#define _CRT_SECURE_NO_WARNINGS 1
#include "Header.h"

bool isWin(char* spell, int* frequency) {
	int last = sizeof(spell) / sizeof(char);
	int loc = spell[last - 1] - 'a';
	if (frequency[loc] == 0)
		return true;
	else
		false;
}



char* easy(char last&, char*** dictionary){}
char* medium(char last, char*** dictionary){}
char* Mindscape_Mastery(char last, char*** dictionary){}





int main()
{
	int frequency[26] = {0};	  // array representing the frequency of the first letter of each word
	char ***map;				  // Hashmap for spells
	char ***used;				  // Hasmap for used spells
	int used_frequency[26] = {0}; // array representing the frequency of the first letter of each use word
								  //    -------------------------- read the spells----------------------------------
	FILE *file;
	errno_t err;
	err = fopen_s(&file, "spells.txt", "r");
	if (file == NULL)
	{
		perror("Error opening the file");
		return 1;
	}
	size_t size = 0;
	fscanf(file, "%zu", &size);					   // storing the number of spells in size
	map = (char ***)malloc(sizeof(char **) * 26);  // allocating memory on the heaap for the unused spells map
	used = (char ***)malloc(sizeof(char **) * 26); // allocating memory on the heaap for the used spells map

	for (int i = 0; i < size; i++)
	{ // filling the map and the frequency array
		char word[50];
		fscanf(file, "%s", &word);
		int p = (int)word[0] - 'a';
		frequency[p]++;
		if (frequency[p] == 1)
		{ // if there is no already a word begiining with this letter in the map
			map[p] = (char **)malloc(sizeof(char *));
		}
		else
		{ // if there already exist a word starting with this letter in the map we reallocate memory
			map[p] = (char **)realloc(map[p], sizeof(char *) * frequency[p]);
		}

		map[p][frequency[p] - 1] = (char *)malloc(strlen(word) + 1);
		strcpy(map[p][frequency[p] - 1], word);
	}
	fclose(file);
	// Finished reading the file
	//---------------------------------------------------------------------------------------------------------------------- -

	char p1[20]; // Player 1 name

	printf("please enter your name : ");
	scanf("%s", &p1, 20);
	
	printf("These are the spells that you may use during the game: \n");
	int count = 0;
	for (int i = 0; i < 26; i++)
	{ // Displaying the spells
		if (frequency[i] > 0)
		{
			// printf("%c: ", map[i][0][0]);
			for (int j = 0; j < frequency[i]; j++)
			{
				printf(" %s", map[i][j]);
				count++;
				if (count % 5 == 0)
					printf("\n -------------------------------------- \n");
			}
		}
	}

	// a fair way to choose which player will start

	printf("\nWe will roll a die, if the number obtained is even you will start otherwise the bot will begin.\n");
	srand(time(NULL));
	int random = (rand() % 6) + 1;
	int s;
	if (random % 2 == 0)
	{
		printf("The number obtained is %d, %s will start\n", random, p1);
		s = 0;
	}
	else
	{
		printf("The number obtained is %d, bot will start\n", random);
		s = 1;
	}

	// Start the game

	int start = 0;
	char condition;
	do
	{
		char w[20];
		if (s == 0)
		{
			printf("%s chooses: ", p1);
			scanf("%s", &w);
		}
		else
		{
			printf("%bot chooses: ");
			strcpy(w,easy(condition,map));
		}

		// if a player choosed a spell that don't start with last letter of the previous spell
		if (start != 0 && w[0] != condition)
		{
			if (s == 0)
				printf("bot wins (you choosed a wrong spell)");
			else
				printf("You won (bot choosed a wrong spell)");
			goto done;
		}
		int location = (int)w[0] - 'a'; // Searching for the location of the spell in the map
		bool found = false;
		for (int i = 0; i < frequency[location]; i++)
		{
			if (strcmp(map[location][i], w) == 0)
			{
				free(map[location][i]);
				found = true;
			}
		}
		if (found)
		{ // if the spell is found
			if (frequency[(int)w[strlen(w) - 1] - 'a'] == 0)
			{				// if there is no more spells start with last letter of the current spell
				if (s == 0) // the player that dislayed the current spell wins
					printf("You won (no more spells in the list that satisfy the character matching condition)");
				else
					printf("Bot won (no more spells in the list that satisfy the character matching condition)");
				frequency[location]--;
				goto done;
			}
			else
			{ // if there is more spells available that starts with the last letter of the current spell
				// Storing the spell in the used spells map
				condition = w[strlen(w) - 1];
				frequency[location]--;
				used_frequency[location]++;
				start++;
				if (used_frequency[location] == 1)
				{
					used[location] = (char **)malloc(sizeof(char *));
				}
				else
				{
					used[location] = (char **)realloc(used[location], sizeof(char *) * used_frequency[location]);
				}
				used[location][used_frequency[location] - 1] = (char *)malloc(strlen(w) + 1);
				strcpy(used[location][used_frequency[location] - 1], w);
				if (s == 0)
					s = 1;
				else
					s = 0;
			}
		}
		else
		{ // If the spell wasn't found in the map
			// First search for it in the used spells map so we can check if it is already used
			for (int i = 0; i < used_frequency[location]; i++)
			{
				if (strcmp(used[location][i], w) == 0)
				{
					// Found the spell in the used map
					if (s == 0)
						printf("Bot won (you repeated a previously cast spell)");
					else
						printf("You won (bot repeated a previously cast spell)");
					goto done;
				}
			}
			if (s == 0) // if the spell isn't in the used map so the spell isn't available
				printf("Bot won (you casted a spell that is not available)");
			else
				printf("You won (bot casted a spell that is not available)");
			goto done;
		}

	} while (true);

done:
	//   -------------------------------done reading the spells-----------------------------
	// Free the allocated memory
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < frequency[i]; j++)
		{
			free(map[i][j]);
		}
		free(map[i]);
	}
	free(map);
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < used_frequency[i]; j++)
		{
			free(used[i][j]);
		}
		free(used[i]);
	}
	free(used);
	return 0;
}
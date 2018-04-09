#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


/*
Larger questions regarding C:

Does all assignment have to occur within a function defition?
It does not seem like there are classes in C. Is it considered object-oriented?
Are structs the closest thing to classes in C?
*/

/*
Test questions:
Validity of rotor positions?
Validity of input string?
Should everything be a constant? (No lterals)

*/

const char LETTERS[27] = {'A','B','C','D','E','F','G','H','I','J',
                          'K','L','M','N','O','P','Q','R','S','T',
						  'U','V','W','X','Y','Z', ' '};
const char ROTOR_VALUES[10] = {7, 3, 0, 1, 9, 5, 2, 6, 4, 8};
const int ROTOR_SIZE = 10;
const int TEXT_SIZE = 256;
int rotorPosition1, rotorPosition2, rotorPosition3;



/* findCharIndex:  Finds the location(index) of a character in the
    Letters array
 * Input:  Character to find in Letters Array
 * Output: Index location in the Letters Array
 * Note:  Returns -1 if not found
 */
int findCharIndex(char c)
{
    for (int i=0; i<27; i++) {
    	if (LETTERS[i] == c) {
    		return i;
    	}
    }

	return -1;
}

/*  mod:  Implements a true modulus function
 *  INPUT: original number (a) and dividor (b)
 *  OUTPUT: remainder
 *  NOTE:  Required since in C (%) does not implement true modulus
 *         function for negative remainders   */
int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}



/* encryptLetter:  Returns an encrypted letter (character)
 * INPUT:  unencrypted letter (character) and key
 * OUTPUT:  encrypted letter   */
char encryptLetter(char unencrypted, int key){
	printf("unencrypted letter %c | encrypts to %c\n", 
		unencrypted, LETTERS[mod(findCharIndex(unencrypted) + key, 27)]);

	// decrypted letter is index_of_character - key % # of letters
    return LETTERS[mod(findCharIndex(unencrypted) + key, 27)];
}

/* decryptLetter:  Returns an decrypted letter (character)
 * INPUT:  encrypted letter (character) and key
 * OUTPUT:  decrypted letter  */
char decryptLetter(char encrypted, int key){
	printf("encrypted letter %c | unencrypts to %c\n", 
		encrypted, LETTERS[mod(findCharIndex(encrypted) - key, 27)]);

	// decrypted letter is index_of_character - key % # of letters
	return LETTERS[mod(findCharIndex(encrypted) - key, 27)];
}

/* getKey: returns key based on current positions of the rotors  */
int getKey()
{
	return ROTOR_VALUES[rotorPosition1]+
	       ROTOR_VALUES[rotorPosition2]+
	       ROTOR_VALUES[rotorPosition3];
}

/* incrementRotors: Advances rotor positions by one
 * USAGE: Used after every letter is encrypted or decrypted  */
void incrementRotors()
{
	rotorPosition1++;
	if (rotorPosition1 == ROTOR_SIZE){
		rotorPosition1 = 0;
		rotorPosition2++;
	}
	if (rotorPosition2 == ROTOR_SIZE){
		rotorPosition2 = 0;
		rotorPosition3++;
	}
	if (rotorPosition3 == ROTOR_SIZE)
		rotorPosition3 = 0;
}

int main(int argc, char *argv[] )
{


	char inputText[TEXT_SIZE];
	char outputText[TEXT_SIZE];
	char mode;
    
	int input_text_size;

	//STEP #1: Get and check Command Line Arguments
	printf(">>engima: ");
	scanf("%d %d %d %c", &rotorPosition1, &rotorPosition2,
		&rotorPosition3, &mode);

  	// output init rotor values
  	printf("Rotor #1 is set to: %d\n", rotorPosition1);
  	printf("Rotor #2 is set to: %d\n", rotorPosition2);
  	printf("Rotor #3 is set to: %d\n", rotorPosition3);
  	mode = tolower(mode);

    //STEP #2: Get text string from user
  	//STEP #3: For each letter, encrypt or decrypt
  	if (mode == 'e') {
  		printf(">>encrypt: ");
  		scanf(" %[^\n]s", inputText);
  		input_text_size = strlen(inputText);
  		for (int i=0; i<input_text_size; i++){
    		outputText[i] = encryptLetter(inputText[i], getKey());
    		incrementRotors();
    	}
    }

    //STEP #2: Get text string from user
    //STEP #3: For each letter, encrypt or decrypt
  	else if (mode == 'd') {
  		printf(">>decrypt: ");
  		scanf(" %[^\n]s", inputText);
  		input_text_size = strlen(inputText);
  		for (int i=0; i<input_text_size; i++){
    		outputText[i] = decryptLetter(inputText[i], getKey());
    		incrementRotors();
    	}
  	}

  	//unknown command - exit
  	else {
  		printf("Unknown command.\n");
  		return EXIT_FAILURE;
  	}

    //STEP #4: Print result
	outputText[input_text_size+1] = '\0';
	printf("Output text: %s\n", outputText);


	return EXIT_SUCCESS;
}
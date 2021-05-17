#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
int encrypt(int input, char* rotor, int ring);
int back_encrypt(int input, char* rotor, int ring, char* alpha);
int main(int argc, int argv[])
{
    char* alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char* rotor1 = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
    char* rotor2 = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
    char* rotor3 = "BDFHJLCPRTXVZNYEIWGAKMUSQO";
    char* reflector = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
    int ring1 = 0;
    int ring2 = 0;
    int ring3 = 1;
    int ref = 0;

    string text = get_string("plaintext:");

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]) != 0)
        {
            char upper_text = toupper(text[i]);
            int input = upper_text - 'A';
            int forword = encrypt(
                encrypt(
                    encrypt(
                        encrypt(input, rotor3, ring3), rotor2, ring2), rotor1, ring1), reflector, ref);
            int backword = back_encrypt(
                                back_encrypt(
                                    back_encrypt(forword, rotor1, ring1, alpha), rotor2, ring2, alpha), rotor3, ring3, alpha);
            char output = alpha[backword];
            printf("%c", output);
            if (ring3 > 24)
            {
                ring3 = 0;
            }
            else if (ring3 > 21)
            {
                ring2++;
            }
            
            if (ring2 > 24)
            {
                ring2 = 0;
            }
            else if (ring2 > 4)
            {
                ring1++;
            }
            
            if (ring1 > 24)
            {
                ring1 = 0;
            }
            ring3++;
        }
        else
        {
            printf("%c", text[i]);
        }
        
    }
    printf("\n");
    return 0;
}

int encrypt(int input, char* rotor, int ring)
{
    char* alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int ringed_input = (input + ring) % 26;
    int output = rotor[ringed_input] - 'A';

    int ringed_output = (output + (26 - ring)) % 26;;

    return ringed_output;
}

int back_encrypt(int input, char* rotor, int ring, char* alpha)
{

    char ringed_input = alpha[(input + ring) % 26];
    for (int i = 0 ; rotor[i] != '\0'; i++)
    {
        if (rotor[i] == ringed_input)
        {
            int output = (i + (26 - ring)) % 26;

            return output;
        }
    }
    return 0;
}
#include <cs50.h>
#include <stdio.h>
int encrypt(int input, char* rotor, int ring);
int back_encrypt(int input, char* rotor, int ring, char* alpha);
int main(void)
{
    char* alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char* rotor1 = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
    char* rotor2 = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
    char* rotor3 = "BDFHJLCPRTXVZNYEIWGAKMUSQO";
    char* reflector = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
    int ring1 = 3;
    int ring2 = 14;
    int ring3 = 7;
    int ref = 0;

    string text = get_string("plaintext:");

    for (int i = 0; text[i] != '\0'; i++)
    {
        int input = text[i] - 'A';
        int forword = encrypt(
            encrypt(
                encrypt(
                    encrypt(input, rotor3, ring3), rotor2, ring2), rotor1, ring1), reflector, ref);
        printf(" <> ");
        int backword = back_encrypt(
                            back_encrypt(
                                back_encrypt(forword, rotor1, ring1, alpha), rotor2, ring2, alpha), rotor3, ring3, alpha);
        char output = alpha[backword];
        printf("-> %c", output);
        printf("|%i|", (output - 'A'));
        printf("\n");
        if (ring3 > 24)
        {
            ring2++;
            ring3 = 0;
        }
        if (ring2 > 24)
        {
            ring1++;
            ring2 = 0;
        }
        if (ring1 > 24)
        {
            ring1 = 0; ring2 = 0; ring3 = 0;
        }
        ring3++;
    }
    printf("\n");
    return 0;
}

int encrypt(int input, char* rotor, int ring)
{
    char* alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int output = rotor[input] - 'A';
    printf("|%i|", output);
    int ringed_output = (output + ring) % 26;
    //printf("%i, ", ringed_output);
    printf("%c,", alpha[ringed_output]);
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
            //printf("%i, ", output);
            printf("%c,", alpha[output]);
            return output;
        }
    }
    return 0;
}
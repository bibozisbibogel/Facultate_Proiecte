/// Explicatiile pentru fiecare functie in parte sunt mai jos de program
	

#include <stdio.h>
#include <stdlib.h>
#include "inputgenerator.h"
#include <time.h>
char *random_string(size_t length)
{
    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!(){}`><-+@$%^&*~/:;\\";
    char *randomString = NULL;

    if (length)
    {
        randomString = malloc(length + 1);
        if (randomString)
        {
            for (size_t i = 0; i < length; i++)
            {
                int key = rand() % (sizeof(charset) - 1);
                randomString[i] = charset[key];
            }
            randomString[length] = '\0';
        }
    }

    return randomString;
}
char *similar_string_generator(char *source)
{
    size_t length = strlen(source);
    char *similarString = malloc(length + 1);
    if (!similarString)
    {
        return NULL;
    }
    strcpy(similarString, source);
    int num_errors = (rand() % length) + 1;
    for (int i = 0; i < num_errors; i++)
    {
        int error_type = rand() % 3;
        int pos = rand() % length;

        if (error_type == 0 && pos < length - 1)
        {
            char temp = similarString[pos];
            similarString[pos] = similarString[pos + 1];
            similarString[pos + 1] = temp;
        }
        else if (error_type == 1 && length > 1)
        {
            memmove(&similarString[pos], &similarString[pos + 1], length - pos);
            similarString[length - 1] = '\0';
            length--;
        }
        else if (error_type == 2)
        {
            similarString[pos] = 'a' + (rand() % 26);
        }
    }
    return similarString;
}
/*

	Vom explica functia random_string in urmatorii pasi:



	1) Definirea functiei si a setului de caractere:

	char *random_string(size_t length)
	{
 	    static char charset[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!(){}`><-+@$%^&*~/:;\\";
	    
	Functia "random_string" primeste un parametru "length", care specifica lungimea sirului aleatoriu care trebuie generat. Setul de caractere ("charset")
	este un sir constant de caractere din care se vor selecta caracterele aleatorii. Este definit ca "static" pentru a nu fi recreat la fiecare apel al functiei.

	~ Ce este static? https://www.geeksforgeeks.org/static-variables-in-c/

	( A static variable remains in memory while the program is running. A normal or auto variable is destroyed when a function call where the variable was declared is over."

 	2) Declaratia pointerului pentru sirul aleatoriu

	char *randomString=NULL;

	3) Verificarea lungimii dorite si alocarea memoriei

	if(length)
	{
	   randomString=malloc(length+1);
	   if(randomString)
	   {

	Se verifica daca "length" este diferit de zero. Daca da, se aloca memorie pentru sirul aleatoriu, inclusiv un spatiu suplimentar pentru terminatorul nul ('\0').
	Daca alocarea memoriei are succes, pointerul randomString va puncta catre zona alocata.

	4) Generarea sirului aleatoriu:

	for(size_t i=0; i<length;i++)
	{
	   int key=rand()%(sizeof(charset)-1);
	   randomString[i]=charset[key];
	}

	Pentru fiecare pozitie a sirului de lungime "length":
	
	* Se genereaza un index aleatoriu "key" intre 0 si "sizeof(charset)-2" (pentru a exclude terminatorul nul din "charset");
	* Caracterul de la acea pozitie din "charset" este copiat in pozitia curenta din "randomString"

	5) Adaugarea terminatorului nul

	   randomString[length]='\0';
	}
     }

	6) Returnarea sirului aleatoriu

		return randomString;
	}


	Rezumat:

	Functia "random_string" genereaza un sir de caractere aleatoriu de o lungime specifica. Setul de caractere posibil contine litere mici si
	litere mari, cifre si diverse simboluri. Functia urmeaza cei 6 pasi.
	
    -------------------------------------

    

    					Explicatie functie similar_string_generator:
    Rezumat:

    Functia creeaza un sir similar cu cel de intrare, dar cu un numar aleatoriu de erori
    (intre 1 si lungimea sirului), care pot fi inversari de caractere, stergeri de caractere sau inlocuiri de caractere.
    Aceasta este utila pentru testarea algoritmilor de corectare automata a erorilor de sintaxa, simuland diferite tipuri de erori care pot aparea intr-un sir de caractere.

    Explicare pasi:

    1) size_t length = strlen(source); /// calculam lungimea sirului sursa

    2) Alocam memorie pentru sirul similar

     char *similarString=malloc(length+1);
     if(!similarString)
     {
	return NULL;
     }

     3) Copierea sirului sursa in sirul rezultat

     strcpy(similarString,source);

     4) Generarea numarului de erori

     int num_errors = (rand()%length)+1;

     5) Introducerea erorilor:

     for(int i=0;i<num_errors;i++)
     {
	int error_type=rand()%3;
	int pos=rand()%length;
	if(error_type==0 && pos<length-1)
	{
	    char temp = similarString[pos];
	    similarString[pos]=similarString[pos+1];
	    similarString[pos+1]=temp;
	} 
	else if(error_type==1 && length>1)
	{
	    memmove(&similarString[pos],&similarString[pos+1],length-pos);
	    similarString[length-1]='\0';
            length--;
        }
	else
	    if(error_type==2)
		similarString[pos]='a'+(rand()%26);   
     }


     Se itereaza de num_errors ori pentru a introduce erori in sirul similar:

      * Inversare: Daca error_type este 0 si pos este mai mic decat length-1, atunci inversam doua caractere adiacente

      * Stergere: Daca error_type este 1 si lungimea sirului este mai mare decat 1, se stergere caracterul de la pozitia "pos"
		  si se deplaseaza caracterele din dreapta cu o pozitie spre stanga, micsorand lungimea sirului

      * Inlocuire: Daca error_type este 2, se inlocuieste caracterul de la pozitia "pos" cu un caracter aleatoriu intre "a" si "z"


   6) Returnam sirul modificat

	return similarString;	
    
*/

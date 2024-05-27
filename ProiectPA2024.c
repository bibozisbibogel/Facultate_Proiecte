/*
    Proiect realizat de Stoian Cristian-Georgian, CR1.2B, F.A.C.E

    Concluzii generale:

    Avem o regula si-un fragment de cod si trebuie sa aducem fragmentul de cod la regula in numarul minim de operatii

       Operatia consta in: (aceste operatiii sunt de cost 1)

    1) Schimbarea unei litere
    2) Stergerea unei litere
    3) Adaugarea unei litere
    4*) Putem si sa inversam literele (cum e in exemplul cu regula = func(myFunction) si fragment_cod = fnuc(myFuncion
    Update: inversiunea e o operatie de cost 1 [ de la regula = func(myFunction) si fragment_cod = fnuc(myFuncion ] ajungem la codul regula prin urmatoarele operatii:

            1) inversam "n" cu "u"
            2) adaugam "t"
            3) adaugam ")" => 3 operatii => afisam 3

       Trebuie sa vedem problema ca o problema de programare dinamica, intrucat gandirea noastra trebuie sa fie in modul respectiv:

    Pentru a ajunge de exemplu de la "ab" la "aaba" trebuie sa ne gandim care e minimul intre: adaugarea unei litere, stergerea unei litere sau schimbarea unei litere

    Calculand totul intr-o matrice dp putem compara foarte simplu acest minim, insa gandirea din spate trebuie sa fie CORECTA, astfel incat sa nu gasim erori in implementarea algoritmului nostru

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "inputgenerator.h"
#include <string.h>
#include <time.h>
#define DIM 100005 /// Vom considera sirul de maxim 100000 de litere, insa pentru siruri sau valori mai lungi putem schimba extrem de usor dimensiunea
int MinOfTwo(int a, int b) /// Pentru simplificarea codului, vom face functia min din C++
{
    if(a>b)
        return b;
    else
        return a;
}
char fragment_cod[DIM];
char regula[DIM];
int dp[DIM][DIM];
int NrMinimOperatii(char regula[DIM], char fragment_cod[DIM], int dp[DIM][DIM], int n, int m)
{
    /// Initializam prima linie si prima coloana a matricei dp cu valorile corespunzatoare
    /// pentru transformarea unui sir vid in sirul regula sau fragment_cod
    for(int i=0; i<=n; i++)
    {
        dp[i][0]=i;
    }
    for(int j=0; j<=m; j++)
    {
        dp[0][j]=j;
    }

    /// Parcurgem ambele siruri, regula si fragment_cod
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            if(regula[i]==fragment_cod[j]) ///Verificam daca caracterele de pe pozitiile i si j din cele 2 siruri sunt egale
                /// Daca caracterele sunt egale atunci costul minim este egal cu costul pana-n punctul respectiv
                /// adica costul de transformare pana la caracterele precedente

                dp[i+1][j+1]=dp[i][j];
            else
            {
                /// Daca caracterele sunt diferite, determinam costul minim de transformare pentru a aduce
                /// fragment_cod[j] la regula[i] folosind una din cele trei operatii:
                ///  1) Schimbarea unei litere
                ///  2) Stergerea unei litere
                ///  3) Adaugarea unei litere
                /// 4*) Aparent avem si comanda de inversiune
                int insert_cost=dp[i+1][j]+1;
                int delete_cost=dp[i][j+1]+1;
                int replace_cost=dp[i][j]+1;
                // Verificam si costul pentru inversiune
                if(regula[i-1]==fragment_cod[j] && regula[i]==fragment_cod[j-1])
                {
                    int swap_cost=dp[i-1][j-1]+1; /// operatie bonus fata de problema originala "Edit Distance"
                    replace_cost=MinOfTwo(replace_cost,swap_cost);
                }
                /*
                		Sa explicam linia urmatoare in detaliu:

                	1) dp[i+1][j] : Acesta este numarul minim de operatii necesare pentru a ajunge la pozitia (i+1,j) din matricea dp, adica la caracterul j din fragment_cod, dar fara a lua in considerare caracterul i+1 din regula
                	2) dp[i][j+1] : Similar cu dp[i+1][j], aceasta reprezinta numarul minim de operatii necesare pentru a ajunge la pozitia (i,j+1) din matricea dp, adica la caracterul i din regula, dar fara a lua in considerare caracterul j+1 din fragment_cod
                	3) dp[i][j] : Acesta reprezinta numarul minim de operatii necesare pentru a ajunge la pozitia (i,j_ din matricea dp, adica la caracterul i din regula si caracterul j din fragment_cod
                	4) '+1" : Adaugam 1 la valoarea minima calculata pentru a reflecta faptul ca este nevoie de o operatie suplimentara pentru a transforma caracterul de la pozitia (i+1,j+1) in sirul fragment_cod in caracterul corespunzator din sirul regula

                	In concluzie, aceasta linie efectueaza calculul pentru a determina numarul minim de operatii necesare pentru a ajunge la pozitia (i+1,j+1) din matricea dp, luand in considerare toate posibilitatile de transformare posibile a prefixului sirului fragment_cod in prefixul sirului regula
                */
                dp[i+1][j+1]=MinOfTwo(MinOfTwo(insert_cost,delete_cost),replace_cost);
            }
        }
    }
    /// Returnam numarul minim de operatii necesare pentru a transforma fragmentul de cod in regula data
    return dp[n][m];
}
int main ()
{
    /// fragment_cod = "fnuc(myFuncion"
    /// regula = "func(myFunction)"
    int chosen_method;
    printf("Metoda 0 = exemplu document\n");
    printf("Metoda 1 = generare input de mana\n");
    printf("Metoda 2 = generare input complet RANDOM\n");
    printf("Metoda 3 = generare input RANDOM, dar fragment_cod seamana cu regula_sirului\n");
    printf("Alegeti metoda prin care doriti sa testati (doar numarul acesteia ) : ");
    scanf("%d",&chosen_method);
    printf("\n");
    if(chosen_method==0)
    {
        char regula_exemplu[]="func(myFunction)";
        char fragment_cod_exemplu[]="fnuc(myFuncion";
        int n=strlen(regula_exemplu);
        int m=strlen(fragment_cod_exemplu);
        printf("Sirul regula este: %s",regula_exemplu);
        printf("\nFragmentul de cod este: %s",fragment_cod_exemplu);
        int exemplu_operatii=NrMinimOperatii(regula_exemplu,fragment_cod_exemplu,dp,n,m);
        printf("\nNumarul minim de operatii necesare pentru a transforma fragmentul de cod intr-un cod valid este egal cu : ");
        printf("%d",exemplu_operatii);
        printf("!\n");
    }
    else if(chosen_method==1)
    {
        printf("Introduceti codul care va defini regula programului  : ");
        scanf("%s",regula);
        printf("Introduceti fragmentul de cod dorit: ");
        scanf("%s",fragment_cod);
        int n=strlen(regula); /// lungimea codului valid
        int m=strlen(fragment_cod); /// lungimea fragmentului de cod introdus
        int nr=NrMinimOperatii(regula,fragment_cod,dp,n,m); /// numarul minim de operatii cerut
        printf("Numarul minim de operatii pentru a ajunge la un cod valid de la fragmentul introdus este egal cu ");
        printf("%d",nr);
        printf("!\n");
    }
    else if(chosen_method==2)
    {
        srand((unsigned int)time(NULL)); // Ne asiguram ca sirurile sunt unice de fiecare data
        printf("Cat de lung doriti sa fie sirul regula? ");
        int rule_length;
        scanf("%d",&rule_length);
        char *regula_sirului;
        char *fragment_incercat_cod;
        printf("\nCat de lung doriti sa fie fragmentul de cod? "); /// numarul de caractere
        int fragment_length;
        scanf("%d",&fragment_length);
        regula_sirului=random_string(rule_length);
        fragment_incercat_cod=random_string(fragment_length);
        if(regula_sirului)
        {
            printf("Sirul regula generat RANDOM este: ");
            printf("%s",regula_sirului);
            printf("\n");
        }
        else
            printf("Alocarea de memorie a dat GRES!\n");
        if(fragment_incercat_cod)
        {
            printf("Fragmentul de cod generat RANDOM este: ");
            printf("%s",fragment_incercat_cod);
            printf("\n");
        }
        else
            printf("Alocarea de memorie a dat GRES!\n");
        printf("Numarul minim de operatii pentru a ajunge la un cod valid de la fragmentul introdus este egal cu: ");
        int number_of_operations=NrMinimOperatii(regula_sirului,fragment_incercat_cod,dp,rule_length,fragment_length); /// numarul minim de operatii cerut
        printf("%d",number_of_operations);
        printf("!\n");
        free(regula_sirului);
        free(fragment_incercat_cod);
    }
    else if(chosen_method==3)
    {
        srand((unsigned int)time(NULL)); // Ne asiguram ca sirurile sunt unice de fiecare data
        int lungime_sir_regula;
        printf("Cat de lung doriti sa fie sirul regula? ");
        scanf("%d",&lungime_sir_regula);
        char *sir_regula;
        sir_regula=random_string(lungime_sir_regula);
        char *fragment_cod_similar;
        if(sir_regula)
        {
            printf("Sirul regula generat RANDOM este: ");
            printf("%s",sir_regula);
            printf("\n");
        }
        else
            printf("Alocarea de memorie a dat GRES!\n");
        fragment_cod_similar=similar_string_generator(sir_regula);
        if(fragment_cod_similar)
        {
            printf("Fragmentul de cod generat RANDOM, dar totusi similar cu sirul regula este: ");
            printf("%s",fragment_cod_similar);
            printf("\n");
        }
        else
            printf("Alocarea de memorie a dat GRES!\n");
        int lungime_fragment_cod=strlen(fragment_cod_similar);
        int nr_operations=NrMinimOperatii(sir_regula,fragment_cod_similar,dp,lungime_sir_regula,lungime_fragment_cod);
        printf("Numarul minim de operatii pentru a ajunge la un cod valid de la fragmentul introdus este egal cu: ");
        printf("%d",nr_operations);
        printf("!\n");
        free(sir_regula);
        free(fragment_cod_similar);
    }
    else
    {
        printf("Metoda introdusa nu exista!\n");
        return 0;
    }
    return 0;
}

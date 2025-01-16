#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// funkcja wypelniajaca plansze znakami niezaznaczenia
void wypelnienie_planszy(int liczba_wierszy, int liczba_kolumn, char **plansza) {
    for (int i = 0; i<liczba_wierszy; i++) {
        for (int j = 0; j<liczba_kolumn; j++) {
            plansza[i][j] = '#';
        }
    }
}

// funkcja wypisujaca plansze
void wypisz_plansze(int liczba_wierszy, int liczba_kolumn, char **plansza) {
    for(int i = 0; i<liczba_wierszy; i++) {
        for(int j = 0; j<liczba_kolumn; j++) {
            printf("[%c]", plansza[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int trudnosc;               //Poziom trudnosci gry
    int liczba_wierszy, liczba_kolumn, liczba_min, mnoznik_punktow;

    printf("Saper");             //Placeholder tu cos ladniejszego dac

    printf("Wybierz poziom trudnosci:\n");
    printf("Latwy :) - 1\t Sredni :| - 2\t Trudny >:( - 3\t Wlasny - 4\n");

    scanf("%d", &trudnosc);

    switch (trudnosc){

            case 1:
                    liczba_kolumn = 9;
                    liczba_wierszy = 9;
                    liczba_min = 10;
                    mnoznik_punktow = 1;
                    printf("Wybrano poziom trudnosci 1 - Latwy :)\n");
                    break;

            case 2:
                    liczba_kolumn = 16;
                    liczba_wierszy = 16;
                    liczba_min = 40;
                    mnoznik_punktow = 2;
                    printf("Wybrano poziom trudnosci 2 - Sredni :|\n");
                    break;

            case 3:
                    liczba_kolumn = 30;
                    liczba_wierszy = 16;
                    liczba_min = 99;
                    mnoznik_punktow = 3;
                    printf("Wybrano poziom trudnosci 3 - Trudny >:(\n");
                    break;

            case 4:
                    printf("Wybrano poziom trudnosci 4 - Wlasny\n");

                    printf("Wybierz liczbe kolumn: ");
                    scanf("%d", &liczba_kolumn);
                    if(liczba_kolumn < 0){
                        printf("Nieprawidlowa liczba kolumn: podana wartosc powinna byc liczba calkowita, wieksza od zera\n");
                        return 2;
                    }

                    printf("Wybierz liczbe wierszy: ");
                    scanf("%d", &liczba_wierszy);
                    if(liczba_wierszy < 0){
                        printf("Nieprawidlowa liczba wierszy: podana wartosc powinna byc liczba calkowita, wieksza od zera\n");
                        return 3;
                    }

                    printf("Wybierz liczbe min ");
                    scanf("%d", &liczba_min);
                    if(liczba_min < 0){
                        printf("Nieprawidlowa liczba min: podana wartosc powinna byc liczba calkowita, wieksza od zera\n");
                        return 4;
                    }
                    if(liczba_min >= liczba_kolumn * liczba_wierszy){
                        printf("Nieprawidlowa liczba min: podana wartosc powinna byc liczba calkowita, wieksza od zera, mniejsza od liczby pol planszy\n");
                        return 5;
                    }

                    printf("Zostaly wybrane nastepujace parametry: Plansza %dx%d, liczba min %d\n", liczba_kolumn, liczba_wierszy, liczba_min);

                    mnoznik_punktow = 0;
                    break;

            default:
                    printf("Nieprawidlowo wybrano poziom trudnosci\n");
                    return 1;
    }

    // alokacja pamieci dla tablicy przechowujacej plansze pod spodem
    char **plansza_pod = (char **)malloc(liczba_wierszy * sizeof(char *));
    for (int i = 0; i<liczba_wierszy; i++) {
        plansza_pod[i] = (char *)malloc(liczba_kolumn * sizeof(char)); 
    }

    // alokacja pamieci dla tablicy przechowujacej plansze wyswietlona uzytkownikowi
    char **plansza_nad = (char **)malloc(liczba_wierszy * sizeof(char *));
    for (int i = 0; i<liczba_wierszy; i++) {
        plansza_nad[i] = (char *)malloc(liczba_kolumn * sizeof(char)); 
    }

    wypelnienie_planszy(liczba_wierszy, liczba_kolumn, plansza_nad);
    wypisz_plansze(liczba_wierszy, liczba_kolumn, plansza_nad);
}
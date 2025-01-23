#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define POLE_NIEODKRYTE '#'
#define POLE_ODKRYTE '.'
#define FLAGA 'F'
#define MINA '*'
#define POLE_BEZ_MIN '0'

// funkcja aktualizujaca na jego podstawie plansze
void aktualizuj_plansze (char **plansza_pod, char **plansza_nad, char dzialanie_na_polu, int x, int y) {
    switch (dzialanie_na_polu) {
    case 'r':
        plansza_nad[x][y] = POLE_ODKRYTE;
        break;
    
    case 'f':
        plansza_nad[x][y] = FLAGA;
        break;

    default:
        printf("\n Podano niepoprawne wejscie\n");
        break;
    }

}


// funkcja wypelniajaca plansze znakami niezaznaczenia
void wypelnienie_planszy(int liczba_wierszy, int liczba_kolumn, char **plansza) {
    for (int i = 0; i<liczba_wierszy; i++) {
        for (int j = 0; j<liczba_kolumn; j++) {
            plansza[i][j] = POLE_NIEODKRYTE;
        }
    }
}

// funkcja wypisujaca plansze
void wypisz_plansze(int liczba_wierszy, int liczba_kolumn, char **plansza) {
    printf("\n   ");
    for(int i = 1; i<=liczba_kolumn; i++) {
        printf("[%d]", i);
    }
    printf("\n");

    for(int i = 0; i<liczba_wierszy; i++) {
        printf("[%d]", i+1);
        for(int j = 0; j<liczba_kolumn; j++) {
            printf("[%c]", plansza[i][j]);
        }
        printf("\n");
    }
}

// funkcja konwertujaca char na int
char konwertuj_char_to_int(int licznik) {
    char wynik = '!';

    if(licznik == 0) {
        wynik = '0';
    }
    if(licznik == 1) {
        wynik = '1';
    }
    if(licznik == 2) {
        wynik = '2';
    }
    if(licznik == 3) {
        wynik = '3';
    }
    if(licznik == 4) {
        wynik = '4';
    }
    if(licznik == 5) {
        wynik = '5';
    }
    if(licznik == 6) {
        wynik = '6';
    }
    if(licznik == 7) {
        wynik = '7';
    }
    if(licznik == 8) {
        wynik = '8';
    }

    return wynik;
}

// funkcja badajaca
char badaj_punkt(int liczba_wierszy, int liczba_kolumn, char **plansza, int x, int y) {
    int licznik = 0;
    char wynik = '?';

    if(x>=0 && x<liczba_kolumn && y>=0 && y<liczba_wierszy) {
        //lewy gorny
        if(x-1>=0 && y-1>=0) {
            if(plansza[x-1][y-1] == MINA) {
                licznik++;
            }
        }
        //lewy
        if(x-1>=0) {
            if(plansza[x-1][y] == MINA) {
                licznik++;
            }
        }
        //lewy dolny
        if(x-1>=0 && y+1<liczba_wierszy) {
            if(plansza[x-1][y+1] == MINA) {
                licznik++;
            }
        }
        //dol
        if(y+1<liczba_wierszy) {
            if(plansza[x][y+1] == MINA) {
                licznik++;
            }
        }
        //prawy dolny
        if(x+1<liczba_kolumn && y+1<liczba_wierszy) {
            if(plansza[x+1][y+1] == MINA) {
                licznik++;
            }
        }
        //prawy
        if(x+1<liczba_kolumn) {
            if(plansza[x+1][y] == MINA) {
                licznik++;
            }
        }
        //prawy gorny
        if(x+1<liczba_kolumn && y-1>=0) {
            if(plansza[x+1][y-1] == MINA) {
                licznik++;
            }
        }
        //gora
        if(y-1>=0) {
            if(plansza[x][y-1] == MINA) {
                licznik++;
            }
        }
    }

    wynik = konwertuj_char_to_int(licznik);

    return wynik;
}


void oznacz_punkty_w_otoczeniu_punktu_poczatkowego(int liczba_wierszy, int liczba_kolumn, int poczatkowy_x, int poczatkowy_y, char **plansza) {

    if(poczatkowy_x>=0 && poczatkowy_x<liczba_kolumn && poczatkowy_y>=0 && poczatkowy_y<liczba_wierszy) {
 
        //srodek
        plansza[poczatkowy_y][poczatkowy_x] = POLE_BEZ_MIN;

        //lewy gorny
        if(poczatkowy_x-1>=0 && poczatkowy_y-1>=0) {
            plansza[poczatkowy_y-1][poczatkowy_x-1] = POLE_BEZ_MIN;
        }
        //lewy
        if(poczatkowy_x-1>=0) {
            plansza[poczatkowy_y][poczatkowy_x-1] = POLE_BEZ_MIN;
        }
        //lewy dolny
        if(poczatkowy_x-1>=0 && poczatkowy_y+1<liczba_wierszy) {
            plansza[poczatkowy_y+1][poczatkowy_x-1] = POLE_BEZ_MIN;
        }
        //dol
        if(poczatkowy_y+1<liczba_wierszy) {
            plansza[poczatkowy_y+1][poczatkowy_x] = POLE_BEZ_MIN;
        }
        //prawy dolny
        if(poczatkowy_x+1<liczba_kolumn && poczatkowy_y+1<liczba_wierszy) {
            plansza[poczatkowy_y+1][poczatkowy_x+1] = POLE_BEZ_MIN;
        }
        //prawy
        if(poczatkowy_x+1<liczba_kolumn) {
            plansza[poczatkowy_y][poczatkowy_x+1] = POLE_BEZ_MIN;
        }
        //prawy gorny
        if(poczatkowy_x+1<liczba_kolumn && poczatkowy_y-1>=0) {
            plansza[poczatkowy_y-1][poczatkowy_x+1] = POLE_BEZ_MIN;
        }
        //gora
        if(poczatkowy_y-1>=0) {
            plansza[poczatkowy_y-1][poczatkowy_x] = POLE_BEZ_MIN;
        }
    }
}



// TO DO: przerobic funkcje tak aby pierwszys strzal uzytkownika trafial w puste pole
// funkcja wypelniajaca plansze_pod bombami
void wypelnianie_bombami(int liczba_wierszy, int liczba_kolumn, int liczba_min, char **plansza_pod, int poczatkowy_x, int poczatkowy_y) {
    int i = 0;
    int wylosowany_x, wylosowany_y;

    int wynik_badania;
    oznacz_punkty_w_otoczeniu_punktu_poczatkowego(liczba_wierszy, liczba_kolumn, poczatkowy_x, poczatkowy_y, plansza_pod);
    wypisz_plansze(liczba_wierszy, liczba_kolumn, plansza_pod);
    //wstawianie min
    while(i<liczba_min) {
        wylosowany_x = rand() % (liczba_wierszy);
        wylosowany_y = rand() % (liczba_kolumn);
        //wynik_badania = badaj_czy_punkt_w_otoczeniu_punktu_poczatkowego(liczba_wierszy, liczba_kolumn, poczatkowy_x, poczatkowy_y, wylosowany_x, wylosowany_y);
        printf("Badany punkt x = %d, y = %d, wynik badania = %d\n", wylosowany_x, wylosowany_y, wynik_badania);
        if(plansza_pod[wylosowany_y][wylosowany_x] != MINA && plansza_pod[wylosowany_y][wylosowany_x] != POLE_BEZ_MIN/*(&& wynik_badania == 0) */){
            plansza_pod[wylosowany_y][wylosowany_x] = MINA;
            i++;
            printf("wstawiam mine w x = %d, y = %d\n", wylosowany_x, wylosowany_y);
        }
    }

    //wstawianie cyfr
    for(int i = 0; i<liczba_wierszy; i++) {
        for(int j = 0; j<liczba_kolumn; j++) {
            if(plansza_pod[i][j] == '\0') {
                plansza_pod[i][j] = '0';
            }
            if(plansza_pod[i][j] != MINA) {
                plansza_pod[i][j] = badaj_punkt(liczba_wierszy, liczba_kolumn, plansza_pod, i, j);
            }
        }
    }

}

int main()
{
    srand(time(NULL));

    int trudnosc;               //Poziom trudnosci gry
    int liczba_wierszy, liczba_kolumn, liczba_min, mnoznik_punktow;
    int stan_gry = 0;           // -1 - przegrana, 0 - trwa, 1 - wygrana
    int x, y;                   // Wspolrzedne pola wpisywane przez uzytkownika
    char dzialanie_na_polu;     // Wybor miedzy odslanieciem pola a wstawieniu flagi (r/f)

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
    printf("\n Rozpoczynamy grę, podaj tryb zaznaczania pola i wspolrzedne: ");
    scanf(" %c %d %d", &dzialanie_na_polu, &x, &y);
    printf("\n");

    printf("Uytkownik podał x=%d, y=%d\n", x, y);
    wypelnianie_bombami(liczba_wierszy, liczba_kolumn, liczba_min, plansza_pod, x-1, y-1);
    aktualizuj_plansze(plansza_pod, plansza_nad, dzialanie_na_polu, y-1, x-1);

    wypisz_plansze(liczba_wierszy, liczba_kolumn, plansza_pod);

    while(stan_gry == 0) {
        wypisz_plansze(liczba_wierszy, liczba_kolumn, plansza_nad);

        printf("\n Podaj tryb zaznaczania pola i wspolrzedne: ");
        scanf(" %c %d %d", &dzialanie_na_polu, &x, &y);
        printf("\n");

        aktualizuj_plansze(plansza_pod, plansza_nad, dzialanie_na_polu, y-1, x-1);

        wypisz_plansze(liczba_wierszy, liczba_kolumn, plansza_nad);
        stan_gry = 1;
    }

    wypisz_plansze(liczba_wierszy, liczba_kolumn, plansza_pod);

}
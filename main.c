#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define POLE_NIEODKRYTE '#'
#define POLE_ODKRYTE '0'
#define FLAGA 'F'
#define MINA '*'
#define POLE_BEZ_MIN '0'

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


// funkcja wypelniajaca plansze_pod bombami
void wypelnianie_bombami(int liczba_wierszy, int liczba_kolumn, int liczba_min, char **plansza_pod, int poczatkowy_x, int poczatkowy_y) {
    int i = 0;
    int wylosowany_x, wylosowany_y;

    int wynik_badania;
    oznacz_punkty_w_otoczeniu_punktu_poczatkowego(liczba_wierszy, liczba_kolumn, poczatkowy_x, poczatkowy_y, plansza_pod);
    // DIAGNOSTYCZNE wypisz_plansze(liczba_wierszy, liczba_kolumn, plansza_pod);
    //wstawianie min
    while(i<liczba_min) {
        wylosowany_x = rand() % (liczba_wierszy);
        wylosowany_y = rand() % (liczba_kolumn);

        if(plansza_pod[wylosowany_y][wylosowany_x] != MINA && plansza_pod[wylosowany_y][wylosowany_x] != POLE_BEZ_MIN) {
            plansza_pod[wylosowany_y][wylosowany_x] = MINA;
            i++;
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

void odkrycie(int liczba_wierszy, int liczba_kolumn, int poczatkowy_x, int poczatkowy_y, char **plansza_nad, char **plansza_pod) {
    // DIAGNOSTYCZNE printf("Przekazne x, y do funkcjo odkrycie: x=%d, y=%d", poczatkowy_x, poczatkowy_y);
    if(poczatkowy_x>=0 && poczatkowy_x<liczba_kolumn && poczatkowy_y>=0 && poczatkowy_y<liczba_wierszy) {
        plansza_nad[poczatkowy_y][poczatkowy_x] = plansza_pod[poczatkowy_y][poczatkowy_x];

        if(plansza_pod[poczatkowy_y][poczatkowy_x] == '0') {
            //lewy gorny
            if(poczatkowy_x-1>=0 && poczatkowy_y-1>=0) {
                if(plansza_pod[poczatkowy_y-1][poczatkowy_x-1] != '0' && plansza_pod[poczatkowy_y-1][poczatkowy_x-1] != MINA) {
                    plansza_nad[poczatkowy_y-1][poczatkowy_x-1] = plansza_pod[poczatkowy_y-1][poczatkowy_x-1];
                }
                else if(plansza_pod[poczatkowy_y-1][poczatkowy_x-1] == '0' && plansza_nad[poczatkowy_y-1][poczatkowy_x-1] == POLE_NIEODKRYTE) {
                    odkrycie(liczba_wierszy, liczba_kolumn, poczatkowy_x-1, poczatkowy_y-1, plansza_nad, plansza_pod);
                }
            }
            //lewy
            if(poczatkowy_x-1>=0) {
                if(plansza_pod[poczatkowy_y][poczatkowy_x-1] != '0' && plansza_pod[poczatkowy_y][poczatkowy_x-1] != MINA) {
                    plansza_nad[poczatkowy_y][poczatkowy_x-1] = plansza_pod[poczatkowy_y][poczatkowy_x-1];
                }
                else if(plansza_pod[poczatkowy_y][poczatkowy_x-1] == '0' && plansza_nad[poczatkowy_y][poczatkowy_x-1] == POLE_NIEODKRYTE) {
                    odkrycie(liczba_wierszy, liczba_kolumn, poczatkowy_x-1, poczatkowy_y, plansza_nad, plansza_pod);
                }
            }
            //lewy dolny
            if(poczatkowy_x-1>=0 && poczatkowy_y+1<liczba_wierszy) {
                if(plansza_pod[poczatkowy_y+1][poczatkowy_x-1] != '0' && plansza_pod[poczatkowy_y+1][poczatkowy_x-1] != MINA) {
                    plansza_nad[poczatkowy_y+1][poczatkowy_x-1] = plansza_pod[poczatkowy_y+1][poczatkowy_x-1];
                }
                else if(plansza_pod[poczatkowy_y+1][poczatkowy_x-1] == '0' && plansza_nad[poczatkowy_y+1][poczatkowy_x-1] == POLE_NIEODKRYTE) {
                    odkrycie(liczba_wierszy, liczba_kolumn, poczatkowy_x-1, poczatkowy_y+1, plansza_nad, plansza_pod);
                }
            }
            //dol
            if(poczatkowy_y+1<liczba_wierszy) {
                if(plansza_pod[poczatkowy_y+1][poczatkowy_x] != '0' && plansza_pod[poczatkowy_y+1][poczatkowy_x] != MINA) {
                    plansza_nad[poczatkowy_y+1][poczatkowy_x] = plansza_pod[poczatkowy_y+1][poczatkowy_x];
                }
                else if(plansza_pod[poczatkowy_y+1][poczatkowy_x] == '0' && plansza_nad[poczatkowy_y+1][poczatkowy_x] == POLE_NIEODKRYTE) {
                    odkrycie(liczba_wierszy, liczba_kolumn, poczatkowy_x, poczatkowy_y+1, plansza_nad, plansza_pod);
                }
            }
            //prawy dolny
            if(poczatkowy_x+1<liczba_kolumn && poczatkowy_y+1<liczba_wierszy) {
                if(plansza_pod[poczatkowy_y+1][poczatkowy_x+1] != '0' && plansza_pod[poczatkowy_y+1][poczatkowy_x+1] != MINA) {
                    plansza_nad[poczatkowy_y+1][poczatkowy_x+1] = plansza_pod[poczatkowy_y+1][poczatkowy_x+1];
                }
                else if(plansza_pod[poczatkowy_y+1][poczatkowy_x+1] == '0' && plansza_nad[poczatkowy_y+1][poczatkowy_x+1] == POLE_NIEODKRYTE) {
                    odkrycie(liczba_wierszy, liczba_kolumn, poczatkowy_x+1, poczatkowy_y+1, plansza_nad, plansza_pod);
                }
            }
            //prawy
            if(poczatkowy_x+1<liczba_kolumn) {
                if(plansza_pod[poczatkowy_y][poczatkowy_x+1] != '0' && plansza_pod[poczatkowy_y][poczatkowy_x+1] != MINA) {
                    plansza_nad[poczatkowy_y][poczatkowy_x+1] = plansza_pod[poczatkowy_y][poczatkowy_x+1];
                }
                else if(plansza_pod[poczatkowy_y][poczatkowy_x+1] == '0' && plansza_nad[poczatkowy_y][poczatkowy_x+1] == POLE_NIEODKRYTE) {
                    odkrycie(liczba_wierszy, liczba_kolumn, poczatkowy_x+1, poczatkowy_y, plansza_nad, plansza_pod);
                }
            }
            //prawy gorny
            if(poczatkowy_x+1<liczba_kolumn && poczatkowy_y-1>=0) {
                if(plansza_pod[poczatkowy_y-1][poczatkowy_x+1] != '0' && plansza_pod[poczatkowy_y-1][poczatkowy_x+1] != MINA) {
                    plansza_nad[poczatkowy_y-1][poczatkowy_x+1] = plansza_pod[poczatkowy_y-1][poczatkowy_x+1];
                }
                else if(plansza_pod[poczatkowy_y-1][poczatkowy_x+1] == '0' && plansza_nad[poczatkowy_y-1][poczatkowy_x+1] == POLE_NIEODKRYTE) {
                    odkrycie(liczba_wierszy, liczba_kolumn, poczatkowy_x+1, poczatkowy_y-1, plansza_nad, plansza_pod);
                }
            }
            //gora
            if(poczatkowy_y-1>=0) {
                if(plansza_pod[poczatkowy_y-1][poczatkowy_x] != '0' && plansza_pod[poczatkowy_y-1][poczatkowy_x] != MINA) {
                    plansza_nad[poczatkowy_y-1][poczatkowy_x] = plansza_pod[poczatkowy_y-1][poczatkowy_x];
                }
                else if(plansza_pod[poczatkowy_y-1][poczatkowy_x] == '0' && plansza_nad[poczatkowy_y-1][poczatkowy_x] == POLE_NIEODKRYTE) {
                    odkrycie(liczba_wierszy, liczba_kolumn, poczatkowy_x, poczatkowy_y-1, plansza_nad, plansza_pod);
                }
            }
        }
        
    }
}

// funkcja aktualizujaca na jego podstawie plansze
void aktualizuj_plansze (int liczba_wierszy, int liczba_kolumn, char **plansza_pod, char **plansza_nad, char dzialanie_na_polu, int x, int y, int licznik_flag, int liczba_min) {
    switch (dzialanie_na_polu) {
    case 'r':
        //plansza_nad[x][y] = POLE_ODKRYTE;
        if(plansza_nad[x][y] != POLE_ODKRYTE && plansza_nad[x][y] != FLAGA && plansza_nad[x][y] !='1' && plansza_nad[x][y] != '2' && plansza_nad[x][y] != '3' && plansza_nad[x][y] != '4' && plansza_nad[x][y] != '5' && plansza_nad[x][y] != '6' && plansza_nad[x][y] != '7' && plansza_nad[x][y] != '8') {
            odkrycie(liczba_wierszy, liczba_kolumn, y, x, plansza_nad, plansza_pod);
        }
        else {
            printf("\n W tym miejscu nie mozna odslonic pola !!!\n");
        }

        break;
    
    case 'f':
        if(licznik_flag<liczba_min) {
            if(plansza_nad[x][y] == POLE_NIEODKRYTE) {
                plansza_nad[x][y] = FLAGA;
                licznik_flag++;         
            }
            else if(plansza_nad[x][y] == FLAGA) {
                plansza_nad[x][y] = POLE_NIEODKRYTE;
                licznik_flag--;
            }
            else {
                printf("\n W tym miejscu nie mozna wstawic flagi !!!\n");
            }
        }
        else {
            printf("\nUmieszczono maksymalna ilosc flag - Prosze usunac inna flage, aby umiescic kolejna\n");
        }
        break;

    default:
        printf("\n Podano niepoprawne wejscie\n");
        break;
    }

}

// funkcja sprawdzajaca czy zostaly osiagniete warunki zwycieztwa
int czy_wygrana(int liczba_wierszy, int liczba_kolumn, int liczba_min, char **plansza_nad, int stan_gry, int x, int y) {

    int liczba_rozstawionych_flag = 0;
    int liczba_odlsonietych_pol = 0;

    if(plansza_nad[x][y] == MINA){
        stan_gry = -1;
        return stan_gry;
    }

    for(int i = 0; i<liczba_wierszy; i++) {
        for(int j = 0; j<liczba_kolumn; j++) {
            if(plansza_nad[i][j] == FLAGA) {
                liczba_rozstawionych_flag++;
            }
            if(plansza_nad[i][j] == POLE_ODKRYTE || plansza_nad[i][j] == '1' || plansza_nad[i][j] == '2' || plansza_nad[i][j] == '3' || plansza_nad[i][j] == '4' || plansza_nad[i][j] == '5' || plansza_nad[i][j] == '6' || plansza_nad[i][j] == '7' || plansza_nad[i][j] == '8') {
                liczba_odlsonietych_pol++;
            }
        }
    }

    if(liczba_rozstawionych_flag == liczba_min && liczba_odlsonietych_pol == (liczba_kolumn * liczba_wierszy - liczba_min)) {
        stan_gry = 1;
        return stan_gry;
    }

    return stan_gry;
}

int main()
{
    srand(time(NULL));

    int trudnosc;               //Poziom trudnosci gry
    int liczba_wierszy, liczba_kolumn, liczba_min, mnoznik_punktow;
    int stan_gry = 0;           // -1 - przegrana, 0 - trwa, 1 - wygrana
    int x, y;                   // Wspolrzedne pola wpisywane przez uzytkownika
    char dzialanie_na_polu;     // Wybor miedzy odslanieciem pola a wstawieniu flagi (r/f)
    int licznik_flag = 0;       // Liczba flag

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
    printf("\n Rozpoczynamy grę, wspolrzedne poczatkowe: ");
    scanf("%d %d", &x, &y);
    printf("\n");

    printf("Uytkownik podał x=%d, y=%d\n", x, y);
    wypelnianie_bombami(liczba_wierszy, liczba_kolumn, liczba_min, plansza_pod, x-1, y-1);
    // DIAGNOSTYCZNE wypisz_plansze(liczba_wierszy, liczba_kolumn, plansza_pod);
    odkrycie(liczba_wierszy, liczba_kolumn, x-1, y-1, plansza_nad, plansza_pod);

    wypisz_plansze(liczba_wierszy, liczba_kolumn, plansza_nad);
    printf("\n");
    // DIAGNOSTYCZNIE wypisz_plansze(liczba_wierszy, liczba_kolumn, plansza_pod);

    while(stan_gry == 0) {
        printf("\nS--------DIAGNOSTYCZNA PLANSZA POD--------------S\n");
        wypisz_plansze(liczba_wierszy, liczba_kolumn, plansza_pod);
        printf("\nK--------DIAGNOSTYCZNA PLANSZA POD--------------K\n");

        printf("\n Podaj tryb zaznaczania pola i wspolrzedne: ");
        scanf(" %c %d %d", &dzialanie_na_polu, &x, &y);
        printf("\n");

        aktualizuj_plansze(liczba_wierszy, liczba_kolumn, plansza_pod, plansza_nad, dzialanie_na_polu, y-1, x-1, licznik_flag, liczba_min);
        wypisz_plansze(liczba_wierszy, liczba_kolumn, plansza_nad);
        /*
        if(plansza_pod[y-1][x-1] == MINA && plansza_nad[y-1][x-1] != FLAGA) {
            stan_gry = -1;
        }
        */
        stan_gry = czy_wygrana(liczba_wierszy, liczba_kolumn, liczba_min, plansza_nad, stan_gry, y-1, x-1);
    }

    if(stan_gry == 1) {
        printf("\n!!!!! WYGRANA !!!!!\n");
    }
    else {
        printf("\nXXXXX PRZEGRANA XXXXX\n");
    }



    // DIAGNOSTYCZNIE wypisz_plansze(liczba_wierszy, liczba_kolumn, plansza_pod);

}
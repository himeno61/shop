#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum Rodzaj{OWOC, WARZYWO, INNY}; // Wyliczenie stosujemy, gdy chcemy oznaczyc wiele predefiniowanych rodzajow jakiejs cechy
// Jest to wygodniejszy zapis rownowazny const int OWOC = 0; const int WARZYWO = 1; const int INNY = 2;

#define NAZWA_LEN 16
#define IMIE_LEN 8
#define LICZBA_PRZED 3

struct tablica
{
    char *wsk;
    int len;
};

void alok(struct tablica* strukt, char *tekst)
{
    strukt->len=strlen(tekst)+1;
    strukt->wsk=malloc(strukt->len);
    strcpy(strukt->wsk,tekst);
}

void zwolnij(struct tablica *a)
{
    if (a->wsk)
    {
     free(a->wsk);
     a->wsk=NULL;
    }
}

struct Przedmiot{ // Struktura jest zbiorem pol, opisanym typami zmiennych
    struct tablica nazwa;
	struct tablica kolor;
	float cena;
	enum Rodzaj rodzaj;
};

struct Klient{ // W strukturach mozemy uzywac innych struktur
	char imie[IMIE_LEN];
	float gotowka;
	struct Przedmiot* koszyk[LICZBA_PRZED];
};

void print_przedmiot(struct Przedmiot p){ // Do pol struktury odwolujemy sie operatorem "."
	printf("%s jest %s i kosztuje %f.\n", p.nazwa.wsk, p.kolor.wsk, p.cena);
}

void opisz_przedmiot(struct Przedmiot* p, char* nazwa, char* kolor, enum Rodzaj rodzaj, float cena){
	alok(&p->nazwa, nazwa); // Do pol wskaznika na strukture odwolujemy sie operatorem "->"
	alok(&p->kolor, kolor);
	p->cena = cena;
	p->rodzaj = rodzaj;
}

void zwolnij_przedmiot(struct Przedmiot* p)
{
zwolnij(&p->nazwa);
zwolnij(&p->kolor);
}

void zaplac(struct Klient* k){
	float suma = 0.0, suma2 = 0.0;
	int n;

	for(n = 0; n < LICZBA_PRZED; n++)
		suma += k->koszyk[n]->cena;

	if(suma < k->gotowka)
		printf("Klient %s zaplacil %f.\n", k->imie, suma);
	else
	{
		printf("Klient %s nie moze zaplacic %f!\n", k->imie, suma);
		suma2=(k->koszyk[0]->cena)+ (k->koszyk[1]->cena);
		if(suma2<k->gotowka) printf("\n Klienta stac na same owoce");
    }
}

int main(){
	struct Przedmiot banan, pomarancza, pomidor, mleko; // Zmienne odwolujace sie do struktu definiujemy podobnie do typow podstawowych

	opisz_przedmiot(&banan, "Banan", "zolty", OWOC, 1.0);
	opisz_przedmiot(&pomarancza, "Pomarancza", "pomaranczowa", OWOC, 1.5);
	opisz_przedmiot(&pomidor, "Pomidor", "czerwony", WARZYWO, 1.2);
	opisz_przedmiot(&mleko, "Mleko", "biale", INNY, 2.0);

	print_przedmiot(banan);
	print_przedmiot(pomarancza);
	print_przedmiot(pomidor);
	print_przedmiot(mleko);

	printf("\nRozmiar struktury Przedmiot: %lu\n", sizeof(struct Przedmiot)); // rozmiar struktury jest suma rozmiarow typow ktore zawiera
	printf("Rozmiar struktury Klient: %lu\n\n", sizeof(struct Klient)); // dlaczego tu jest taki rozmiar?

	struct Klient* klient = malloc(sizeof(struct Klient)); // do struktur rowniez mozemy przypisac pamiec dynamicznie

	klient->gotowka = 3.0;
	strcpy(klient->imie, "Ala"); // dlaczego tu robimy tak, a nie poprostu przypisujemy?
	klient->koszyk[0] =&banan;
	klient->koszyk[1] = &pomarancza;
	klient->koszyk[2] = &mleko;


	zaplac(klient);
	zwolnij_przedmiot(&banan);
	zwolnij_przedmiot(&pomarancza);
	zwolnij_przedmiot(&pomidor);
	zwolnij_przedmiot(&mleko);
	return 0;
}

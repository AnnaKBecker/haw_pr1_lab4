#include <stdio.h>
#include <math.h>

int getint(char text[], int grenzwert);
float getfloat(char text[], float grenzwert);
void formel_auswertung(int stadt, int winkel, float spitzenleistung);
void printfinale(float ergebnis[]);
void fill(char zeichen, int anzahl);

int main(void) {
    printf("\n \n");
    printf("Dies ist ein Programm eines PV-Rechners, welcher die monatlichen und jährlichen Energieerträge errechnet.\nAbhängig vom Ort und der dortigen Globalstrahlung sowie der neigung und Spitzenleistung der PV-Anlage.\n");
    fill('_', 100);
    printf("\n\n");
    printf("EINFACHER PV-RECHNER \n\n\n");
  

    int stadt;
    int winkel;
    float nutzereingabe_spitzenleistung;

    stadt = getint("BITTE WAEHLEN SIE EINEN ORT AUS\n(1 = Berlin, 2 = Kassel, 3 = Stuttgart, 4 = Freiburg, 5 = Hamburg): ", 5);
    printf("\n");

    winkel = getint("WIE WIRD IHRE PV-ANLAGE AUSGERICHTET ?\n(1 = Horizontal, 2 = -30 Grad Sudlich, 3 = -45 Grad Suedlich, 4 = -60 Grad Suedlich): ", 4);
    printf("\n");

    nutzereingabe_spitzenleistung = getfloat("Wie gross ist die Spitzenleistung (kWp)\n[Werteberich zwischen 1 und 30.] ", 30);
    fill('_', 100);

    formel_auswertung(stadt, winkel, nutzereingabe_spitzenleistung);

    return 0;
}

int getint(char text[], int grenzwert) {
    int retval;
    int ergebnis;
    int korrekt = 0;

    while (korrekt == 0) {
        printf("%s", text);
        retval = scanf("%d", &ergebnis);
        if (retval != 1)
            printf("Dies ist eine ungültige Angabe !\n");
        else if (ergebnis < 1 || ergebnis > grenzwert)
            printf("Die Eingabe war ausserhalb des Bereichs!");
        else
            korrekt++;

        while (getchar() != '\n') {}
    }

    return ergebnis;
}

float getfloat(char text[], float grenzwert) {
    int retval;
    float ergebnis2;
    int korrekt = 0;

    while (korrekt == 0) {
        printf("%s", text);
        retval = scanf("%f", &ergebnis2);
        if (retval != 1)
            printf("Ungültige Eingabe !\n");
        else if (ergebnis2 < 1 || ergebnis2 > grenzwert)
            printf("Eingabe ausserhalb des Wertebereichs!");
        else
            korrekt++;

        while (getchar() != '\n') {}

    }
    return ergebnis2;
}

void formel_auswertung(int stadt, int winkel, float spitzenleistung) {
    float ergebnis[12];
    int monate_tage[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    float HH_mittelwert[12] = {0.52f, 1.13f, 2.23f, 3.55f, 4.67f, 5.44f, 4.82f, 4.34f, 2.79f, 1.49f, 0.67f, 0.40f};

    float city[5][12] = {
        {19, 33, 75, 128, 160, 166, 158, 134, 94, 51, 26, 15},
        {20, 34, 77, 123, 150, 162, 154, 132, 90, 52, 25, 16},
        {29, 45, 85, 130, 153, 174, 164, 140, 99, 62, 36, 24},
        {29, 45, 84, 129, 153, 172, 166, 141, 104, 63, 38, 24}
    };

    float ausrichtung[4][12] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1.44f, 1.40f, 1.17f, 1.08f, 1.00f, 0.96f, 0.97f, 1.03f, 1.17f, 1.30f, 1.47f, 1.42f},
        {1.57f, 1.50f, 1.19f, 1.05f, 0.94f, 0.90f, 0.91f, 1.00f, 1.18f, 1.37f, 1.61f, 1.55f},
        {1.63f, 1.54f, 1.15f, 0.98f, 0.85f, 0.81f, 0.83f, 0.92f, 1.14f, 1.38f, 1.68f, 1.61f}
    };

    if (stadt == 5) {
        for (int i = 0; i < 12; i++) {
            HH_mittelwert[i] = HH_mittelwert[i] * monate_tage[i];
            city[4][i] = HH_mittelwert[i];
        }
    }

    for (int i = 0; i < 12; i++) {
        ergebnis[i] = city[stadt - 1][i] * ausrichtung[winkel - 1][i] * spitzenleistung
    ;
    }

    printfinale(ergebnis);
}

void printfinale(float ergebnis[]) {
    printf("\n Berechneter PV-Ertrag: \n\n");
    printf("  Jan |  Feb |  Mar |  Apr |  Mai |  Jun |  Jul |  Aug |  Sep |  Okt |  Nov |  Dez      | | Gesamt [kWh]\n");

    for (int i = 0; i < 12; i++) {
        printf(" %4.d |", lround(ergebnis[i]));
    }

    for (int i = 1; i < 12; i++) {
        ergebnis[i] += ergebnis[i - 1];
    }

    printf(" | %d\n", lround(ergebnis[11]));
}

void fill(char zeichen, int anzahl)
{
    for (int i = 0; i < anzahl; i++)
        printf("%c", zeichen);
}
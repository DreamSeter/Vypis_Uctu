#include <stdio.h>

#define UROKOVA_MIRA 5.61

#define DAN_Z_UROKU 0.15

#define MIN_POCATECNI_VKLAD 1000
#define MAX_POCATECNI_VKLAD 100000

#define MIN_MESICNI_VKLAD 100
#define MAX_MESICNI_VKLAD 10000



int cisticBufer() {
    int buffer = 0;
    while (getchar() != '\n') {
        buffer++;
    }
    return buffer;
}

double kontrolaCislo(double min, double max) {
    double cislo;
    int spravne = 0;

    while (spravne == 0) {
        scanf("%lf", &cislo);
        cisticBufer();

        if (cislo < min) {
            printf("Cislo je mensi nez minimum. Zadej znovu:\n");
        }
        else {
            if (cislo > max) {
                printf("Cislo je vetsi nez maximum. Zadej znovu:\n");
            }
            else {
                spravne = 1;
            }
        }
    }

    return cislo;
}


int jePrestupny(int rok) {
    return(rok %4 == 0 && rok % 100 != 0) || rok % 400 == 0;
}


int DnyVMesici(int mesic, int rok) {
    int dni;
    if (mesic == 2) {
        if (jePrestupny(rok))
            dni = 29;
        else
            dni = 28;
    }
    else {
        int dnyMesice[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        dni = dnyMesice[mesic - 1]; 
    }

    return dni;
}


int main() {
    double pocatecni_stav;
    double mesicni_vklad;
    double stav;

    double zacatek_mesice;
    double urok;
    double dan;
    double cisty_urok;

    int mesic;
    int den;
    int rok;

    printf("Zadej rok:");
    scanf("%d" , &rok);
    cisticBufer();

    printf("Zadej pocatecni stav mezi %d a %d:\n", MIN_POCATECNI_VKLAD, MAX_POCATECNI_VKLAD);
    pocatecni_stav = kontrolaCislo(MIN_POCATECNI_VKLAD, MAX_POCATECNI_VKLAD);

    printf("Zadej mesicni vklad mezi %d a %d:\n", MIN_MESICNI_VKLAD, MAX_MESICNI_VKLAD);
    mesicni_vklad = kontrolaCislo(MIN_MESICNI_VKLAD, MAX_MESICNI_VKLAD);

    stav = pocatecni_stav;

    printf( "Sporici ucet\n");
    printf( "Rocni urokova mira: %.2f %%\n", UROKOVA_MIRA);
    printf( "Stav na zacatku roku %d: %.2f Kc\n\n", rok, stav);

    printf( "  datum          zacatek          vklad         urok       dan        konec\n");
    printf( "----------------------------------------------------------------------------\n");
    for (mesic = 1; mesic <= 12; mesic++) {
        den = DnyVMesici(mesic, rok);
        zacatek_mesice = stav + mesicni_vklad;

        urok = zacatek_mesice * ((UROKOVA_MIRA / 100) / 12.0);
        dan = urok * DAN_Z_UROKU;

        cisty_urok = urok - dan;
        stav = zacatek_mesice + cisty_urok;

        printf("%02d.%02d.%d  %12.2fKc  %10.2fKc  %10.2fKc  %8.2fKc  %12.2fKc\n",
                den, mesic, rok,
                zacatek_mesice,
                mesicni_vklad,
                urok,
                dan,
                stav);
    }

    printf( "----------------------------------------------------------------------------\n");
    printf( "Stav na konci roku %d: %.2f Kc\n", rok, stav);
    printf( "Usetril jsi: %.2f Kc\n", stav - pocatecni_stav);

    return 0;
}


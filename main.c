#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char koltuk;
int Hasilat;
struct Matine
{
    koltuk Koltuk[50];
};
typedef struct Salon
{
    struct Matine matine[5];
} s;
enum
{
    red = 1,
    green = 2,
    blue = 3
};
struct Sinema
{
    struct Salon salon[3];
} sinema;

void ilkKayit()
{
    FILE *kEkle = fopen("sifre.txt", "w");
    FILE *logOlustur = fopen("log.txt", "w");
    fclose(logOlustur);
    char kskont[40];
    char kadi[20];
    char sifre[20];
    printf("Kullanici Adi:");
    scanf("%s", kadi);
    printf("Sifre:");
    scanf("%s", sifre);
    strcpy(kskont, kadi);
    strcat(kskont, sifre);
    if (kEkle == NULL)
    {
        printf("Veri okuma hatasi!.\n");
        exit(1);
    }
    fprintf(kEkle, "%s", kskont);
    fclose(kEkle);
    printf("Kayit Yapildi.\n");
}

int kullaniciEkleKontrol()
{
    int secim;
    while (1)
    {
        printf("Giris yapmak icin > 1\n");
        printf("Kayit yapmak icin > 2\n");
        printf("Seciminiz:");
        scanf("%d", &secim);
        if (secim == 1 || secim == 2)
        {
            break;
        }
        else
        {
            printf("Hatali secim\n");
        }
    }

    FILE *kKontrol = fopen("sifre.txt", "r");
    FILE *kEkle = fopen("sifre.txt", "a");
    char kkont[40];
    char kskont[40];
    char kadi[20];
    char sifre[20];
    int kekontrol = 0;
    printf("Kullanici Adi:");
    scanf("%s", kadi);
    printf("Sifre:");
    scanf("%s", sifre);

    if (kKontrol == NULL || kEkle == NULL)
    {
        printf("Veri okuma hatasi!.\n");
        exit(1);
    }
    switch (secim)
    {
    case 1:
        while (!feof(kKontrol))
        {
            fscanf(kKontrol, "%s", kkont);
            strcpy(kskont, kadi);
            strcat(kskont, sifre);
            int a = strcmp(kkont, kskont);
            if (a == 0)
            {
                kekontrol = 1;
                fclose(kKontrol);
                fclose(kEkle);
                printf("Giris Yapildi.\n");
                return kekontrol;
            }
        }
        kekontrol = -1;
        return kekontrol;
    case 2:
        strcpy(kskont, kadi);
        strcat(kskont, sifre);
        fprintf(kEkle, "\n%s", kskont);
        fclose(kKontrol);
        fclose(kEkle);
        printf("Kayit Yapildi.\n");
        kekontrol = 0;
        return kekontrol;
    }
}

int hasilatHesap(int ogrtam)
{
    if (ogrtam == 1)
    {
        Hasilat += 20;
    }
    else if (ogrtam == 0)
    {
        Hasilat += 30;
    }
    else
    {
    }
    FILE *hasilatYaz = fopen("hasilat.txt", "w");
    fprintf(hasilatYaz, "Toplam Hasilat: %d", Hasilat);
    fclose(hasilatYaz);
    return Hasilat;
}

void hasilat()
{
    int toplam = hasilatHesap(-1);
    printf("Toplam Hasilat:%d TL\n", toplam);
}

int biletAl()
{
    int salonno;
    int matineno;
    int koltukno;
    int kontrol;
    int tekrarAlinacakMi;
    int ogrTam;
    char salonAd[6];

    while (1)
    {
        printf("Ogrenci Misiniz? EVET(1) - HAYIR(0):");
        scanf("%d", &ogrTam);
        if (ogrTam >= 2 || ogrTam <= -1)
        {
            printf("Yanlis secim\n");
        }
        else
        {
            break;
        }
    }
    while (1)
    {
        printf("Salon Seciniz RED - GREEN - BLUE:");
        scanf("%s", salonAd);
        int sc = strcmp(salonAd, "RED");
        if (sc == 0)
        {
            salonno = red;
        }
        sc = strcmp(salonAd, "GREEN");
        if (sc == 0)
        {
            salonno = green;
        }
        sc = strcmp(salonAd, "BLUE");
        if (sc == 0)
        {
            salonno = blue;
        }
        if (salonno > 3 || salonno < 1)
        {
            printf("Yanlis secim\n");
        }
        else
        {
            break;
        }
    }
    while (1)
    {
        printf("Matine Seciniz:");
        scanf("%d", &matineno);
        if (matineno > 5 || matineno < 1)
        {
            printf("Yanlis secim\n");
        }
        else
        {
            break;
        }
    }
    while (1)
    {
        printf("Koltuk Seciniz:");
        scanf("%d", &koltukno);
        if (koltukno > 50 || koltukno < 1)
        {
            printf("Yanlis secim\n");
        }
        else
        {
            break;
        }
    }

    if (sinema.salon[salonno].matine[matineno].Koltuk[koltukno] == 1)
    {
        kontrol = 2;
        printf("Almak Istediginiz Koltuk Dolu\n");
    }
    else
    {
        kontrol = 1;
    }

    if (kontrol == 1)
    {
        sinema.salon[salonno].matine[matineno].Koltuk[koltukno] = 1;
        printf("Bilet alindi.\n");
        FILE *biletyaz = fopen("log.txt", "a");
        fprintf(biletyaz, "%s Salon %d.Matine %d. Koldutk Satildi.\n", salonAd, matineno, koltukno);
        fclose(biletyaz);
        hasilatHesap(ogrTam);
        printf("Bilet alacak misiniz EVET(1)-HAYIR(0):");
        scanf("%d", &tekrarAlinacakMi);
        return tekrarAlinacakMi;
    }
}

void biletleriGotuntule()
{
    int Ssecim;
    int Msecim;
    int koltukSay = 0;
    char salonAd[6];
    FILE *biletGor = fopen("log.txt", "r");
    printf("Goruntulemek istediginiz salon Red(1) - Green(2) - Blue(3):");
    scanf("%d", &Ssecim);
    printf("Goruntulemek istediginiz matine:");
    scanf("%d", &Msecim);
    for (int i = 0; i < 50; ++i)
    {
        if (sinema.salon[Ssecim].matine[Msecim].Koltuk[i] == 1)
        {
            koltukSay += 1;
        }
    }
    if (Ssecim == red)
    {
        strcpy(salonAd, "RED");
    }
    else if (Ssecim == green)
    {
        strcpy(salonAd, "GREEN");
    }
    else if (Ssecim == blue)
    {
        strcpy(salonAd, "BLUE");
    }
    printf("%s Salonda %d. Matinede %d kisi suan izlemekte.\n", salonAd, Msecim, koltukSay);
    fclose(biletGor);
}

int AnaSayfa()
{
    printf("* * * Sinema Otomasyonu * * *\n");
girisedon:
    while (1)
    {
        int a = kullaniciEkleKontrol();
        if (a == 1)
        {
            break;
        }
        else if (a == 0)
        {
        }
        else
        {
            printf("Hatali Giris!\n");
        }
    }

    while (1)
    {
        int secim;
        int cikis;
        if (cikis == 1)
        {
            break;
        }
        printf("\n------ ANA MENU ------\n");
        printf("Bilet almak icin > 1\n");
        printf("Hasilat gormek icin > 2\n");
        printf("Izleyici sayisi icin > 3\n");
        printf("Girise donmek icin > 4\n");
        printf("Cikmak icin > 5\n");
        printf("Secim bekleniyor:");
        scanf("%d", &secim);
        switch (secim)
        {
        case 1:
            while (1)
            {
                int a = biletAl();
                if (a == 0)
                    break;
            }
            break;
        case 2:
            hasilat();
            break;
        case 3:
            biletleriGotuntule();
            break;
        case 4:
            goto girisedon;
        case 5:
            cikis = 1;
            break;
        default:
            printf("Hatali secim yaptiniz\n");
            break;
        }
    }
}

int main()
{
    ilkKayit();
    AnaSayfa();
    return 0;
}
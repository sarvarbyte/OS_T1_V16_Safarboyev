/*
 * OS_T1_V16_Safarboyev — 1-topshiriq, 16-variant
 * 1-masala: [a, b] oralig'idagi Armstrong sonlari (100 <= a <= b <= 999999),
 *           daraja pow() siz, o'zimiz yozgan butun sonli funksiya bilan.
 * 2-masala: void raqamlarga(int n, int *r, int *k) — sonni raqamlarga ajratib,
 *           massivga va raqamlar sonini pointerga yozadi.
 */
#include <stdio.h>
#include <string.h>

#define MIN_CHEGARA 100
#define MAX_CHEGARA 999999
#define MAX_RAQAM   10      /* int sonda ko'pi bilan 10 ta raqam bo'ladi */
#define SATR_HAJMI  100

/* asos^kor ni faqat butun sonlarda hisoblaydi.
   pow() double qaytaradi va yaxlitlashda xato berishi mumkin. */
int daraja(int asos, int kor)
{
    int natija = 1;
    for (int i = 0; i < kor; i++)
        natija *= asos;
    return natija;
}

/* ======================= 1-masala ======================= */

/* Sonning nechta raqamdan iboratligini topadi */
int raqamlar_soni(int n)
{
    int soni = 0;
    do {
        soni++;
        n /= 10;
    } while (n > 0);
    return soni;
}

/* n Armstrong soni bo'lsa 1, aks holda 0 qaytaradi */
int armstrongmi(int n)
{
    int k = raqamlar_soni(n);
    int yigindi = 0;
    int x = n;

    while (x > 0) {
        yigindi += daraja(x % 10, k);   /* oxirgi raqamni k-darajaga */
        x /= 10;                        /* oxirgi raqamni olib tashlash */
    }
    return yigindi == n;
}

/* ======================= 2-masala ======================= */

/* n ni raqamlarga ajratadi: raqamlar r massivga (birlar xonasidan boshlab)
   yoziladi, raqamlar soni esa k pointer orqali chaqiruvchiga qaytadi. */
void raqamlarga(int n, int *r, int *k)
{
    int *p = r;                 /* p massiv boshini ko'rsatadi */
    do {
        *p = n % 10;            /* joriy raqamni p ko'rsatgan joyga yozamiz */
        p++;                    /* keyingi elementga o'tamiz */
        n /= 10;
    } while (n > 0);
    *k = (int)(p - r);          /* pointerlar ayirmasi = yozilgan raqamlar soni */
}

/* raqamlarga() yordamida Armstrong ekanini tekshiradi */
int armstrongmi_ptr(int n)
{
    int r[MAX_RAQAM];
    int k;
    int yigindi = 0;

    raqamlarga(n, r, &k);                 /* &k — k ning manzili */
    for (int *p = r; p < r + k; p++)      /* [] siz, pointer bilan yurish */
        yigindi += daraja(*p, k);
    return yigindi == n;
}

/* ================= Kiritish va tekshirish ================= */

/* Bir qatorni o'qiydi va oxiridagi '\n' ni olib tashlaydi.
   Qator juda uzun bo'lsa, qolgan qismini tashlab yuboradi.
   EOF bo'lsa 0, aks holda 1 qaytaradi. */
int satr_oqi(char *buf, int hajm)
{
    if (fgets(buf, hajm, stdin) == NULL)
        return 0;

    char *yangi_qator = strchr(buf, '\n');
    if (yangi_qator != NULL) {
        *yangi_qator = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;   /* bufferga sig'magan qismni tozalash */
    }
    return 1;
}

/* a va b ni o'qib tekshiradi. To'g'ri bo'lsa 1, xato bo'lsa 0 qaytaradi.
   Natijalar a va b pointerlar orqali qaytadi. */
int oraliq_oqi(int *a, int *b)
{
    char satr[SATR_HAJMI];
    char ortiqcha;

    printf("a va b ni kiriting (%d <= a <= b <= %d): ", MIN_CHEGARA, MAX_CHEGARA);
    if (!satr_oqi(satr, SATR_HAJMI))
        return 0;

    /* %c sonlardan keyin ortiqcha belgi bor-yo'qligini ushlaydi:
       "100 999" -> 2,  "100 99x" yoki "abc" -> 2 emas */
    if (sscanf(satr, "%d %d %c", a, b, &ortiqcha) != 2) {
        printf("Xato: ikkita butun son kiriting (masalan: 100 999).\n");
        return 0;
    }
    if (*a < MIN_CHEGARA || *b > MAX_CHEGARA) {
        printf("Xato: sonlar %d va %d oralig'ida bo'lishi kerak.\n",
               MIN_CHEGARA, MAX_CHEGARA);
        return 0;
    }
    if (*a > *b) {
        printf("Xato: a b dan katta bo'lmasligi kerak.\n");
        return 0;
    }
    return 1;
}

/* ===================== Masalalar ===================== */

void masala1(void)
{
    int a, b, soni = 0;

    if (!oraliq_oqi(&a, &b))
        return;

    printf("[%d, %d] oralig'idagi Armstrong sonlari:\n", a, b);
    for (int n = a; n <= b; n++) {
        if (armstrongmi(n)) {
            printf("%d ", n);
            soni++;
        }
    }
    if (soni == 0)
        printf("topilmadi");
    printf("\nJami: %d ta\n", soni);
}

void masala2(void)
{
    int a, b, soni = 0;
    int r[MAX_RAQAM];
    int k;

    if (!oraliq_oqi(&a, &b))
        return;

    /* raqamlarga() ishini a soni misolida ko'rsatamiz */
    raqamlarga(a, r, &k);
    printf("\nraqamlarga(%d): k = %d ta raqam\n", a, k);
    printf("k o'zgaruvchisining manzili: %p\n", (void *)&k);
    for (int *p = r; p < r + k; p++)
        printf("  *(r + %d) = %d   manzil: %p\n", (int)(p - r), *p, (void *)p);

    printf("\n[%d, %d] oralig'idagi Armstrong sonlari (pointerlar bilan):\n", a, b);
    for (int n = a; n <= b; n++) {
        if (armstrongmi_ptr(n)) {
            printf("%d ", n);
            soni++;
        }
    }
    if (soni == 0)
        printf("topilmadi");
    printf("\nJami: %d ta\n", soni);
}

int main(void)
{
    char satr[SATR_HAJMI];
    char ortiqcha;
    int tanlov;

    while (1) {
        printf("\n===== 16-variant: Armstrong sonlari =====\n");
        printf("1 - 1-masala (oddiy usul)\n");
        printf("2 - 2-masala (pointerlar, raqamlarga())\n");
        printf("0 - Chiqish\n");
        printf("Tanlov: ");

        if (!satr_oqi(satr, SATR_HAJMI))
            break;                              /* EOF (Ctrl+D) */

        if (sscanf(satr, "%d %c", &tanlov, &ortiqcha) != 1) {
            printf("Xato: 0, 1 yoki 2 kiriting.\n");
            continue;
        }

        switch (tanlov) {
        case 1:  masala1(); break;
        case 2:  masala2(); break;
        case 0:  printf("Dastur tugadi.\n"); return 0;
        default: printf("Xato: bunday menyu bandi yo'q.\n");
        }
    }
    return 0;
}
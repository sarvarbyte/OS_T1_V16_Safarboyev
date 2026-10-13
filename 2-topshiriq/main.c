/*
 * OS_T1_V16_Safarboyev — 2-topshiriq, 16-variant
 * Ikki dinamik matritsaning ko'paytmasi: A (n x m) * B (p x k) = C (n x k).
 * O'lchamlar mos kelmasa (m != p), ajratilgan barcha xotira bo'shatilib,
 * dasturdan chiqiladi. Xotira faqat malloc bilan dinamik ajratiladi.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#define MAX_OLCHAM 100     /* qator/ustunlar soni uchun yuqori chegara */
#define SATR_HAJMI 4096    /* bitta kiritish qatori uchun bufer */

/* ================= Xotira bilan ishlash ================= */

/* n x m matritsa uchun xotira ajratadi: avval qatorlarga pointerlar massivi,
   keyin har bir qator alohida. Xato bo'lsa, shu paytgacha ajratilgan
   hamma narsani bo'shatib, NULL qaytaradi. */
int **matritsa_yarat(int n, int m)
{
    int **a = malloc(n * sizeof *a);
    if (a == NULL)
        return NULL;

    for (int i = 0; i < n; i++) {
        a[i] = malloc(m * sizeof **a);
        if (a[i] == NULL) {
            for (int j = 0; j < i; j++)   /* oldin ajratilgan qatorlar */
                free(a[j]);
            free(a);
            return NULL;
        }
    }
    return a;
}

/* Matritsani bo'shatadi va chaqiruvchidagi pointerni NULL qiladi.
   a — matritsa pointerining manzili, shuning uchun int ***. */
void matritsa_bushat(int ***a, int n)
{
    if (*a == NULL)
        return;
    for (int i = 0; i < n; i++)
        free((*a)[i]);       /* avval har bir qator */
    free(*a);                /* keyin qatorlar massivi */
    *a = NULL;               /* osilib qolgan pointer qolmasin */
}

/* ================= Kiritish ================= */

/* Bir qatorni o'qiydi, oxiridagi '\n' ni olib tashlaydi.
   Bufferga sig'magan qismini tashlab yuboradi. EOF bo'lsa 0 qaytaradi. */
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
            ;
    }
    return 1;
}

/* Matritsa o'lchamlarini o'qiydi va tekshiradi.
   Natija qatorlar va ustunlar pointerlari orqali qaytadi. */
int olcham_oqi(char nom, int *qatorlar, int *ustunlar)
{
    char satr[SATR_HAJMI];
    char ortiqcha;

    printf("%c matritsa o'lchamlari (qatorlar ustunlar, 1..%d): ", nom, MAX_OLCHAM);
    if (!satr_oqi(satr, SATR_HAJMI)) {
        printf("\nXato: kiritish tugadi.\n");
        return 0;
    }
    if (sscanf(satr, "%d %d %c", qatorlar, ustunlar, &ortiqcha) != 2) {
        printf("Xato: ikkita butun son kiriting (masalan: 2 3).\n");
        return 0;
    }
    if (*qatorlar < 1 || *qatorlar > MAX_OLCHAM ||
        *ustunlar < 1 || *ustunlar > MAX_OLCHAM) {
        printf("Xato: o'lchamlar 1 va %d oralig'ida bo'lishi kerak.\n", MAX_OLCHAM);
        return 0;
    }
    return 1;
}

/* Bitta qatordan aynan m ta butun sonni o'qiydi.
   Son kam, ko'p yoki harf aralashgan bo'lsa 0 qaytaradi. */
int qator_oqi(int *qator, int m)
{
    char satr[SATR_HAJMI];
    char *p = satr;
    char *oxiri;

    if (!satr_oqi(satr, SATR_HAJMI))
        return 0;

    for (int j = 0; j < m; j++) {
        errno = 0;
        long qiymat = strtol(p, &oxiri, 10);
        if (oxiri == p)                          /* son topilmadi */
            return 0;
        if (errno == ERANGE || qiymat < INT_MIN || qiymat > INT_MAX)
            return 0;                            /* int ga sig'maydi */
        qator[j] = (int)qiymat;
        p = oxiri;                               /* keyingi songa o'tish */
    }
    while (*p == ' ' || *p == '\t')
        p++;
    return *p == '\0';                           /* ortiqcha belgi yo'q */
}

/* Matritsaning barcha qatorlarini o'qiydi */
int matritsa_oqi(int **a, int n, int m, char nom)
{
    for (int i = 0; i < n; i++) {
        printf("%c matritsa %d-qatori (%d ta son): ", nom, i + 1, m);
        if (!qator_oqi(a[i], m)) {
            printf("Xato: %d-qatorga aynan %d ta butun son kiriting.\n", i + 1, m);
            return 0;
        }
    }
    return 1;
}

/* ================= Hisoblash va chiqarish ================= */

/* C = A * B. A: n x m, B: m x k, C: n x k (yangi ajratilgan xotirada).
   Xotira ajratilmasa NULL qaytaradi. */
int **kopaytir(int **a, int **b, int n, int m, int k)
{
    int **c = matritsa_yarat(n, k);
    if (c == NULL)
        return NULL;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            int yigindi = 0;
            for (int t = 0; t < m; t++)
                yigindi += a[i][t] * b[t][j];
            c[i][j] = yigindi;
        }
    }
    return c;
}

void matritsa_chiqar(int **a, int n, int m, const char *nom)
{
    printf("\n%s (%d x %d):\n", nom, n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            printf("%8d", a[i][j]);
        printf("\n");
    }
}

/* ================= main ================= */

int main(void)
{
    int **A = NULL, **B = NULL, **C = NULL;
    int n = 0, m = 0, p = 0, k = 0;
    int natija = 1;          /* 1 — xato bilan tugadi, 0 — muvaffaqiyatli */

    /* --- A matritsa --- */
    if (!olcham_oqi('A', &n, &m))
        goto tozalash;
    A = matritsa_yarat(n, m);
    if (A == NULL) {
        printf("Xato: A uchun xotira ajratilmadi.\n");
        goto tozalash;
    }
    if (!matritsa_oqi(A, n, m, 'A'))
        goto tozalash;

    /* --- B matritsa --- */
    if (!olcham_oqi('B', &p, &k))
        goto tozalash;
    B = matritsa_yarat(p, k);
    if (B == NULL) {
        printf("Xato: B uchun xotira ajratilmadi.\n");
        goto tozalash;
    }

    /* --- O'lchamlar mosligini tekshirish --- */
    if (m != p) {
        printf("Xato: A ning ustunlari soni (%d) B ning qatorlari soniga (%d) "
               "teng emas, ko'paytirish mumkin emas.\n", m, p);
        printf("Ajratilgan xotira bo'shatilib, dastur tugatiladi.\n");
        goto tozalash;
    }
    if (!matritsa_oqi(B, p, k, 'B'))
        goto tozalash;

    /* --- Ko'paytirish --- */
    C = kopaytir(A, B, n, m, k);
    if (C == NULL) {
        printf("Xato: C uchun xotira ajratilmadi.\n");
        goto tozalash;
    }

    matritsa_chiqar(A, n, m, "A");
    matritsa_chiqar(B, p, k, "B");
    matritsa_chiqar(C, n, k, "C = A * B");

    printf("\nA matritsa manzili (bo'shatishdan oldin): %p\n", (void *)A);
    natija = 0;

tozalash:
    /* Har qanday holatda ham shu yerga kelinadi va barcha xotira bo'shatiladi.
       NULL bo'lgan matritsani matritsa_bushat o'zi o'tkazib yuboradi. */
    matritsa_bushat(&C, n);
    matritsa_bushat(&B, p);
    matritsa_bushat(&A, n);

    if (natija == 0)
        printf("A matritsa manzili (bo'shatishdan keyin): %p\n", (void *)A);
    return natija;
}
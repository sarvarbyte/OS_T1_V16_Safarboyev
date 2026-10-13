# OS_T1_V16_Safarboyev

Operatsion tizimlar fanidan 1-topshiriq, 16-variant.
Mavzu: C tili asoslari, kompilyatsiya bosqichlari va pointerlar.

Muallif: Sarvar Safarboyev

## Muhit

- Ubuntu Linux
- GCC

## A qism: kompilyatsiya bosqichlari

```bash
gcc -E hello.c -o hello.i   # preprotsessor
gcc -S hello.i -o hello.s   # kompilyator (assembler kodi)
gcc -c hello.s -o hello.o   # assembler (obyekt fayl)
gcc hello.o -o hello        # linker (bajariluvchi fayl)
./hello
```

## B qism: Armstrong sonlari va pointerlar

- 1-masala: [a, b] oralig'idagi (100 ≤ a ≤ b ≤ 999999) Armstrong sonlari. Daraja `pow()` siz, butun sonli funksiya bilan hisoblanadi.
- 2-masala: `void raqamlarga(int n, int *r, int *k)` sonni raqamlarga ajratib, massivga va raqamlar sonini pointerga yozadi.

Kompilyatsiya va ishga tushirish:

```bash
gcc -Wall -Wextra -o main main.c
./main
```

Menyu: `1` — 1-masala, `2` — 2-masala, `0` — chiqish.
# OS_T1_V16_Safarboyev

Operatsion tizimlar fanidan topshiriq, 16-variant.
Muallif: Sarvar Safarboyev

## Tuzilma

```
1-topshiriq/   C asoslari, kompilyatsiya bosqichlari, pointerlar
2-topshiriq/   Pointerlar va dinamik xotira (malloc/free)
```

## 1-topshiriq

### A qism: kompilyatsiya bosqichlari

```bash
cd 1-topshiriq
gcc -E hello.c -o hello.i   # preprotsessor
gcc -S hello.i -o hello.s   # kompilyator (assembler kodi)
gcc -c hello.s -o hello.o   # assembler (obyekt fayl)
gcc hello.o -o hello        # linker (bajariluvchi fayl)
./hello
```

### B qism: Armstrong sonlari va pointerlar

```bash
cd 1-topshiriq
gcc -Wall -Wextra -o main main.c
./main
```

Menyu: `1` — 1-masala, `2` — 2-masala (`raqamlarga()` funksiyasi), `0` — chiqish.

## 2-topshiriq: dinamik matritsalarni ko'paytirish

A (n × m) · B (p × k). O'lchamlar mos kelmasa (m ≠ p), ajratilgan barcha xotira bo'shatilib, dasturdan chiqiladi.

```bash
cd 2-topshiriq
gcc -Wall -Wextra -g -o main main.c
./main
./main < test_mos.txt
./main < test_mos_emas.txt
```

Valgrind:

```bash
valgrind --leak-check=full ./main < test_mos.txt 2> valgrind.txt
valgrind --leak-check=full ./main < test_mos_emas.txt 2> valgrind_mos_emas.txt
```
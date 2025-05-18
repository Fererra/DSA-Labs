# Лабораторна робота 6. Мiнiмальний кiстяк графа

## Основні параметри:

- Варіант: **4328**
- Кількість вершин: **12**
- Коефіцієнт: **0.89**
- Розташування вершин: **прямокутником з вершиною в центрі**
- Алгоритм для знаходження мінімального кістяка: **Краскала**

## Встановлення та компіляція

Ви повинні мати встановлений компілятор **GCC**. Для початку склонуйте репозиторій:

```bash
git clone https://github.com/Fererra/DSA-Labs.git
```

Перейдіть у папку **з шостою лабораторною роботою** та скомпілюйте:

```bash
gcc -Iheaders src/main.c src/utils/matrix_utils.c src/utils/coords_utils.c src/utils/dataStructures.c src/utils/kruskal.c src/drawing.c -mwindows -o main.exe
```

```bash
gcc -Iheaders src/output.c src/utils/matrix_utils.c src/utils/dataStructures.c src/utils/kruskal.c -o output.exe
```

> main.exe - вікно з графами, output.exe - консольний вивід матриць цих графів (рекомендується запускати з консолі)

## Матриця суміжності ненапрямленого графа

![Adjacency matrix](https://github.com/user-attachments/assets/ca055a9e-a908-431a-bed3-b21b63bac920)

## Матриця ваг ребер

![Weight matrix](https://github.com/user-attachments/assets/45367e00-ebd1-42d3-bb15-4624e07cd6fd)

## Графічне представлення

### Неорієнтований граф

![Undirected graph](https://github.com/user-attachments/assets/68b97025-702a-41f6-b3e5-d60f9a05b3fc)

### Мінімальний кістяк

![MST](https://github.com/user-attachments/assets/b4066e8d-3b69-463d-8ffd-60088f3279cf)

## Сума ваг ребер знайденого мiнiмального кiстяка

![Weights](https://github.com/user-attachments/assets/7e7ad288-feae-40c0-8d62-9d4ed7e66e94)

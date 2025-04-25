# Лабораторна робота 3. Графічне представлення графів

## Основні параметри:

- Варіант: **4328**
- Кількість вершин: **12**
- Коефіцієнт: **0.67**
- Розташування вершин: **прямокутником з вершиною в центрі**

## Встановлення та компіляція
Ви повинні мати встановлений компілятор **GCC**. Для початку склонуйте репозиторій:

```bash
git clone https://github.com/Fererra/DSA-Labs.git
```

Перейдіть у папку **з третьою лабораторною роботою** та скомпілюйте:

```bash
gcc -Iheaders src/main.c src/utils/matrix_utils.c src/utils/coords_utils.c src/drawing.c -mwindows -o main.exe
```

```bash
gcc -Iheaders src/utils/matrix_utils.c src/output.c -o output.exe
```

>main.exe - вікно з графами, output.exe - консольний вивід матриць цих графів (рекомендується запускати з консолі)

## Матриці суміжності
![Adjacency matrices](https://github.com/user-attachments/assets/7e4ac080-e106-4060-b620-5f2cfa4295be)

## Графічне представлення

### Орієнтований граф
![Directed graph](https://github.com/user-attachments/assets/b2a3ebc0-ab98-484f-adfc-f1fbc0a44274)

### Неорієнтований граф
![Undirected graph](https://github.com/user-attachments/assets/c09d3fed-0c17-41ad-8800-f764f360e033)


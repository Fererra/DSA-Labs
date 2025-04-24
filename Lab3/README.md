# Лабораторна робота 3. Графічне представлення графів

## Основні параметри:

- Варіант: **4328**
- Кількість вершин: **12**
- Коефіцієнт: **0.67**
- Розташування вершин: **прямокутником з вершиною в центрі**

## Встановлення та компіляція
Ви повинні мати встановлений компілятор **GCC**. Для спочатку склонуйте репозиторій з лабораторними роботами:

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
![Directed graph](https://github.com/user-attachments/assets/29b4a2c5-4b75-4fd3-9707-cd19968751cd)


### Неорієнтований граф
![Undirected graph](https://github.com/user-attachments/assets/45b1d3be-f545-40fb-b726-6ab858fb6a35)

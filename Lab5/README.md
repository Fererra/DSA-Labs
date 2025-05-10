# Лабораторна робота 5. Обхiд графа

## Основні параметри:

- Варіант: **4328**
- Кількість вершин: **12**
- Коефіцієнт: **0.79**
- Розташування вершин: **прямокутником з вершиною в центрі**

## Встановлення та компіляція

Ви повинні мати встановлений компілятор **GCC**. Для початку склонуйте репозиторій:

```bash
git clone https://github.com/Fererra/DSA-Labs.git
```

Перейдіть у папку **з п'ятою лабораторною роботою** та скомпілюйте:

```bash
gcc -Iheaders src/main.c src/utils/dataStructures.c src/utils/matrix_utils.c src/utils/coords_utils.c src/drawing.c -mwindows -o main.exe
```

```bash
gcc -Iheaders src/utils/matrix_utils.c src/utils/dataStructures.c src/output.c -o output.exe
```

> main.exe - вікно з графами, output.exe - консольний вивід матриць цих графів та їх обходу (рекомендується запускати з консолі)

## Матриця суміжності

![Adjacency matrix](https://github.com/user-attachments/assets/56657db1-e7bd-46dc-ab99-3884f66c23c1)

## Матриця сумiжностi дерева обходу, відповідності вершин і одержаної нумерації та її векторне представлення

### BFS

![BFS matrices](https://github.com/user-attachments/assets/7ff5826c-133b-4e4a-8eee-e7c6dffa1b99)

### DFS

![DFS matrices](https://github.com/user-attachments/assets/985148fa-eaa5-4dd5-bfce-ad3e1ec57dff)

## Графічне представлення алгоритмів обходу

### BFS

![bfs](https://github.com/user-attachments/assets/07953e45-2c39-4d58-a2c6-f701ea597f46)
![bfs](https://github.com/user-attachments/assets/44aa5fd2-692a-40b8-b21c-985f6b254209)
![bfs](https://github.com/user-attachments/assets/873cf3fd-016c-407e-8261-9fe49953d36d)

### DFS

![dfs](https://github.com/user-attachments/assets/73b1685d-f5ef-4593-847b-b9a24b8cdfaa)
![dfs](https://github.com/user-attachments/assets/69f4cc97-9118-4479-862e-b047978399b1)
![dfs](https://github.com/user-attachments/assets/a2273d32-1cbe-4b8e-bdf1-1c54a8709f57)

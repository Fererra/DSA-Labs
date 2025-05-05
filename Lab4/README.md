# Лабораторна робота 4. Характеристики та зв’язнiсть графа

## Основні параметри:

- Варіант: **4328**
- Кількість вершин: **12**
- Коефіцієнт 1: **0.6**
- Коефіцієнт 2: **0.68**
- Розташування вершин: **прямокутником з вершиною в центрі**

## Встановлення та компіляція

Ви повинні мати встановлений компілятор **GCC**. Для початку склонуйте репозиторій:

```bash
git clone https://github.com/Fererra/DSA-Labs.git
```

Перейдіть у папку **з четвертою лабораторною роботою** та скомпілюйте:

```bash
gcc -Iheaders src/main.c src/utils/matrix_utils.c src/utils/coords_utils.c src/drawing.c -mwindows -o main.exe
```

```bash
gcc -Iheaders src/utils/matrix_utils.c src/output.c -o output.exe
```

> main.exe - вікно з графами, output.exe - консольний вивід матриць та характеристик графів (рекомендується запускати з консолі)

## Матриці суміжності та характеристики графів

![Directed graph info](https://github.com/user-attachments/assets/8a485abe-5744-4499-b718-5d22e672939a)

![Undirected graph info](https://github.com/user-attachments/assets/4e36d183-3bb0-4664-b31b-d76a80f66e73)

![Modified graph info](https://github.com/user-attachments/assets/61210d14-2502-4b32-9eef-532372facda0)

![Modified graph info](https://github.com/user-attachments/assets/b55be7fe-b831-4151-a4c9-36f2dfe98385)
![Modified graph info](https://github.com/user-attachments/assets/8f315e9c-3a3f-4578-9f18-68b698de7138)

![Modified graph info](https://github.com/user-attachments/assets/abf26cc6-47ff-468d-9d4c-dd2c45e3d63f)
![Modified graph info](https://github.com/user-attachments/assets/0d7be533-5bb1-4721-9c97-816b33782a6f)
![Modified graph info](https://github.com/user-attachments/assets/b573a632-3750-4f10-84dc-631bbacdc221)
![Modified graph info](https://github.com/user-attachments/assets/a94a8fda-71c6-46b5-94b4-7208ee15b56e)

## Графічне представлення

### Орієнтований граф

![Directed graph](https://github.com/user-attachments/assets/5e3d70bb-5529-4062-b4c5-24c0d38a0500)

### Неорієнтований граф

![Undirected graph](https://github.com/user-attachments/assets/d75b110d-52cc-4db0-8e7f-72d6dd7d6d17)

### Модифікований граф

![Modified graph](https://github.com/user-attachments/assets/bad0070c-88e4-459a-853d-99b6b7b137d7)

### Граф конденсації

![Condensation graph](https://github.com/user-attachments/assets/23f9f1f8-0660-421d-8b2f-0b771a761b76)

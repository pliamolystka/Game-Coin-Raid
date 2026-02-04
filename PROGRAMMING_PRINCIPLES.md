# Programming Principles

У цьому проєкті я дотримуюсь принципів написання чистого зрозумілого коду, щоб було легко читати, підтримувати та розширювати.

---

## 1. Зрозумілий код

Назви функцій та змінних описові, щоб відразу було зрозуміло, що вони роблять.

Приклад:
https://github.com/pliamolystka/Game-Coin-Raid/blob/main/main.cpp#L1-L50

---

## 2. Модульність

Код розбитий на окремі модулі, кожен відповідає за окрему частину гри:
- керування гравцем (`controlPlayer`)
- логіка рівнів (`gameLevel1`, `gameLevel2`)
- меню (`menu`)
- правила гри (`rules`)

Приклад:
https://github.com/pliamolystka/Game-Coin-Raid/blob/main/controlPlayer.c

---

## 3. Інтерфейс і реалізація

Оголошення функцій винесено у `.h` файли, а реалізація — у `.c` файли.

Приклад:
https://github.com/pliamolystka/Game-Coin-Raid/blob/main/menu.h

---

## 4. Одна відповідальність

Кожна функція виконує лише одну логічну задачу — ні більше, ні менше.

Приклад:
https://github.com/pliamolystka/Game-Coin-Raid/blob/main/rules.c#L10-L40

---

## 5. Без дублювання

Повторюваний функціонал винесено у окремі функції.

Приклад:
https://github.com/pliamolystka/Game-Coin-Raid/blob/main/controlPlayer.c#L20-L60

# L. Минимум на отрезке

<table>
    <tr>
        <td>Ограничение времени</td>
        <td>0.5 секунд</td>
    </tr>
    <tr>
        <td>Ограничение памяти</td>
        <td>256Mb</td>
    </tr>
    <tr>
        <td>Ввод</td>
        <td>стандартный ввод или input.txt</td>
    </tr>
    <tr>
        <td>Вывод</td>
        <td>стандартный вывод или output.txt</td>
    </tr>
</table>

Рассмотрим последовательность целых чисел длины $N$. По ней с шагом $1$ двигается «окно» длины $K$, то есть сначала в «окне» видно первые $K$ чисел, на следующем шаге в «окне» уже будут находиться $K$ чисел, начиная со второго, и так далее до конца последовательности. Требуется для каждого положения «окна» определить минимум в нём.

## Формат ввода

В первой строке входных данных содержатся два числа $N$ и $K$ $(1 \leq N \leq 150000, 1 \leq K \leq 10000, K \leq N)$ – длины последовательности и «окна», соответственно. На следующей строке находятся N чисел – сама последовательность. Числа последовательности не превосходят по модулю $10^5$.

## Формат вывода

Выходые данные должны содержать $N - K + 1$ строк – минимумы для каждого положения «окна».


### Пример

| Ввод | Вывод |
| -- | -- |
| 7 3<br>1 3 2 4 5 3 1 | 1 2 2 3 1<br><br>|

# Matrix
Сформировать и вывести массив, состоящий из номеров столбцов, в которых второй элемент меньше первого. 
Вычислить средние арифметические в этих столбцах и заменить элементы этих столбцов  соответствующими значениями средних арифметических. 
"Программа обработки числовой матрицы, загружаемой из текстового файла"

Ввод/вывод – потоковый.

Имя файла с матричными данными должно вводиться пользователем с клавиатуры.
Результат операции открытия файлового потока должен проверяться и, в случае неудачи, запрос на ввод имени файла должен повторяться.

Число строк и столбцов матрицы программа должна определять автоматически по содержимому файла.

При определении размеров матрицы программа должна корректно обрабатывать ситуации, связанные с наличием в файле «лишних» символов-разделителей, которое не должно считаться ошибкой задания матрицы.
Символы-разделители (пробелы, знаки табуляции) могут при задании матрицы в файле находиться в любых местах (в начале любой строки, между любыми элементами строки, в конце любой строки) и в любом количестве.
Файл с матрицей также может содержать пустые строки или строки, содержащие только символы разделители, в любых местах (перед первой строкой матрицы, между любыми строками матрицы, после последней строки матрицы) и в любом количестве.
Такие "пустые" (не содержащие элементов) строки в файле должны просто игнорироваться и не учитываться при подсчете строк матрицы.

Также при определении размеров матрицы программа должна проверять корректность задания значений её элементов.
Примеры некорректных значений: q23 q 12w 12345678901 (слишком большое для типа int) 1e320 (слишком большое для типа double).
При обнаружении некорректного значения программа должна выводить пользователю информацию о его положении в матрице (номер строки, номер столбца) и, желательно, полную последовательность символов, составляющих это некорректное значение.

Матрица должна проверяться на прямоугольность. (Непрямоугольной считается матрица количество элементов в строках (столбцах) которой не одинаково.)
При обнаружении непрямоугольности, программа должна выводить пользователю номер строки матрицы, в которой обнаружилось расхождение кол-ва элементов.

Память под хранение матричных данных должна выделяться динамически в 2 этапа: выделение памяти для хранения указателей на строки, выделение памяти для хранения элементов каждой строки.
Освобождение памяти должно осуществляться соответственно её выделению.
Работа с динамической памятью – new, delete.
Результат выполнения каждой операции выделения памяти должен проверяться.
В случае возникновения ошибки на каком-либо шаге выделения памяти, должно осуществляться полное освобождение всех выделенных ресурсов, дальнейшее использование которых стало невозможным из-за возникшей ошибки.
При загрузке матрицы в память программа должна действовать по принципу "всё или ничего", т.е. матрица должна быть получена в памяти, только если всё полностью прошло успешно и не возникло никаких ошибок.
Если в какой-то момент (при определении размеров матрицы, при проверке корректности её элементов, при проверке её прямоугольности, при выделении памяти под неё) обнаруживается какая-либо ошибка, то считается, что матрица не может быть получена, и процесс её загрузки надо прерывать.

Исходная (загруженная) матрица выводится на экран. Вывод - форматированный (у матрицы д.б. ровные столбцы с выравниванием элементов по правому краю, десятичная точка (в случае вещественных элементов) - на одной и той же позиции у всех элементов).

Обработка по условию задачи №8 выбранного вами варианта.

Вывод результирующей матрицы и векторов (если предусмотрено заданием) – форматированный.

В программе должны присутствовать все необходимые приглашения, подсказки и т.п. на русском языке.

Необходимо продемонстрировать использование адресной арифметики для доступа к элементам матрицы хотя бы в одном, любом месте программы.

Необходимо провести декомпозицию всей задачи на отдельные подзадачи и реализовать их в виде функций, принимающих необходимые параметры и возвращающих полученные результаты.
При этом:
1) Весь обмен данными между всеми вызывающими и вызываемыми функциями должен осуществляться через параметры и возвращаемое значение. Использование глобальных (по отношении к функции) переменных внутри функции не допускается.
2) Нужно подумать, как сделать функции наиболее универсальными (в разумных пределах, конечно, но в предположении того, что они могут использоваться не только в данной, но и во множестве других программ - совершенно разных, но работающих с данными такой же структуры) и допускающими бОльшую степень своего повторного использования.
3) Чтобы декомпозиция была правильная и каждая функция была в меру универсальна, функции не должны совмещать в себе разнородные задачи, каждая из которых имеет какую-то свою специфику, т.к. это будет ограничивать универсальность функции и возможность её применения в других задачах, других программах.
Пример: функция загрузки матрицы не должна сама запрашивать имя файла у пользователя, т.к. это имеет привязку к консольному вводу/выводу (которого в другом приложении может не быть, а будет GUI; или получение имени файла осуществляется по сети и т.п.) и к конкретному языку вывода запроса пользователю (который в других приложения м.б. не русским). Также, обрабатывая возникающие при загрузке ошибки, она не должна (по тем же самым причинам) сама выводить пользователю сообщение о возникшей ошибке, а должна вместо этого формировать в числовом виде (виде, не зависящем от специфики конкретного приложения, общем для всех) информацию о возникшей ошибке (причине и месте возникновения, еще какую-то полезную доп. информацию) и возвращать её в вызывающую функцию, в которой эта информация уже может быть использована нужным, специфическим для каждого приложения, образом.
4) При объявлении параметров не забывать про выбор правильного способа их передачи, делающих передачу в нужном направлении не только возможной, но и эффективной.
5) Где это уместно и полезно, объявить параметры с использованием const.
6) Где это уместно и полезно, задать параметрам значения по умолчанию.

Примерный состав функций:
1) Функция загрузки матрицы из файла.
2) Функция обработки матрицы по варианту задания.
3) Функция форматированного вывода матрицы в окно консоли.
Дополнительно можно "научить" эту функцию выводить в текстовый файл, реализовав оба вывода только один раз, но сделав его универсальным для обоих случаев.
Также настройки формата для форматированного вывода можно задавать не жестко в коде функции, а передавать через параметр(ы).
4) Если функция обработки матрицы изменяет исходную матрицу (а не создает новую), то дополнительно можно реализовать функцию создания копии матрицы, чтобы можно было сохранить исходную матрицу для какой-то другой дальнейшей её обработки.
5) Чтобы форматированный текстовый вывод матрицы мог осуществляться не только в окно консоли, то вместо функции п. 3 можно реализовать функцию создания строки, содержащей форматированное текстовое представление матрицы (конечно же, с разбиением строк матрицы на строки текста). Тогда такую строку с помощью 1-2 тривиальных операторов можно будет вывести в любое место (окно консоли, окно GUI, передать по сети, сохранить в текстовый файл, вывести на печать и т.п.).

Реализованные функции оформить в виде программного модуля, состоящего из двух файлов (заголовочного (*.h) и с реализацией (*.cpp)), имеющего защиту от повторного включения и т.п., т.е. оформленного по всем правилам.


Содержание отчета:
1) Титульный лист, оформленный как полагается, со всеми стандартными необходимыми элементами.
2) Задание.
3) Листинг программы.

Отчет распечатать.


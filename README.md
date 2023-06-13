# Задание
Написать программу, находящую в заданном каталоге и всех его подкаталогах все файлы заданного размера. Имя каталога задаётся пользователем в качестве первого аргумента командной строки. Диапазон (min - max) размеров файлов задаётся пользователем в качестве второго и третьего аргументов командной строки. Программа выводит результаты поиска в файл (четвертый аргумент командной строки) в виде полный путь, имя файла, его размер. На консоль выводится общее число просмотренных файлов.





### Пример компиляции и запуска
~~~
gcc -o main main.c
./main /usr/src 10 40 ./output.txt
~~~

### Пример выполнения программы
![file](https://github.com/Strong-Tea/Directory-File-Searcher/assets/135996451/1d9f74c0-f028-4196-b60b-23a76a90c2e5)
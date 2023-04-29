# OWNI библиотека С++
Для каждой латинской буквы создаётся пространство имён и пишутся вспомогательные классы, функции и др.
Чтобы использовать нужные возможности подключайте необходимые заголовочные файлы.

```C++
#include "_array.h";// для подключения массивов и основных типов данных
```
## Перечень заголовочных файлов
|#|?|Наименование|Описание|Зависимости|
|-|-|------------|--------|-----------|
|A|+|\_array.h|Массивы|\_types.h|
|B|-|\_base.h|Базовые классы||
|C|-|\_calc.h|Вычисления\преобразования|\_types.h|
|D|-|\_disc.h|Работа с диском||
|E|+|\_error.h|[Обработка ошибок](https://github.com/arbnet/CppLibrary/wiki/Обработка-ошибок "посмотреть описание обработки ошибок")|iostream|
|F|-|\_flows.h|Потоки||
|G|-|\_grafica.h|||
|H|-|\_|||
|I|-|\_interface.h|Интерфейс|iostream, \_types.h|
|J|-|\_|||
|K|-|\_|||
|L|-|\_libdll.h|Работа с DLL||
|M|-|\_media.h|Аудио, Видео||
|N|-|\_net.h|Работа с сетью||
|O|-|\_|||
|P|-|\_|||
|Q|-|\_|||
|R|-|\_|||
|S|-|\_|||
|T|+|\_types.h|[Типы данных](https://github.com/arbnet/CppLibrary/wiki/Типы-данных "посмотреть описание типов данных")||
|U|-|\_|||
|V|-|\_|||
|W|-|\_winapi.h|Window API||
|X|-|\_|||
|Y|-|\_|||
|Z|+|\_zests.h|Изюменки для отладки|clocale, cstdlib, \_types.h, \_interface.h, \_calc.h|

Обозначения в колонке `?` **-** не реализовано **+** реализовано.

В зависимостях указываются подключения которые использует тот или иной заголовочный файл, то есть вы можете использовать возможности зависимостей без их подключения в главном файле своей программы.

[Задать вопрос или оставить комментарий](https://github.com/arbnet/CppLibrary/discussions/1 "Обсуждение библиотеки OWNI C++") | [Связатся с разработчиком в телеграмм](https://t.me/+a818R23zeb9jYjYy "Телеграмм канал") | [Wiki](https://github.com/arbnet/CppLibrary/wiki "Wiki")
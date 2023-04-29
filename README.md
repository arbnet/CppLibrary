# OWNI библиотека С++

Кому и зачем нужна эта библиотека? Кто-то скажет есть же уже готовые библиотеки, зачем изобретать велосипед и тд.
Во-первых в существующих много лишнего чем вы никогда не воспользуетесь и нужно их изучать подстраиваться под их синтаксисы и тд. проблемы при отладке т.к. не знаете как что работает и тп. Во-вторых в своей знаешь, что и как работает, при необходимости можно доработать, написаны только самые основные нужные функции и классы с удобным для себя синтаксисом. В-третьих при создании своей библиотеки вы изучаете нативные функции и возможности самого языка программирования и на примерах пишите по своему, тестируете и оттачиваете свои мастерство и знания, которые в последствии вам помогут при создании своих будущих проектов.

> Эта библиотека будет полезна начинающим кто хочет изучить язык программирования C++. В данной библиотеке упрощённый подход, определены типы данных(заглавными буквами) так чтобы сразу было понятно что это за тип и как с ним работать, вместо использования стандартного типа String создан класс для строк STRING, так же ещё тип для даты времени DATETIME, ссылка на переменную LINK, ANY тип который может хранить любой тип данных добавленный через ID_TYPE. Более подробно смотрите описание в [Wiki](https://github.com/arbnet/CppLibrary/wiki "Wiki библиотеки OWNI C++")

> Почему сразу не начать с стандартных типов, классов и библиотек?  Тем кто изучает свой первый язык это может и приемлемо, но тот кто начинает изучать C++ переходя с языка более высокого уровня, где менее строгая типизация и упрощённый подход к программированию, переходить к языку низкоуровневого программирования не комфортно, поэтому я предлагаю воспользоваться своей библиотекой, в последствии по мере надобности будете расширять свои знания стандартных классов, библиотек и возможно в будущем эта библиотека вам будет не нужна. А сейчас если вам надо быстро что-то сделать, то эта библиотека может быть решением.
___
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
|E|+|\_error.h|Обработка ошибок|iostream|
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
|T|+|\_types.h|Типы данных||
|U|-|\_|||
|V|-|\_|||
|W|-|\_winapi.h|Window API||
|X|-|\_|||
|Y|-|\_|||
|Z|+|\_zests.h|Изюменки для отладки|clocale, cstdlib, _interface.h, _calc.h|

Обозначения в колонке `?` **-** не реализовано **+** реализовано.

В зависимостях указываются подключения которые использует тот или иной заголовочный файл, то есть вы можете использовать возможности зависимостей без их подключения в главном файле своей программы.

[Задать вопрос или оставить комментарий](https://github.com/arbnet/CppLibrary/discussions/1 "Обсуждение библиотеки OWNI C++") | [Связатся с разработчиком в телеграмм](t.me/+a818R23zeb9jYjYy "Телеграмм канал")
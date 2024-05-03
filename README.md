

# Проект "Ипподром"

## [Вариант: 4](/docs/4Var.txt)
 - Лабораторная работа 5, БГУ, 2024г.

## Исполнители:
- [**Кохан Даниил**](https://github.com/ExiDola):heart_eyes: - *Mentor and DocWriter*
- [**Башев Ян**](https://github.com/tafoiji) :racehorse:- *Main Coder*
- [**Соловьёв Даниил**](https://github.com/soldansd) :fearful:- *Devops engineer* 
- [**Ходин Дмитрий**](https://github.com/rollcookie) :stuck_out_tongue_closed_eyes:- *The tester*

## Описание проекта:
Проект "Ипподром" представляет собой систему управления для ипподрома, позволяющую хранить информацию о лошадях, жокеях и проведенных забегах. Система предоставляет функционал для получения информации о победителях, участниках забегов, а также обновления данных и распределения призового фонда.

## Installation:

- Clone the repository: git clone 
```git@github.com:fpmi-tp2024/tpmp-rvn-lab5-belated_capybaras.git ```
- Change into the project directory: ```tpmp-rvn-lab5-belated_capybaras.git```
- To create necessary folders use: ```make```
- To run application use: ```make install```


## Основные требования к проекту:
   - <span style="color: lightgreen;">[x]</span> Создать таблицы БД с учетом ограничений целостности данных.
   - <span style="color: lightgreen;">[x]</span> Используя оператор Select, выдать информацию по требованиям.
   - <span style="color: lightgreen;">[x]</span> Обеспечить с помощью операторов Insert, Update, Delete обновление информации в указанных таблицах.
   - <span style="color: lightgreen;">[x]</span> Создать функцию, который запрещает помещать информацию в таблицу забегов при отсутствии соответствия кличек лошадей и фамилий жокеев с аналогичными данными в таблицах лошадей и жокеев.
   - <span style="color: lightgreen;">[x]</span> Создать функцию, которая осуществляет распределение призового фонда для тройки призеров последнего забега в соотношении 50 %, 30 %, 20 %. В качестве параметра передать величину призового фонда. Результаты занести в специальную таблицу.
   - <span style="color: lightgreen;">[x]</span> Создать функцию, которая за указанный период выводит по указанному жокею сведения о забегах, где он участвовал(*).
   - <span style="color: lightgreen;">[x]</span> Работа с документацией.
      - [XML диаграмма классов](./docs//Diagrams/XML_class_diagramm.png)


      - [XML диаграмма серверной части](./docs/Diagrams/XML_serverPart_Diagramm.png)

      - [XML диаграмма клиентской части](./docs/Diagrams/XML_UserPart_Diagramm.png)

      - [Ссылка на сайт на GitHubPages](https://fpmi-tp2024.github.io/tpmp-rvn-lab5-belated_capybaras/)
      - [Ссылка на разбор БД](./docs/DataBase.md)

## Реализация проекта:
1. **Создание таблиц БД**: Созданы таблицы с учетом ограничений целостности данных.
   - [Ссылка на БД DataBase.md](/docs/DataBase.md)
2. **Запросы к БД**: Используя оператор `SELECT`, реализованы запросы по заданным критериям:
   - По лошади с максимальным количеством побед.
   - По жокею с наибольшим количеством участий в забегах.
   - По указанному жокею и владельцу лошади.
   - По всем проведенным забегам за указанный период.
3. **Обновление данных**: Обеспечено обновление информации с помощью операторов `INSERT`, `UPDATE`, `DELETE`.
4. **Проверка данных**: Создана функция для проверки соответствия данных при вставке в таблицу забегов.
5. **Распределение призового фонда**: Создана функция для распределения призового фонда для тройки призеров.
6. **Функция для получения информации о забегах**: Реализована функция для получения информации о забегах, в которых участвовал указанный жокей.

## Полезные ссылки:


## Файлы прописываемые в Make
![](https://img.shields.io/badge/*.cpp-main%2C_owner%2C_jockey%2C_database%2C_authentification%2C_admin-blue)
![](https://img.shields.io/badge/*.h-main%2C_owner%2C_jockey%2C_database%2C_authentification%2C_admin-pink
)

## Используемый язык программирвания,СУБД, IDE и т.д. :
<img src="https://simpleicons.org/icons/cplusplus.svg" alt="C++ Logo" width="100" height="100"> <img src="https://simpleicons.org/icons/sqlite.svg" alt="C++ Logo" width="100" height="100"> <img src="https://simpleicons.org/icons/visualstudiocode.svg" alt="C++ Logo" width="100" height="100"> <img src="https://simpleicons.org/icons/visualstudio.svg" alt="C++ Logo" width="100" height="100"> <img src="https://simpleicons.org/icons/git.svg" alt="C++ Logo" width="100" height="100">




<br><br>
<br><br>
<br><br>
<br><br>
## Картинка забега лошадей с жокеями
<img src="https://hotwalls.ru/wallpapers/horse_racing/download/1600x1200.jpg" alt="Horse Racing" style="opacity: 0.4; height: 700px;">




# Проект "Ипподром"

## [Вариант: 4](./4Var.txt)
 - Лабораторная работа 5, БГУ, 2024г.

## Listening of programm:
 1. [Listening main.cpp](./ListeningMain.md)

 2. [listening admin.cpp](./ListeningAdmin.md)

 3. [listening authentification.cpp](./ListeningAutentif.md)

 4. [listening database.cpp](./ListeningDatabases.md)

 5. [listening jockey.cpp](./ListeningJockey.md)

 6. [listening owner.cpp](./ListeningOwner.md)

## Installation:

- Clone the repository: git clone 
```git@github.com:fpmi-tp2024/tpmp-rvn-lab5-belated_capybaras.git ```
- Change into the project directory: ```tpmp-rvn-lab5-belated_capybaras.git```
- To create necessary folders use: ```make```
- To run application use: ```make install```

<br><br>
1. **Запросы к БД**: Используя оператор `SELECT`, реализованы запросы по заданным критериям:
   - По лошади с максимальным количеством побед.
   - По жокею с наибольшим количеством участий в забегах.
   - По указанному жокею и владельцу лошади.
   - По всем проведенным забегам за указанный период.
2. **Обновление данных**: Обеспечено обновление информации с помощью операторов `INSERT`, `UPDATE`, `DELETE`.
3. **Проверка данных**: Создана функция для проверки соответствия данных при вставке в таблицу забегов.
4. **Распределение призового фонда**: Создана функция для распределения призового фонда для тройки призеров.
5. **Функция для получения информации о забегах**: Реализована функция для получения информации о забегах, в которых участвовал указанный жокей.

## Полезные ссылки:

[Информация в Базах Данных(документ со всеми данными в виде скриншотов)](./DataBase.md)

 1. [XML диаграмма классов](./Diagrams/XML_class_diagramm.png)

 2. [XML диаграмма серверной части](./Diagrams/XML_serverPart_Diagramm.png)

 3. [XML диаграмма клиентской части](./Diagrams/XML_UserPart_Diagramm.png)

## Файлы прописываемые в Make
![](https://img.shields.io/badge/*.cpp-main%2C_owner%2C_jockey%2C_database%2C_authentification%2C_admin-blue)
![](https://img.shields.io/badge/*.h-main%2C_owner%2C_jockey%2C_database%2C_authentification%2C_admin-pink
)

## Исполнители:
- [**Кохан Даниил**](https://github.com/ExiDola):heart_eyes: - *Mentor and DocWriter*
- [**Башев Ян**](https://github.com/tafoiji) :racehorse:- *Main Coder*
- [**Соловьёв Даниил**]() :fearful:- *Devops engineer* 
- [**Ходин Дмитрий**](https://github.com/rollcookie) :stuck_out_tongue_closed_eyes:- *The tester*

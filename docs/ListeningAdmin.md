# Описание класса Admin

Этот файл README содержит подробное описание функций класса `Admin`, который предназначен для управления соревнованиями, лошадьми и жокеями в базе данных.

## Список функций и их описание

### Конструктор: Admin(sqlite3* db)

- **Назначение**: Инициализация нового экземпляра класса `Admin`, настройка циклического меню для действий администратора до завершения работы.
- **Параметры**:
  - `db`: Указатель на базу данных SQLite.

### void prize_pool()

- **Назначение**: Запрос у администратора суммы призового фонда и его распределение между победителями.
- **Ввод**:
  - Общая сумма призового фонда.
- **Вывод**:
  - Отображение распределения призового фонда на 1-е, 2-е и 3-е места.

### void divide_prize(double prize)

- **Назначение**: Расчет и отображение распределения приза на основе предопределенных процентных ставок.
- **Параметры**:
  - `prize`: Общий призовой фонд.

### void Insert()

- **Назначение**: Вставка новой записи в таблицу соревнований.
- **Операции**:
  - Запрашивает данные для каждого поля записи соревнования и выполняет вставку в базу данных.

### void Update()

- **Назначение**: Обновление существующей записи в таблице соревнований.
- **Операции**:
  - Получение идентификатора соревнования и новых данных, обновление записи в базе данных.

### void Delete()

- **Назначение**: Удаление записи из таблицы соревнований.
- **Операции**:
  - Запрашивает идентификатор соревнования и удаляет соответствующую запись из базы данных.

### int protected_horse_id()

- **Назначение**: Проверка существования лошади в базе данных по идентификатору.
- **Возвращаемое значение**:
  - Возвращает идентификатор лошади, если она существует, иначе -1.

### int protected_jockey_id()

- **Назначение**: Проверка существования жокея в базе данных по идентификатору.
- **Возвращаемое значение**:
  - Возвращает идентификатор жокея, если он существует, иначе -1.

### void SelectAllOutRaces()

- **Назначение**: Вывод информации о всех соревнованиях, где участвовали лошади данного владельца.
- **Операции**:
  - Выполнение SQL-запроса и отображение результатов.

### void Select2()

- **Назначение**: Вывод статистики выступлений жокеев.
- **Операции**:
  - Выполнение SQL-запроса для получения статистики и её отображение.

### void Select5()

- **Назначение**: Вывод информации о соревнованиях за определенный период.
- **Операции**:
  - Запрашивает период, выполняет SQL-запрос и отображает результаты.
-- Created by Vertabelo (http://vertabelo.com)
-- Last modification date: 2024-04-11 20:51:35.133

-- tables
-- Table: horses
CREATE TABLE horses (
    id integer NOT NULL CONSTRAINT horses_pk PRIMARY KEY,
    name varchar(255),
    age integer,
    experience integer,
    owner varchar(255),
    price double
);

-- Table: jockeys
CREATE TABLE jockeys (
    id integer NOT NULL CONSTRAINT jockeys_pk PRIMARY KEY,
    surname varchar(255),
    experience integer,
    year_of_birthday integer,
    address varchar(255)
);

-- Table: races
CREATE TABLE races (
    id integer NOT NULL CONSTRAINT races_pk PRIMARY KEY,
    date date,
    race_number integer,
    horse_id integer NOT NULL,
    jockey_id integer NOT NULL,
    taken_place integer,
    CONSTRAINT races_horses FOREIGN KEY (horse_id)
    REFERENCES horses (id),
    CONSTRAINT races_jockeys FOREIGN KEY (jockey_id)
    REFERENCES jockeys (id)
);

-- Table: user_type
CREATE TABLE user_type (
    id integer NOT NULL CONSTRAINT user_type_pk PRIMARY KEY,
    type varchar(255) NOT NULL
);

-- Table: users
CREATE TABLE users (
    id integer NOT NULL CONSTRAINT users_pk PRIMARY KEY,
    user_type integer NOT NULL,
    surname varchar(255) NOT NULL,
    password varchar(255) NOT NULL,
    CONSTRAINT users_user_type FOREIGN KEY (user_type)
    REFERENCES user_type (id)
);

-- End of file.


DROP SCHEMA IF EXISTS wordle_schema CASCADE;

CREATE SCHEMA IF NOT EXISTS wordle_schema;

CREATE TABLE IF NOT EXISTS wordle_schema.sessions
(
    id           SERIAL PRIMARY KEY,
    words_amount integer
        CONSTRAINT words_amount_positive CHECK (words_amount >= 0) DEFAULT (0)
);

CREATE TABLE IF NOT EXISTS wordle_schema.words
(
    id       INTEGER REFERENCES wordle_schema.sessions (id),
    word_num integer
        CONSTRAINT word_num_positive CHECK (words.word_num >= 0),
    word     char(5)
        CONSTRAINT word_len_5 NOT NULL,
    PRIMARY KEY (id, word_num),
    FOREIGN KEY (id) REFERENCES wordle_schema.sessions (id)
);
-- Добавить is_guessed, attempts amount
CREATE TABLE IF NOT EXISTS wordle_schema.players
(
    id         SERIAL PRIMARY KEY,
    name       varchar(40)
        CONSTRAINT name_len_less_than_40 NOT NULL,
    token      char(32)
        CONSTRAINT token_len_32 UNIQUE NOT NULL,
    score      integer CHECK (score >= 0) DEFAULT (0),
    reg_time   timestamp                  DEFAULT (now()),
    session_id SERIAL REFERENCES wordle_schema.sessions (id)
);

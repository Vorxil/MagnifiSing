PRAGMA foreign_keys = ON;

CREATE TABLE users (
  id integer primary key,
  name text unique,
  realname text
);
INSERT INTO users ( name, realname ) values ( 'klaus', 'Klaus Lapela' );

CREATE TABLE files (
  id integer primary key,
  filename text unique,
  lyrics integer,
  melody integer
);

CREATE TABLE performances (
  userid integer,
  fileid integer,
  time datetime,
  quality double,
  FOREIGN KEY( userid ) REFERENCES users( id ),
  FOREIGN KEY( fileid ) REFERENCeS files( id )
);

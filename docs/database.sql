
CREATE TABLE users (
  id integer primary key,
  name text unique,
  realname text
);

INSERT INTO users ( name, realname ) values ( 'klaus', 'Klaus Lapela' );



CREATE TABLE colors (
  color VARCHAR(25)
);


INSERT INTO colors VALUES ('Red');
/*insert into colors values('Blue');*/
insert into colors values('Green');
insert into colors values('Black');
insert into colors values('');
insert into colors values(null);


Select * from colors where Color not in ('Blue', 'Black', null);
Select * from colors where Color  in ('Blue', 'Black', null);


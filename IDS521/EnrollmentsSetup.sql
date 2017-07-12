/* Arnold Lee
UIN: 665453451
IDS 521 HW #1 
09/23/2015
*/

DROP DATABASE IF EXISTS `Enrollments`;

CREATE DATABASE `Enrollments`;

USE `Enrollments`;

CREATE TABLE `Student` (
    `sno` INT,
    `sName` VARCHAR(10),
    PRIMARY KEY (`sno`),
    `age` SMALLINT
);

CREATE TABLE `Course` (
    `cno` VARCHAR(5),
    `title` VARCHAR(10),
    PRIMARY KEY (`cno`),
    `credits` SMALLINT
);

CREATE TABLE `Professor` (
    `lname` VARCHAR(10),
    `dept` VARCHAR(10),
    `salary` SMALLINT,
    `age` SMALLINT,
    PRIMARY KEY (`lname`)
);

CREATE TABLE `Enroll` (
    `sno` INT,
    `cno` VARCHAR(5),
    PRIMARY KEY (`cno`, `sno`),
    FOREIGN KEY (sno) REFERENCES Student(sno),
    FOREIGN KEY (cno) REFERENCES Course(cno)
);

CREATE TABLE `Teach` (
    `lname` VARCHAR(10),
    `cno` VARCHAR(5),
    PRIMARY KEY (`cno`, `lname`),
    FOREIGN KEY (lname) REFERENCES Professor(lname),
    FOREIGN KEY (cno) REFERENCES Course(cno)
);

insert into student values(1, 'AARON',20);
insert into student values(2, 'CHUCK',21);
insert into student values(3, 'DOUG',20);
insert into student values(4, 'MAGGIE',19);
insert into student values(5, 'STEVE',22); 

insert into student values(6, 'JING',18); 
insert into student values(7, 'BRIAN',21); 
insert into student values(8, 'KAY',20); 
insert into student values(9, 'GILLIAN',20); 
insert into student values(10, 'CHAD',21); 

insert into course values('CS112', 'PHYSICS',4); 
insert into course values('CS113', 'CALCULUS',4); 
insert into course values('CS114', 'HISTORY',4); 

insert into professor values('CHOI', 'SCIENCE',400,45); 
insert into professor values('GUNN', 'HISTORY',300,60); 
insert into professor values('MAYER', 'MATH',400,55); 
insert into professor values('POMEL', 'SCIENCE',500,65); 
insert into professor values('FEUER', 'MATH',400,40); 

insert into enroll values(1,'CS112');
insert into enroll values(1,'CS113');
insert into enroll values(1,'CS114');
insert into enroll values(2,'CS112');
insert into enroll values(3,'CS112');
insert into enroll values(3,'CS114');
insert into enroll values(4,'CS112');
insert into enroll values(4,'CS113');

insert into enroll values(5,'CS113');
insert into enroll values(6,'CS113');
insert into enroll values(6,'CS114');

insert into teach values('CHOI','CS112');
insert into teach values('CHOI','CS113');
insert into teach values('CHOI','CS114');
insert into teach values('POMEL','CS113');
insert into teach values('MAYER','CS112');
insert into teach values('MAYER','CS114');

/*  Actual answers starts here */

/*  Answer 3(a) 
Students who take at least one course, exlcuding students who take all courses */


Select distinct S.* from student S, enroll E where
	E.sno = S.sno /* Student with at least one course */
and
	S.sno in (  /* including student missing at least one courses */
		    select S1.sno from student S1, course C1
				where (S1.sno,C1.cno) not in (select sno,cno from enroll)
                   );
                
	
/*  Answer 3(b) 
The oldest students who take more than one courses */

Select * from (
	Select distinct S.* from student S, enroll E
		where S.sno in ( 
			select distinct E1.sno from enroll E1, enroll E2
				where E1.sno = E2.sno and E1.cno < E2.cno )) as Q1
	Having age = max(Q1.age); 
		

			  
/* Answer 3(c)
Professors who teach exactly one course */

Select P.* from professor p, teach t
	where p.lname = t.lname and
		p.lname not in (
			select t1.lname from teach t1,teach t2
            where t1.lname = t2.lname and t1.cno < t2.cno
            );



/* Answer 3(d)
Professors who teach all courses */

Select * from professor where lname not in (
  select p.lname from professor p, course c
	where (p.lname,c.cno) not in (select lname,cno from teach)  
);



/* Answer 3(e)
The professor who is paid less than at most two other professors */

Select * from professor where lname not in (
	Select P1.lname from professor P1, professor P2,
		professor P3 where
			P1.salary < P2.salary and 
            P2.salary < P3.salary 
);
        


/* Answer 3(f)
The third highest paid professor. Also, is this query different from 3(e)? why or why not? */

Select distinct * from Professor order by salary desc limit 2,1;


/* Answer to question 3F */
/* The queries on part E and Part F are not the same as query E gives all results on the 
that has the matched criteria (tied results) while the query in F will give only one result*/
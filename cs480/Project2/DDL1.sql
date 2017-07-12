create database university1;

use university1;

create table department
	(dept_name		varchar(20) primary key, 
	 building		varchar(15), 
	 budget		        numeric(12,2)
	);

create table student
	(ID			int, 
	 name			varchar(20) not null, 
	 dept_name		varchar(20), 
	 tot_cred		numeric(3,0),
	 primary key (ID),
	 foreign key (dept_name) references department(dept_name)
	);

create table course
	(course_id		int, 
	 title			varchar(50), 
	 dept_name		varchar(15),
	 credits		numeric(2,0),
	 primary key (course_id),
	 foreign key (dept_name) references department(dept_name)
	);

create table instructor
	(ID			int, 
	 name			varchar(20) not null, 
	 dept_name		varchar(20), 
	 salary			numeric(8,2),
	 primary key (ID),
	 foreign key (dept_name) references department(dept_name)
	);

create table teaches
	(ID			int, 
	 course_id		int,
	 semester		varchar(6),
	 year			numeric(4,0),
	 primary key (ID, course_id, semester, year),
	 foreign key (course_id) references course(course_id)
		on delete cascade,
	 foreign key (ID) references instructor(ID)
		on delete cascade
	);


create table takes
	(ID			int, 
	 course_id		int,
	 semester		varchar(6),
	 year			numeric(4,0),
	 grade		        varchar(2),
	 primary key (ID, course_id, semester, year),
	 foreign key (course_id) references course(course_id)
		on delete cascade,
	 foreign key (ID) references student(ID)
		on delete cascade
	);

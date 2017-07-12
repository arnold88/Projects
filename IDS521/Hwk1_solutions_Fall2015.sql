-- Homework 1 solutions, posted Oct. 4, 2015
-- Ali Tafti

-- a)	Students who take at least one course, 
-- excluding students who take all courses. 

Select distinct s.* From Student s, Enroll e 
where s.sno = e.sno 
and s.sno not in (
	Select sno from Student where sno not in (
/* Student who is NOT taking some course*/
		Select s.sno from Course c, Student s where (s.sno, c.cno) not in
		(Select sno, cno from Enroll)
		)
);

-- alternative
Select * From Student s 
where s.sno in
	(
 Select sno from Enroll   
)
and s.sno not in (
	Select sno from Student where sno not in (
/* Student who is NOT taking some course*/
		Select s.sno from Course c, Student s where (s.sno, c.cno) not in
		(Select sno, cno from Enroll)
		)
);


-- b) The oldest student(s) who take(s) more than one course. 
Create View AtLeastTwo As Select * From Student where sno in (
	select e1.sno from enroll e1, enroll e2
	where e1.sno = e2.sno
	and e1.cno < e2.cno);
    
Select at_0.* From AtLeastTwo at_0
Where at_0.sno not in (
Select at_2.sno From
	AtLeastTwo  at_1, 
	AtLeastTwo at_2
Where at_1.age > at_2.age);

-- Alternative solution

Select at_0.* From
(Select * From Student where sno in (
	select e1.sno from enroll e1, enroll e2
	where e1.sno = e2.sno
	and e1.cno < e2.cno
)) at_0
where at_0.sno not in (
Select at_1.sno From
(Select * From Student where sno in (
	select e1.sno from enroll e1, enroll e2
	where e1.sno = e2.sno
	and e1.cno < e2.cno
)) at_1, 
(Select * From Student where sno in (
	select e1.sno from enroll e1, enroll e2
	where e1.sno = e2.sno
	and e1.cno < e2.cno
)) at_2
Where at_1.age < at_2.age);

-- c) Professors who teach exactly one course.
Select * from Professor where lname in  
(Select t1.lname from Teach t1)
and lname not in 
(
Select t1.lname from Teach t1, Teach t2
Where t1.lname = t2.lname and 
t1.cno > t2.cno 
);

-- d) Professors who teach all courses. 
Select lname from Professor where lname not in (
/* Professor who is NOT teaching some course*/
		Select lname from Course c, Professor p where (p.lname, c.cno) not in
		(Select lname, cno from Teach)
);

-- e) The professor who is paid less than at most two other professors.

-- Note that here is the first pass at a solution, but we can easily see why it
-- will need an additional subfilter when the database contains ties for salary rank.
-- So this solution is not sufficient, but is a building block:
Select * from Professor where lname not in 
(
	Select p4.lname from Professor p1, Professor p2, Professor p3, Professor p4
	Where p1.salary > p2.salary and p2.salary > p3.salary and
    p3.salary > p4.salary
);

-- The subfilter needs to show:
-- For each professor (ok to skip the highest earning), show a count of professors who make more than he or she does. 
-- Then add a filter for more than two.
-- Here is another building block:
Select p2.lname, count(p1.lname) num_withmore from professor p1,
 professor p2 where p1.salary > p2.salary and p1.lname != p2.lname
group by p2.lname
having  num_withmore > 2;

-- Putting the pieces together for the solution:
Select * from Professor where lname not in 
(
	Select p4.lname from Professor p1, Professor p2, Professor p3, Professor p4
	Where p1.salary > p2.salary and p2.salary > p3.salary and
    p3.salary > p4.salary
) and lname not in
(
Select lname from (
	Select p2.lname, count(p1.lname) as num_withmore from professor p1, 
	professor p2 where p1.salary > p2.salary and p1.lname != p2.lname
	group by p2.lname
	having num_withmore >2) subquery
);

-- f)	The third highest paid professor. Question: Is this query different from (e); 
-- and why or why not? (Please answer as a comment)
-- Third highest paid professor
Select * from Professor where lname not in
(
	Select p4.lname from Professor p1, Professor p2, Professor p3, Professor p4
	Where p1.salary > p2.salary and p2.salary > p3.salary and
    p3.salary > p4.salary
)
and lname in
(
	Select p3.lname from Professor p1, Professor p2, Professor p3
	Where p1.salary > p2.salary and p2.salary > p3.salary 
)
;

-- We will award credit based on the quality of insight conveyed in your written answers. Here
-- is the insight that we are looking for:

-- Note that the difference between (e) and (f) plays upon a subtle ambiguity in the English language.
-- Being the third highest professor allows that there might be more than one professor who 
-- earn more. Some ranking systems will skip a number to show the information. For example, if there are three
-- who earn the second highest amount (as in the sample database provided), the next professor in order of 
-- salary gets a ranking of five rather than three. Other ranking systems will just assign the rank of three for
-- the third highest amount, even when there are four other professors who earn more. 


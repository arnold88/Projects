
USE  `TwitterResearch_Fall2015`;

-- get a cumulative count as well as daily count
Select count(t.twitterpermin) as dailycount, t.smblid, t.dateend as t_date, 
	(Select count(twitterpermin) from tweets3 where dateend < t_date and smblid = t.smblid) 
     as cum_count
from tweets3 t where dateend ='2012-06-08' 
group by smblid, dateend;

-- Test the above query
Select smblid, count(twitterpermin) from tweets3 t  where dateend < '2012-06-08' 
group by smblid;

-- 
drop table temp_twitcount;
Create Table temp_twitcount (
	smblid VARCHAR(8),
	t_date DATE, 
	dailycount decimal,
	cumcount decimal,
	percentile_rank  int
); 

Insert into temp_twitcount 
select t.smblid as smblid, t.dateend as t_date, count(t.twitterpermin) as dailycount, 
	(Select count(twitterpermin) from tweets3 where dateend < t_date and smblid = t.smblid) as cum_count, null as percentile_rank
from tweets3 t where t.dateend   >= '2012-06-01' and t.dateend  <= '2012-07-09'
group by smblid, dateend;


Select *, cumcount, round(cumcount*0.01) as percentile_Rank from temp_twitcount;

Update temp_twitcount set percentile_rank = round(cumcount*0.01);

-- thresholds calculated only on the daily basis, which is not what we want ultimately 
Select temp_twitcount.smblid, temp_twitcount.t_date,temp_twitcount.percentile_rank, 
substring_index (
	substring_index(
		group_concat(t.twitterpermin Order by t.twitterpermin desc SEPARATOR ','), 
		',',percentile_rank + 1
	), ',', -1) as 'threshold99pctl'
from tweets3 t
join temp_twitcount on temp_twitcount.smblid = t.smblid and temp_twitcount.t_date = t.dateend
where temp_twitcount.t_date  >= '2012-06-01' and temp_twitcount.t_date <= '2012-07-09'
group by temp_twitcount.smblid, temp_twitcount.t_date;


-- thresholds calculated  using the same type of logic as with cumulative counts, using inline query 
Select temp_twitcount.smblid as t_symbol, temp_twitcount.t_date as t_date,temp_twitcount.percentile_rank, 
	(SELECT substring_index (
	substring_index(
		group_concat(t_in.twitterpermin Order by t_in.twitterpermin desc SEPARATOR ','), 
		',',percentile_rank + 1
	), ',', -1) 
	from tweets3 t_in where t_in.dateend < t_date and t_in.smblid = t_symbol
	) as 'threshold99pctl'
from tweets3 t
join temp_twitcount on temp_twitcount.smblid = t.smblid and temp_twitcount.t_date = t.dateend
where temp_twitcount.t_date  >= '2012-06-01' and temp_twitcount.t_date <= '2012-07-09'
group by temp_twitcount.smblid, temp_twitcount.t_date;




-- You can verify threshold results with small subqueries; e.g. 9th ranking ADSK tweets prior to '06/07/12'
select smblid, t.dateend, t.twitterpermin from tweets3 t where
t.dateend  < '2012-06-07'
and 
 t.smblid = 'ADSK'
order by t.twitterpermin desc
limit 9, 1;





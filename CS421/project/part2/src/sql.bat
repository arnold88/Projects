create table results(comp_id int, winner varchar(20), medal varchar(10));
create table athletes(name varchar(20) primary key,  nationality varchar(20), gender char(1));
create table competitions(comp_id int primary key, name varchar(20), type varchar(10));



insert into results values (3, 'svedsen','silver');
insert into results values(3, 'jay','gold');
insert into results values(3, 'fak','bronze');
insert into results values(4,'ammann','gold');
insert into results values(4,'malysz','silver');
insert into results values(4,'schlierenzauer','bronze');
insert into results values(5,'davis','gold');
insert into results values(5,'mo','silver');
insert into results values(5,'hedrick','bronze');
insert into results values(6,'kramer','gold');
insert into results values(6,'lee','silver');
insert into results values(6,'skobrev','bronze');
insert into results values(7,'ohno','silver');
insert into results values(7,'lee','gold');
insert into results values(7,'cleski','bronze');
insert into results values(8,'hedrick','bronze');
insert into results values(8,'davis','gold');
insert into results values(8,'mo','silver');
insert into results values(9,'kim','gold');
insert into results values(9,'rochette','bronze');
insert into results values(9,'asada','silver');
insert into results values(9,'lysacek','gold');
insert into results values(9,'plushenko','silver');
insert into results values(9,'takahashi','bronze');
insert into results values(10,'miller','gold');
insert into results values(10,'kostelic','silver');
insert into results values(10,'zurbriggen','bronze');
insert into results values(11,'mcivor','gold');
insert into results values(11,'hedda','silver');
insert into results values(11,'huttary','bronze');
insert into results values(12,'razzoli','gold');
insert into results values(12,'kostelic','silver');
insert into results values(12,'myhrer','bronze');
insert into results values(13,'mancuso','silver');
insert into results values(13,'riesch','gold');
insert into results values(13,'paerson','bronze');
insert into results values(15,'ammann','gold');
insert into results values(15,'malysz','silver');
insert into results values(15,'schlierenzauer','bronze');
insert into results values(16,'kuzmina','gold');
insert into results values(16,'neuner','silver');
insert into results values(16,'dorin','bronze');


insert into athletes values('svedsen','norway','M');
insert into athletes values('zurbriggen','switzerland','M');
insert into athletes values('jay','france','M');
insert into athletes values('kostelic','croatia','M');
insert into athletes values('myhrer','sweden','M');
insert into athletes values('fak','croatia','M');
insert into athletes values('cleski','usa','M');
insert into athletes values('mo','korea','M');
insert into athletes values('ammann','switzerland','M');
insert into athletes values('malysz','poland','M');
insert into athletes values('schlierenzauer','austria','M');
insert into athletes values('kramer','netherlands','M');
insert into athletes values('skobrev','russia','M');
insert into athletes values('lee','korea','M');
insert into athletes values('kuzmina','slovakia','F');
insert into athletes values('neuner','germany','F');
insert into athletes values('dorin','france','F');
insert into athletes values('davis','usa','M');
insert into athletes values('ohno','usa','M');
insert into athletes values('hedrick','usa','M');
insert into athletes values('kim','korea','F');
insert into athletes values('asada','japan','F');
insert into athletes values('rochette','canada','F');
insert into athletes values('mcivor','canada','F');
insert into athletes values('hedda','norway','F');
insert into athletes values('huttary','autria','F');
insert into athletes values('miller','usa','M');
insert into athletes values('andrea','austria','F');
insert into athletes values('lysacek','usa','M');
insert into athletes values('plushenko','russia','M');
insert into athletes values('takahashi','japan','M');
insert into athletes values('paerson','sweden','F');
insert into athletes values('riesch','germany','F');
insert into athletes values('razzoli','italy','M');
insert into athletes values('mancuso','usa','F');


insert into competitions values(3,'biathlon','1000');
insert into competitions values(4,'skijumping','nh');
insert into competitions values(5,'speedskating','1000');
insert into competitions values(6,'speedskating','500');
insert into competitions values(7,'shorttrack','1500');
insert into competitions values(8,'speedskating','1000');
insert into competitions values(9,'figureskating','');
insert into competitions values(10,'giantslalom','');
insert into competitions values(11,'crosscountry','');
insert into competitions values(12,'slalom','');
insert into competitions values(13,'super-combined','');
insert into competitions values(15,'skijumping','lh');
insert into competitions values(16,'biathlon','7500');

.exit;




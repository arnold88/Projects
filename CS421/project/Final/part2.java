import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.lang.Exception;
import java.sql.*;
import java.io.*;

 
//start
public class part2 {
  
	//start main
	
	public static void main (String[] args) throws IOException {
		try
		{
		//File file = new File("/mnt_nfs/home1/class/temp563/Desktop/lopar/question.txt");
		File file = new File("question.txt");
//File file = new File("/mnt_nfs/home4/grad4/vsingla/LoPar-3.0/question.txt");
		//	File file = new File("C:\\Masters\\SP-10\\421\\Term project\\questions.txt");
		   FileInputStream fis = null;
		    BufferedInputStream bis = null;
		    DataInputStream dis = null;
		    Writer output =null;
		//	File file1 = new File("/mnt_nfs/home1/class/temp563/Desktop/lopar/data/part2.txt");
			File file1 = new File("data/part2.txt");
		    //File file1 = new File("/mnt_nfs/home4/grad4/vsingla/LoPar-3.0/data/part2.txt");
		    //File file1 = new File("C:\\Masters\\SP-10\\421\\Term project\\questions1.txt");
			String sourceLine;
	     String content = "";
	     String s1;
	     output = new BufferedWriter(new FileWriter(file1));
			String sql="";
		fis = new FileInputStream(file);
		
		FileReader rd = new FileReader(file);
		int leng,leng1,leng2;
		int index1, index2;
		String substring1;
		String substring2;
		String str;
        // Here BufferedInputStream is added for fast reading.
        bis = new BufferedInputStream(fis);
        dis = new DataInputStream(bis);
        while (dis.available() != 0) {
            // this statement reads the line from the file and print it to
              // the console.
        	
                s1 = dis.readLine();
                leng1=s1.length();
                leng2=0;
                index1=0;
                while(leng2<leng1)
                {
                	index2 = s1.indexOf(" "); 
                	
                	if(index2==-1)
                	{
                		index2 = s1.indexOf("?");
                		//System.out.println(index2);
                		str = s1.substring(0,index2);
                		//System.out.println("str"+str);
                		leng2 = leng2+str.length()+1;
                		index1=index2+1;
                		output.write(str);
                		output.write("\n");
                		output.write("\n");
                		//System.out.println("leng2"+leng2);
                    	//s1=s1.substring(index1,s1.length());
                	}
                	else{
                	str = s1.substring(0,index2);
                	leng2 = leng2+str.length()+1;
                	index1=index2+1;
                	s1=s1.substring(index1,s1.length());
                	//System.out.println(str);
                	output.write(str);
                	output.write("\n");
                	/*System.out.println("leng2 " + leng2);
                	System.out.println("leng1 " + leng1);*/
                	//System.out.println("s1 "+s1);
                	//System.out.println("index2 "+index2);
                	//System.out.println("index1 "+index1);
                	}
                }	
                //output.write(str)
                //System.out.println(s1);
                
    }
        output.close();
	 
	//   System.out.print(db.get_table("select count(*) from athletes a,competitions c,results r where a.name=r.winner and c.comp_id=r.comp_id and r.medal='bronze' and c.name='figureskating' and a.gender='M' and a.nationality='canada';"));
	   
	 } catch (Exception e) {
	 }
	 


	    // lopar parsing
		try {
			String line;
			String [] lopar_cmd = {"./lopar","-in","data/part2" , "-symbolic", "-trees", "data/part2.txt", "lopar_output.txt" };
		 	Process p = Runtime.getRuntime().exec(lopar_cmd);
		 	BufferedReader input =
		 	 	new BufferedReader
		 	 	(new InputStreamReader(p.getInputStream()));
		 	 	while ((line = input.readLine()) != null) {
		 	 		System.out.println(line);
		 	 	}
		 	 	input.close();
               
		 	
		} catch (Exception err) 
		    {
		 	err.printStackTrace();
		 	}
			 	
		//  Algorithm to convert lopar syntatic trees into SQL queries, written to a batch file
		try{
			
//			File file = new File("/mnt_nfs/home4/grad4/vsingla/LoPar-3.0/question.txt");
//			File file = new File("/mnt_nfs/home1/class/temp563/Desktop/lopar/question.txt");
			File file = new File("question.txt");
			//File file = new File("C:\\Masters\\SP-10\\421\\Term project\\questions.txt");   
			FileInputStream fis = null;
			    BufferedInputStream bis = null;
			    DataInputStream dis = null;
			    Writer output =null;
			//File file1 = new File("/mnt_nfs/home4/grad4/vsingla/LoPar-3.0/sql1.bat");			    
//			File file1 = new File("/mnt_nfs/home1/class/temp563/Desktop/lopar/sql1.bat");
File file1 = new File("sql1.bat");
			//File file1 = new File("C:\\Masters\\SP-10\\421\\Term project\\questions2.txt");
				String sourceLine;
		     String content = "";
		     String s1;
		     output = new BufferedWriter(new FileWriter(file1));
				String sql="";
				String text="";
				String question="";
				String sql1="";
				String separator="";
			fis = new FileInputStream(file);
			
			FileReader rd = new FileReader(file);
			int leng,leng1,leng2;
			int index1, index2;
			String substring1;
			String substring2;
			String str;
	        // Here BufferedInputStream is added for fast reading.
	        bis = new BufferedInputStream(fis);
	        dis = new DataInputStream(bis);
	        String gender="";
	        String name="";
			String first_part;
			String second_part="";
			String nationality ="";
			String won="";
			String type="";
			String arrive="";
			String medal = "";
			String position = "";
			String event="";
//			output.write(".separator k ");
			output.write(".output sql_out.txt ");
			output.write("\n");
			
		output.write("create table text(sentence varchar(100),question varchar(100),sql varchar(100), separator varchar(100),number int);");
		output.write("\n");
		output.write("create table results(comp_id int, winner varchar(20), medal varchar(10));");
		output.write("\n");
		output.write("create table athletes(name varchar(20) primary key,  nationality varchar(20), gender char(1));");
		output.write("\n");
		output.write("create table competitions(comp_id int primary key, name varchar(20), type varchar(10));");
		output.write("\n");

		output.write("insert into text values ('Answer to question 1 is','','','--------------------------------------------------------------------------------------------',1);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 2 is','','','--------------------------------------------------------------------------------------------',2);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 3 is','','','--------------------------------------------------------------------------------------------',3);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 4 is','','','--------------------------------------------------------------------------------------------',4);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 5 is','','','--------------------------------------------------------------------------------------------',5);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 6 is','','','--------------------------------------------------------------------------------------------',6);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 7 is','','','--------------------------------------------------------------------------------------------',7);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 8 is','','','--------------------------------------------------------------------------------------------',8);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 9 is','','','--------------------------------------------------------------------------------------------',9);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 10 is','','','--------------------------------------------------------------------------------------------',10);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 11 is','','','--------------------------------------------------------------------------------------------',11);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 12 is','','','--------------------------------------------------------------------------------------------',12);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 13 is','','','--------------------------------------------------------------------------------------------',13);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 14 is','','','--------------------------------------------------------------------------------------------',14);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 15 is','','','--------------------------------------------------------------------------------------------',15);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 16 is','','','--------------------------------------------------------------------------------------------',16);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 17 is','','','--------------------------------------------------------------------------------------------',17);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 18 is','','','--------------------------------------------------------------------------------------------',18);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 19 is','','','--------------------------------------------------------------------------------------------',19);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 20 is','','','--------------------------------------------------------------------------------------------',20);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 21 is','','','--------------------------------------------------------------------------------------------',21);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 22 is','','','--------------------------------------------------------------------------------------------',22);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 23 is','','','--------------------------------------------------------------------------------------------',23);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 24 is','','','--------------------------------------------------------------------------------------------',24);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 25 is','','','--------------------------------------------------------------------------------------------',25);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 26 is','','','--------------------------------------------------------------------------------------------',26);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 27 is','','','--------------------------------------------------------------------------------------------',27);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 28 is','','','--------------------------------------------------------------------------------------------',28);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 29 is','','','--------------------------------------------------------------------------------------------',29);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 30 is','','','--------------------------------------------------------------------------------------------',30);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 31 is','','','--------------------------------------------------------------------------------------------',31);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 32 is','','','--------------------------------------------------------------------------------------------',32);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 33 is','','','--------------------------------------------------------------------------------------------',33);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 34 is','','','--------------------------------------------------------------------------------------------',34);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 35 is','','','--------------------------------------------------------------------------------------------',35);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 36 is','','','--------------------------------------------------------------------------------------------',36);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 37 is','','','--------------------------------------------------------------------------------------------',37);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 38 is','','','--------------------------------------------------------------------------------------------',38);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 39 is','','','--------------------------------------------------------------------------------------------',39);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 40 is','','','--------------------------------------------------------------------------------------------',40);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 41 is','','','--------------------------------------------------------------------------------------------',41);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 42 is','','','--------------------------------------------------------------------------------------------',42);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 43 is','','','--------------------------------------------------------------------------------------------',43);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 44 is','','','--------------------------------------------------------------------------------------------',44);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 45 is','','','--------------------------------------------------------------------------------------------',45);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 46 is','','','--------------------------------------------------------------------------------------------',46);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 47 is','','','--------------------------------------------------------------------------------------------',47);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 48 is','','','--------------------------------------------------------------------------------------------',48);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 49 is','','','--------------------------------------------------------------------------------------------',49);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 50 is','','','--------------------------------------------------------------------------------------------',50);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 51 is','','','--------------------------------------------------------------------------------------------',51);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 52 is','','','--------------------------------------------------------------------------------------------',53);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 54 is','','','--------------------------------------------------------------------------------------------',54);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 55 is','','','--------------------------------------------------------------------------------------------',55);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 56 is','','','--------------------------------------------------------------------------------------------',56);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 57 is','','','--------------------------------------------------------------------------------------------',57);");
		output.write("\n");
		output.write("insert into text values ('Answer to question 58 is','','','--------------------------------------------------------------------------------------------',58);");
		output.write("\n");

		output.write("insert into results values (3, 'svendsen','silver');");
		output.write("\n");
		output.write("insert into results values(3, 'jay','gold');");
		output.write("\n");
		output.write("insert into results values(3, 'fak','bronze');");
		output.write("\n");
		output.write("insert into results values(4,'ammann','gold');");
		output.write("\n");
		output.write("insert into results values(4,'malysz','silver');");
		output.write("\n");
		output.write("insert into results values(4,'schlierenzauer','bronze');");
		output.write("\n");
		output.write("insert into results values(5,'davis','gold');");
		output.write("\n");
		output.write("insert into results values(5,'mo','silver');");
		output.write("\n");
		output.write("insert into results values(5,'hedrick','bronze');");
		output.write("\n");
		output.write("insert into results values(6,'kramer','gold');");
		output.write("\n");
		output.write("insert into results values(6,'lee','silver');");
		output.write("\n");
		output.write("insert into results values(6,'skobrev','bronze');");
		output.write("\n");
		output.write("insert into results values(7,'ohno','silver');");
		output.write("\n");
		output.write("insert into results values(7,'lee','gold');");
		output.write("\n");
		output.write("insert into results values(7,'cleski','bronze');");
		output.write("\n");
//		output.write("insert into results values(8,'hedrick','bronze');");
//		output.write("\n");
//		output.write("insert into results values(8,'davis','gold');");
//		output.write("\n");
//		output.write("insert into results values(8,'mo','silver');");
//		output.write("\n");
		output.write("insert into results values(9,'kim','gold');");
		output.write("\n");
		output.write("insert into results values(9,'rochette','bronze');");
		output.write("\n");
		output.write("insert into results values(9,'asada','silver');");
		output.write("\n");
		output.write("insert into results values(9,'lysacek','gold');");
		output.write("\n");
		output.write("insert into results values(9,'plushenko','silver');");
		output.write("\n");
		output.write("insert into results values(9,'takahashi','bronze');");
		output.write("\n");
		output.write("insert into results values(10,'miller','gold');");
		output.write("\n");
		output.write("insert into results values(10,'kostelic','silver');");
		output.write("\n");
		output.write("insert into results values(10,'zurbriggen','bronze');");
		output.write("\n");
		output.write("insert into results values(11,'mcivor','gold');");
		output.write("\n");
		output.write("insert into results values(11,'hedda','silver');");
		output.write("\n");
		output.write("insert into results values(11,'huttary','bronze');");
		output.write("\n");
		output.write("insert into results values(12,'razzoli','gold');");
		output.write("\n");
		output.write("insert into results values(12,'kostelic','silver');");
		output.write("\n");
		output.write("insert into results values(12,'myhrer','bronze');");
		output.write("\n");
		output.write("insert into results values(13,'mancuso','silver');");
		output.write("\n");
		output.write("insert into results values(13,'riesch','gold');");
		output.write("\n");
		output.write("insert into results values(13,'paerson','bronze');");
		output.write("\n");
		output.write("insert into results values(15,'ammann','gold');");
		output.write("\n");
		output.write("insert into results values(15,'malysz','silver');");
		output.write("\n");
		output.write("insert into results values(15,'schlierenzauer','bronze');");
		output.write("\n");
		output.write("insert into results values(16,'kuzmina','gold');");
		output.write("\n");
		output.write("insert into results values(16,'neuner','silver');");
		output.write("\n");
		output.write("insert into results values(16,'dorin','bronze');");

		output.write("insert into athletes values('svendsen','norway','M');");
		output.write("\n");
		output.write("insert into athletes values('zurbriggen','switzerland','M');");
		output.write("\n");
		output.write("insert into athletes values('jay','france','M');");
		output.write("\n");
		output.write("insert into athletes values('kostelic','croatia','M');");
		output.write("\n");
		output.write("insert into athletes values('myhrer','sweden','M');");
		output.write("\n");
		output.write("insert into athletes values('fak','croatia','M');");
		output.write("\n");
		output.write("insert into athletes values('cleski','usa','M');");
		output.write("\n");
		output.write("insert into athletes values('mo','korea','M');");
		output.write("\n");
		output.write("insert into athletes values('ammann','switzerland','M');");
		output.write("\n");
		output.write("insert into athletes values('malysz','poland','M');");
		output.write("\n");
		output.write("insert into athletes values('schlierenzauer','austria','M');");
		output.write("\n");
		output.write("insert into athletes values('kramer','netherlands','M');");
		output.write("\n");
		output.write("insert into athletes values('skobrev','russia','M');");
		output.write("\n");
		output.write("insert into athletes values('lee','korea','M');");
		output.write("\n");
		output.write("insert into athletes values('kuzmina','slovakia','F');");
		output.write("\n");
		output.write("insert into athletes values('neuner','germany','F');");
		output.write("\n");
		output.write("insert into athletes values('dorin','france','F');");
		output.write("\n");
		output.write("insert into athletes values('davis','usa','M');");
		output.write("\n");
		output.write("insert into athletes values('ohno','usa','M');");
		output.write("\n");
		output.write("insert into athletes values('hedrick','usa','M');");
		output.write("\n");
		output.write("insert into athletes values('kim','korea','F');");
		output.write("\n");
		output.write("insert into athletes values('asada','japan','F');");
		output.write("\n");
		output.write("insert into athletes values('rochette','canada','F');");
		output.write("\n");
		output.write("insert into athletes values('mcivor','canada','F');");
		output.write("\n");
		output.write("insert into athletes values('hedda','norway','F');");
		output.write("\n");
		output.write("insert into athletes values('huttary','austria','F');");
		output.write("\n");
		output.write("insert into athletes values('miller','usa','M');");
		output.write("\n");
		output.write("insert into athletes values('andrea','austria','F');");
		output.write("\n");
		output.write("insert into athletes values('lysacek','usa','M');");
		output.write("\n");
		output.write("insert into athletes values('plushenko','russia','M');");
		output.write("\n");
		output.write("insert into athletes values('takahashi','japan','M');");
		output.write("\n");
		output.write("insert into athletes values('paerson','sweden','F');");
		output.write("\n");
		output.write("insert into athletes values('riesch','germany','F');");
		output.write("\n");
		output.write("insert into athletes values('razzoli','italy','M');");
		output.write("\n");
		output.write("insert into athletes values('mancuso','usa','F');");
		output.write("\n");
		output.write("insert into competitions values(3,'biathlon','1000');");
		output.write("\n");
		output.write("insert into competitions values(4,'skijumping','nh');");
		output.write("\n");
		output.write("insert into competitions values(5,'speedskating','1000');");
		output.write("\n");
		output.write("insert into competitions values(6,'speedskating','500');");
		output.write("\n");
		output.write("insert into competitions values(7,'shorttrack','1500');");
		output.write("\n");
//		output.write("insert into competitions values(8,'speedskating','1000');");
//		output.write("\n");
		output.write("insert into competitions values(9,'figureskating','');");
		output.write("\n");
		output.write("insert into competitions values(10,'giantslalom','');");
		output.write("\n");
		output.write("insert into competitions values(11,'crosscountry','');");
		output.write("\n");
		output.write("insert into competitions values(12,'slalom','');");
		output.write("\n");
		output.write("insert into competitions values(13,'super-combined','');");
		output.write("\n");
		output.write("insert into competitions values(15,'skijumping','lh');");
		output.write("\n");
		output.write("insert into competitions values(16,'biathlon','7500');");
		output.write("\n");

		int count =1;

		while (dis.available() != 0) {
            // this statement reads the line from the file and print it to
              // the console.

                s1 = dis.readLine();
                //System.out.println(s1);
         if(s1.contains("who")==true || s1.contains("Who")==true)
         {
        	 if(s1.contains("gold")==true || s1.contains("first")==true || s1.contains("Gold")==true || s1.contains("First")==true)
        		 medal="gold";
        	 if(s1.contains("silver")==true || s1.contains("second")==true || s1.contains("Silver")==true || s1.contains("Second")==true)
            	 medal="silver";
        	 if(s1.contains("bronze")==true || s1.contains("third")==true || s1.contains("Bronze")==true || s1.contains("Third")==true)
            	 medal="bronze";
        	 
         	if(s1.contains("biathlon")==true || s1.contains("Biathlon")==true)
         		event="biathlon";
         	if(s1.contains("skijumping")==true || s1.contains("Skijumping")==true || s1.contains("SkiJumping")==true)
         		event="skijumping";
         	if(s1.contains("speedskating")==true || s1.contains("Speedskating")==true || s1.contains("SpeedSkating")==true)
         		event="speedskating";
         	if(s1.contains("shorttrack")==true || s1.contains("Shorttrack")==true || s1.contains("ShortTrack")==true)
         		event="shorttrack";
         	if(s1.contains("figureskating")==true || s1.contains("Figureskating")==true || s1.contains("FigureSkating")==true)
         		event="figureskating";
         	if(s1.contains("slalom")==true || s1.contains("Slalom")==true)
         		event="slalom";
         	if(s1.contains("giantslalom")==true || s1.contains("Giantslalom")==true || s1.contains("GiantSlalom")==true)
         		event="giantslalom";
         	if(s1.contains("crosscountry")==true || s1.contains("CrossCountry")==true || s1.contains("crossCountry")==true)
         		event="crosscountry";
         	
         	if(s1.contains("super-combined")==true || s1.contains("Super-Combined")==true)
         		event="super-combined";
		sql = "select r.winner from results r ,competitions c where r.comp_id=c.comp_id and r.medal=\"" + medal +"\" and c.name=\""+event+"\";";
		output.write("update text set question='Question is: "+s1+"',sql='Corresponding SQL generated is: "+sql+"' where number="+count+";");
		output.write("\n");
		
		question = "select question from text where number =" +count +";";
		output.write(question);
		output.write("\n");
		
		sql1 = "select sql from text where number =" +count +";";
		output.write(sql1);
		output.write("\n");

		text = "select sentence from text where number =" +count +";";         	
         	output.write(text);
		output.write("\n");
		//sql = "select count (*) from results r ,competitions c where r.comp_id=c.comp_id and r.medal='" + medal +"' and c.name='"+event+"';";
         	//output.write(sql);
         	//output.write("\n");

		
         	
         	
         	//System.out.print(sql);
         	//System.out.println("/n");
         	output.write(sql);
         	output.write("\n");
		separator = "select separator from text where number =" +count +";";         	
         	output.write(separator);
		output.write("\n");
		count++;
         	// 	System.out.print(db.get_table(sql));
        }
         
    if(s1.contains("Italian")==true || s1.contains("Norwegian")==true || s1.contains("swiss")==true || s1.contains("Canadian")==true || s1.contains("french")==true || s1.contains("Croatian")==true || s1.contains("American")==true || s1.contains("korean")==true || s1.contains("polish")==true || s1.contains("austrian")==true ||s1.contains("dutch")==true || s1.contains("russian")==true || s1.contains("slovak")==true || s1.contains("slovakian")==true || s1.contains("german")==true || s1.contains("japanese")==true || s1.contains("swedish")==true || s1.contains("italian")==true || s1.contains("norwegian")==true || s1.contains("Swiss")==true || s1.contains("canadian")==true || s1.contains("French")==true || s1.contains("croatian")==true || s1.contains("american")==true || s1.contains("Korean")==true || s1.contains("Polish")==true || s1.contains("Austrian")==true ||s1.contains("Dutch")==true || s1.contains("Russian")==true || s1.contains("Slovak")==true || s1.contains("Slovakian")==true || s1.contains("German")==true || s1.contains("Japanese")==true || s1.contains("Swedish")==true)    	 
    {
    			if(s1.contains("Italian")==true || s1.contains("italian")==true)
    
                	{
                		nationality = "italy";
                	}
                if(s1.contains("Norwegian")==true || s1.contains("norwegian")==true)
                	{
                	nationality = "norway";
                	}
                if(s1.contains("swiss")==true || s1.contains("Swiss")==true)
                	{
                	nationality = "switzerland";
                	}
                if(s1.contains("Canadian")==true || s1.contains("canadian")==true)
                	{
                	nationality = "canada";
                	}
                if(s1.contains("french")==true || s1.contains("French")==true)
                	{
                	nationality = "france";
                	}
                if(s1.contains("Croatian")==true || s1.contains("croatian")==true)
                	{
                	nationality = "croatia";
                	}
                if(s1.contains("American")==true || s1.contains("american")==true)
                {
                	nationality = "usa";
                }
                if(s1.contains("korean")==true || s1.contains("Korean")==true)
            	{
                	nationality = "korea";
            	}
            if(s1.contains("polish")==true || s1.contains("Polish")==true)
            	{
            	nationality = "poland";
            	}
            if(s1.contains("austrian")==true || s1.contains("Austrian")==true)
            	{
            	nationality = "austria";
            	}
            if(s1.contains("dutch")==true || s1.contains("Dutch")==true)
            	{
            	nationality = "netherlands";
            	}
            if(s1.contains("russian")==true || s1.contains("Russian")==true)
            	{
            	nationality = "russia";
            	}
            if(s1.contains("slovak")==true || s1.contains("Slovak")==true || s1.contains("slovakian")==true || s1.contains("Slovakian")==true)
            	{
            	nationality = "slovakia";
            	}
            if(s1.contains("german")==true || s1.contains("German")==true)
            {
            	nationality = "germany";
            }
            if(s1.contains("japanese")==true || s1.contains("Japanese")==true)
            {
            	nationality = "japan";

            }
            if(s1.contains("swedish")==true || s1.contains("Swedish")==true)
            {
            	nationality = "sweden";
            }
            if(s1.contains("man")==true || s1.contains("Man")==true)
            	gender="M";
            if (s1.contains("woman")==true || s1.contains("Woman")==true)
            	gender="F";
            if(s1.contains("gold")==true || s1.contains("first")==true || s1.contains("Gold")==true || s1.contains("First")==true)
       		 medal="gold";
       	 if(s1.contains("silver")==true || s1.contains("second")==true || s1.contains("Silver")==true || s1.contains("Second")==true)
           	 medal="silver";
       	 if(s1.contains("bronze")==true || s1.contains("third")==true || s1.contains("Bronze")==true || s1.contains("Third")==true)
           	 medal="bronze";
       	 
        	if(s1.contains("biathlon")==true || s1.contains("Biathlon")==true)
        		event="biathlon";
        	if(s1.contains("skijumping")==true || s1.contains("Skijumping")==true || s1.contains("SkiJumping")==true)
        		event="skijumping";
        	if(s1.contains("speedskating")==true || s1.contains("Speedskating")==true || s1.contains("SpeedSkating")==true)
        		event="speedskating";
        	if(s1.contains("shorttrack")==true || s1.contains("Shorttrack")==true || s1.contains("ShortTrack")==true)
        		event="shorttrack";
        	if(s1.contains("figureskating")==true || s1.contains("Figureskating")==true || s1.contains("FigureSkating")==true)
        		event="figureskating";
        	if(s1.contains("slalom")==true || s1.contains("Slalom")==true)
        		event="slalom";
        	if(s1.contains("giantslalom")==true || s1.contains("Giantslalom")==true || s1.contains("GiantSlalom")==true)
        		event="giantslalom";
        	if(s1.contains("crosscountry")==true || s1.contains("CrossCountry")==true || s1.contains("crossCountry")==true)
        		event="crosscountry";
        	
        	if(s1.contains("super-combined")==true || s1.contains("Super-Combined")==true)
        		event="super-combined";
sql = "select count(*) from athletes a,results r ,competitions c where r.winner=a.name and r.comp_id=c.comp_id and r.medal=\"" + medal +"\" and c.name=\""+event+"\" and a.gender=\""+gender+"\" and a.nationality=\""+nationality+"\";";
output.write("update text set question='Question is: "+s1+"',sql='Corresponding SQL generated is: "+sql+"' where number="+count+";");
		output.write("\n");
		
		question = "select question from text where number =" +count +";";
		output.write(question);
		output.write("\n");
		
		sql1 = "select sql from text where number =" +count +";";
		output.write(sql1);
		output.write("\n");
text = "select sentence from text where number =" +count +";";         	
         	output.write(text);
		output.write("\n");

//System.out.print(sql);
//System.out.println("/n");
output.write(sql);
	output.write("\n");
separator = "select separator from text where number =" +count +";";         	
         	output.write(separator);
		output.write("\n");
	count++;
         //	System.out.print(db.get_table(sql));
    }                 	
if(s1.contains("1000")==true || s1.contains("500")==true || s1.contains("1500")==true || s1.contains("nh")==true || s1.contains("lh")==true || s1.contains("7500")==true)
{
if(s1.contains("1000")==true)
type="1000";
if(s1.contains("500")==true)
type="500";
if(s1.contains("1500")==true)
type="1500";
if(s1.contains("7500")==true)
type="7500";
if(s1.contains("lh")==true)
type="lh";
if(s1.contains("nh")==true)
type="nh";
if(s1.contains("biathlon")==true || s1.contains("Biathlon")==true)
        		event="biathlon";
        	if(s1.contains("skijumping")==true || s1.contains("Skijumping")==true || s1.contains("SkiJumping")==true)
        		event="skijumping";
        	if(s1.contains("speedskating")==true || s1.contains("Speedskating")==true || s1.contains("SpeedSkating")==true)
        		event="speedskating";
        	if(s1.contains("shorttrack")==true || s1.contains("Shorttrack")==true || s1.contains("ShortTrack")==true)
        		event="shorttrack";
/*        	if(s1.contains("figureskating")==true || s1.contains("Figureskating")==true || s1.contains("FigureSkating")==true)
        		event="figureskating";
        	if(s1.contains("slalom")==true || s1.contains("Slalom")==true)
        		event="slalom";
        	if(s1.contains("giantslalom")==true || s1.contains("Giantslalom")==true || s1.contains("GiantSlalom")==true)
        		event="giantslalom";
        	if(s1.contains("crosscountry")==true || s1.contains("CrossCountry")==true || s1.contains("crossCountry")==true)
        		event="crosscountry";
        	
        	if(s1.contains("super-combined")==true || s1.contains("Super-Combined")==true)
        		event="super-combined";*/
if(s1.contains("gold")==true || s1.contains("first")==true || s1.contains("Gold")==true || s1.contains("First")==true)
       		 medal="gold";
       	 if(s1.contains("silver")==true || s1.contains("second")==true || s1.contains("Silver")==true || s1.contains("Second")==true)
           	 medal="silver";
       	 if(s1.contains("bronze")==true || s1.contains("third")==true || s1.contains("Bronze")==true || s1.contains("Third")==true)
           	 medal="bronze";
if(s1.contains("svedsen")==true || s1.contains("Svedsen")==true || s1.contains("svendsen")==true || s1.contains("Svendsen")==true)
    		name="svendsen";
    	if(s1.contains("urbriggen")==true || s1.contains("Urbriggen")==true)
    		name="zurbriggen";
    	if(s1.contains("jay")==true || s1.contains("Jay")==true)
    		name="jay";
    	if(s1.contains("kostelic")==true || s1.contains("Kostelic")==true)
    		name="kostelic";
    	if(s1.contains("myhrer")==true || s1.contains("Myhrer")==true)
    		name="myhrer";
    	if(s1.contains("fak")==true || s1.contains("Fak")==true)
    		name = "fak";
    	if(s1.contains("cleski")==true || s1.contains("Cleski")==true)
    		name="cleski";
    	if(s1.contains("mo")==true || s1.contains("Mo")==true)
    		name="mo";
    	if(s1.contains("ammann")==true || s1.contains("Ammann")==true)
    		name="ammann";
    	if(s1.contains("malysz")==true || s1.contains("Malysz")==true)
    		name="malysz";
    	if(s1.contains("schlierenzauer")==true || s1.contains("Schlierenzauer")==true)
    		name="schlierenzauer";
    	if(s1.contains("kramer")==true || s1.contains("Kramer")==true)
    		name="kramer";
    	if(s1.contains("skobrev")==true || s1.contains("Skobrev")==true)
    		name="skobrev";
    	if(s1.contains("Lee")==true || s1.contains("lee")==true)
    		name="lee";
    	if(s1.contains("kuzmina")==true || s1.contains("Kuzmina")==true)
    		name="kuzmina";
    	if(s1.contains("neuner")==true || s1.contains("Neuner")==true)
    		name="neuner";
    	if( s1.contains("dorin")==true || s1.contains("Dorin")==true)
    		name="dorin";
    	if(s1.contains("davis")==true || s1.contains("Davis")==true)
    		name="davis";
    	if(s1.contains("ohno")==true || s1.contains("Ohno")==true)
    		name="ohno";
    	if(s1.contains("hedrick")==true || s1.contains("Hedrick")==true)
    		name="hedrick";
    	if(s1.contains("kim")==true || s1.contains("Kim")==true)
    		name="kim";
    	if(s1.contains("asada")==true || s1.contains("Asada")==true)
    		name="asada";
    	if(s1.contains("rochette")==true || s1.contains("Rochette")==true)
    		name="rochette";
    	if(s1.contains("mcivor")==true || s1.contains("Mcivor")==true)
    		name="mcivor";
    	if(s1.contains("hedda")==true || s1.contains("Hedda")==true)
    		name="hedda";
    	if(s1.contains("huttary")==true || s1.contains("Huttary")==true)
    		name="huttary";
    	if(s1.contains("miller")==true || s1.contains("Miller")==true)
    		name="miller";
    	if(s1.contains("andrea")==true || s1.contains("Andrea")==true)
    		name="andrea";
    	if(s1.contains("lysacek")==true || s1.contains("Lysacek")==true)
    		name="lysacek";
    	if(s1.contains("plushenko")==true || s1.contains("Plushenko")==true)
    		name="plushenko";
    	if(s1.contains("takahashi")==true || s1.contains("Takahashi")==true)
    		name="takahashi";
    	if(s1.contains("paerson")==true || s1.contains("Paerson")==true)
    		name="paerson";
    	if(s1.contains("riesch")==true || s1.contains("Riesch")==true)
    		name="riesch";
    	if(s1.contains("razzoli")==true || s1.contains("Razzoli")==true)
    		name="razzoli";
    	if(s1.contains("mancuso")==true || s1.contains("mancuso")==true)
    		name="mancuso";
sql = "select count(*) from results r ,competitions c where r.comp_id=c.comp_id and r.medal=\"" + medal +"\" and c.name=\""+event+"\" and r.winner=\""+name+"\" and c.type=\""+type+"\";";
	output.write("update text set question='Question is: "+s1+"',sql='Corresponding SQL generated is: "+sql+"' where number="+count+";");
		output.write("\n");
		
		question = "select question from text where number =" +count +";";
		output.write(question);
		output.write("\n");
		
		sql1 = "select sql from text where number =" +count +";";
		output.write(sql1);
		output.write("\n");
text = "select sentence from text where number =" +count +";";         	
         	output.write(text);
		output.write("\n");

//System.out.print(sql);
//System.out.println("/n");
output.write(sql);
	output.write("\n");
separator = "select separator from text where number =" +count +";";         	
         	output.write(separator);
		output.write("\n");
	count++;
}
    if((s1.contains("svedsen")==true || s1.contains("svendsen")==true || s1.contains("zurbriggen")==true || s1.contains("jay")==true || s1.contains("kostelic")==true || s1.contains("myhrer")==true || s1.contains("fak")==true || s1.contains("cleski")==true || s1.contains("mo")==true || s1.contains("ammann")==true || s1.contains("malysz")==true || s1.contains("schlierenzauer")==true || s1.contains("kramer")==true || s1.contains("skobrev")==true || s1.contains("lee")==true || s1.contains("kuzmina")==true || s1.contains("neuner")==true || s1.contains("dorin")==true || s1.contains("davis")==true || s1.contains("ohno")==true || s1.contains("hedrick")==true || s1.contains("kim")==true || s1.contains("asada")==true || s1.contains("rochette")==true || s1.contains("mcivor")==true || s1.contains("hedda")==true || s1.contains("huttary")==true || s1.contains("miller")==true || s1.contains("andrea")==true || s1.contains("lysacek")==true || s1.contains("plushenko")==true || s1.contains("takahashi")==true || s1.contains("paerson")==true || s1.contains("riesch")==true || s1.contains("razzoli")==true || s1.contains("ancuso")==true || s1.contains("Svedsen")==true || s1.contains("Svendsen")==true || s1.contains("Zurbriggen")==true || s1.contains("Jay")==true || s1.contains("Kostelic")==true || s1.contains("Myhrer")==true || s1.contains("Fak")==true || s1.contains("Cleski")==true || s1.contains("Mo")==true || s1.contains("Ammann")==true || s1.contains("Malysz")==true || s1.contains("Schlierenzauer")==true || s1.contains("Kramer")==true || s1.contains("Skobrev")==true || s1.contains("Lee")==true || s1.contains("Kuzmina")==true || s1.contains("Neuner")==true || s1.contains("Dorin")==true || s1.contains("Davis")==true || s1.contains("Ohno")==true || s1.contains("Hedrick")==true || s1.contains("Kim")==true || s1.contains("Asada")==true || s1.contains("Rochette")==true || s1.contains("Mcivor")==true || s1.contains("Hedda")==true || s1.contains("Huttary")==true || s1.contains("Miller")==true || s1.contains("Andrea")==true || s1.contains("Lysacek")==true || s1.contains("Plushenko")==true || s1.contains("Takahashi")==true || s1.contains("Paerson")==true || s1.contains("Riesch")==true || s1.contains("Razzoli")==true || s1.contains("Mancuso")==true) && (s1.contains("1000")==false && s1.contains("500")==false && s1.contains("1500")==false && s1.contains("nh")==false && s1.contains("lh")==false && s1.contains("7500")==false))
    {
    	if(s1.contains("svedsen")==true || s1.contains("Svedsen")==true || s1.contains("svendsen")==true || s1.contains("Svendsen")==true)
    		name="svendsen";
    	if(s1.contains("urbriggen")==true || s1.contains("Urbriggen")==true)
    		name="zurbriggen";
    	if(s1.contains("jay")==true || s1.contains("Jay")==true)
    		name="jay";
    	if(s1.contains("kostelic")==true || s1.contains("Kostelic")==true)
    		name="kostelic";
    	if(s1.contains("myhrer")==true || s1.contains("Myhrer")==true)
    		name="myhrer";
    	if(s1.contains("fak")==true || s1.contains("Fak")==true)
    		name = "fak";
    	if(s1.contains("cleski")==true || s1.contains("Cleski")==true)
    		name="cleski";
    	if(s1.contains("mo")==true || s1.contains("Mo")==true)
    		name="mo";
    	if(s1.contains("ammann")==true || s1.contains("Ammann")==true)
    		name="ammann";
    	if(s1.contains("malysz")==true || s1.contains("Malysz")==true)
    		name="malysz";
    	if(s1.contains("schlierenzauer")==true || s1.contains("Schlierenzauer")==true)
    		name="schlierenzauer";
    	if(s1.contains("kramer")==true || s1.contains("Kramer")==true)
    		name="kramer";
    	if(s1.contains("skobrev")==true || s1.contains("Skobrev")==true)
    		name="skobrev";
    	if(s1.contains("Lee")==true || s1.contains("lee")==true)
    		name="lee";
    	if(s1.contains("kuzmina")==true || s1.contains("Kuzmina")==true)
    		name="kuzmina";
    	if(s1.contains("neuner")==true || s1.contains("Neuner")==true)
    		name="neuner";
    	if( s1.contains("dorin")==true || s1.contains("Dorin")==true)
    		name="dorin";
    	if(s1.contains("davis")==true || s1.contains("Davis")==true)
    		name="davis";
    	if(s1.contains("ohno")==true || s1.contains("Ohno")==true)
    		name="ohno";
    	if(s1.contains("hedrick")==true || s1.contains("Hedrick")==true)
    		name="hedrick";
    	if(s1.contains("kim")==true || s1.contains("Kim")==true)
    		name="kim";
    	if(s1.contains("asada")==true || s1.contains("Asada")==true)
    		name="asada";
    	if(s1.contains("rochette")==true || s1.contains("Rochette")==true)
    		name="rochette";
    	if(s1.contains("mcivor")==true || s1.contains("Mcivor")==true)
    		name="mcivor";
    	if(s1.contains("hedda")==true || s1.contains("Hedda")==true)
    		name="hedda";
    	if(s1.contains("huttary")==true || s1.contains("Huttary")==true)
    		name="huttary";
    	if(s1.contains("miller")==true || s1.contains("Miller")==true)
    		name="miller";
    	if(s1.contains("andrea")==true || s1.contains("Andrea")==true)
    		name="andrea";
    	if(s1.contains("lysacek")==true || s1.contains("Lysacek")==true)
    		name="lysacek";
    	if(s1.contains("plushenko")==true || s1.contains("Plushenko")==true)
    		name="plushenko";
    	if(s1.contains("takahashi")==true || s1.contains("Takahashi")==true)
    		name="takahashi";
    	if(s1.contains("paerson")==true || s1.contains("Paerson")==true)
    		name="paerson";
    	if(s1.contains("riesch")==true || s1.contains("Riesch")==true)
    		name="riesch";
    	if(s1.contains("razzoli")==true || s1.contains("Razzoli")==true)
    		name="razzoli";
    	if(s1.contains("mancuso")==true || s1.contains("mancuso")==true)
    		name="mancuso";
    	if(s1.contains("gold")==true || s1.contains("first")==true || s1.contains("Gold")==true || s1.contains("First")==true)
      		 medal="gold";
      	 if(s1.contains("silver")==true || s1.contains("second")==true || s1.contains("Silver")==true || s1.contains("Second")==true)
          	 medal="silver";
      	 if(s1.contains("bronze")==true || s1.contains("third")==true || s1.contains("Bronze")==true || s1.contains("Third")==true)
          	 medal="bronze";
      	 
       	if(s1.contains("biathlon")==true || s1.contains("Biathlon")==true)
       		event="biathlon";
       	if(s1.contains("skijumping")==true || s1.contains("Skijumping")==true || s1.contains("SkiJumping")==true)
       		event="skijumping";
       	if(s1.contains("speedskating")==true || s1.contains("Speedskating")==true || s1.contains("SpeedSkating")==true)
       		event="speedskating";
       	if(s1.contains("shorttrack")==true || s1.contains("Shorttrack")==true || s1.contains("ShortTrack")==true)
       		event="shorttrack";
       	if(s1.contains("figureskating")==true || s1.contains("Figureskating")==true || s1.contains("FigureSkating")==true)
       		event="figureskating";
       	if(s1.contains("slalom")==true || s1.contains("Slalom")==true)
       		event="slalom";
       	if(s1.contains("giantslalom")==true || s1.contains("Giantslalom")==true || s1.contains("GiantSlalom")==true)
       		event="giantslalom";
       	if(s1.contains("crosscountry")==true || s1.contains("CrossCountry")==true || s1.contains("crossCountry")==true)
       		event="crosscountry";
       	
       	if(s1.contains("super-combined")==true || s1.contains("Super-Combined")==true)
       		event="super-combined";
sql = "select count(*) from results r ,competitions c where r.comp_id=c.comp_id and r.medal=\"" + medal +"\" and c.name=\""+event+"\" and r.winner=\""+name+"\";";
	output.write("update text set question='Question is: "+s1+"',sql='Corresponding SQL generated is: "+sql+"' where number="+count+";");
		output.write("\n");
		
		question = "select question from text where number =" +count +";";
		output.write(question);
		output.write("\n");
		
		sql1 = "select sql from text where number =" +count +";";
		output.write(sql1);
		output.write("\n");
text = "select sentence from text where number =" +count +";";         	
         	output.write(text);
		output.write("\n");

//System.out.print(sql);
//System.out.println("/n");
output.write(sql);
	output.write("\n");
separator = "select separator from text where number =" +count +";";         	
         	output.write(separator);
		output.write("\n");
	count++;
        	//System.out.print(db.get_table(sql));
    }
    }
		
		output.write(".exit;");		
		output.close();

	   //System.out.print(db.get_table("select count(*) from athletes a,competitions c,results r where a.name=r.winner and c.comp_id=r.comp_id and r.medal='bronze' and c.name='figureskating' and a.gender='M' and a.nationality='canada';"));
	   
	 
		
		
	    // perform SQL database insertion and queries with the batch file
	
				String line1;
			 	Process q = Runtime.getRuntime().exec(" ./sqlite.bin -init sql1.bat ");
			 	
			 	BufferedReader input1 =
			 	 	new BufferedReader
			 	 	(new InputStreamReader(q.getInputStream()));
			 	 	while ((line1 = input1.readLine()) != null) {
			 	 		System.out.println(line1);
			
			 	 		
			 	 	}
			 	 	input1.close();
			 	    
			 	 	
			} catch (Exception err2) 
			    {
			 	err2.printStackTrace(); 
			    }
	        
			System.out.print("The answer can be found in file sql_output_final.txt in the same directory.\n");
			File file2 = new File("sql_out.txt");
		   FileInputStream fis = null;
		    BufferedInputStream bis = null;
		    DataInputStream dis = null;
		    Writer output =null;
		//	File file1 = new File("/mnt_nfs/home1/class/temp563/Desktop/lopar/data/part2.txt");
			File file3 = new File("sql_output_final.txt");
		    //File file1 = new File("/mnt_nfs/home4/grad4/vsingla/LoPar-3.0/data/part2.txt");
		    //File file1 = new File("C:\\Masters\\SP-10\\421\\Term project\\questions1.txt");
			String sourceLine;
	     String content = "";
	     String s1;
	     output = new BufferedWriter(new FileWriter(file3));
			String sql="";
		fis = new FileInputStream(file2);
		
		FileReader rd = new FileReader(file2);
		int leng,leng1,leng2;
		int index1, index2;
		String substring1;
		String substring2;
		String str;
		int count=1;		
        // Here BufferedInputStream is added for fast reading.
        bis = new BufferedInputStream(fis);
        dis = new DataInputStream(bis);
        while (dis.available() != 0) {
			s1 = dis.readLine();
			if(s1.contains("Answer to")==true)
{
			output.write(s1);
				output.write("\n");
}
if(s1.contains("1000")==true || s1.contains("1500")==true || s1.contains("500")==true || s1.contains("7500")==true || s1.contains("lh")==true || s1.contains("nh")==true)
{
		output.write(s1);
				output.write("\n");
}
			if(s1.contains("1")==true && s1.contains("Answer to")==false && s1.contains("1000")==false && s1.contains("1500")==false && s1.contains("500")==false && s1.contains("7500")==false && s1.contains("lh")==false && s1.contains("nh")==false)
{
			output.write("Yes");
				output.write("\n");				
}

if(s1.contains("2")==true && s1.contains("Answer to")==false && s1.contains("1000")==false && s1.contains("1500")==false && s1.contains("500")==false && s1.contains("7500")==false && s1.contains("lh")==false && s1.contains("nh")==false)
{
			output.write("Yes");
				output.write("\n");				
}
if(s1.contains("3")==true && s1.contains("Answer to")==false && s1.contains("1000")==false && s1.contains("1500")==false && s1.contains("500")==false && s1.contains("7500")==false && s1.contains("lh")==false && s1.contains("nh")==false)
{
			output.write("Yes");
				output.write("\n");				
}
if(s1.contains("4")==true && s1.contains("Answer to")==false && s1.contains("1000")==false && s1.contains("1500")==false && s1.contains("500")==false && s1.contains("7500")==false && s1.contains("lh")==false && s1.contains("nh")==false)
{
			output.write("Yes");
				output.write("\n");				
}

if(s1.contains("0")==true && s1.contains("Answer to")==false && s1.contains("1000")==false && s1.contains("1500")==false && s1.contains("500")==false && s1.contains("7500")==false && s1.contains("lh")==false && s1.contains("nh")==false)
{
			output.write("No");
				output.write("\n");				
}
				
if(s1.contains("Answer to")==false && s1.contains("1")==false && s1.contains("0")==false && s1.contains("lh")==false && s1.contains("nh")==false)
{
output.write(s1);
				output.write("\n");
}
//			System.out.println(s1);


/*if(s1.contains("0")==true)
{
output.write("Answer to question " +count + " is: No");
output.write("\n");
				count++;
}
else
{
output.write("Answer to question " +count + " is ");

}*/
		}
output.close();
  }// end main
	
}// end class

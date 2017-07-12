`	import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.lang.Exception;
import SQLite.*;
import java.sql.*;
import java.io.*;

public class termproject {

	public static void main (String[] args) throws IOException {
		Connection conn = null;
		 SQLite.Database db = null;
		 try {
		   Class.forName("SQLite.JDBCDriver").newInstance();
		   conn = DriverManager.getConnection("jdbc:sqlite:/blabla");
		  // conn = DriverManager.getConnection("C:\\Users\\Vineet\\Desktop\\sqlite-3_6_23_1\\sqlite3.exe");
		   java.lang.reflect.Method m =
		     conn.getClass().getMethod("getSQLiteDatabase", null);
		   db = (SQLite.Database) m.invoke(conn, null);
		   db = new SQLite.Database();
		   db.open("db", 0);
		   File file = new File("C:\\Masters\\SP-10\\421\\Term project\\questions.txt");
		   FileInputStream fis = null;
		    BufferedInputStream bis = null;
		    DataInputStream dis = null;
		    Writer output =null;
		    File file1 = new File("C:\\Masters\\SP-10\\421\\Term project\\questions1.txt");
			String sourceLine;
	        String content = "";
	        String s1;
	        output = new BufferedWriter(new FileWriter(file1));
			String sql="";
		   //System.out.print(db.get_table("create table competitions(comp_id int primary key, name varchar(20), type varchar(10));"));
		   //System.out.println("asf");
		   //System.out.print(db.get_table("insert into results values(3, 'fak','bronze');"));
		   //System.out.print(db.get_table("delete from results where winner='fak';"));
		   //System.out.print(db.get_table("select * from sqlite_master;"));
		   //System.out.print(db.get_table("insert into results values(4,'ammann','gold');"));
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
                    	System.out.println(str);
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
             
		   System.out.print(db.get_table("select count(*) from athletes a,competitions c,results r where a.name=r.winner and c.comp_id=r.comp_id and r.medal='bronze' and c.name='figureskating' and a.gender='M' and a.nationality='canada';"));
		   
		 } catch (Exception e) {
		 }
		 
	}
	
}

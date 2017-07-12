//Arnold Lee
//UIN: 665453451
//CS 480 Program 2
//August 1st,2012

package University;

import java.sql.*;
import java.util.Random;
import java.io.*;
import java.math.*;

public class University {

	static Connection db; // a socket to the database
	
	    //connecting
		public static void connect(int num)
		{
			try
			{			
				Class.forName("com.mysql.jdbc.Driver").newInstance();
				db = DriverManager.getConnection("jdbc:mysql://localhost/?"+"user=root&password=Iluvlcp2");			
		        // please change your host name, user name and password on above line.
			
			} catch (SQLException ex) {
				System.out.println("SQLException: " + ex.getMessage());
			    System.out.println("SQLState: " + ex.getSQLState());
			    System.out.println("VendorError: " + ex.getErrorCode());
			}
			catch(Exception e) {
				e.printStackTrace();
			}
		}
		
		
		//database creation
		
		public static void create_db (int count, int dept_tuple, int student_tuple, 
				int inst_tuple, int course_tuple, int teach_tuple, int takes_tuple)
		{
			
			//section 1. Database creation;
			
			String export = "";
			
			Statement stmt = null;
			
			try {
			
			stmt = db.createStatement();
			
			stmt.execute("drop schema if exists university"+count+";");
			
			export = "create database if not exists university" +  count  + ";";
			
			stmt.execute(export);

			export = "use university1;";
			
			stmt.execute(export);
			
			export = "";
	
			export = export + "create table department  \n";		
			export = export + "(dept_name		varchar(20) primary key, \n"; 
			export = export + "	 building		varchar(15), \n "; 
			export = export + "	 budget		        numeric(12,2) \n";
			export = export + "	);";
			
			stmt.execute(export);
			
			export = "";

			export = export + "create table student ";
			export = export + "	(ID			int, ";
			export = export + "	 name			varchar(20) not null, "; 
			export = export + "	 dept_name		varchar(20), "; 
			export = export + "	 tot_cred		numeric(3,0), ";
			export = export + "	 primary key (ID), ";
			export = export + "	 foreign key (dept_name) references department(dept_name) ";
			export = export + "	); \n";
			
			stmt.execute(export);
			export = "";

			export = export + "create table course ";
			export = export + "	(course_id		int, ";
			export = export + "	 title			varchar(50),"; 
			export = export + "dept_name		varchar(15),";
			export = export + "credits		numeric(2,0),";
			export = export + "primary key (course_id),";
			export = export + "foreign key (dept_name) references department(dept_name)";
			export = export + "); \n";
			
			stmt.execute(export);
			export = "";
			
			export = export + "create table instructor ";
			export = export + "(ID			int,"; 
			export = export + "name			varchar(20) not null,"; 
			export = export + "dept_name		varchar(20),"; 
			export = export + "salary			numeric(8,2),";
			export = export + "primary key (ID),";
			export = export + "foreign key (dept_name) references department(dept_name)";
			export = export + "); \n";
			
			stmt.execute(export);
			export = "";
			
			export = export + "create table teaches ";
			export = export + "(ID			int,"; 
			export = export + "course_id		int,";
			export = export + "semester		varchar(6),";
			export = export + "year			numeric(4,0),";
			export = export + "primary key (ID, course_id, semester, year),";
			export = export + "foreign key (course_id) references course(course_id) ";
			export = export + "on delete cascade,";
			export = export + "foreign key (ID) references instructor(ID) ";
			export = export + "on delete cascade";
			export = export + "); \n";

			stmt.execute(export);
			export = "";
			
			export = export + "create table takes ";
			export = export + "(ID			int,"; 
			export = export + "course_id		int,";
			export = export + "semester		varchar(6),";
			export = export + "year			numeric(4,0),";
			export = export + "grade		        varchar(2),";
			export = export + "primary key (ID, course_id, semester, year),";
			export = export + "foreign key (course_id) references course(course_id)";
			export = export + "on delete cascade,";
			export = export + "foreign key (ID) references student(ID) ";
			export = export + "on delete cascade";
			export = export + ");";

			stmt.execute(export);
			
			} catch (SQLException e) {
				System.out.println("There are problems in your JDBC setup.");
				e.printStackTrace();
			};
			
			// section 2. Prefill the database with randomly generated data
			
			String semester;
			int year;
			char course_id;
			int ID;
			int name;
			int salary;
			int credits;
		    char grade;
		    int tot_cred;
		    String dept_name;
		    int budget;
		    String building;
			
		    Random r = new Random();
		    
		    for (int x=0;x<dept_tuple;x++)
		    {
		    	export = "";
		    	dept_name = Long.toString(Math.abs(r.nextLong()), 36);
		    	building = Long.toString(Math.abs(r.nextLong()), 36);
		    	budget = (int) Math.random() *1000000;
		    	
		    	export = "insert into department ";
		    	export = export + "values ('" +dept_name+"','"+building+"','"+budget+"');";
		    	
		    	try {
					stmt.execute(export);
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
		    	
		    };
		   		
			
		}
		
	
	
	// main goes here
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		
	int count=0;
	char more = 0;
	String more_temp = "0";
	int dept_tuple = 0;
	int student_tuple = 0;
	int inst_tuple = 0;
	int teach_tuple = 0;
	int takes_tuple = 0;
	int course_tuple = 0;
	
	
		University uni = new University();
		
		connect(count+1);
		
		do
		{
			
			count++; // how many university database you have created so far?
			
			System.out.println( "Main Prompt" );
			System.out.println( "*******************************************" );
			System.out.print("University Database #");
			System.out.println(count);
			
            BufferedReader inputReader = new BufferedReader(new InputStreamReader(System.in)) ;
			
			
			try {
				
				System.out.print( "How many tuples would you like in department table-->" );
				
				dept_tuple =  Integer.parseInt(inputReader.readLine());
				
				System.out.print( "How many tuples would you like in student table-->" );
				
				student_tuple =  Integer.parseInt(inputReader.readLine());
				
				System.out.print( "How many tuples would you like in instructor table-->" );
				
				inst_tuple =  Integer.parseInt(inputReader.readLine());
				
				System.out.print( "How many tuples would you like in course table-->" );
				
				course_tuple =  Integer.parseInt(inputReader.readLine());
				
				System.out.print( "How many tuples would you like in teaches table-->" );
				
				teach_tuple =  Integer.parseInt(inputReader.readLine());
				
				System.out.print( "How many tuples would you like in takes table-->" );
				
				takes_tuple = Integer.parseInt(inputReader.readLine());
				
				System.out.println( "Do you want to make another database?" );
				System.out.print( "Press Y for yes, N for No, all other entry treat as N. Case Insensitve. Only first char counts -->" );
				
				more_temp =  (inputReader.readLine());
				
				more = more_temp.charAt(0);
				
				}
				catch(IOException e) {
				System.out.println("Error reading keyboard input") ;
				
				};
				
			   
			
			   create_db(count, dept_tuple, student_tuple, course_tuple, inst_tuple, teach_tuple, takes_tuple);
			   		   
			   System.out.println( "Database University #" + count + " has been created." );
			 
			
			
		}while ((more == 'y') || (more == 'Y'));
			
		System.out.println("Thank you for using this program.") ;
		
		try {
			db.close();
		}
		catch(Exception e) {
			e.printStackTrace();
		};
		
	} // end main

}// end class file

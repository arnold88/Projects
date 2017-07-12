//Arnold Lee
//UIN: 665453451
//CS 480 Program 1
//July 13th, 2012

package bookstore;

import java.sql.*;
import java.io.*;

public class Bookstore {

	static Connection db; // a socket to the database
	static boolean sign_in_flag = false; // signed in?
	boolean admin_flag = false; // administrator account used?
	String sign_in_id = "0"; // member ID of the signed in user
	
	// main program
	
	public static void main(String[] args) {
		
		Bookstore b = new Bookstore();
		b.connect();
		
		String selection = null;
		
		selection = b.main_menu();
		
		switch (selection)
		{
		case "R":
			registration();
		case "S":
			if (sign_in_flag == true)
				sign_out();
			else sign_in();
		case "V":
			viewtitles();
		case "C":
			view_shopping_history();
		
		}
	    	
		
		
		
			
		System.exit(1);
			
	}	
	
	//****************************************************
	//*************Functions goes down here***************
	
	//**************************************************
	//***********Section 1. Connection functions********
	//**************************************************
	
	//closing
	private void close()
	{
		try {
			db.close();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
	//connecting
	public void connect()
	{
		try
		{			
			Class.forName("com.mysql.jdbc.Driver").newInstance();
			db = DriverManager.getConnection("jdbc:mysql://localhost/bookstore?"+"user=root&password=Iluvlcp2");			
		} catch (SQLException ex) {
			System.out.println("SQLException: " + ex.getMessage());
		    System.out.println("SQLState: " + ex.getSQLState());
		    System.out.println("VendorError: " + ex.getErrorCode());
		}
		catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	//*******************************************
	//***********2. Menus************************
	//*******************************************
	
	//main menu
	public String main_menu()
	{
		boolean error_flag = true;
		
		String inputData = "";
			
		 do
		 {
			 
			error_flag = true;
			System.out.println( "Bookstore Main Menu" );
			System.out.println( "*******************************************" );
			System.out.println( "Register: R" );
			
			if (sign_in_flag)
				System.out.println( "Sign In: S" );
			else
				System.out.println( "Sign Out: S" );
			
			System.out.println( "View Titles: V" );
			System.out.println( "View Shpping History: C" );
			System.out.println( "End: E" );
			
			
			System.out.print( "Type your choice below-->" );
			
			BufferedReader inputReader = new BufferedReader(new InputStreamReader(System.in)) ;
			
			
			try {
				inputData = inputReader.readLine();
				}
				catch(IOException e) {
				System.out.println("Error reading keyboard input") ;
				error_flag = false;
				}
			
			
			
		 } while (!error_flag);
		 
			return inputData;
			
	}; // end main menu
	
	// Main menu - administrative user
	public String admin_menu()
	{
		boolean error_flag = true;
		
		String inputData = "";
			
		 do
		 {
			 
			error_flag = true;
			System.out.println( "Bookstore Admin Main Menu" );
			System.out.println( "*******************************************" );
			System.out.println( "Register: R" );
			
			if (sign_in_flag)
				System.out.println( "Sign In: S" );
			else
				System.out.println( "Sign Out: S" );
			
			System.out.println( "View Titles: V" );
			System.out.println( "View Shpping History: C" );
			System.out.println( "Manage Users: U" );
			System.out.println( "Manage Books: B" );
			System.out.println( "End: E" );
			
			
			System.out.print( "Type your choice below-->" );
			
			BufferedReader inputReader = new BufferedReader(new InputStreamReader(System.in)) ;
			
			
			try {
				inputData = inputReader.readLine();
				}
				catch(IOException e) {
				System.out.println("Error reading keyboard input") ;
				error_flag = false;
				}
		 } while (!error_flag);
		 
			return inputData;
		
	}
	
	// manage users
	public void manage_users()
	{
		boolean error_flag = true;
		
		String inputData = "";
			
		 do
		 {
			 
			error_flag = true;
			System.out.println( "Bookstore Admin - manage users" );
			System.out.println( "*******************************************" );
			System.out.println( "view members:V" );
			System.out.println( "Add Member: A" );
			System.out.println( "Delete Member: D" );
			System.out.println( "Back to main menu: B" );	
			System.out.print( "Type your choice below-->" );
			
			BufferedReader inputReader = new BufferedReader(new InputStreamReader(System.in)) ;
			
			
			try {
				inputData = inputReader.readLine();
				}
				catch(IOException e) {
				System.out.println("Error reading keyboard input") ;
				error_flag = false;
				}
		 } while (!error_flag);
	
		 switch (inputData)
		 {
		 case "V":
			 view_members();
			 return;
		 case "A":
			 add_member();
			 return;
		 case "D":
			 delete_member();
			 return;
		 case "B":
			 return;
		 default:
			 System.out.println("Invalid Selection.") ;
			 manage_users();
			 return;
		 }

	}
	
	
	
	public void manage_books()
	{
		
          boolean error_flag = true;
		
		String inputData = "";
			
		 do
		 {
			 
			error_flag = true;
			System.out.println( "Bookstore Admin - manage books" );
			System.out.println( "*******************************************" );
			System.out.println( "View books:V" );
			System.out.println( "Add books: A" );
			System.out.println( "Delete books: D" );
			System.out.println( "Back to main menu: B" );	
			System.out.print( "Type your choice below-->" );
			
			BufferedReader inputReader = new BufferedReader(new InputStreamReader(System.in)) ;
			
			
			try {
				inputData = inputReader.readLine();
				}
				catch(IOException e) {
				System.out.println("Error reading keyboard input") ;
				error_flag = false;
				}
		 } while (!error_flag);
	
		 switch (inputData)
		 {
		 case "V":
			 view_members();
			 return;
		 case "A":
			 add_member();
			 return;
		 case "D":
			 delete_member();
			 return;
		 case "B":
			 return;
		 default:
			 System.out.println("Invalid Selection.") ;
			 manage_users();
			 return;
		 }
		
	}
	
	//********************************************************************
	
	//***********************
	// Section 2. Viewing functions
	
	//view titles
	public static void viewtitles()
	{
		System.out.println("**************************************************");
		System.out.println("No. - Title View - Price - Author");
		System.out.println("**************************************************");
		try
		{
				String export = "select item_id,name,price,author from items; ";
			
				ResultSet result = null;
			
				Statement stmt = db.createStatement();
				if(!stmt.execute(export))
					System.out.println("Error");
				else {
					result =stmt.getResultSet();
	
					while(result.next()) {
						String res = result.getString(1);
						System.out.print(res);
						System.out.print(" - ");
						String res1 = result.getString(2);
						System.out.print(res1);
						System.out.print(" - ");
						String res2 = result.getString(3);
						System.out.print(res2);
						System.out.print(" - ");
						String res3 = result.getString(4);
						System.out.println(res3);	
					}	
				}			
				
				System.out.println("-TO buy a bookm type in: buy <book_number>,<quantity>");
				System.out.println("to return to the main menu, type in: back");
				
				BufferedReader inputReader = new BufferedReader(new InputStreamReader(System.in)) ;
				
				String inputData = "";
				
				try {
					inputData = inputReader.readLine();
					}
					catch(IOException e) {
					System.out.println("Error reading keyboard input") ;
					
					}
			 
				while (!((inputData.startsWith("buy") ) || (inputData == "back")))
				{
					System.out.println("entry invalid. please try again");
					try {
						inputData = inputReader.readLine();
						}
						catch(IOException e) {
						System.out.println("Error reading keyboard input") ;
						
						}
				}
				
				
				if (inputData.startsWith("buy")) // buy command issued 
				{
					String book_no = "0";
					String book_quant = "0";
					
					book_no=inputData.substring(5,6);
					book_quant = inputData.substring(7,8);
					
					buy(book_no,book_quant); // invoke
					
				}
				else
					return;
				
		}
		catch (SQLException ex) {
			System.out.println("SQLException: " + ex.getMessage());
		    System.out.println("SQLState: " + ex.getSQLState());
		    System.out.println("VendorError: " + ex.getErrorCode());
		}
		catch(Exception e) {
			e.printStackTrace();
		}
		
	}// end view titles
	
	public static void view_shopping_history()
	{
	
		// not logged in - reject
		if (sign_in_flag == false)
		{
			System.out.println("Please sign in before continuing.");
			return;
		}
		
		System.out.println("**************************************************");
		System.out.println("No. - Title View - Price - Author");
		System.out.println("**************************************************");
		
			try
			{
				String export = "select order_id,book_id,title,price from orders" 
						+"natural join books where member_id = '"+sign_in_id+"';"; 
				
				ResultSet result = null;
			
				Statement stmt = db.createStatement();
				if(!stmt.execute(export))
					System.out.println("Error");
				else {
					result =stmt.getResultSet();
	
					while(result.next()) {
						String res = result.getString(1);
						System.out.print(res);
						System.out.print(" - ");
						String res1 = result.getString(2);
						System.out.print(res1);
						System.out.print(" - ");
						String res2 = result.getString(3);
						System.out.print(res2);
						System.out.print(" - ");
						String res3 = result.getString(4);
						System.out.println(res3);	
					}	
				}			

			} catch (SQLException e) {
				e.printStackTrace();
			}

		
	}// end view shopping history
	
	//view books same as view titles with call back to admin menu
	public void view_books()
	{
		viewtitles();
		manage_books();
	}
	
	
	public void view_members()
	{
		System.out.println("**************************************************");
		System.out.println("Login - First Name - Last Name - Email");
		System.out.println("**************************************************");
		
			try
			{
				String export = "select member_login,first_name,last_name,email from members;"; 
				
				ResultSet result = null;
			
				Statement stmt = db.createStatement();
				if(!stmt.execute(export))
					System.out.println("Error");
				else {
					result =stmt.getResultSet();
	
					while(result.next()) {
						String res = result.getString(1);
						System.out.print(res);
						System.out.print(" - ");
						String res1 = result.getString(2);
						System.out.print(res1);
						System.out.print(" - ");
						String res2 = result.getString(3);
						System.out.print(res2);
						System.out.print(" - ");
						String res3 = result.getString(4);
						System.out.println(res3);	
					}	
				}			

			} catch (SQLException e) {
				e.printStackTrace();
			}
	
	}
	
	//***********************************************
	//***********Section 3. Access Control**********
	
	// sign in procedure
		public static void sign_in () 
		{
			String login = null;
			String password = null;
			
			System.out.println("Please sign in.");
			
			BufferedReader inputReader = new BufferedReader(new InputStreamReader(System.in)) ;
			
			try {
				System.out.print( "login-->" );
				login = inputReader.readLine();
				System.out.print( "password-->" );
				password = inputReader.readLine();
			}
			catch(IOException e) {
				System.out.println("Error reading keyboard input") ;
				
				}
			
			    String export;
			    
			    export = "SELECT member_ID,member_level FROM members"
			    		+"WHERE (member_login = '"+ login +"' AND member_password = '"+password+"'); ";		 
			    
			    Statement stmt;
				
			    ResultSet result;
			    
			    try {
					stmt = db.createStatement();
					 stmt.execute(export);
					 result = stmt.getResultSet();
					
					    if (result.getString(1) == null)
					    {
					    	System.out.println("Invalid user name or password, please retry.");
					    }
					    else
					    {
					    System.out.println("Sign in successful.");
					    sign_in_id = result.getString(1);
					    sign_in_flag = true;
					    
					       if (result.getString(2) == "2" )
					       {
					    	   admin_flag = true;
					       }
					    }
			      
			    } catch (SQLException e) {
					
			    	System.out.println("An error has been detected on your system. Please Restart.");
					e.printStackTrace();
				}
		}// end sign in
	
	public static void sign_out()
	{
		sign_in_id = "0";
		admin_flag = false;
		sign_in_flag = false;
		
	}
	
	//registration
	public static void registration()
	{

		String login = null;
		String password = null;
		String first_name = null;
		String last_name = null;
		String email = null;
		
		System.out.println( "Registration Menu" );
		System.out.println( "*******************************************" );
	
		BufferedReader inputReader = new BufferedReader(new InputStreamReader(System.in)) ;
	
		try {
			System.out.print( "login-->" );
			login = inputReader.readLine();
			System.out.print( "password-->" );
			password = inputReader.readLine();
			System.out.print("First Name-->");
			first_name = inputReader.readLine();
			System.out.print("Last Name-->");
			last_name = inputReader.readLine();
			System.out.print("Email-->");
			email = inputReader.readLine();
			
			}
			catch(IOException e) {
			System.out.println("Error reading keyboard input") ;
			
			}
            
		    String export;
		    
		    export = "insert into members (member_login,member_password,first_name,last_name,email )"
		    		+ "values (" + login + "," + password + "," + first_name + ","+ last_name + "," + email + ");" ;
		    
		    Statement stmt;
			try {
				stmt = db.createStatement();
				 stmt.execute(export);
			} catch (SQLException e) {
				System.out.println("Login ID is taken. Please choose another.");
				e.printStackTrace();
			}
			
			System.out.println("Registration sucessful");
		   
		    		
	}//end registration

	
	// same as registration, once finished, back to admim manage users
	public void add_member()
	{
		registration();
		manage_users();
		
	}
	
	public void delete_member()
	{
		System.out.println( "Delete user menu" );
		System.out.println( "*******************************************" );
	
		BufferedReader inputReader = new BufferedReader(new InputStreamReader(System.in)) ;
	
		String login = null;
		
		try {
			System.out.print( "enter login ID to delete-->" );
			login = inputReader.readLine();
		}
			catch(IOException e) {
				System.out.println("Error reading keyboard input") ;
				
				}
		
		String export;
		
		 export = "delete member_id,member_login,first_name,last_name,email from members where member_login = '"
				 + login + "';";
		 
		 Statement stmt;
			try {
				stmt = db.createStatement();
				 stmt.execute(export);
			} catch (SQLException e) {
				System.out.println("User ID did not exist;");
				e.printStackTrace();
				return;
			}
			
			System.out.println("User ID sucessfully deleted.");
			
	}
	
	//***********************************************************************
	//*************Section 4. Inventory management and transaction***********

	
	public void add_book()
	{
		String title = null;
		String author = null;
		String price = null;
		String URL = null;
		String notes = null;
		
		System.out.println( "Book add Menu" );
		System.out.println( "*******************************************" );
	
		BufferedReader inputReader = new BufferedReader(new InputStreamReader(System.in)) ;
	
		try {
			System.out.print( "title-->" );
			title = inputReader.readLine();
			System.out.print( "author-->" );
			author = inputReader.readLine();
			System.out.print("price-->");
			price = inputReader.readLine();
			System.out.print("URL-->");
			URL = inputReader.readLine();
			System.out.print("Notes-->");
			notes = inputReader.readLine();
			
			}
			catch(IOException e) {
			System.out.println("Error reading keyboard input") ;
			
			}
            
		    String export;
		    
		    export = "insert (name,author,url,price,notes ) into items  "
		    		+ "values (" + title + "," + author + "," + URL + ","+ price + "," + notes + ");" ;
		    
		    Statement stmt;
			try {
				stmt = db.createStatement();
				 stmt.execute(export);
			} catch (SQLException e) {
				System.out.println("Login ID is taken. Please choose another.");
				e.printStackTrace();
			}
			
			System.out.println("Registration sucessful");
		   
	}
	
	public void delete_book()
	{
		System.out.println( "Delete book menu" );
		System.out.println( "*******************************************" );
	
		BufferedReader inputReader = new BufferedReader(new InputStreamReader(System.in)) ;
	
		String name = null;
		
		try {
			System.out.print( "enter book name to delete-->" );
			name = inputReader.readLine();
		}
			catch(IOException e) {
				System.out.println("Error reading keyboard input") ;
				
				}
		
		String export;
		
		 export = "delete name,author,price,URL,notes from items where name = '"
				 + name + "';";
		 
		 Statement stmt;
			try {
				stmt = db.createStatement();
				 stmt.execute(export);
			} catch (SQLException e) {
				System.out.println("User ID did not exist;");
				e.printStackTrace();
				return;
			}
			
			System.out.println("User ID sucessfully deleted.");
	}
	
	
	
	public void buy(String book_no, String book_quant)
	{
		// not logged in - reject
		if (sign_in_flag == false)
		{
			System.out.println("Order rejected. Please sign in before continuing.");
			return;
		}
		
		
		String export = "insert into orders (member_id,item_id,quantity) "
				+ "values ('"+sign_in_id+"','"+book_no+"','"+book_quant+";)";
		
	
	
		try {
			Statement stmt = db.createStatement();
			stmt.execute(export);
			System.out.println("Order processed successfully");
		} catch (SQLException e) {
			System.out.println("Order rejected due to internal error.");
			e.printStackTrace();
		}
		
		return;
	}
	
}// end main class Bookstore

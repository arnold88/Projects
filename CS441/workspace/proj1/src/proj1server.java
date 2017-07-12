//Arnold Lee
//UIN: 665453451
//CS 441 Project 1
//Booking Agent Server


import java.net.*; 
import java.io.*; 

public class proj1server extends Thread
{ 
 protected static boolean serverContinue = true;
 protected Socket clientSocket;
 public int total_events;
 
 // arrays
 public static int [] event_id ;
 public static String [] event_desc;
 public static int [] space_available;
 public static int [] total_space;
 public static int counter = 0;
 public static int limit = 100;
 

 
 public static void main(String[] args) throws IOException 
   { 
    ServerSocket ManagerSocket = null;
    ServerSocket ClientSocket = null;
    String inputLineLocal;
	BufferedReader stdIn = new BufferedReader(
            new InputStreamReader(System.in));
	
	 event_id = new int[limit];
	 event_desc = new String [limit];
	 space_available = new int [limit];
	 total_space = new int [limit];
	 
	 

    InetAddress addr = InetAddress.getLocalHost();
    System.out.println(addr);
    System.out.println(addr.getHostName());
    System.out.println(addr.getHostAddress());
    
    System.out.println ("Welcome to New Age Event Reservation System");
    System.out.println ("This is the server program.");


       try { 
            ManagerSocket = new ServerSocket(31337); 
            System.out.println ("Manager Socket Created");
            ClientSocket = new ServerSocket(23888); 
            System.out.println ("Client Socket Created");
             
            try { 
                 while (true)
                    {
                	 
                	 // threads list
                	 
                     System.out.println ("Waiting for Connection");
                     new proj1server (ManagerSocket.accept()); 
                     System.out.println ("Waiting for Connection");
                     new proj1server (ClientSocket.accept()); 
                                         
                    }
                } 
            catch (IOException e) 
                { 
                 System.err.println("Accept failed."); 
                 System.exit(1); 
                } 
           } 
       catch (IOException e) 
           { 
            System.err.println("Could not listen on any port."); 
            System.exit(1); 
           } 
       finally
           {
            try {
                 ManagerSocket.close(); 
                 ClientSocket.close();
                }
            catch (IOException e)
                { 
                 System.err.println("Could not close any port."); 
                 System.exit(1); 
                } 
           }
      }

    private proj1server (Socket clientSoc)
      {
       clientSocket = clientSoc;
       start();
      }

    public void run()
      {
       System.out.println ("New Communication Thread Started");

       try { 
            PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), 
                                         true); 
            BufferedReader in = new BufferedReader( 
                    new InputStreamReader( clientSocket.getInputStream())); 

            String inputLine; 

            while ((inputLine = in.readLine()) != null) 
                { 
            	
            	 // scan input  from socket
            	 // use if-else statement
                
        
                 
                 if (inputLine.equals("view"))
                 {
                	 view();
                 }
                 else if (inputLine.equals("reserve"))
                 {
                	 reserve();
                 }
                 else if (inputLine.equals("delete"))
                 {
                	 delete();
                 }
                 else if (inputLine.equals("exit"))
                 {
                	 exit();
                 }
                 else if (inputLine.equals("add"))
                 {
                	 add();
                 }
                 else if (inputLine.equals("remove"))
                 {
                	 remove();
                 }
                 else 
                 {
                	 System.out.println ("Unknown command");
                 }

                 if (inputLine.equals("Bye.")) 
                     break; 
                } 

            out.close(); 
            in.close(); 
            clientSocket.close(); 
           } 
       catch (IOException e) 
           { 
            System.err.println("Problem with Communication Server");
            System.exit(1); 
           } 
       }
    
    public void add()
    {
    	 try {
			BufferedReader in = new BufferedReader( 
			  new InputStreamReader( clientSocket.getInputStream()));
			
			 String inputLine; 
			 
			 if ((inputLine = in.readLine()) != null) 
			 {
				 if (counter == limit)
				 {
					 System.out.println ("capacity limit reached");
					 System.exit(counter);
				 }
				 else
				 {
				     event_desc[counter] = inputLine;	 
					 	 
				 }
				 
			 }
			 
			 total_space [counter] = Integer.parseInt(in.readLine());
			 event_id[counter]=counter;
			 
			 counter = counter + 1;
			 
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
    	
   } 

    public void remove()
    {
    	try {
			BufferedReader in = new BufferedReader( 
			  new InputStreamReader( clientSocket.getInputStream()));
			
			 String inputLine; 
			 
			 if ((inputLine = in.readLine()) != null) 
			 {
				 int temp = Integer.parseInt(inputLine);
				 
				 event_id[temp]=0;
				 total_space[temp]=0;
				 space_available[temp]=0;
				 event_desc[temp]=null;
				 
			 }
	
			 
			 counter = counter - 1;
			 
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
    	
    	
    }
    
    public void exit()
    {
       System.exit(1);	
    }
    
    public void reserve()
    {
    	BufferedReader in;
		try {
			in = new BufferedReader( 
				  new InputStreamReader( clientSocket.getInputStream()));
		
  			
  			 String inputLine; 
    	
    	if ((inputLine = in.readLine()) != null) 
		 {
    		int temp = Integer.parseInt(inputLine);
    		space_available[temp]--; 
		
		 }
    	
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    }
   
    public void view()
    {
    	for (int i = 1;i < counter ; i++)
    	{
    		 System.out.println(event_id[i]);
    		 
    		 System.out.println(event_desc[i]);
    		 System.out.println(space_available[i]);
    		 
    		 System.out.println(total_space[i]);
    		 
    	}
    }
    
    public void delete()
    {
    	BufferedReader in;
		try {
			in = new BufferedReader( 
				  new InputStreamReader( clientSocket.getInputStream()));
		
  			
  			 String inputLine; 
    	
    	if ((inputLine = in.readLine()) != null) 
		 {
    		int temp = Integer.parseInt(inputLine);
    		space_available[temp]++; 
		
		 }
    	
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    }
}
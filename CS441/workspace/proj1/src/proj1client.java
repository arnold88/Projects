//Arnold Lee
//UIN: 665453451
//CS 441 Project 1
//Booking Agent Client



import java.io.*;
import java.net.*;

public class proj1client {
    public static void main(String[] args) throws IOException {

        Socket clientSocket = null;
        PrintWriter out = null;
        BufferedReader in = null;
        String serverName = null;

        if (args.length == 0)
           serverName = "127.0.0.1";
        else
           serverName = args[0];

        try {
       
            clientSocket = new Socket(serverName, 23888); //(port #:31337)
            out = new PrintWriter(clientSocket.getOutputStream(), true);
            in = new BufferedReader(new InputStreamReader(
                                        clientSocket.getInputStream()));
        } catch (UnknownHostException e) {
            System.err.println("Host not found!");
            System.exit(1);
        } catch (IOException e) {
            System.err.println("There seems to be a I/O "
                               + "issue to the host.");
            System.exit(1);
        }

	BufferedReader stdIn = new BufferedReader(
                                   new InputStreamReader(System.in));
	String userInput;

       
	while ((userInput = stdIn.readLine()) != null) 
           {
	    out.println(userInput);

            // end loop
            if (userInput.equals("Bye."))
                break;

	   
	   }

	out.close();
	in.close();
	stdIn.close();
	clientSocket.close();
	
	
    }
}



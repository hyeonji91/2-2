package ex3_Chat;
import java.io.*;
import java.net.*;
import java.util.Scanner;

public class ChatServer {
    public static void main(String[] arg) {
        BufferedReader inFromClient = null;
        Scanner sc = null;
        BufferedWriter outToClient = null;
        ServerSocket listener = null;
        Socket socket = null;

        String serverText;
        String clientText;
        int num = 1;

        try {
            while(true) {
                listener = new ServerSocket(8888);
                System.out.println("Start Server...");
                System.out.println("Waiting for clients");


                socket = listener.accept();

                System.out.println("#"+num+"A new connection has been established!");
                inFromClient = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                sc = new Scanner(System.in);
                outToClient = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));

                while (true) {
                    clientText = inFromClient.readLine();
                    if (clientText.equalsIgnoreCase("bye")) {
                        System.out.println("Bye");
                        break;
                    }
                    System.out.println(clientText);
                    serverText = sc.nextLine();
                    outToClient.write("Server> " + serverText + "\n");
                    outToClient.flush();
                }
                num++;
            }
        }catch(IOException e) {
            System.out.println(e.getMessage());
        } finally{
            try{
                socket.close();
                listener.close();
            }catch(IOException e){
                System.out.println("Disconnected");
            }
        }



    }
}

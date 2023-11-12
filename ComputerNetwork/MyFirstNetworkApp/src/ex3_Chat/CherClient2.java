package ex3_Chat;

import java.io.*;
import java.net.Socket;
import java.util.Scanner;

public class CherClient2 {
    public static void main(String[] arg) throws IOException{
        BufferedReader inFromServer = null;
        BufferedWriter outToServer = null;
        Socket socket = null;
        Scanner sc = null;
        String serverText;
        String clientText;


        try {
            socket = new Socket("localhost", 8888);
            sc = new Scanner(System.in);
                    //new BufferedReader(new InputStreamReader(System.in));
            outToServer = new BufferedWriter(
                    new OutputStreamWriter(socket.getOutputStream()));
            inFromServer = new BufferedReader(
                    new InputStreamReader(socket.getInputStream()));

            while(true) {
                clientText = sc.nextLine();
                outToServer.write("Client> "+clientText+"\n");
                outToServer.flush();
                if (clientText.equalsIgnoreCase("bye")) {
                    break;
                }
                serverText = inFromServer.readLine();
                System.out.println(serverText);

            }
        }catch(IOException e){
            System.out.println(e.getMessage());
        }finally{
            try{
                socket.close();
            }catch (IOException e){
                System.out.println("Disconnected");
            }
        }
    }
}

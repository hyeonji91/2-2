package ex2_DateServer;
import java.net.*;
import java.io.*;
import java.util.Date;

public class DateServer {
    public static void main(String[] arg) throws IOException{
        ServerSocket listener = new ServerSocket(59090);
        System.out.println("The date server is running...");
        while(true){
            try(Socket socket = listener.accept()){
                PrintWriter out= new PrintWriter(socket.getOutputStream(), true);
                out.println(new Date().toString());
            }
        }
    }
}

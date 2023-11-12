package ex2_DateServer;

import java.io.*;
import java.net.*;
import java.util.Scanner;

public class DateClient {
    public static void main(String[] arg) throws IOException{
        Socket socket = new Socket("127.0.0.1", 59090);
        //Scanner in = new Scanner(socket.getInputStream());
        //System.out.println("Server response: " + in.nextLine());

        //Scanner 대신
        BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        System.out.println("Server response: " + in.readLine());
    }
}

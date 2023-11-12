package ex4_calculate;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class CalcClient {
    public static void main(String[] arg){
        BufferedReader in = null;
        BufferedWriter out = null;
        Socket socket = null;
        Scanner sc = null;
        String clientText;
        String serverText;

        try{
            socket = new Socket("127.0.0.1", 9999);

            in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
            sc = new Scanner(System.in);

            while(true) {
                System.out.print("계산식 >> ");
                clientText = sc.nextLine();
                out.write(clientText + "\n");
                out.flush();
                if(clientText.equalsIgnoreCase("bye"))
                    break;
                System.out.println("계산결과 : " + in.readLine());
            }
        } catch(IOException e){
            System.out.println(e.getMessage());
        } finally{
            try {
                sc.close();
                if (socket != null)
                    socket.close();
            }catch(IOException e) {
                System.out.println("서버와의 채팅 주 오류가 발생했습니다.");
            }
        }
    }
}

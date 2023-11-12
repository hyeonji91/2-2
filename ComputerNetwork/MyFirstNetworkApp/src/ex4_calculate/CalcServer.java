package ex4_calculate;

import java.util.*;
import java.io.*;
import java.net.*;
public class CalcServer {
    public static String calc(String exp){
        StringTokenizer st = new StringTokenizer(exp, " ");
        if(st.countTokens() != 3)
            return "error";
        String res = "";
        int op1 = Integer.parseInt(st.nextToken());
        String opcode = st.nextToken();
        int op2 = Integer.parseInt(st.nextToken());
        switch(opcode){
            case "+":
                res = Integer.toString(op1 + op2);
                break;
            case "-":
                res = Integer.toString(op1-op2);
                break;
            case "*":
                res = Integer.toString(op1*op2);
                break;
            default:
                res = "error";
        }
        return res;
    }

    public static void main (String[] arg){
        BufferedReader in = null;
        BufferedWriter out = null;
        ServerSocket listener = null;
        Socket socket = null;
        String ClientText;
        String ServerText;

        try{
            listener = new ServerSocket(9999);
            System.out.println("연결을 기다리고 있습니다......");

            socket = listener.accept();

            System.out.println("연결되었습니다.");
            in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));

            while(true) {
                ClientText = in.readLine();
                if(ClientText.equalsIgnoreCase("bye")){
                    System.out.println("클라이언트에서 연결을 종료했습니다");
                    break;
                }
                System.out.println(ClientText);

                out.write(calc(ClientText)+"\n");
                out.flush();
            }
        } catch(IOException e){
            System.out.println(e.getMessage());
        } finally{
            try {
                if(listener!=null)
                    listener.close();
                if(socket != null)
                    socket.close();
            } catch(IOException e){
                System.out.println("클라이언트와 채팅 중 오류가 발생했습니다.");
            }
        }
    }
}

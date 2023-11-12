import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.*;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

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
            case "/":
                if(op2 == 0)
                    res = "error";
                else
                    res = Double.toString((double) op1 /op2);
            default:
                res = "error";
        }
        return res;
    }

    public static void main (String[] arg) throws IOException{

        ServerSocket listener = new ServerSocket(9999);
        System.out.println("연결을 기다리고 있습니다......");
        ExecutorService pool = Executors.newFixedThreadPool(20);
        while(true) {
            Socket socket = listener.accept();
            pool.execute(new CalcThread(socket));
        }
    }

    private static class CalcThread implements Runnable{
        private Socket socket;

        CalcThread(Socket socket){
            this.socket = socket;
        }

        @Override
        public void run(){
            System.out.println("Connected: "+ socket);

            BufferedReader in = null;
            BufferedWriter out = null;
            String ClientText;
            String ServerText;

            try{
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
                System.out.println("Error : "+ socket);
            } finally{
                try {

                    if(socket != null)
                        socket.close();
                } catch(IOException e){
                    System.out.println("Closed : "+socket);
                }
            }
        }
    }
}

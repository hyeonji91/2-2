import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.*;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/*
[PROTOCOL] server to client
#1 ERROR
[400] format error
[401] not number
[402] divided by ZERO
[403] not operator
 */

public class CalcServer {
    public static class ReturnValue{
        public String success = "s"; //s:success, e:error
        public Integer errorCode;
        public Double result;
    }
    public static ReturnValue calc(String exp){//계산하기
        ReturnValue returnValue = new ReturnValue();
        double result = 0;
        StringTokenizer st = new StringTokenizer(exp, " ");//나누기
        //3개가 아니면 포맷에러
        if(st.countTokens() != 3){
            returnValue.success = "e";
            returnValue.errorCode = 400;
            return returnValue;
        }

        String opcode = st.nextToken().toLowerCase();
        double op1 = 0, op2 = 0;
        try{
            op1 = Double.parseDouble(st.nextToken());
            op2 = Double.parseDouble(st.nextToken());
        }catch(NumberFormatException e){//double이 아니면 not number 에러
            returnValue.success = "e";
            returnValue.errorCode = 401;
        }
        //계산하기
        switch(opcode){
            case "add":
                result = op1 + op2;
                returnValue.result = result;
                break;
            case "sub":
                result = op1-op2;
                returnValue.result = result;
                break;
            case "mul":
                result = op1*op2;
                returnValue.result = result;
                break;
            case "div":
                if(op2 == 0){//divided by zero 에러
                    returnValue.success = "e";
                    returnValue.errorCode = 402;
                }
                else{
                    result = op1 /op2;
                    returnValue.result = result;
                }
                break;
            default://not operator 에러
                returnValue.success = "e";
                returnValue.errorCode = 403;
        }
        //System.out.println(returnValue.success + returnValue.errorCode + returnValue.result);
        return returnValue;
    }

    public static void main (String[] arg) throws IOException{

        ServerSocket listener = new ServerSocket(9999);
        System.out.println("연결을 기다리고 있습니다......");
        ExecutorService pool = Executors.newFixedThreadPool(20);
        while(true) {
            Socket socket = listener.accept();//포트 열어두고 연결을 기다리다가 요청오면 소캣 생성
            pool.execute(new CalcThread(socket));//스레드만들기
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

            Scanner in = null;
            PrintWriter out = null;
            String ClientText;
            String ServerText;

            try{
                in = new Scanner(socket.getInputStream());
                out = new PrintWriter(socket.getOutputStream());

                while(true) {
                    //from client
                    ClientText = in.nextLine();
                    if(ClientText.equalsIgnoreCase("q")){
                        System.out.println("클라이언트에서 연결을 종료했습니다");
                        break;
                    }
                    //계산하기
                    System.out.println(ClientText);
                    ReturnValue returnValue = calc(ClientText);
                    //server to client
                    out.println(returnValue.success +"\n");//성공인지 에러인지 반환
                    if(returnValue.success.equals("s")) {//성공이면 계산 값 반환
                        out.println(returnValue.result.toString());
                        out.flush();
                        System.out.println("s: " +returnValue.result);
                    }
                    else {//실패면 에러코드 반환
                        out.println(returnValue.errorCode.toString());
                        out.flush();
                        System.out.println("e: " + returnValue.errorCode);
                    }
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

    public static void closeConnect(Socket socket){
        try {
            if(socket != null)
                socket.close();
        } catch(IOException e){
            System.out.println("Closed : "+socket);
        }
    }
}

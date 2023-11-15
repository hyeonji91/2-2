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
[402] not operator
[403] divided by ZERO
 */

public class CalcServer {
    public static class ReturnValue{//연산한 값을 담을 클래스
        public String success = "s"; //s:success, e:error
        public Integer errorCode;
        public double result;
    }
    public static ReturnValue calc(String exp){//계산하기
        ReturnValue returnValue = new ReturnValue();
        double result = 0.0;
        StringTokenizer st = new StringTokenizer(exp, " ");//나누는 기준 설정
        //요소가 3개가 아니면 포맷 에러
        if(st.countTokens() != 3){
            returnValue.success = "e";
            returnValue.errorCode = 400;
            return returnValue;
        }
        //입력값 넣기
        String opcode = st.nextToken().toLowerCase();
        double op1 = 0.0, op2 = 0.0;
        try{
            op1 = Double.parseDouble(st.nextToken());
            op2 = Double.parseDouble(st.nextToken());
        }catch(NumberFormatException e){//double이 아니면 not number 에러
            returnValue.success = "e";
            returnValue.errorCode = 401;
            return returnValue;
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
                    returnValue.errorCode = 403;
                }
                else{
                    result = op1 /op2;
                    returnValue.result = result;
                }
                break;
            default://not operator 에러
                returnValue.success = "e";
                returnValue.errorCode = 402;
        }
        //System.out.println(returnValue.success + returnValue.errorCode + returnValue.result);
        return returnValue;
    }

    private static ServerSocket listener =null;
    public static void main (String[] arg) throws IOException{

        listener = new ServerSocket(9999);
        System.out.println("연결을 기다리고 있습니다......");
        ExecutorService pool = Executors.newFixedThreadPool(20);
        while(true) {
            Socket socket = listener.accept();//포트 열어두고 연결을 기다리다가 요청오면 소캣 생성
            pool.execute(new CalcThread(socket));//스레드만들기
        }
    }

    private static class CalcThread implements Runnable{
        private Socket socket;
        private Scanner in = null;
        private PrintWriter out = null;
        private String fromClientText;

        CalcThread(Socket socket){
            this.socket = socket;
        }

        @Override
        public void run(){
            System.out.println("Connected: "+ socket);

            try{
                in = new Scanner(socket.getInputStream());
                out = new PrintWriter(socket.getOutputStream());

                while(true) {
                    //from client
                    fromClientText = in.nextLine();
                    if(fromClientText.equalsIgnoreCase("q")){//만약 client에서 q입력했다면 스레드 종료
                        System.out.println("클라이언트에서 연결을 종료했습니다");
                        break;
                    }
                    //계산하기
                    //System.out.println(ClientText);
                    ReturnValue returnValue = calc(fromClientText);

                    //server to client
                    out.println(returnValue.success);//성공인지 에러인지 반환
                    if(returnValue.success.equals("s")) {//성공이면 계산 값 반환
                        out.println(returnValue.result);
                        out.flush();
                        System.out.println("[SUCCESS] " +fromClientText +" : "+ returnValue.result);
                    }
                    else {//실패면 에러코드 반환
                        out.println(returnValue.errorCode);
                        out.flush();
                        System.out.println("[Error] " + returnValue.errorCode+" : "+fromClientText);
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

}

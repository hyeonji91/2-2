import java.io.*;
import java.net.Socket;
import java.util.Scanner;

/*
[PROTOCOL] Client to Server
#1 CALCULATE
[operator] [first number] [second number]
- operator : add, sub, mul, div (not case-sensitive)
#2 EXIT
if you want exit program, enter q (not case-sensitive)
 */

public class CalcClient {
    public static void main(String[] arg){
        BufferedReader br = null;
        String fileName = "serverInfo.dat";
        Scanner in = null;
        PrintWriter out = null;
        Socket socket = null;
        Scanner sc = null;
        String clientText;
        String serverText;

        String IP = "";
        int portNum = 0;

        //IP address, port number 파일에서 입력받기
        try {
            br = new BufferedReader(new FileReader(fileName));
            IP = br.readLine();
            portNum = Integer.parseInt(br.readLine());
            System.out.println(IP + " " + portNum);
            br.close();
        }catch (IOException e) {
            System.out.println("Can not open file " +fileName + ". Set IP address and port number default");
            IP = "127.0.0.1";
            portNum = 9999;
        }

        try{
            socket = new Socket(IP, portNum);

            in = new Scanner(socket.getInputStream());
            out = new PrintWriter(socket.getOutputStream(), true);
            sc = new Scanner(System.in);

            System.out.println("===========[Calculator in the Cloud]==============================");
            System.out.println("FORMAT : [operator] [first number] [second number]");
            System.out.println("- operator : add, sub, mul, div (not case-sensitive)");
            System.out.println("if you want exit program, enter 'q' (not case-sensitive)");
            System.out.println("==================================================================");
            while(true) {
                //client to server
                System.out.print("계산식 >> ");
                clientText = sc.nextLine();
                out.println(clientText);
                if(clientText.equalsIgnoreCase("q"))
                    break;

                //from server
                String success = in.nextLine(); //성공:s 실패:e
                if(success.equals("s")){//Success
                    System.out.print("[SUCCESS] ");
                    String msg = in.nextLine();
                    System.out.println("msg: "+msg);
                }
                else{//Error
                    System.out.print("[ERROR]");
                    String msg = in.nextLine();
                    System.out.println("msg: "+msg);
                    //Integer errorCode = Integer.parseInt(in.nextLine());
                    printErrorMsg(Integer.parseInt(msg));
                }
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

    public static void printErrorMsg(int errorCode){
        /*
        [PROTOCOL] server to client
        #1 ERROR
        [400] format error
        [401] not number
        [402] divided by ZERO
        [403] not operator
         */
        switch(errorCode){
            case 400:
                System.out.println("Format error");
                System.out.println("Please enter it in this format : [operator] [first number] [second number]");
                break;
            case 401:
                System.out.println("Not number");
                System.out.println("The second and third values must be number");
                break;
            case 402:
                System.out.println("Divided by ZERO");
                System.out.println("Cannot be divided by ZERO");
                break;
            case 403:
                System.out.println("Not operator");
                System.out.println("The first value is must be operator");
                System.out.println("You can only use this operators : add, sub, mul, div (not case-sensitive)");
                break;
            default:
                System.out.println("error");
                break;
        }
    }
}

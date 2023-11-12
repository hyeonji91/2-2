import java.io.*;
import java.net.*;

public class TCPClient1 {
    public static void main(String argv[]) throws Exception{
        String sentence;
        String modifiedSentence;
        String serverIP = "127.0.0.1";
        int nPort = 6789;
        BufferedReader inFromUser = new BufferedReader(
                new InputStreamReader(System.in));

        Socket clientSocket = new Socket(serverIP, nPort);//클라이언트 소켓 생성,
        // socket 객체가 생성되면 serverIP주소로 자동 접속
        //네트워크 입출력 스트림 생성
        DataOutputStream outToServer = new DataOutputStream(clientSocket.getOutputStream());
        BufferedReader inFromServer = new BufferedReader(
                new InputStreamReader(clientSocket.getInputStream()));

        sentence = inFromUser.readLine();

        outToServer.writeBytes(sentence + '\n');
        modifiedSentence = inFromServer.readLine();
        System.out.println("FROM SERVER: "+modifiedSentence);

        clientSocket.close();//연결 끊기


    }
}

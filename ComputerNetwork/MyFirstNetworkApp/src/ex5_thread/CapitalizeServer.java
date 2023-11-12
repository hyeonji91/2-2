package ex5_thread;
import java.io.*;
import java.net.*;
import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class CapitalizeServer {
    public static void main(String[] arg) throws IOException{
        ServerSocket listener = new ServerSocket(7777);
        System.out.println("The capitalization server is running...");
        ExecutorService pool = Executors.newFixedThreadPool(20);
        while(true){
            Socket socket = listener.accept();
            pool.execute(new Capitalizer(socket));
        }
    }

    private static class Capitalizer implements Runnable{
        private Socket socket;

        Capitalizer(Socket socket){
            this.socket = socket;
        }
        @Override
        public void run(){
            System.out.println("Connected: "+ socket);
            try{
                Scanner in = new Scanner(socket.getInputStream());
                PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
                while(in.hasNextLine()){
                    String clientText = in.nextLine();
                    System.out.println("Client>"+clientText);
                    out.println(clientText.toUpperCase());
                }
            }catch(IOException e){
                System.out.println("Error : "+ socket);
            }finally {
                try{
                    socket.close();
                }catch(IOException e){;
                }
                System.out.println("Closed : "+socket);
            }
        }
    }
}

package MonoClient;

import java.net.*;
import java.util.Scanner;

public class Client {

    public static void main(String []args) {
        try {
            DatagramSocket s = new DatagramSocket();
            String serverAdress = "127.0.0.1";
            InetSocketAddress serverSockAdress = new InetSocketAddress(serverAdress,5678);
            long responseTime = 0;
            int correctNum = 0;
            int errorNum = 0;
            Scanner userInput = new Scanner(System.in);
            String input;
            String[] tokens;
            byte numbers[] = new byte[100];

            /* String splitting and string to int conversion */
            System.out.println("Please enter the sum you want the server to calculate :\n"); //Expecting user input
            input = userInput.nextLine();
            tokens = input.split("\\+");

            // String to int conversion
            for (int i = 0; i < tokens.length; i++) {
                numbers[i] = (byte) Integer.parseInt(tokens[i].trim());
                System.out.println(numbers[i]);
            }

            DatagramPacket numbersToSend = new DatagramPacket(numbers,numbers.length,serverSockAdress);

            byte []result = new byte[1]; //Byte array for incoming message from server
            DatagramPacket paqRecu = new DatagramPacket(result,result.length); //New packet for server message
            s.setSoTimeout(2000);
            s.send(numbersToSend);  //sending numbers to sum to server

            try {
                s.receive(paqRecu); //Expecting the sum result
                System.out.println(paqRecu.getData().toString());
                byte sumResultAsByte[] = paqRecu.getData();
                int sumResult = Byte.toUnsignedInt(sumResultAsByte[0]);  //Conversion de la somme en entier
                System.out.println("Le résultat de la somme est :" + sumResult);

            } catch (SocketTimeoutException|PortUnreachableException e) {
                System.out.println("timeout exception");
            }


        } catch(Exception ex) {
            ex.printStackTrace();
            System.exit(1);
        }
    }
}

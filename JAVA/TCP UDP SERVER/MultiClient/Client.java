package MultiClient;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.*;
import java.util.Arrays;
import java.util.Scanner;

public class Client {

    public static void main(String []args) {
        try {
            int port = 4446;
            DatagramSocket s = new DatagramSocket();
            MulticastSocket multiCastReceive = new MulticastSocket(port);
            String serverAdress = "230.0.0.1";
            InetSocketAddress serverSockAdress = new InetSocketAddress(serverAdress,4446);

            Scanner userInput = new Scanner(System.in);
            String input = new String("");
            String[] tokens;
            byte numbers[] = new byte[Long.BYTES];
            long enteredNumber = 0, sumResult = 0;
            boolean stop = true;
            /* String splitting and string to int conversion */
            System.out.println("Please enter the sum you want the server to calculate.\n" +
                    " Inscribe a number and press enter to add a value to the sum. \n" +
                    "To compute the sum, insert 0 and press enter.\n"); //Expecting user input


            do{
                enteredNumber = Long.valueOf(userInput.nextLine());
                numbers = ByteUtils.longToBytes(enteredNumber);
                DatagramPacket numbersToSend = new DatagramPacket(numbers,numbers.length,serverSockAdress);
//                s.setSoTimeout(2000);
                s.send(numbersToSend);  //sending numbers to sum to server

                if(input == "0") //Stop the loop if user inscribed "0"
                    stop = false;

            }while(stop == true);

            byte []result = new byte[100]; //Byte array for incoming long message from server
            DatagramPacket paqRecu = new DatagramPacket(result,result.length); //New packet for server message

            try {
                multiCastReceive.joinGroup(InetAddress.getByName(serverAdress));
                multiCastReceive.receive(paqRecu); //Expecting the sum result
                System.out.println("Received data from: " +
                        paqRecu.getAddress().toString() +
                        ":" + paqRecu.getPort() + " with length: " +
                        paqRecu.getLength()); //DEBUG
                byte sumResultAsByte[] = paqRecu.getData();
                sumResult = ByteUtils.bytesToLong(sumResultAsByte);
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


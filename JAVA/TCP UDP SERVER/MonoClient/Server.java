package MonoClient;

import java.net.DatagramPacket;
import java.net.DatagramSocket;

public class Server {
    public static void main(String []args) {
        int numbers[] = new int[100];
        int result = 0;
        byte resultAsByte[] = new byte[1];

        try {
            System.out.println("MultiClient.Server is up and running");

            // Declaring a new UDP Socket based on port 5678
            DatagramSocket s = new DatagramSocket(5678);
            // Byte array containing data received from client
            byte []data = new byte[100];
            // Datagram Packet for client
            DatagramPacket paqRecu = new DatagramPacket(data,data.length);

            while (true) {

                s.receive(paqRecu); // Expecting to receive a packet from connected socket
                byte numbersAsByte[] = paqRecu.getData();

                //Byte to int conversion
                for(int i = 0 ; i < numbersAsByte.length ; i++) {
                    numbers[i] = Byte.toUnsignedInt(numbersAsByte[i]);
                    System.out.println("J'ai reçu [" + numbers[i] + "] depuis la machine " +
                            paqRecu.getAddress().getCanonicalHostName() + " via le port " +
                            paqRecu.getPort());
                    result += numbers[i];
                }
                resultAsByte[0] = (byte)result;

                System.out.println("Le resultat de la somme est : "+ result +
                        " Le résultat de la somme en byte est : " + resultAsByte.toString());
                
                DatagramPacket resultOfSum = new DatagramPacket(resultAsByte, resultAsByte.length,paqRecu.getSocketAddress());
                s.send(resultOfSum);
                result = 0;
            }
        } catch(Exception ex) {
            ex.printStackTrace();
            System.exit(1);
        }
    }
}
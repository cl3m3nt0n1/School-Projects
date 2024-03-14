package MultiClient;

import java.io.IOException;
import java.net.*;

public class Server {
    public static void main(String []args){

            System.out.println("MultiClient.Server is up and running");
            while(true){
                MulticastReceiver receiver = new MulticastReceiver();
                receiver.run();
            }

    }
}

/*
* This class allows server to deal with multicast.
* Using this class let the server send and receive
* datas from various clients.
*/
class MulticastReceiver extends Thread {
    int port = 4446;  // UDP Port
    protected MulticastSocket socket = null;
    protected MulticastSocket socketEmit = null;
    protected byte[] buf = new byte[Long.BYTES];
    long result = 0;
    long receivedNumber = 0;
    long receivedNumbers[] = new long[20];
    int numberOfNumbersReceived = 0;
    long sumResult = 0;
    byte[] receivedDataAsByte = new byte[8];



    public void run() {
        try {
            socket = new MulticastSocket(port);
            socketEmit = new MulticastSocket();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        InetAddress group = null; //Multicast group to subscribe to

        try {
            group = InetAddress.getByName("230.0.0.1"); // Suitable address for multicasting
        } catch (UnknownHostException e) {
            throw new RuntimeException(e);
        }

        try {
            socket.joinGroup(group); //Subscribing to the new group

        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        while (true) {
            //New DatagramPacket to communicate with client associated with dedicated thread
            DatagramPacket packet = new DatagramPacket(buf, buf.length);
            try {
                socket.receive(packet); // Receiving packet
                System.out.println("Received data from: " + packet.getAddress().toString() +
                        ":" + packet.getPort() + " with length: " + packet.getLength()); //DEBUG
            } catch (IOException e) {
                throw new RuntimeException(e);
            }

            //Transforming byte[] to long
            receivedNumber = ByteUtils.bytesToLong(packet.getData());

            // Keeping received datas inside long[]
            receivedNumbers[numberOfNumbersReceived] = receivedNumber;
            numberOfNumbersReceived++;

            if(receivedNumber == 0) //Stopping sum
                break;
        }
        //Computing the sum
        for(int i = 0 ; i < receivedNumbers.length ; i ++)
            sumResult += receivedNumbers[i];

        //Returning datas
        byte[] sumResultToSend = new byte[8];
        sumResultToSend = ByteUtils.longToBytes(sumResult);
        DatagramPacket sumResultPacket = new DatagramPacket(sumResultToSend, sumResultToSend.length,group,port);

        try {
            socketEmit.send(sumResultPacket, (byte)2) /*TTL*/; //Sending datas
            System.out.println("Sent result to port : " + socketEmit.getPort());
            sumResult = 0;
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        try {
            socket.leaveGroup(group); //Leave subscribed group
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        socket.close();  //Closing connection to socket
    }
}


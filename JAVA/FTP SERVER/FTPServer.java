import java.io.*;
import java.net.*;

class FTPServer {

    /* Même principe que précédemment
    * En Multiclient et avec gestion de fichiers */

    ServerSocket server = null;
    Socket client = null;
    private final static int PORT = 65534;


    public static void main(String[] arg) {
        FTPServer serv = new FTPServer();
        serv.Connect();
    }
    public void Connect() {
        try {
            server = new ServerSocket(PORT);
            System.out.println("Le serveur est pret...");
            while(true) {
                /* Accepter une nouvelle connexion client */
                client = server.accept();

                /* Génération d'un Thread Dédié au nouveau client */
                System.out.println("Un client vient d'apparaitre");
                ClientThread cli = new ClientThread(client);
                cli.start();
                if (!cli.isAlive())
                    System.out.println("Le client est parti\n");
            }

        }
        catch(Exception e) {}
    }
}

class ClientThread extends Thread {

    private static final String SRVPATH = "SERVER_DIR";
    private static final String CLIPATH = "CLIENT_DIR";
    /* Socket Client */
    public Socket client = null;

    /* Flux d'entrées/Sorties de données */
    public DataInputStream dataIn = null;
    public DataOutputStream dataOut = null;

    /* Flux d'entrées/Sorties de Fichier (partie FTP) */
    public FileInputStream fileIn = null;
    public FileOutputStream fileOut = null;
    public File file = null;

    /* Lire depuis le clavier */
    public BufferedReader input = null;
    public String inputFromUser = "";

    public ClientThread(Socket client) {
        try {
            this.client = client;  //socket passé depuis la méthode main.
            dataIn =new DataInputStream(client.getInputStream());
            dataOut = new DataOutputStream(client.getOutputStream());
        }
        catch(Exception e) {}
    }
    public void run() {

        while(true) {
            /* Faire indéfiniment... */
            try {
                String input = dataIn.readUTF();
                String filename = "",filedata ="";
                byte[] data;
                if(input.equals("GET_FILE")) {
                    filename = dataIn.readUTF();
                    file = new File(SRVPATH +"/" + filename);

                    /* Gestion d'erreurs */
                    if(file.isFile()) {
                        fileIn = new FileInputStream(file);
                        data = new byte[fileIn.available()];
                        fileIn.read(data);
                        filedata = new String(data);
                        fileIn.close();
                        dataOut.writeUTF(filedata);
                    }
                    else {
                        dataOut.writeUTF("");
                    }
                }
                else if(input.equals("PUT_FILE")) {
                    filename = SRVPATH + "/" + dataIn.readUTF();
                    filedata = dataIn.readUTF();
                    fileOut = new FileOutputStream(filename);
                    fileOut.write(filedata.getBytes());
                    fileOut.close();
                }
                else if(input.equals("LS_DIR")) {

                }
                else {
                    System.out.println("Error at Server");
                }
            }
            catch(Exception e) {}
        }
    }
}
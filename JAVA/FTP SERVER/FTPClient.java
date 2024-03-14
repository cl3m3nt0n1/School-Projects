import java.io.*;
import java.net.*;

public class FTPClient {

    /* Répertoire des fichiers serveurs */
    private static final String PATH = "SERVER_DIR";

    /* Socket Client */
    public Socket client = null;

    /* Flux d'entrées/Sorties de données */
    public DataInputStream dataIn = null;
    public DataOutputStream dataOut = null;

    /* Flux d'entrées/Sorties de Fichier (partie FTP) */
    public FileInputStream fileIn = null;
    public FileOutputStream fileOut = null;

    /* Lire depuis le clavier */
    public BufferedReader reader = null;
    public String userInput = "";

    /* Port de connexion*/
    private final static int PORT = 65534;

    public static void main(String[] args) {
        FTPClient client = new FTPClient();
        client.connectToServer();
    }

    public void connectToServer() {
        try {
            client = new Socket("localhost",PORT);

            InputStreamReader reader = new InputStreamReader(System.in);
            this.reader = new BufferedReader(reader);
            dataIn = new DataInputStream(client.getInputStream());
            dataOut = new DataOutputStream(client.getOutputStream());


        }
        catch(Exception e) {
            System.out.println("Impossible de se connecter au serveur !");
            System.exit(1);
        }

        while(true) {
            try {
                System.out.println("Que puis-je faire pour vous ?");
                userInput = reader.readLine();
                int whatToDo = 0;

                /* Pour gérer les différentes requêtes du client,
                *  on se sert d'un switch qui permettra de gérer plus facilement
                *  tous les différents cas d'utilisation.*/

                if (userInput.equals("LS")) {
                    whatToDo = 0;
                }
                else if (userInput.equals("GET")) {
                    whatToDo = 1;
                }
                else if (userInput.equals("PUT")) {
                    whatToDo = 2;
                }
                else if(userInput.equals("help")|userInput.equals("HELP"))
                    whatToDo = 3;


                switch(whatToDo) {
                    case 0: ls(); break; //Lister les fichiers du serveur
                    case 1: get(); break; //Récupérer un fichier depuis serveur
                    case 2: put(); break; //Envoyer un fichier au serveur
                    case 3: { //Help
                        System.out.println("Commandes:\nLS: Lister les fichier\n" +
                                "GET: Recuperer un fichier depuis le serveur\n" +
                                "PUT: Envoyer un fichier au serveur\n");
                        break;
                    }
                    default: System.out.println("Tapez HELP pour obtenir de l'aide\n");
                }
            }
            catch(Exception e)
            {
                System.out.println("Error : Something happened inside the Switch");
            }
        }
    }

    /* Liste les fichiers actuellement présents sur le serveur */
    public void ls() {
        File dir  = new File(PATH);
        File[] liste = dir.listFiles();

        /* Boucle ForEach pour lister les fichiers */
        for(File item : liste){
            if(item.isFile())
            {
                System.out.format("Nom du fichier: %s%n", item.getName());
            }
            else if(item.isDirectory())
            {
                System.out.format("Nom du répertoire: %s%n", item.getName());
            }
        }
    }


    public void get() {
        try {
            String filename="",filedata="";
            System.out.println("Entrez le nom du fichier : ");
            filename = reader.readLine();
            dataOut.writeUTF("GET_FILE");
            dataOut.writeUTF(filename);
            filedata = dataIn.readUTF();
            if(filedata.equals(""))
            {
                System.out.println("Pas de fichier !");
            }
            else
            {
                fileOut = new FileOutputStream("CLIENT_DIR/" + filename);
                fileOut.write(filedata.getBytes());
                fileOut.close();
                System.out.println("Fichier recupere !");
            }
        }
        catch(Exception e)
        {
        }
    }

    public void put() {
        try{
            String filename="",filedata="";
            File file;
            byte[] data;
            System.out.println("Entrez le nom du fichier : ");
            filename = reader.readLine();
            file = new File("CLIENT_DIR/" + filename);
            if(file.isFile())
            {
                fileIn = new FileInputStream(file);
                data = new byte[fileIn.available()];
                fileIn.read(data);
                fileIn.close();
                filedata = new String(data);
                dataOut.writeUTF("PUT_FILE");
                dataOut.writeUTF(filename);
                dataOut.writeUTF(filedata);
                System.out.println("Fichier envoye !");
            }
            else
            {
                System.out.println("Pas de fichier !");
            }
        }
        catch(Exception e) {}
    }
}
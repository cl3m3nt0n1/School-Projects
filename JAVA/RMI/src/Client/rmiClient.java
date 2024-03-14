package Client;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Scanner;

import Common.XmlOperationsI;

public class rmiClient {

	static String text;
	static Scanner sc = new Scanner(System.in);

	public static void main(String[] args) {
		try {
			Registry reg = LocateRegistry.getRegistry("localhost", 1099);
			XmlOperationsI xmlOD = (XmlOperationsI) reg.lookup("xmlOP");
			System.out.println("OD=" + xmlOD);
			System.out.println(xmlOD.addUser("michel","forever"));
			System.out.println(xmlOD.addUser("bastien","forever"));
			System.out.println(xmlOD.removeUser("michel"));

			do{
				//get the command line from user
				System.out.println("Veuillez saisir une commande " +
						" :\n P_EXIST  <pseudo> \nU_EXIST  <pseudo> <mdp>\nADD  <pseudo> <mdp>\nREMOVE  <pseudo>\n");
				text= sc.nextLine();


				String commande= text.substring(0,text.indexOf(' '));

				if(commande.equals("P_EXIST")){
					String pseudo= text.substring(text.indexOf(' ')+1,text.lastIndexOf(' '));

					System.out.println(xmlOD.pseudoExist(pseudo));
				}
				if(commande.equals("U_EXIST")){
					String pseudo= text.substring(text.indexOf(' ')+1,text.lastIndexOf(' '));
					String mdp= text.substring(text.lastIndexOf(' ')+1);

					System.out.println(xmlOD.userExist(pseudo,mdp));
				}
				if(commande.equals("ADD")){
					String pseudo= text.substring(text.indexOf(' ')+1,text.lastIndexOf(' '));
					String mdp= text.substring(text.lastIndexOf(' ')+1);

					System.out.println(xmlOD.addUser(pseudo,mdp));
				}
				if(commande.equals("REMOVE")){
					String pseudo= text.substring(text.indexOf(' ')+1);
					System.out.println(xmlOD.removeUser(pseudo));

				}

			}while (!text.equals("STOP"));

		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
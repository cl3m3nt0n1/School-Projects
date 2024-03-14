package Serveur;

import Common.Client;
import Common.Clients;
import org.w3c.dom.Document;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.ArrayList;
import java.util.List;

public class rmiServeur {

	public static void main(String[] args) {

		try {

			XmlOperations xmlOD = new XmlOperations();
			xmlOD.readXMLFile("C:\\Users\\Clementoni\\Documents\\ENSIM\\4A\\Programmation concurrente\\TP5\\src\\Serveur\\clients.xml");
			xmlOD.getClients();

			Registry reg = LocateRegistry.createRegistry(1099);
			reg.bind("xmlOP", xmlOD);
			System.out.println("C'est bon " + xmlOD);
		} catch (Exception e) {
			System.out.println("ERREUR");
			e.printStackTrace();
		}
	}

}
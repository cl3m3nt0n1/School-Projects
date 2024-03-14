package Common;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface XmlOperationsI extends Remote{

	public Boolean pseudoExist(String pseudo) throws RemoteException;
	public Boolean userExist(String pseudo, String mdp) throws RemoteException;
	public String addUser(String pseudo, String mdp) throws RemoteException;
	public String removeUser(String pseudo) throws RemoteException;
}

package Common;

import java.util.ArrayList;
import java.util.List;

public class Clients {

    private List<Client> clientList = new ArrayList<Client>();

    public void addClient(Client cli){
        clientList.add(cli);
    }

    public void setClientList(List<Client> clientList){
        this.clientList = clientList;
    }

    public List<Client> getClientList(){
        return this.clientList;
    }

}

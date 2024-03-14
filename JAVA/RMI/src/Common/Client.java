package Common;

public class Client {
    private String pseudo;

    private String mdp;

    public Client(){
    }

    public void setPseudo(String pseudo){
        this.pseudo = pseudo;
    }

    public void setMdp(String mdp){
        this.mdp = mdp;
    }

    public String getPseudo(){
        return this.pseudo;
    }

    public String getMdp(){
        return this.mdp;
    }

}

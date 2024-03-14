<!doctype html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport"
          content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <link rel="stylesheet" href ="../css/style.css">
    <title>Conciergerie - Ajouter Client</title>
    <?php
    include_once('connect_db.php');
    include_once("clientInfoDisplay.php");
    $dbname = "conciergerie";
    $link = connectDB($dbname, "localhost", "root", "");
    $displayOrders = false;
    ?>
</head>
<body>
    <?php 
        $query="SELECT * FROM produit";
        $result = askDB($link, $dbname, $query);
    ?>
    <form method=GET>
    
        
                
        <div>
    
                        
            <br><br>
                <label for="id">id client</label>
                <input type="text" id="id"name="id_client" >
                <?php while ($row = mysqli_fetch_array($result)) { ?>
                <label for="quantity"><?= $row["Nom_produit"]?></label>
                <input type="number" id=<?='quantity'.$row['id_produit']?> name=<?='quantity'.$row['id_produit']?> value="0" min="0">                            

           <?php } ?>

        </div>

                
        <input type="submit" value="Confirmer">
    </form>

    <?php
       

        if(isset($_GET['id_client'])){
            $query2="INSERT INTO `commande`(`id_client`, `Etat`) VALUES('".$_GET['id_client']."','Ongoing')";
            $result2= askDB($link, $dbname, $query2);
            $query="SELECT * FROM produit";
            $result = askDB($link, $dbname, $query);
            $query4="SELECT MAX(id_commande) FROM commande";
            $result4=askDB($link,$dbname,$query4);
            $row4=mysqli_fetch_assoc($result4);
            $id_commande=$row4["MAX(id_commande)"];

            while ($row = mysqli_fetch_array($result)) {
                if($_GET['quantity'.$row['id_produit']]>0){
                    for($i=0;$i<$_GET['quantity'.$row['id_produit']];$i++){
                        $query3="INSERT INTO contenir VALUES('$id_commande','".$row['id_produit']."')";
                        $result3= askDB($link, $dbname, $query3);
                    }
                }
                
            }
            ?>
            <script>
            location.replace("index.php");
            </script>
            <?php
        }
    ?>
    
</body>
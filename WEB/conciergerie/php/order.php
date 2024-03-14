<!doctype html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport"
          content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-GLhlTQ8iRABdZLl6O3oVMWSktQOp6b7In1Zl3/Jr59b6EGGoI1aFkw7cmDA6j6gD" crossorigin="anonymous">
    <link rel="stylesheet" href ="../css/style.css">

    <!-- What happens if we add BootStrap ? -->
    <title>Conciergerie - Commandes</title>
    


</head>
<header>
    <h1 id="pageTitle">
        Gestion des commandes
    </h1>
    <script>
                document.querySelector('#pageTitle').addEventListener('click', function(){
                location.href = 'index.php';
            });
    </script>
    <?php
    include_once('connect_db.php');
    include_once("clientInfoDisplay.php");
    $dbname = "conciergerie";
    $link = connectDB($dbname, "localhost", "root", "");
    ?>
    
    
</header>

<body>
    <div class = lesproblemes>

        <div class = orderList>
            <div class="orderListForm">
            <h2>Liste des commandes du client</h2>
            <?php
            if (isset($_GET['id_commande'])){
                $query = "SELECT * FROM commande WHERE id_client = '" . $_GET['id_client'] . "'";
                $sqlResult = askDB($link,$dbname,$query);
                ?>
                <form class = "clientListOrder" method = POST>
                    <?php
                while($sqlRow = mysqli_fetch_array($sqlResult)){
                    ?>
                    <div class="orderListDots">
                        <input type="radio" name="id_order" value="<?= $sqlRow['id_commande']?>">
                        <label for='id_order'>ID : <?= $sqlRow['id_commande']?> | Date Commande : <?= $sqlRow['Date']?> | Etat : <?= $sqlRow['Etat']?></label>
                    </div>
                        <?php
                } ?>
                <input id="orderListButton" type="submit" value="Modifier">
            </form>
            <form method= GET action="newOrder.php">
                
                <input type="hidden" value="<?=$_GET['id_client']?>">
                <input id="orderListButton" type="submit" value="Ajouter une commande">
            </form>
            <?php
                }
            ?>
        </div>
    </div>
    

    <aside>
        <div class="clientInfoForm" style="width: 100%;">
            <h2>Informations Client</h2>
            <div id="partsContainer">
            <div id=part1>
            <?php
            if (isset($_GET['id_client'])) {
                $query = "SELECT `id_client`, `Membership`,`Points`,`Solde`,`Nom`, `Prenom`
                            FROM `client` WHERE `id_client` = " . $_GET['id_client'];
                $result = askDB($link, $dbname, $query);
                $row = mysqli_fetch_array($result);
                $query2 = "SELECT `Adresse`,`Numero_tel`,`Facebook`,`Instagram`,`Mail`
                               FROM `info_client` WHERE `id_client` = " . $row["id_client"];
                $result2 = askDB($link, $dbname, $query2);
                $row2 = mysqli_fetch_array($result2);
                ?>
                


                <!-- infos from client table -->
                <label for= "id_client">id_client</label>
                <input type = text name="id_client" value = "<?= $row['id_client']?>" readonly>
                <label for= "Nom">Nom</label>
                <input type = text name="Nom" value = <?= $row['Nom']?> readonly>
                <label for= "Prenom">Prenom</label>
                <input type = text name="Prenom"  value = <?= $row['Prenom']?> readonly>
                <label for= "Membership">Membership</label>
                <input type = text name="Membership"  value = <?= $row['Membership']?> readonly>
                <label for= "Solde">Solde</label>
                <input type = text name="Solde"  value = <?= $row['Solde']?> readonly>
                <label for= "Points">Points</label>
                <input type = text name="Points"  value = <?= $row['Points']?> readonly>
                
            </div>
            <div id="part2">
                <!-- infos from clientInfos table -->
                <label for= "Adresse">Adresse</label>
                <input type = text name="Adresse"  value = "<?= $row2['Adresse'] ?>" readonly>
                <label for= "Numero_tel">Numero_tel</label>
                <input type = text name="Numero_tel"  value = <?= $row2['Numero_tel']?> readonly>
                <label for= "Facebook">Facebook</label>
                <input type = text name="Facebook"  value = "<?= $row2['Facebook']?>" readonly>
                <label for= "Instagram">Instagram</label>
                <input type = text name="Instagram"  value = "<?= $row2['Instagram']?>" readonly>
                <label for= "Mail">Mail</label>
                <input type = text name="Mail"  value = <?= $row2['Mail']?> readonly>
            </div>

            <?php
            }
            ?>

        </div>
        </div>
        </div>
    </aside>
    
    </div>

    <div id="orderContainer">
    <div class = orderInfos>
            <?php
            if (isset($_POST['id_order'])) {
                // Dump de la db pour récupérer les infos nécessaires à la facture
                $sql = "SELECT id_produit, Nom_produit, count(id_produit) as \"Nombre\", produit.Prix_vente 
                       as \"Prix unite\", (produit.Prix_vente * COUNT(*)) as \"Prix Total\"  FROM `contenir` 
                       NATURAL JOIN produit WHERE id_commande = '" . $_POST['id_order'] . "' GROUP BY id_produit";
                $sqlR = askDB($link, $dbname, $sql);

                

                ?>
            <table class="table table-striped table-hover">
                <thead>
                    <tr>
                        <th colspan="5">Commande Client</th>
                    </tr>
                    <th scope = "col">Id Produit</td>
                    <th scope = "col">Nom Produit</td>
                    <th scope = "col">Quantité</td>
                    <th scope = "col">Prix unité</td>
                    <th scope = "col">Prix total</td>
                </thead>
                <tbody>

                <form method=POST>
                    
                    <input type="hidden" value="<?=$_POST['id_order'] ?>"name="id_order">
                    <input type="submit" value="Supprimer la commande" name="deleteOrder">
                </form>
                <?php
                    if(isset($_POST['deleteOrder'])){
                        $queryDELETE="DELETE FROM commande WHERE id_commande='".$_POST['id_order']."'";
                        $resultDELETE=askDB($link, $dbname,$queryDELETE);
                        $queryDELETE2="DELETE FROM contenir WHERE id_commande='".$_POST['id_order']."'";
                        $resultDELETE2=askDB($link, $dbname,$queryDELETE2);
                    }
                ?>
                <!--- -->
                <form method =POST>
                <?php
                while ($result = mysqli_fetch_array($sqlR)) {
                    ?>

                    <tr>
                    <th  scope = "row"> <?= $result['id_produit'] ?> </td>
                    <td > <?= $result['Nom_produit'] ?> </td>
                    <td > <?= $result['Nombre'] ?> </td>
                    <td > <?= $result['Prix unite'] ?> </td>
                    <td > <?= $result['Prix Total'] ?> </td>
                    <td>
                            <input type="number" name="delta" value="0" step="1" min="-50" max="50" />
                            <input type="submit" value="Confirmer" >
                            <input type="hidden" name="id_commande" value="<?= $_POST['id_order'] ?>">
                            <input type="hidden" name="id_produit" value="<?= $result['id_produit']  ?>">
                            <label for="delete">Supprimer le produit</label>
                            <input type="radio" name="delete">

                    </td>
                    </tr>
                <?php
                }
            }
                ?>
               
                </form>
                <?php
                    
                    if(isset($_POST['delta'])){
                        $id_prod=$_POST['id_produit'];
                        $id_commande=$_POST['id_commande'];
                        if($_POST['delta']>=0){
                            for($i=0;$i<$_POST['delta'];$i++){

                                $query="INSERT INTO contenir VALUES ('$id_commande','$id_prod')";
                                $result2 = askDB($link, $dbname,$query);
                            }
                        }
                        if(isset($_POST['delete'])){

                             
                                $query="DELETE FROM contenir WHERE id_commande='".$_POST['id_commande']."' AND id_produit='".$_POST['id_produit']."'";
                                $result = askDB($link, $dbname,$query);
                             
                        }

                    }
                ?>
                
                </tbody>

            </table>
            <button id="export">Export HTML table to CSV file</button>
            </div>
    </div>
    <!-- Adding JS functions  for table export-->
    <script type="text/javascript" src="../js/tableToCSV.js"></script>
</body>
</html>
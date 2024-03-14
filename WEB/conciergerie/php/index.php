<!doctype html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport"
          content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <link rel="stylesheet" href ="../css/style.css">
    <title>Conciergerie</title>

</head>
<header>
    <h1>
        Gestion des clients
    </h1>
    <?php
        include_once('connect_db.php');
        include_once("clientInfoDisplay.php");
        $dbname = "conciergerie";
        $link = connectDB($dbname, "localhost", "root", "");
        $displayOrders = false;
    ?>
</header>


<body>
    <div class = "search">
            <form class = searchForm method=POST>
            <input class = searchTerm type=search name=recherche placeholder=Rechercher un client required autofocus/>
            <select class=searchCat  name=filtres id=filtres>
            <option value=Nom selected> Nom</option>
            <option value=id_client>id</option>
            </select>
            <input class=searchButton type=submit value=Rechercher>
            </form>
    </div>
    <div class="insertClient">
        <a href="addClient.php">Ajouter Client</a>
    </div>


    <div class = clientItems>
        <div class = "client_list">
            <?php
                $query = "SELECT * FROM client";
                $result = askDB($link,$dbname,$query);
                ?>

            <form class = "clientListForm" method = POST>
            <h2>Liste des clients</h2>
                    <?php while ($row = mysqli_fetch_array($result)) { ?>
                    <div class = clientListDots>
                        <input type = radio name="id_client" value="<?= $row['id_client']?>">
                        <label for='id_client'><?= $row["Nom"]. " ". $row["Prenom"]?></label>
                        
                    </div>

                    <?php } ?>
                    <input id="clientListButton" type = submit value="Afficher les informations"/>
            </form>
        </div>

        <div class = "client_infos">
        <div id="searchResults">
            <?php

            // Treating  client info display from radio buttons form
            if (isset($_POST['id_client'])){
                $query = "SELECT `id_client`, `Membership`,`Points`,`Solde`,`Nom`, `Prenom`
                            FROM `client` WHERE `id_client` = "  . $_POST['id_client'];
                $result = askDB($link,$dbname,$query);
                $row = mysqli_fetch_array($result);
                $query2 = "SELECT `Adresse`,`Numero_tel`,`Facebook`,`Instagram`,`Mail`
                               FROM `info_client` WHERE `id_client` = " . $row["id_client"];
                $result2 = askDB($link,$dbname,$query2);
                $row2 = mysqli_fetch_array($result2);

                clientInfoDisplay($row, $row2);

            }

            // Treating changes in client info
            if(isset($_POST['Numero_tel']))
            {
                //NON A XSS !
                //NON A L'INJECTION SQL !
                $id = mysqli_real_escape_string($link,htmlspecialchars($_POST['id_client']));
                $nom = mysqli_real_escape_string($link,htmlspecialchars($_POST['Nom']));
                $prenom = mysqli_real_escape_string($link,htmlspecialchars($_POST['Prenom']));
                $member = mysqli_real_escape_string($link,htmlspecialchars($_POST['Membership']));
                $solde = mysqli_real_escape_string($link,htmlspecialchars($_POST['Solde']));
                $points = mysqli_real_escape_string($link,htmlspecialchars($_POST['Points']));

                $adresse = mysqli_real_escape_string($link,htmlspecialchars($_POST['Adresse']));
                $num = mysqli_real_escape_string($link,htmlspecialchars($_POST['Numero_tel']));
                $facebook = mysqli_real_escape_string($link,htmlspecialchars($_POST['Facebook']));
                $insta = mysqli_real_escape_string($link,htmlspecialchars($_POST['Instagram']));
                $mail = mysqli_real_escape_string($link,htmlspecialchars($_POST['Mail']));


//                Updating data in db
                $query = "UPDATE client SET Nom = '$nom', Prenom = '$prenom', Membership = '$member',
                  Solde = '$solde', Points = '$points' WHERE id_client = '$id'";

                $query2 = "UPDATE info_client SET Adresse = '$adresse', Numero_tel = '$num',
                  Facebook = '$facebook', Instagram = '$insta', Mail = '$mail' WHERE id_client = '$id'";

                askDB($link, $dbname, $query);
                askDB($link, $dbname, $query2);
                $displayOrders = true;

            }

            // Treating client infos display from search bar
            if(isset($_POST['recherche'])){

                //NON A XSS !
                //NON A L'INJECTION SQL !
                $recherche = mysqli_real_escape_string($link,htmlspecialchars($_POST['recherche']));
                $filtres = mysqli_real_escape_string($link,htmlspecialchars($_POST['filtres']));

                if($recherche !== "")
                {
                    $searchDone=false;
                    $query = "SELECT `id_client`, `Membership`,`Points`,`Solde`,`Nom`, `Prenom`
                            FROM `client` WHERE `" . $filtres . "`=\"" . $recherche . "\"";
                    $result = askDB($link,$dbname,$query);
                    $row = mysqli_fetch_array($result);

                    if($filtres === "id_client")
                        $query2 = "SELECT `Adresse`,`Numero_tel`,`Facebook`,`Instagram`,`Mail`
                               FROM `info_client` WHERE `id_client` = `" . $filtres . "`";

                    // If user chooses the name input
                    else
                        if(!($row===NULL)){
                            $query2 = "SELECT `Adresse`,`Numero_tel`,`Facebook`,`Instagram`,`Mail`
                               FROM `info_client` WHERE `id_client` = " . $row["id_client"];
                        }
                        else
                            echo "<h2>Aucun résultat !</h2>";


                    $result2 = askDB($link,$dbname,$query2);
                    $row2 = mysqli_fetch_array($result2);

                    if(!($row === NULL)){
                        clientInfoDisplay($row, $row2);
                        $searchDone = true;
                    }
                    if($row === NULL && !$searchDone) echo "<h2>Aucun résultat !</h2>";
                    if($row === NULL && !$searchDone) echo "<h2>Aucun résultat !</h2>";

                }

            }
            ?>

        </div>
    </div>
    </div>

    <div class="clientOrders">
        <div id="ordersContainer">
        <h2>Liste des commandes</h2>
        <div>
            <!-- Add a new order for this client-->
        <form method= GET action="newOrder.php">
                
                
                <input id="orderListButton" type="submit" value="Ajouter une commande">
            </form>
        </div>
        <ul>
        <?php

//        if the user searches by using clientList
        if(isset($_POST['id_client'])){
            $sql =  "SELECT * FROM commande WHERE commande.id_client = " . $_POST['id_client'];
            $sqlResult = askDB($link,$dbname,$sql);
            while($sqlRow = mysqli_fetch_array($sqlResult)){
                ?>
                <li>
                id commande : <?= $sqlRow['id_commande']?> |
                Date commande : <?= $sqlRow['Date']?> |
                Etat commande : <?= $sqlRow['Etat']?> |
                <a href="order.php?id_commande=<?= $sqlRow['id_commande']?>&id_client=<?= $sqlRow['id_client']?>">Modifier</a>
                </li>
            <?php
            }
        }
        ?>
            <?php
            //        if the user searches by using search form and id
            if((isset($_POST['recherche']) AND ($_POST['filtres'] == "id_client"))){
                $sql =  "SELECT * FROM commande WHERE commande.id_client = " . $_POST['recherche'];
                $sqlResult = askDB($link,$dbname,$sql);
                while($sqlRow = mysqli_fetch_array($sqlResult)){
                    ?>
                    <li>
                        id commande : <?= $sqlRow['id_commande']?> |
                        Date commande : <?= $sqlRow['Date']?> |
                        Etat commande : <?= $sqlRow['Etat']?> |
                        <a href="order.php?id_commande=<?= $sqlRow['id_commande']?>">Modifier</a>

                    </li>
                    <?php
                }
            }
            ?>

            <?php
            //        if the user searches by using search form and name
            if((isset($_POST['recherche']) AND ($_POST['filtres'] == "Nom"))){
                $sql = "SELECT * FROM commande WHERE commande.id_client IN (SELECT id_client FROM client WHERE Nom= '" . $recherche . "')";
                $sqlResult = askDB($link,$dbname,$sql);
                while($sqlRow = mysqli_fetch_array($sqlResult)){
                    ?>
                    <li>
                        id commande : <?= $sqlRow['id_commande']?> |
                        Date commande : <?= $sqlRow['Date']?> |
                        Etat commande : <?= $sqlRow['Etat']?> |
                        <a href="order.php?id_commande=<?= $sqlRow['id_commande']?>">Modifier</a>

                    </li>
                    <?php
                }
            }
            ?>
        </ul>
        </div>
    </div>
</body>
</html>

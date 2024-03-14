<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Discothèque - Bienvenue</title>
    <link rel="stylesheet" href="../css/style.css">
</head>
<body>

    <?php
        include_once('connect_database.php');
        $link = connectDB("projet Ludotheque","localhost","root","");

        $query = "SELECT `Genre` FROM albums"; //Requête SQL : Choisir la colonne genre de la table Albums
        $result = askDB($link,$dbName,$query);
    ?>
    <header>
        <div id="headerLeftSide">
            <img src="../assets/Images/gramophone.png" alt="logo">
            <h1>Discothèque</h1>
        </div>
        <div id="headerRightSide">
            <a href="recherche.php">Rechercher</a>
            <button>ConnexionStatus</button>
            <p id="usertag">Username</p>
        </div>
    </header>
    <div id="welcome">
    <?php


        if (!isset($_GET['ID']))
        {
            echo "<h2>Bienvenue !<h2><br/><h3>N'hésitez pas à vous identifier </h3>";
        }

        if (isset($_GET['ID']))
        {
            $query = "SELECT `Nom`,`Prenom` FROM `membres` WHERE `ID`=" . $_GET['ID'];
            $result = askDB($link,$dbName,$query);
            $row = mysqli_fetch_array($result);
            

            //var_dump($row);
            echo "<h3>Bienvenue ". $row['Prenom'] . " ". $row['Nom'] . "</h3>";
        }	

    ?>

    </div>
    <section id="mosaique">
        <?php
        
        $query = "SELECT * FROM albums";
        $result = askDB($link,$dbName,$query);
    
            
            while($row = mysqli_fetch_array($result)){
                
                echo "<div class=\"discList\"><img src=\"data:image/jpeg;base64,"; 
                echo base64_encode($row['Image']) . "\"/><h3>" . $row['Nom'] . "</h3><h4>"; 
                echo $row['Artiste'] . "</h4><a class=\"cmnButton\" href=\"album.php?album=". $row['Nom'] ."&amp;artiste=". $row['Artiste'] ."\">Consulter</a></div>";
            }

        ?>
    </section>


    <?php
        mysqli_close($link);    //Fermeture de la connexion
    ?>
</body>
</html>

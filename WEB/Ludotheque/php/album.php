<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="../css/style.css">
    <title><?php echo $_GET['artiste']. "-" . $_GET['album']; ?></title>
</head>
<body>
    
    <?php
        include('header.php');
    ?>
    
    <div class="albumArtist">
        <h2>
            <?php
                echo $_GET['artiste']. "-" . $_GET['album'];
            ?>
        </h2>
    </div>
    <div id="coverDescription">
    <div class="albumCover">
        <?php 

            include_once('connect_database.php');
            $link = connectDB("projet Ludotheque","localhost","root","");
            

            //Requête SQL pour récupérer l'image correspondante à l'album
            $query = "SELECT `Image` FROM `albums` WHERE `Artiste` = '" . $_GET['artiste']. "' && `Nom`='".$_GET['album']."'";
            $result = askDB($link,"projet Ludotheque", $query);
            $row = mysqli_fetch_array($result);
            echo "<img src=\"data:image/jpeg;base64," . base64_encode($row['Image'])."\"/>";    //Afficher l'illustration
            
        ?>
    </div>

    <div class="descriptionBox">
        <?php
            $query = "SELECT `Description` FROM `albums` WHERE `Artiste` = '" . $_GET['artiste']. "' && `Nom`='".$_GET['album']."'";
            $result = askDB($link,$dbName,$query);
            $row = mysqli_fetch_array($result);

            echo "<h3>Description :</h3>";
            echo "<p id=\"story\">". $row['Description'] ."</p>";
            
        ?>
    </div>
    </div>
    <div class="reservation">
         
        <?php
            $query = "SELECT `ID` FROM `albums` WHERE `Artiste` = '" . $_GET['artiste']. "' && `Nom`='".$_GET['album']."'";
            $result = askDB($link,$dbName,$query);
            $row = mysqli_fetch_array($result);

            $query = "SELECT `Restant` FROM `stock` WHERE `album_ID` = " . $row['ID']. "";
            $result = askDB($link,$dbName,$query);
            $row = mysqli_fetch_array($result);
            
            
            echo $row['Restant'];
            
        ?>
        
    </div>
    
    
    <?php
        mysqli_close($link);    //Fermeture de la connexion
    ?>
</body>
</html>

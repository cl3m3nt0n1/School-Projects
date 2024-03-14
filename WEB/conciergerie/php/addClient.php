<!doctype html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport"
          content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <link rel="stylesheet" href ="../css/style.css">
    <title>Conciergerie - Ajouter Client</title>
</head>

<header>
    <h1 id="pageTitle">Ajouter un client</h1>
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
    $displayOrders = false;
    ?>
</header>

<body>
<div class="client_infos" style="position: absolute;left: 22%;">
    <form class = clientInfoForm method="post">
        <!-- infos from client table -->
        <label for= "Nom">Nom</label>
        <input type = text name="Nom" required>
        <label for= "Prenom">Prenom</label>
        <input type = text name="Prenom" required>
        <label for= "Membership">Membership</label>
        <input type = text name="Membership" required>
        <label for= "Solde">Solde</label>
        <input type = text name="Solde" required>
        <label for= "Points">Points</label>
        <input type = text name="Points" required>


        <!-- infos from clientInfos table -->
        <label for= "Adresse">Adresse</label>
        <input type = text name="Adresse" required>
        <label for= "Numero_tel">Numero_tel</label>
        <input type = text name="Numero_tel" required>
        <label for= "Facebook">Facebook</label>
        <input type = text name="Facebook" required>
        <label for= "Instagram">Instagram</label>
        <input type = text name="Instagram" required>
        <label for= "Mail">Mail</label>
        <input type = text name="Mail" required>
        <input class = "clientInfoFormButton"type="submit" value="Ajouter Client">
    </form>
</div>
<div>
    <?php
    if(isset($_POST['Nom'])){

        $sql = "SELECT Nom FROM Client";
        $result4 = askDB($link,$dbname,$sql);
        $names = mysqli_fetch_array($result4);


        $nom = mysqli_real_escape_string($link,htmlspecialchars($_POST['Nom']));
        $prenom = mysqli_real_escape_string($link,htmlspecialchars($_POST['Prenom']));
        $member = mysqli_real_escape_string($link,htmlspecialchars($_POST['Membership']));
        $solde = mysqli_real_escape_string($link,htmlspecialchars($_POST['Solde']));
        $points = mysqli_real_escape_string($link,htmlspecialchars($_POST['Points']));

        $adresse = mysqli_real_escape_string($link,htmlspecialchars($_POST['Adresse'], ENT_QUOTES));
        $num = mysqli_real_escape_string($link,htmlspecialchars($_POST['Numero_tel']));
        $facebook = mysqli_real_escape_string($link,htmlspecialchars($_POST['Facebook']));
        $insta = mysqli_real_escape_string($link,htmlspecialchars($_POST['Instagram']));
        $mail = mysqli_real_escape_string($link,htmlspecialchars($_POST['Mail']));



            $query = "INSERT INTO `client`( `Membership`, `Points`, `Solde`, `Nom`, `Prenom`) VALUES ('$member',$points,$solde,'$nom','$prenom')";
            $result = askDB($link, $dbname,$query);

            $query2 = "SELECT id_client FROM client WHERE Nom = '$nom'";
            $result2 = askDB($link,$dbname,$query2);
            $row2 = mysqli_fetch_array($result2);
            $id = $row2['id_client'];

            $query3 = "INSERT INTO `info_client`(`Adresse`, `Numero_tel`, `Facebook`, `Instagram`, `Mail`, `id_client`) 
                        VALUES ('$adresse',$num,'$facebook','$insta','$mail',$id)";
            $result3 = askDB($link,$dbname,$query3);
    ?>
    <script>
        location.replace("index.php");
    </script>
<?php

    }
?>

</div>
</body>
</html>
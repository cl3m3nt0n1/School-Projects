<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="../css/style.css" />
    <title>Discothèque - Login</title>
</head>
<body>

    <?php
        include('connect_database.php');
        $link = connectDB("projet Ludotheque","localhost","root","");

        //Dump des users de la database
        //Si le formulaire est bon, Afficher accueil.php en version non-restricted
        //Formulaire de connexion si faux, redemander les id et mdp
        
        // $query = "SELECT * FROM `membres`";
        // $result = askDB($link,$dbName,$query); 
        // //Dump des utilisateurs de la base dans $users
        // while($row = mysqli_fetch_array($result)){
            
        //     $users[] = $row;
        // }
        // // //DEBUG...
        // var_dump($users);
        // echo "<br/>";

        // foreach($users as $user){
        //     echo $user['Nom']. " ";
        // }
        // //END OF DEBUG...

        if(isset($_POST['ID']) && isset($_POST['MDP']))
        {
            //NON A XSS !
            //NON A L'INJECTION SQL !
            $ID = mysqli_real_escape_string($link,htmlspecialchars($_POST['ID']));
            $MDP = mysqli_real_escape_string($link,htmlspecialchars($_POST['MDP']));
            
            if($ID !== "" && $MDP !== "")
            {
                $query = "SELECT count(*) FROM `membres` WHERE
                    ID = '".$ID."' and MDP = '".$MDP."' ";
                $result = askDB($link,$dbName,$query);
                $row = mysqli_fetch_array($result);

                $count = $row['count(*)'];
                //var_dump($count);   //DEBUG...
                if($count != 0) //Si l'utilisateur existe
                {
                    
                    header('Location:accueil.php?ID='. $ID);
                }
                if($count == 0)
                {
                    echo "<p>Mot de passe ou identifiant incorrect</p>";
                }
            }
        }

    ?>
    <form method="POST" action="login.php">
        <p>
            <label for="ID">ID :</label>
            <input type="text" name="ID" placeholder="Votre Identifiant" required autofocus/>

            <br/>
            <label for="MDP">Mot De Passe :</label>
            <input type="password" name="MDP" placeholder="Votre mot de passe" required/>
        </p>
        <input type="submit" value="Connexion">
    </form>
    
</body>
</html>

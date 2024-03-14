<?php
    $db_name = "conciergerie";
    function connectDB($dbName,$hostName,$userName,$password){
        $link = mysqli_connect($hostName,$userName, $password); //Ouverture de la connexion à la database
        // Check connection
        if($link === false){
            die("ERROR: Could not connect. " . mysqli_connect_error());
        }
        mysqli_select_db($link,$dbName); //Choix de la DB
        return $link;
    }
    function askDB($link,$dbName,$query){
        mysqli_select_db($link,$dbName); //Choix de la DB
        $result = mysqli_query($link,$query);
        return $result;
    }
?>
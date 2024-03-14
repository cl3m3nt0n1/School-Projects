<?php
    function clientInfoDisplay($row1, $row2)
    {
        ?>
        <div>
            <form class = clientInfoForm method="post">
                <h2>Informations client</h2>
                <!-- infos from client table -->
                <div id="partsContainer">
                <div id="part1">
                <label for= "id_client">id_client</label>
                <input type = text name="id_client" value = "<?= $row1['id_client']?>" readonly>
                <label for= "Nom">Nom</label>
                <input type = text name="Nom" value = <?= $row1['Nom']?>>
                <label for= "Prenom">Prenom</label>
                <input type = text name="Prenom"  value = <?= $row1['Prenom']?>>
                <label for= "Membership">Membership</label>
                <input type = text name="Membership"  value = <?= $row1['Membership']?>>
                <label for= "Solde">Solde</label>
                <input type = text name="Solde"  value = <?= $row1['Solde']?>>
                <label for= "Points">Points</label>
                <input type = text name="Points"  value = <?= $row1['Points']?>>
                </div>

                <!-- infos from clientInfos table -->
                <div id="part2">
                <label for= "Adresse">Adresse</label>
                <input type = text name="Adresse"  value = "<?= $row2['Adresse'] ?>">
                <label for= "Numero_tel">Numero_tel</label>
                <input type = text name="Numero_tel"  value = <?= $row2['Numero_tel']?>>
                <label for= "Facebook">Facebook</label>
                <input type = text name="Facebook"  value = "<?= $row2['Facebook']?>">
                <label for= "Instagram">Instagram</label>
                <input type = text name="Instagram"  value = "<?= $row2['Instagram']?>">
                <label for= "Mail">Mail</label>
                <input type = text name="Mail"  value = <?= $row2['Mail']?>>
                <input id = "clientInfoFormButton" type="submit" value="Modifier les données clients">
                </div>
                </div>
            </form>
        </div>

    <?php
    }

?>

#Robot arduino

Ce Robot est tiré de l'exemple sur le site de remoteXY. J'ai simplement découvert qu'un copier/coller ne suffit pas toujours à faire fonctionner le projet.
Dans mon cas il a fallut ajouter une alim 12V 5A, un condensateur au plus pres de chaque servo et même détacher le servo pour éviter l'effet parkinson.
J'expliquerais plus en detail avec un schema quand j'aurais le temps.

## nodemcu

Je souhaite adapter ce programme à mon nodemcu.
Dans un premier temps j'adapte mon arduino IDE au nodemcu. Je mettrais le lien plus tard.
Puis à la place du module bluetooth j'utiliserais le wifi du node.

### module wifi
   http://forum.remotexy.com/viewtopic.php?id=15
Ce post explique comment creer de multiple session remoteXY sur un nodeMCU :)
ça fonctionne. Je n'ai besoin que d'une session :)

La maniere classique ne fonctionne pas mais cette méthode fonctionne.
NB : l'API a du changer depuis le post car il faut ajouter un paramettre mot de passe d'accès. Je l'ai mis à vide dans mon exemple :)

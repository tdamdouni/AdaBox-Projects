# Librairie IoT ESP8266 - MQTT
____
## Sommaire

1. __Classes C++__
    - IoT
    - HTMLUtil
    - Config
    - APConfig
    - NetworkConfig
    - BrokerConfig
1. __Site de configuration__
    - Se connecter au site
    - Les différentes pages
1. __Didacticiel__
    - Se connecter sur un réseau wifi
    - Se connecter à un broker MQTT
    - S'enregistrer sur un topic
    - Publier sur un topic
    - Ajouter des callbacks et des handlers
    - Utiliser les statuts de connexion
    - Configurer les identifiants pour le site de configuration
1. __Problèmes connus__
1. __FAQ__

____

## Description des classes

### Classe IoT
La classe _IoT_ est la classe centrale de la librairie et sert d'interface pour utiliser les fonctionnalités de cette dernière. Elle permet de **créer des clients** _pubsub_, de s'enregistrer sur un _topic_, de **publier des messages**, d'**enregistrer des _callbacks_** et des handlers d'événements, et possède en plus de cela quelques méthodes utilitaires (redémarrage, **retour à la configuration par défaut**, déconnexion du réseau, etc...).

Elle contient également en privé les fonctions qui permettent d'un serveur web, qui à notamment la charge de permettre l'accès au site de configuration. Certaines fonctions ont pour but de générer le code html des pages du site, d'autres ont pour but de répondre aux requêtes arrivant sur le serveur web.

### Classe HTMLUtil
La classe _HTMLUtil_ contient des **fonctions utilitaires** permettant de récupérer rapidement des portions de **code HTML**, qui sont actuellement utilisées pour le site de configuration. 

### Classe Config
La classe _Config_  encapsule le code permettant l'**initialisation** du **système de fichier** embarqué sur la carte. Ce système de fichier est ensuite utilisé pour **configNetwork pour le point** d'accès wifi, le réseau et le _broker MQTT_

### Classe APConfig
La classe _APConfig_ contient les fonctions permettant de récupérer et modifier la **configuration du point d'accès wifi** (_SSID_ et mot de passe).

### Classe NetworkConfig
La classe _NetworkConfig_ permet de modifier les informations utilisées par l'ESP pour **se connecter à internet**. Elle possède pour cela de fonctions permettant de rentrer un **_SSID_**, un **mot de passe** wifi, ainsi qu'un **nom d'utilisateur** et un **mot de passe** utilisateur qui sont utilisés pour les réseaux en nécessitant et pour se connecter au site de configuration.

### Classe BrokerConfig
La classe _BrokerConfig_ permet de configurer les **informations** relatives au **_broker MQTT_** auquel l'ESP va se connecter. Les informations configurables sont au nombre de 3 : 	**adresse IP** du serveur, **port** de connexion et **_UID_** du broker.
____

## Site de configuration

La librairie IoT encapsule un serveur web qui met à disposition un site de configuration auquel on peut se connecter via le point d'accès wifi de l'ESP.

### Se connecter au site
Pour se connecter au site de configuration, il faut d'abord que l'ESP ait son **point d'accès activé** et que le **site de configuration soit démarré**. 
Une fois que ces deux conditions sont valides, vous pouvez vous connecter au site. Pour ce faire, vous devez

 1. Vous connecter à l'_access point_ de l'ESP (*ESPAccessPoint* par défaut) avec un objet pouvant se connecter sur un réseau wifi (ordinateur, smartphone, etc ...)
 2. Ouvrez un **navigateur web** et connectez-vous sur l'adresse **_192.168.4.1_**. Vous arriverez alors sur le site de configuration.
 3. Entrez le **nom d'utilisateur** et le **mot de passe** associé tels que vous les avez configurés, et validez. Vous arriverez ensuite sur la page principale du site. Par défaut, l'identifiant et le mot de passe sont vides, vous n'avez qu'à cliquer sur le bouton "Valider" pour vous connecter.

### Les différentes pages
Le site comprend plusieurs pages servant chacune à configurer un élément de la lib _IoT_: 

#### Page de configuration du réseau wifi
Cette page permet de **configurer la connexion à internet** par l'ESP. Elle liste notamment les wifi visibles par ce dernier, et permet de modifier le wifi sur lequel l'ESP tentera de se connecter. 

_Note : le temps d'affichage de cette page est plus élevé que celui des autres pages, à cause du temps nécessaire à l'établissement de la liste des réseaux WiFi visibles._
#### Page de configuration du broker MQTT
Cette page permet la **configuration** des **informations** relatives au _**broker MQTT**_.
#### Page de configuration du point d'accès de l'ESP
Cette page comprend les éléments permettant la **modification des informations** du **point d'accès wifi** de l'ESP. Un **redémarrage** du point d'accès est **nécessaire** pour que les modifications soient prises en compte.

___

## Didacticiel

### Se connecter sur un réseau wifi

La connexion à un réseau wifi se fait automatiquement  avec les informations stockées dans le fichier de configuration qui est géré par la classe _NetworkConfig_. 
Pour modifier ces informations, il est nécessaire de passer par le __site de configuration__ en allant sur la page _**configuration réseau**_ (url : _192.168.4.1/configNetwork_) une fois que vous avez entré les identifiants admin. 

Vous pouvez également modifier la classe _IoT_ de sorte à pouvoir paramétrer ces valeurs via son attribut _IoT::networkConfig_

### Se connecter à un broker MQTT
Pour se connecter à un _broker MQTT_, vous devez utiliser les fonctions **_IoT::createPubSubClient_**. Il existe deux version de cette fonction : 

```C++
bool createPubSubClient(void (*pubSubCallback)(char*, byte*, unsigned int));
```

Cette première fonction utilise l'adresse ip, le port et l'_UID_ qui est enregistré dans le fichier de configuration. Vous pouvez modifier ces données avec le site de configuration. Elle prend cependant en paramètre un pointeur sur une fonction, qui sera utilisée comme un _callback_ par le client _PubSub_

```C++
bool createPubSubClient(String serverIp, String port, String UID, void (*pubSubCallback)(char*, byte*, unsigned int));
```

Cette fonction-ci prend directement l'adresse, le port et l'_UID_ en paramètre, et n'utilise pas ceux stocké dans le fichier de configuration. Elle prend également un _callback_ comme la précédente.

### S'enregistrer sur un topic

Pour s'enregistrer sur un topic _MQTT_, il suffit d'utiliser la fonction **_IoT::mqttSubscribe_**. Cette dernière prend en paramètre une chaîne de caractères, correspondant au nom du topic en question. Ce nom doit respecter la syntaxe définie par _MQTT_ : un nom de topic est composé d'une succession de noms de salons séparés par des '/', le plus à gauche étant le plus général, et le plus à droite étant le plus précis.
Exemple : 
> IOT/ESP8266/ACTIONS

Ce nom de topic correspond au salon _ACTIONS_, situé dans le salon _ESP8266_, lui-même étant situé dans le salon _IOT_.

Exemple d'utilisation de la fonction : 
```C++
if (iot->isNetworkConnected() && iot->isMQTTBrokerConnected()) {
	iot->mqttSubscribe("IOT/ESP8266/ACTIONS");
}
```

### Publier sur un topic
Pour publier un message sur un topic _MQTT_, il faut utiliser la fonction **_IoT::mqttPublish_**. Cette fonction prend en paramètre le nom du topic (syntaxe comme décrite ci-dessus) et le message à publier dans ce topic.

Exemple d'utilisation : 
```C++
if (iot->isNetworkConnected() && iot->isMQTTBrokerConnected()) {
	iot->mqttPublish("IOT/ESP8266/ACTIONS", "esp activé");
}
```

### Ajouter des callbacks et des handlers

La classe IoT propose certaines méthodes qui permettent de spécifier des traitements à appliquer dans certains cas, les *handlers*. Les fonctions de handlers sont reconnaissables dans la classe pour plusieurs raisons :

 - Leurs noms commencent par `on`
 - Elles prennent un pointeur de fonction en paramètre
 - Elles ne renvoient rien (`void`)

Exemple : 
```C++
	void onWebServerConfigDeleted(void(*func)(const byte));
```

Pour les utiliser, il suffit d'**appeler** une fois cette fonction _handler_ avec en **paramètre** un **pointeur** vers une autre fonction, celle que vous voulez **exécuter** lorsque l'**événement** a lieu. Dans l'exemple-ci dessus, la fonction passé en paramètre sera appelée lorsque la configuration du _web server_ sera effacée.

La signature des fonctions à passer en paramètre est décrite dans la signature de la méthode _handler_. Pour reprendre l'exemple précédent, on voit que la fonction en paramètre doit avoir comme seul paramètre une variable de type `const byte`.

La classe IoT contient également des fonctions de _callback_. Elles possèdent des noms de la forme `setXXXCallback(...)` et fonctionnent sur le même principe que les handlers en prenant un pointeur de fonction en paramètre, mais les fonctions passées en paramètre doivent avoir pour paramètre un _event_ d'un certain type.

Exemple : 
```C++
	void setAPConnectedCallback( void (*func)(const WiFiEventSoftAPModeStationConnected& event));
```

Dans cet exemple, le paramètre de la fonction en paramètre doit être une référence vers une variable de type `const WiFiEventSoftAPModeStationConnected&`.

### Utiliser les statuts de connexion

La classe _IoT_ définie dans son fichier descripteur un enum nommé _CONNECT\_ RESULT_ qui définis des cas situationnels vis-à-vis de l'état de la connexion. L'état actuel peut être récupéré avec la méthode `IoT::autoConnect`.

Vous pouvez ensuite appliquer le traitement que vous voulez aux cas situationnels que vous souhaitez traiter.

Exemple de traitement :
```C++
switch(iot->autoConnect()){
	case (IoT::NETWORK_CONNECTED) :
		Serial.println("#INO> Network connected");
	break;
	default:
	break;
}
```

La liste des cas possibles se trouve au début du fichier `IoT.h`.

### Configurer le nom d'utilisateur et le mot de passe du site de configuration

Par défaut, le nom d'utilisateur et le mot de passe pour se connecter au site de configuration sont vides. Pour modifier cela, vous devez passer par le site de configuration ou modifier la classe IoT pour accéder à l'attribut `networkConfig` ou à ses fonctions.

Via le site de configuration, vous devez :

 1. Allez sur le site
 2. Connectez-vous avec les identifiants actuels
 3. Allez sur la page _Configuration réseau_
 4. Entrez les nouveaux identifiants dans la partie _Authentification de l'utilisateur_
 5. Validez

#	Problèmes connus
1. __Connexion impossible sur Eduroam__
	_Depuis la version 1.0_

	La connexion de l'ESP n'est actuellement pas possible sur les réseaux WiFi utilisant le protocole _WPA2 Entreprise_, comme Eduroam. Nous vous invitons à utiliser d'autres réseaux WiFi, comme _UTBM Visiteur_.

2. __Réseaux WiFi apparaissant plusieurs fois dans la liste__
	_Depuis la version 1.0_

	Dans la page de configuration réseau du site de l'ESP, le listing des réseaux à portée affiche plusieurs fois les mêmes réseaux, les uns à la suite des autres. 
	Ce phénomène ne pose pas de problèmes majeurs, dans la mesure où tous les réseaux visibles par l'ESP sont affichés au moins une fois.
	
#	FAQ
Si vous avez lu cette documentation et qu'il vous reste des questions, nous serons heureux d'y répondre. Veuillez nous contacter par mail.
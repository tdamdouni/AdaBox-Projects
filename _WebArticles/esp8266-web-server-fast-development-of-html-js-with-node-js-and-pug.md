# ESP8266 (Web Server): Fast development of HTML + js with Node.js and Pug

_Captured: 2017-11-08 at 23:48 from [diyprojects.io](https://diyprojects.io/esp8266-web-server-fast-development-of-html-js-with-node-js-and-pug/#.WgOJpEq1Kf0)_

**Developing a Web server for ESP8266 can quickly become tedious. Indeed, it is necessary to download the files (HTML, js ..) with each modification in order to be able to focus. Fortunately, Node.js will allow us to develop and develop on a computer all the code of the Web Server part before downloading it on the ESP8266**. Node.js is so great that we will be able to directly use Pug templates (presentation article) and even retrieve real measurements directly on the ESP8266!

In this tutorial we will see how to quickly realize an HTML interface that will display the measurements of a DHT22 and drive the GPIO of the ESP8266. We can also retrieve the data (and reports) on a computer using a mini web server developed in a few lines of code with Nodejs. The project accounts code is available on GitHub [here](https://github.com/projetsdiy/Fast-ESP8266-HTML-JS-development-with-Nodejs-Pug).

Node.js is a popular cross-platform [Open Source project](https://nodejs.org/en/) (system independent). Originally designed to develop websites, Nodejs is now used to make applications for smartphones and tablets ([Meteorjs](https://www.meteor.com/), [ionicframework](https://ionicframework.com/), [phonegap](http://phonegap.com/)). It is possible to "transform" the site into application. This is the case, for example, of the [Atom text editor](https://atom.io/) developed by GitHub. And if you use Node-RED, this is the engine of this project for IBM IoT. We will stop there on Node.js for this time, we will have the opportunity to use it in many projects in the future.

The first thing to do is to install Node.js on your computer. Before you start, it is best to check that Node.js is not already installed on your machine. So definitely the case if you use Raspbian. Open the Terminal or PowerShell on Windows and run this command

If you do not get any results, go to the official Nodejs website to retrieve the version that corresponds to your system. It is preferable to install the stable version (LTS) to avoid edge effects of the version being developed.

![nodejs download macos windows linux arm](https://www.projetsdiy.fr/wp-content/uploads/2017/01/nodejs-download-macos-windows-linux-arm-.jpg)

On macOS, it is preferable to install Node.js using the Homebrew package manager ([the official page of the project](http://brew.sh/index_fr.html)). Homebrew manages to declare paths. It is also easier to uninstall (cleanly) Node.js and npm (the associated package manager) with the brew uninstall node command

![node-red mongodb brew](https://www.projetsdiy.fr/wp-content/uploads/2016/11/node-red-mongodb-brew-.png)

Open a Terminal and paste this command

Answer the questions to complete the installation of Homebrew on your Mac. Once the installation of Homebrew is complete, you can install Node.js by executing the command

Node.js is also available for ARM v6, v7 and v8 platforms. The archive is directly recoverable for download but the simplest remains to go through the Terminal. We start by adding the Nodejs sources to the system's repository manager. Complete the order according to the desired version.

For version 7.x under development

For the stable version

Now, a simple apt-get command to install Node.js on your Raspberry Pi for example.

Nodejs has its own shell that is simply launched with the node command in the Terminal. If everything is correctly installed, you will get the prompt (>). Make a small addition. To exit the shell, type** .exit**

We start a Web server in a few lines with Node.js. Here, we will use express.js which is a framework simplifying the management of the roads (and accelerates the rendering of the pages, but it's accessory here). We use npm to install new package.

To make HTTP requests and retrieve actual data on the ESP8266, we will need the package request

It would be a shame to generate the HTML files after each change. To use the Pug files, you have to do 2 things:

  * Create a folder views in the project's data folder. Then move all your pug files inside. It is possible to keep the tree (but I have not tested)
  * Specify that the **view engine** will be **pug**.

Here is the code of the server which will enable us to test in local the HTML interface of our projects ESP8266. It takes only 7 lines of code to run the interface

123456789101112 
var express = require('express');var app = express();// Cree directement les pages HTML a partir de templates pug app.set('views', './views');app.set('view engine', 'pug');app.get('/', function(req, res) {res.render('index')});app.listen(8080);

Save the file as server.js and run the server with the node server.js command from the Terminal (without forgetting to place it in the project directory). Open a browser and type localhost: 8080 in the address bar. And here you can now develop your interfaces and javascript code much faster on your own computer!

![nodejs esp8266 webserveur fast development](https://www.projetsdiy.fr/wp-content/uploads/2017/01/nodejs-esp8266-webserveur-fast-development.jpg)

If your project contains resources, such as a folder with images, you must make them accessible to the web browser. To do this, you must create a public folder in which you will have to move the resources (images among others). Then we tell express.js to make public resources available to the Web client.

The modified project tree.

![](https://www.projetsdiy.fr/wp-content/uploads/2017/01/nodejs-esp8266-web-seveur-project-folder-structure.png)

You have noticed that it is necessary to restart the server after each modification (scripts js, templates pug …). We will therefore automate the restart of the Web server after each modification. For this, there is the **nodemon** plugin that requires very little configuration. This avoids installing and configuring a task manager like Grunt or Gulp, oversized in this case!

Now, you run the server using the nodemon server.js command. There are [many parameters](https://github.com/remy/nodemon) available that can be put in a small configuration file that should be named **nodemon.json** and place it on the same level as the server.js file. In the **watch** section, the directories to be monitored are indicated. The **ext** key is used to indicate extensions of the files to be monitored.

12345678910111213141516 
{"restartable": "rs","ignore": [".git","node_modules/**/node_modules"],"verbose": true,"execMap": {"js": "node --harmony"},"watch": ["views",""],"ext": "js json pug"}

Now we start the server with the command nodemon server.js . We can see here that there are 2 files monitored. Note that the server was automatically restarted after a modification of the index.pug file. It is also possible to restart the web server at any time by entering **rs**.

> Note. Nodemon does not refresh the page on the browser (no Livereload), it must be done manually

123456789101112131415161718 
$ nodemon server.js[nodemon] 1.11.0[nodemon] reading config /Volumes/Macintosh HD/Users/christophe/DHT22WebserverESP8266_SPIFFS_Tuto3/data/nodemon.json[nodemon] to restart at any time, enter `rs`[nodemon] ignoring: .git .nyc_output .sass-cache bower_components coverage node_modules .git node_modules/**/node_modules[nodemon] watching: /Volumes/Macintosh HD/Users/christophe/DHT22WebserverESP8266_SPIFFS_Tuto3/data/views/**/*[nodemon] watching extensions: js,json,pug[nodemon] starting `node --harmony server.js`[nodemon] child pid: 10892[nodemon] watching 2 files[nodemon] files triggering change check: views/index.pug[nodemon] matched rule: **/Volumes/Macintosh HD/Users/christophe/DHT22WebserverESP8266_SPIFFS_Tuto3/data/views/**/*[nodemon] changes after filters (before/after): 1/1[nodemon] restarting due to changes...[nodemon] views/index.pug[nodemon] starting `node --harmony server.js`[nodemon] child pid: 10902

It is much easier to develop and set up interfaces when a dataset is available. We will therefore answer the calls of the interface and return data. That's how I developed the integration of Google Charts.

With express.js, you retrieve a call on a route using the function **app.use('/route', function (req, res, next) {})**. For example, here we intercept a request for data on the route /mesures.json.

We will try to retrieve actual measurements on the ESP8266, and if the ESP8266 did not respond within 2 seconds (timeout: 2000),

It will suffice to test the response or catch an error to return the data from the ESP8266 or a test set if the ESP8266 did not respond to our request. The response of the ESP8266 is contained in the body

1234567 
if (!error && response.statusCode == 200) {console.log("Mesures receptionnees depuis ESP8666" \+ body)res.send(body);} else {console.log("ESP8666 muet, envoi du jeu de donnees test")res.send({"t":"21.70","h":"29.50","pa":"984.43"});}

Which gives once assembled

1234567891011 
app.use('/mesures.json', function (req, res, next) {request({url: baseUrl + '/mesures.json',timeout:2000}, function (error, response, body) {if (!error && response.statusCode == 200) {console.log("Mesures receptionnees depuis ESP8666" \+ body)res.send(body);} else {console.log("ESP8666 muet, envoi du jeu de donnees test")res.send({"t":"21.70","h":"29.50","pa":"984.43"});}})});

For the GPIO, it's a bit more complicated. Remember, you can easily decode a query in which the data is passed in parameters in the url. For example, http://192.168.1.21/gpio&id=D7&etat=1 . Side Node.js, we'll have to build the query that goes well. We will use the request function but this time we will not pass to him a series of options that will allow him to construct the URL

12345678910 
var options = {url: baseUrl + "/gpio",method: 'GET',headers: {'User-Agent': 'Super Agent/0.0.1','Content-Type': 'application/x-www-form-urlencoded'},qs: {'id': req.param.('id'), 'etat': req.param('etat')},timeout:2000}

The value of each parameter is retrieved using the function **req.param('param')**. All that remains is to interrogate the ESP8266 and return the answer or a test set if it remains silent after 2 seconds.

123456789 
request(options, function (error, response, body) {if (!error && response.statusCode == 200) {console.log("Retour GPIO ESP8266 : " \+ body);res.send(body);} else {console.log("ESP8666 muet, envoi du jeu de donnees test")res.send({id:req.param('id'), etat: req.param('etat'), success:'1'});}};

Here is the complete code of the server that you can adapt to your needs. It is also present in the GitHub repositories of the Web Server project ESP8266.

Now, if an ESP8266 is connected to the network, you are able to retrieve data to easily develop your project. Messages sent to the Terminal using the console.log () command make it easier to focus more.

![nodejs esp8266 donnees reelles](https://www.projetsdiy.fr/wp-content/uploads/2017/01/nodejs-esp8266-donnees-reelles.jpg)

So, you can now develop your HTML interfaces and javascript code much faster for your ESP8266 projects. This is an accelerated tutorial. We will return in more detail to the different technologies discussed here in future tutorials.

```
/*
*   Serveur de développement rapide d'interfaces Web pour projets ESP8266
*   Fast development Web Server for ESP8266 projects
*   http://www.projetsdiy.fr - 2017
*/
var express = require('express');
var request = require('request');

// Sert les fichiers publics (css, img) - Serve public files
var app = express();
var baseUrl = "http://192.168.1.22";

// Créé directement les pages HTML à partir de templates pug 
app.set('views', './views');
app.set('view engine', 'pug');

app.use(express.static('public'));
app.use('/static', express.static(__dirname + '/public'));

app.get('/', function(req, res) {
  res.render('index')
});

app.use('/mesures.json', function (req, res, next) {
  request({url: baseUrl + '/mesures.json',timeout:2000}, function (error, response, body) {
    if (!error && response.statusCode == 200) {
      console.log("Mesures receptionnées depuis ESP8666" + body) 
      res.send(body);
    } else {
      console.log("ESP8666 muet, envoi du jeu de données test")
      res.send({"t":"21.70","h":"29.50","pa":"984.43"});
    }
  })
});

app.use('/tabmesures.json', function (req, res, next) {
  request({url: baseUrl + '/tabmesures.json',timeout:2000}, function (error, response, body) {
    if (!error && response.statusCode == 200) {
      console.log("tabmesures receptionnées depuis l'ESP8666" + body) 
      res.send(body);
    } else {
      console.log("ESP8666 muet, envoi du jeu de données test")
      res.send([{"mesure":"Température","valeur":"21.60","unite":"°C","glyph":"glyphicon-indent-left","precedente":"19.80"},{"mesure":"Humidité","valeur":"29.80","unite":"%","glyph":"glyphicon-tint","precedente":"30.40"},{"mesure":"Pression Atmosphérique","valeur":"984.51","unite":"mbar","glyph":"glyphicon-dashboard","precedente":"984.74"}]);
    }
  })
});

app.use('/graph_temp.json', function (req, res, next) {
  request({url: baseUrl + '/graph_temp.json',timeout:2000}, function (error, response, body) {
    if (!error && response.statusCode == 200) {
      console.log("Graph receptionnées depuis l'ESP8666" + body) // Show the HTML for the Google homepage.
      res.send(body);
    } else {
      console.log("ESP8666 muet, envoi du jeu de données test")
      res.send({"timestamp":[1485273937,1485273938,1485273939,1485273940,1485273941,1485273942,1485273943,1485273944,1485273945,1485273946,1485273947,1485273948,1485273949,1485273950],"t":[23.3,23.3,23.3,23.3,23.3,23.3,23.3,23.3,23.3,23.3,23.3,23.3,23.3,23.3],"h":[35.6,35.6,35.6,35.6,35.6,35.5,35.5,35.4,35.4,35.5,35.5,35.5,35.5,35.5],"pa":[987.7,987.7,987.7,987.8,987.7,987.7,987.7,987.7,987.7,987.8,987.7,987.7,987.7,987.7],"bart":[23.30,23.30,23.30,23.30,23.30,23.30,23.30],"barh":[35.60,35.60,35.50,35.40,35.50,35.50,35.50]});
    }
  })
});

app.use('/gpio', function (req, res, next) {
	var options = {
      url: baseUrl + "/gpio",
      method: 'GET',
      headers: {
    	  'User-Agent':       'Super Agent/0.0.1',
    	  'Content-Type':     'application/x-www-form-urlencoded'
	    },
      qs: {'id': req.param('id'), 'etat': req.param('etat')},
      timeout:2000
    }

	//_url = baseUrl + "/gpio&id=" + req.param('id') + "&etat="+ req.param('etat');
	//console.log(_url);
	request(options, function (error, response, body) {
    if (!error && response.statusCode == 200) {  
      console.log("Retour GPIO ESP8266 : " + body);
      res.send(body);
    } else {
      console.log("ESP8666 muet, envoi du jeu de données test")
      res.send({id:req.param('id'), etat: req.param('etat'), success:1});
    }  
	});
})

app.listen(8080);
```

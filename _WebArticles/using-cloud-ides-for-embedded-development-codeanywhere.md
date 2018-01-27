# Using Cloud IDEs for Embedded Development: CodeAnywhere

_Captured: 2017-12-04 at 21:58 from [www.thingforward.io](http://www.thingforward.io/techblog/2017-12-01-using-cloud-ides-for-embedded-development-codeanywhere.html)_

[Lately](http://www.thingforward.io/techblog/2017-11-17-cloud-services-for-embedded-agile-development.html) we have been looking at cloud services for software development. Regarding developing web applications, using cloud services for various aspect of the software development process is nothing really new. But we're also interested in IoT and Embedded Development, so we like to find out if that's doable as well.

Developing for Embedded Boards is highly dependent on the board's toolchain: cross compiler, flash tools, debugger etc. The majority of these tools work locally, because of the board connected locally via USB oder some form of debug/flash adapters (i.e. J-Link). How should that work out with a remote cloud service?

From our former embedded testing blogposts, you are now familiar with [PlatformIO](http://platformio.org) and its powerful features like unit testing, remote controlling and continuous integration. As you can recall, with PIO Remote, you can flash firmware and reach monitor serial output from remote network locations. So that's the exact functionality we need here, connect the firmware building and flashing process between a remote Cloud IDE and a local installation.

Today we will learn how to implement our existing Git projects to the cloud IDE's and carry out PIO run-remote upload-remote test functions. Thanks to Cloud IDE's, you can share and collaborate your projects on cloud and make pair programming easier. These projects are always reachable via their URL's from everywhere you have internet! No need to say, but of course it is possible to connect your Git, GitHub, Bitbucket accounts. There are several cloud IDE solutions on the market and they are nearly the same. According to your necessity and expectations, you can select some of them. Today, we'll be looking at CodeAnywhere. The physical setup that we been using consist on our local computer, RPi and a NodeMCU that is connected to the RPi via USB Port.

Let's start!

### Codeanywhere

[CodeAnywhere](https://codeanywhere.com/) is a Cloud IDE solution with a lot of features. Fully customisable container on Codeanywhere allows us to select special development stacks. You can also download Codeanywhere application to your mobile platform, in case you prefer working on mobile/tablet. Please type following command on RPi side. In order to use PIO features like testing and remote, you should login with your PIO account. If you still don't have a free PIO account, you need to get one from: <http://platformio.org/get-started>.
    
    
    $ pio account login
    <Your eMail address and Password>
    Successfully logged in.

Please plug your NodeMCU to the RPi and find its port by typing:
    
    
    $ pio device list
    /dev/cu.thingforwardiot-Bluetoo
    -------------------------------
    Hardware ID: n/a
    Description: n/a
    /dev/cu.SLAB_USBtoUART
    ----------------------
    Hardware ID: USB VID:PID=10C4:EA60 SER=0001 LOCATION=20-1
    Description: CP2102 USB to UART Bridge Controller - CP2102 USB to UART Bridge Controller

Save the name of port name of NodeMCU on RPi: "/dev/cu.SLAB_USBtoUART". We will use this later*. After that start the remote agent - our RPi- by typing:
    
    
    $ pio remote agent start

Now, let us move on to local computer side. The first thing to do is registration! Go to <https://codeanywhere.com> and become a member. It is free and takes only 1-2 minutes to register. After the registration, please login and open the editor. Type your project name and select Python for Ubuntu 14.04, which is necessary for PlatformIO, on the screen that you will see:

![Image 1: Codeanywhere Project Wizard](http://www.thingforward.io/fileadmin/user_upload/bp10/1.png)

> _After creating this project, right click on project and open SSH Terminal:_

![Image 2: Codeanywhere SSH Terminal](http://www.thingforward.io/fileadmin/user_upload/bp10/2.png)

In a terminal, we will clone our template testing repository from GitHub. To do so,copy and paste following commands:
    
    
    $ git clone --branch blogpost2 https://github.com/thingforward/unit-testing-with-platformio.git 
    $ cd unit-testing-with-platformio/

If you cannot see the project on project explorer, click on your project called "Test_Project" and click on "Refresh". Install the PlatformIO toolchain by typing:
    
    
    $ sudo python -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/develop/scripts/get-platformio.py)"

Define the "upload_port" in platformio.ini, which we already have have*:

![Image 3: Codeanywhere Upload Port Settings](http://www.thingforward.io/fileadmin/user_upload/bp10/3.png)

> _Login to your PIO account and run the project locally:_
    
    
    $ pio account login
    $ pio run

![Image 4: Codeanywhere Run Command](http://www.thingforward.io/fileadmin/user_upload/bp10/4.png)

> _You can also execute "pio run" command by specialising built-in Run function of IDE. To do so:_

  * Right click on "Test_Project" and choose "Config"
  * Set commands field to ` "commands": [ "cd unit-testing-with-platformio && pio run" ]`
![Image 5: Codeanywhere Built-in Configurations](http://www.thingforward.io/fileadmin/user_upload/bp10/10.png)

> _Now you can use Run button (it's the solid triangle) to run your project locally:_

After the local run, now it is time to try remote functions. First, let's see our working remote agent by typing:
    
    
    $ pio remote agent list
    PlatformIO Plus (https://pioplus.com) v0.10.14
    CC-C02SG159FVH6.local
    ---------------------
    ID: 12xxd5kf3e8xx40d789716bxx9251xx2
    Started: 2017-11-13 13:45:19

Let's execute the remote upload and open remote device monitor:
    
    
    $ pio remote run -t upload -e nodemcuv2 
    $ pio remote device monitor
    PlatformIO Plus (https://pioplus.com) v0.10.14
    Starting Serial Monitor on CC-C02SG159FVH6.local:/dev/cu.SLAB_USBtoUART
    --- Miniterm on socket://localhost:53132 9600,8,N,1 ---
    --- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---

![Image 6: Codeanywhere Remote Upload](http://www.thingforward.io/fileadmin/user_upload/bp10/11.png)

> _Finally the remote test function will be executed:_
    
    
    $ pio remote test -e nodemcuv2

Here is the result:

![Image 7: Codeanywhere Remote Upload](http://www.thingforward.io/fileadmin/user_upload/bp10/12.png)

> _Every remote upload and test commands can be traced on RPi, our remote agent:_

![Image 8: Codeanywhere Remote Agent](http://www.thingforward.io/fileadmin/user_upload/bp10/13.png)

So much about CodeAnywhere! Thanks to PlatformIO, the embedded projects can be uploaded and tested locally or remotely in very understandable ways. By combining a Cloud IDE and PlatformIO features, developing for "things" becomes easier. At the upcoming post, we'll be taking an additional look at CodeEnvy, also known as Eclipse Che!

Eren

Andreas

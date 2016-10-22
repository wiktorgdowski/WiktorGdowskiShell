#WiktorGdowskiShell
A specific purpose command shell to run on a Linux system. The purpose of the shell is to present a limited set of functionality to a Linux system user, such that they can examine and set a limited selection of network related settings on Linux.

###External Commands:
The shell allows the user to run two external commands: pwd and ifconfig. In the case of pwd, the abbreviation pw is being used to run pwd. no command-tail is required. In the case of ifconfig, the abbrevation ifc should be used to run ipconfig. The default behavior of ifc should be used to run ifc is to display the settings for the first interface, e.g. eth0. No command tail is required.

###Internal Commands:
The shell allows the user to run two internal commands: dt and ud. In the case of dt, the internal command displays the current date and time on the system without using an external command. The following format is used: date +%Y%m%d%H%M%S i.e. 20130926215222. In the case of ud, the internal command displays the following users details without using an external command. The following format is used: userID, groupID, username, groupname, iNode of user’s home directory i.e. 501,20,briankeegan,staff,335665

###Extra Functionality:
The shell allows the user to run a help command. User can type in help to display functionality of all internal and external commands.

###How to run
In order to run this shell as a standard application from within an existing command-shell on a Linux system a user must first install C on his machine using:<br />
**_sudo apt-get install build-essential_**<br />
This command installs C, C++, Python compilers and all their libraries. To compile the code, user must first navigate to the directory in which it is stored. Once in a proper directory wgsh.c can be compiled using:<br />
**_gcc wgsh.c -o wgsh_**<br />
and run using:<br />
**_./wghs_**<br />
To create a new user:<br />
**_sudo adduser testuser_**<br />
User then has to type in his own password and then pick a password for the new user. To set wgsh as a default login shell for an account on the system, the program must be first moved into /usr/bin:<br />
**_sudo cp wgsh /usr/bin_**<br />
To set this shell as a default shell to the new user:<br />
**_sudo chsh -s /usr/bin/wgsh testuser_**<br />
Now, everytime we log in as a testuser:<br />
**_su testuser_**<br />
The custom shell will be initiated. To exit:<br />
**_exit_**<br />

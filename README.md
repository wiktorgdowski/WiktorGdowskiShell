# WiktorGdowskiShell
A specific purpose shell command shell to ron on a Linux system. The purpose of the shell is to present a limited set of functionality to
a Linux system user, such that they can examine and set a limited selection of network related settings on Linux.

# External Commands:
The shell allows the user to run two external commands: pwd and ifconfig. In the case of pwd, the abbreviation pw is being used to run
pwd. no command-tail is required. In the case of ifconfig, the abbrevation ifc should be used to run ipconfig. The default behavior of ifc
should be used to run ifc is to display the settings for the first interface, e.g. eth0. No command tail is required.

# Internal Commands:
The shell allows the user to run two internal commands: dt and ud. In the case of dt, the internal command displays the current date and
time on the system without using an external command. The following format is used: date +%Y%m%d%H%M%S i.e. 20130926215222.
In the case of ud, the internal command displays the following users details without using an external command. The following format is
used: userID, groupID, username, groupname, iNode of user’s home directory i.e. 501,20,briankeegan,staff,335665

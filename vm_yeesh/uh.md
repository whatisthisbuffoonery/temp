*This project has been created as part of the 42 curriculum by dthoo*
  
## Born2BeRoot  
  
### Description  
  
Goal: install linux (wooo scary) on a vm:  
	- partition it  
	- set the hostname correctly  
	- install a firewall, and leave only port 4242 open  
	- not allow root ssh  
	- make a user with my login "dthoo" as its name  
	- set a strong "password policy"  
		-	implement password expiry and a warning for it too  
		-	min length 10, alphanumeric, lower and uppercase  
		-	cannot contain username  
		-	cannot have 3 identical characters in a row  
		-	root and user password obey the above rules  
		-	user password cannot have less than 7 characters different from the password before changing  
	- install and configure sudo with strict rules  
		-	3 attempts to authenticate  
		-	custom error message on wrong password  
		-	log all sudo actions in folder var/log/sudo, including input and output  
		-	tty mode enabled  
		-	"restrict" paths used by sudo  
			-		(TBA)  
	- make a script that shows info \(check the pdf\)  
		-	on all terminals:  
			-		on startup  
			-		every 10 minutes  
	- partition even more drives and make a working ftp service if bonus is concerned  
		- leave moe ssh ports open in that case
  
Also part of my goal: learn stuff and explain/do:  
	- interrupt the info script using cron...?  
	- what SELinux and Apparmor is  
	- test ssh setup by making a new user during eval  
		-	and assign it to a group  
	- explain below:  
		-	design choices????  
			-		openssh vs dropbear, try dropbear  
		-	debian vs rocky  
		-	apparmor vs selinux  
		-	ufw vs firewalld  
			-		pls go look up firewalld syntax  
		-	virtualbox oracle vs utm  
  
### Resources  
  
initial partition section, and helpful commands:  
`https://github.com/Vikingu-del/Born2beRoot?tab=readme-ov-file`  
  
sshd\_config: \(aka man 5 sshd\_config\)  
`https://man7.org/linux/man-pages/man5/sshd_config.5.html`
### command list  
  
lsblk  
sudo reboot  
sudo adduser  
sudo addgroup  
getent group user42  
sudo adduser user group  
  
`/etc/ssh/ssh_config`   system wide client config  
  
`/etc/ssh/sshd_config`  server conf  
^after changing, sudo service ssh restart  
sudo service ssh status  
  
sudo ufw enable  
sudo ufw allow 4242  
sudo ufw status  
  
sudo configs:  `prefix Defaults`
	- secure\_path="...": people like to change their $PATH var to look for a trojan ls binary  
	so, we 'restrict' what paths sudo can take to find binaries  
### Informal rant  
  
The project description is further down, I will just document my insanity here  
  
The abovementioned github link is basically an answer sheet, but I do see a lot of  
server projects around campus, I will try to see what feels more natural instead.  
  
To do it the way listed in the guide, you would have to do a manual install by:  
	- not providing a .iso file before hitting finish  
	- or, checking the 'skip unattended install' option  
I have elected to do neither \(thanks for bringing me exactly this far akaung\),  
and have instead had to go into options > system > boot order to load the optical drive first  
	- of course I then have to load the iso into the optical, which it still isnt for some reason:  
		-	storage > empty > blue icon all the way to the right  
	- and I just know I will forget to unset it later  
	- I could actually hit f12 and select CD, that worked  
I sure hope that blank domain name doesnt backstab me later  
  
I read up to the start of partitioning and I will actually try to copy less now lmao  
  
sda1 says its mounted in boot so we will do that  
  
Q: why do we choose beginning for the boot sector?  
A: because why not. starting from the end is for:  
	- leaving prefix growth space for lvm  
	- squeezing in backup drives or a second OS that the bootloader can see  
  
BOY i SURE HOPE ALL THESE LINK TO SDA AND NOT SDB  
  
from the answer sheet:  
```
- Primary: The only partition on which an OS can be installed. There can only be 4 primary partitions per hard drive or 3 primary and one extended.

- Secondary/Extended: It was designed to break the limitation of 4 primary partitions on a single physical disk. There can only be one partition of this type per disk, and it is only used to contain logical partitions.

- Logical: Occupies a portion of the extended/primary partition or its entirety, which has been formatted with a specific type of file system (in our case we will use ext4) and a drive has been assigned to it, thus the system The operating system recognizes the logical partitions or their file system. There can be a maximum of 23 logical partitions in an extended partition, however, Linux, the OS we currently work with, reduces this to 15, more than enough to carry out this project.
```  
  
Q: why partition? why not folders?	
A: because they can span multiple physical storage devices, and host their own filesystems  
  
Q: wait why did the answer sheet skip sda2?  
  
Q: why no mount sda5?  
A: an lvg partition is not a filesystem. it hosts filesystems  
  
Q: why is var--log named var-log instead?  
A: ion know I renamed it to double dashes, it even shows the list command being lsblk  
A: update it made four dashes ajklhdfhfsgjfgjkl  
  
my current sizes for the folders are:  
	- root, 2gb  
	- var, 1gb  
	- var log, 500m  
	- everything else 100m  
  
Q: why does sda2 appear out of nowhere?  
A: its an extended partition to manage lvg sda5  
  
OH LOOK a technical choice, the sudo logfile in var/log is named sudo\_log and not sudo\_config  
  
Q: whats requiretty?  
A: sudo requires user terminal, and refuses scripts, cron jobs, and ... CGI?? `90s common gateway interface for web stuff, like js`
  
Q: so can I use root over ssh?  
A: yes, but not by `ssh root@localhost`, I have to su through regular user. this prevents some brute force attacks  
	- scripts trying to su will bring up interactive password input  
  
Q: what do logs do?  
A: logfile gets readable metadata, log input gets keystrokes, log output stores output to later display with journalctl, and iolog\_dir formats stuff to have shell replay  
  
password expiry and strength policies in /etc/login.defs  
package just has to be libpam pwquality  
/etc/pam.d is modern config, pam.config is legacy  
	- pam.d has several config files, legacy has one. we use common-password  
  
Q: why count lines for cpu/virtual cpu count?  
A: because the other fields are for each core, which is different. so the /prod/cpuinfo file will have several of the same fields  
  
Q: did you learn shell syntax?  
A: kind of, I learnt grep, refreshed awk, learnt regular print, 
  
Q: no delay on vmstat?  
A: it helps for acuracy, but my display is left sitting half done for a few seconds. so I didnt do that  
  
### config files

wordpress: inside /var/html
sudo: inside /etc/sudoers.d/sudo\_config
passwd: /etc/login.defs and /etc/pam.d/common-password
ssh: /etc/ssh/ssh\_config, sshd\_config
crontab: crontab -e


### SSH  
  
the vm has to be running when you poke it from host os, do `ssh dthoo@localhost -p 4242`  

### wordpress

it sits in /var/www/ ,some folder renaming shenanigans, 

### php fpm

not too much work



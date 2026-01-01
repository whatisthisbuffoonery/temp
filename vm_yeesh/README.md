*This project has been created as part of the 42 curriculum by dthoo*  
  
## Born2beroot  
  
### Description  
  
Goal: make a debain server with no gui and put some services on it  
Said services are a wordpress website and a ip banning system  
  
### Instructions  
  
Just open up oracle VM and start the vm  
  
### Resources  
  
Disk partitioning and starting me off on getting more commands in the terminal: (https://github.com/Vikingu-del/Born2beRoot?tab=readme-ov-file)  
  
Incredibly simplified ssh, ufw, sudo log file, crontab, and mariadb configs: also that github link above  
  
Password policy editing: (https://www.debian.org/doc/manuals/securing-debian-manual/ch04s11.en.html)  
  
monitoring script commands: syntax checking done by perplexity  
  
wordpress installation: seriously I would not have thought of the process turning out the way it did \(unzipping a download in /var/www/, really\): github link.  
  
php\-\(fpm\): online resources are flooded with nginx rig guides, perplexity helped for this one  
  
fail2ban: (https://www.digitalocean.com/community/tutorials/how-to-protect-ssh-with-fail2ban-on-ubuntu-20-03)  
  
wordpress hardening: perplexity  
  
### Project description  
  
Rocky is a free OS suited for using packages that are more suited for enterprises.  
Seeing as there are a number of reddit and personal blogs whining about the OS \(not listed\), I am going with debian instead.  
Less steps overall, not as much of the red hat ecosystem that... I do not understand well anyway.  
  
#### Actual configs done  
  
Partitioning: extra space given to /root and /var to install stuff \(and because it kept complaining\), 5gb total  
  
Security policies:  
	- sudo  
		-	paths restricted to prevent accidentally using a trojan binary in place of a system binary  
		-	log file placed in var/log/sudo  
		-	no sudo actions outside of tty allowed  
		-	password policies done using passwd-quality:  
			-		password expiry after 30 days  
			-		expiry warning 7 days before  
			-		minimum 2 days before allowed password change  
			-		minimum 7 different chars from previous password  
			-		minimum password length at 10 chars  
			-		using username in password is disallowed  
			-		3 same characters in a row disallowed  
			-		the above applies to root password as well  
			-		3 attempts allowed  
	- ufw: ports 4242 and 80 opened for ssh and tcp respectively, ports are closed by default  
	- apparmor: running at startup, but I seriously did not use it  
  
User management:  
	- dthoo in user42 and sudo groups  
  
services installed:  
	- sudo takes the cake tbh  
	- lighttpd  
	- wordpress  
	- fail2ban  
	- passwd-quality  
	- openssh-server  
	- mariadb-server  
	- ufw  
	- cron  
  
#### Comparisons  
  
Debian vs Rocky: see above  
  
AppArmor vs SELinux: apparmor uses paths to determine permissions, more simple. selinux has finer, more complex permissions controls.  
  
UFW vs firewalld: UFW needs to be reloaded after changes, simpler to use. firewalld does not, has more feature but is more complex.  
  
VirtualBox vs UTM: VirtualBox has more features and wider OS support, UTM runs better on apple silicon cpus  

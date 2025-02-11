# tcpconnectscanner
This program scans the a range of ports on a host. Checks if they are open or not.
This programs completes the threeway handshake to ports but they closes the connection. 
This is not a really good way to scan has most computers tend to log or keep track of these things. 


gcc -g connectscanner.c



sudo ./a.out first_port last_port ipaddress


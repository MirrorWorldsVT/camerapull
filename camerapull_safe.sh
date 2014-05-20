#/bin/bash


#you must change the username and password below before this will work
while :
do
 for IP in 192.168.1.10 192.168.1.11 192.168.1.13 192.168.1.15
  do
    curl -u username:password $IP/snapshot.cgi > camera.$IP.$(date +%Y-%m-%d_%H:%M:%S:%2N).jpg & 
 done
 wait
sleep .5
done


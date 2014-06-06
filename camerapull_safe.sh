#you must change the username and password below before this will work
while :
do
 for IP in 192.168.1.10 192.168.1.11 192.168.1.13 192.168.1.15
  do
    curl --silent -u user:password $IP/snapshot.cgi >camera.$IP.$(date +%Y-%m-%d_%H:%M:%S:%2N).jpg &
    #curl --silent -u user:password $IP/snapshot.cgi >/dev/null &
    #echo "$IP  $(date +%Y-%m-%d_%H:%M:%S:%2N)" >> timestamps
    #this code will test how fast we can pull images without disk IO overhead.  
  done
 wait
#sleep .25
done

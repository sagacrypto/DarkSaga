# Linux Build Instructions

## Dependencies  
    sudo apt-get update && apt-get upgrade  
    sudo apt-get dist-upgrade  
    sudo apt-get install libzmq3-dev libminiupnpc-dev libssl-dev libevent-dev -y  
    sudo apt-get install build-essential libtool autotools-dev automake pkg-config -y  
    sudo apt-get install libssl-dev libevent-dev bsdmainutils   software-properties-common -y  
    sudo apt-get install libboost-all-dev -y  
    sudo add-apt-repository ppa:bitcoin/bitcoin  
    sudo apt-get update  
    sudo apt-get install libdb4.8-dev libdb4.8++-dev  -y  
    sudo apt-get install libgmp3-dev 
	sudo apt-get install libdb5.3++ unzip libzmq5 -y
	
#### Firewall 
    sudo ufw limit ssh/tcp  
    sudo ufw allow 62620/tcp  
    sudo ufw enable  

#### Swapfile
    fallocate -l 4G /swapfile  
    chown root:root /swapfile  
    chmod 0600 /swapfile  
    sudo bash -c "echo 'vm.swappiness = 10' >> /etc/sysctl.conf"  
    mkswap /swapfile  
    swapon /swapfile    
    echo '/swapfile none swap sw 0 0' >> /etc/fstab 
	
#####  Restart the system
    sudo reboot
	
#####  Download Source code
    sudo git clone https://github.com/sagacrypto/DarkSaga.git
	
### Compiling  
    cd DarkSaga/src/leveldb  
    chmod +x build_detect_platform  
    make clean  
    make libleveldb.a libmemenv.a  
    cd ../  
    make -f makefile.unix  
 
##### Edit the config file  
    nano ~/.darksaga/darksaga.conf  

		rpcuser=username(Configure your own)  
		rpcpassword=password(Configure your own)  
		rpcallowip=127.0.0.1  
		rpcport=62720  
		daemon=1  
		server=1  
		listen=1  
		logtimestamps=1  
		maxconnections=256  
    
	For masternodes, also add:
	
		masternode=1  
		masternodeprivkey=your private key
		masternodeaddr=your VPS IP:62620
		
#### Usage  
Start daemon

	./darksagad  

Stop daemon 

	./darksagad stop  

Display information  

	./darksagad help
	./darksagad getinfo  
	./darksagad getmininginfo  
	./darksagad getblockcount  
	./darksagad masternode status  
	./darksagad masternode list  
___

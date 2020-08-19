# Masternode Setup Guide

### 1. Requirements
* 2500 SAGA  
* VPS server
	* [Vultr](https://www.vultr.com/?ref=7684542)
	* [Digital Ocean](https://m.do.co/c/917baa6de4c8)
* SSH client ([Bitvise](https://www.bitvise.com/) for windows)
* Text Editor (e.g. Notepad)
___
### 2. Local wallet setup part 1 of 2  
Download latest wallet: [GitHub](https://github.com/sagacrypto/DarkSaga/releases)  

Open the wallet

 *Note: If you're setting up using an Ubuntu desktop wallet and you do not see the File, Settings, or Help wallet menu options then you must uninstall apppmenu-qt5 from your system (Terminal> sudo apt-get remove appmenu-qt5)*

Go to the `Receive` tab

![walletsetup1](https://raw.githubusercontent.com/sagacrypto/DarkSaga/master/Images/Receive.PNG	)

Click `New Address` and enter a Masternode Address name (e.g. MN01) and click `OK` *(do not check `Stealth Address`)*  

![walletsetup2](https://raw.githubusercontent.com/sagacrypto/DarkSaga/master/Images/New%20Address.png)

Select the Masternode Address and click `Copy Address`. Paste the address in a text editor  

Click `New Address` again and enter a label for your Reward Address (e.g. Rewards1) and click `OK` *(do not check `Stealth Address`)*  

Select the Reward Address and click `Copy Address`. Paste the address in a text editor

Go to the `Send` tab

![walletsetup2](https://raw.githubusercontent.com/sagacrypto/DarkSaga/master/Images/Send.png)

*Use "Coin Control" to select your collateral. If Coin Control is not visible, enable by navigating to menu >Options>Display*

Paste the address on the `Pay To` box and enter 2500 in the `Amount` box  

*Note : You must be sent exactly 2500 SAGA in a single transaction*  

Click `Send` *(do not check `Darksend`)*

Go to `Help` > `Debug window`  

Open `Console`and type `masternode genkey`

![walletsetup6](https://raw.githubusercontent.com/sagacrypto/DarkSaga/master/Images/genkey.PNG)

Copy the key and paste the masternode genkey (also referred later as a "PrivKey" or "Masternode Private Key") into your text editor  

Wait for 10 confirmations (Go to the next step while waiting)
___
### 3. Setup VPS   
Login to your VPS ([Vultr](https://www.vultr.com/?ref=7684542) or [Digital Ocean](https://m.do.co/c/917baa6de4c8)) using your SSH client
Deploy a new instance *(1GB RAM  VPS Recommended)*

Login to your instance using your SSH Client

#### 3-1. Installation  

Paste the applicable command below into your terminal to run the automated masternode installation script.
*these scripts automatically install the daemon and a bootstrap; therefore, they will take some time to run. Please be patient.*

Ubuntu 16.04 VPS:
```
wget -q https://github.com/sagacrypto/DarkSaga/releases/download/3.01/masternode1604.sh
bash masternode1604.sh
```  

Ubuntu 18.04 VPS:
```
wget -q https://github.com/sagacrypto/DarkSaga/releases/download/3.01/masternode1804.sh
bash masternode1804.sh
```  
Paste your masternode genkey when prompted
___
### 4. Setup local wallet part 2 of 2  

After 15 confirmations type `masternode outputs` in the `Debug window`

![outputs1](https://raw.githubusercontent.com/sagacrypto/DarkSaga/master/Images/genkey.PNG)  

Copy the TxHash and output index number and paste it into your text editor

*the "Output Index" number is after the collateral tx and is either a "1" or "0"*
___
### 5. Create the Masternode  
Go to the `Masternodes` tab

Click the `Create...` button

Fill in the form using the information recorded in your text editor from previous steps

Click `OK`  

Click `Update`  

Select your masternode
Click `Start`  

*Note: If you receive an error such as "Could not allocate VIN", unlock your wallet and click `Start` again.*
*If the error reoccurs then you may need to reinstall your VPS, remove the masternode (see below) from your masternode.conf file, and begin the setup from the beginning*

The above steps will create a 'masternode.conf' file in your %appdata% folder (windows).
Masternodes can be removed by editing or deleting file. Your collateral will reappear after you restart your wallet.

You may need to wait a few hours or even a day to receive rewards depending on the number of masternodes on the network.
___
### 6. Checking masternode status  
Click `Update` periodically to ensure your masternodes are running

After 30 minutes, your masternode `Active(secs)` will be reflected in the DarkSaga subtab

### Thank you for running a DarkSaga Masternode!
___

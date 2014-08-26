//sends and receives messages via UDP and TCP

#ifndef NETWORK
#define NETWORK

#include "random.h"
#include <SFML/Network.hpp>
#include <string>
#include <vector>

//UDP
class NetworkUDP
{
public:
	NetworkUDP();
	void sendMessageLan(unsigned short, std::string const&);
	void sendMessage(sf::IpAddress, unsigned short, std::string const&);
	void receiveMessages();
	void clearMessages();

	//sets and gets
	void setBlocking(bool);
	short getMyIdentifier();
	std::string getBroadcastIP();
	std::string getLocalIP();
	std::string getLocalHost();
	std::string getPacketMessage(int);
	short getPacketIdentifier(int);
	int getNumberOfMessages();
	void setBoundPort(unsigned short);
	void setMessage(int, std::string const&);
	int getNumberConnected();
	std::string getIPAdress(int);

private:
	std::vector<std::pair<short, std::string>> receivedMessages;
	sf::UdpSocket socket;
	short myIdentifier;
	short tempShort;
	sf::Packet tempPacket;
	std::string tempStr;
	sf::IpAddress lastIP;
	unsigned short lastPort;
	std::vector<sf::IpAddress> connectedIP;
};

//TCP
class NetworkTCP
{
public:
	NetworkTCP();
	~NetworkTCP();
	bool connect(sf::IpAddress, unsigned short);
	bool listenForConnections();
	void disconnect();
	void sendMessage(std::string);
	void receiveMessages();
	void setMySocketBlocking(bool);
	void setListenBlocking(bool);
	void clearMessages();

	std::string getMessage(int);
	int getNumberOfMessages();
	int getNumberConnected();
	void setListeningPort(unsigned short);
	void setConnectedSocketBlocking(int, bool);

private:
	sf::TcpListener listener;
	sf::TcpSocket mySocket;
	sf::Packet tempPacket;
	std::string tempStr;
	std::vector<std::string> messageQue;
	std::vector<sf::TcpSocket*> connectedSockets;
	unsigned short listeningPort;
};


#endif
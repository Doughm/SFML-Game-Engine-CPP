//TCP and UDP network functionally

#include "network.h"

// - - - - - - - - - - - - - //
//			UDP				 //
// - - - - - - - - - - - - - //
NetworkUDP::NetworkUDP()
{
	socket.setBlocking(false);
	Random rand;
	myIdentifier = rand.getRandomNumber(0, 32767);
}

//sends a message to a specific IP address on a specific port
void NetworkUDP::sendMessage(sf::IpAddress address, unsigned short port, std::string const& message)
{
	tempPacket.clear();
	tempPacket<<myIdentifier<<message;
	socket.send(tempPacket, address, port);
}

//sends a message on a lan on a specific port
void NetworkUDP::sendMessageLan(unsigned short port, std::string const& message)
{
	tempPacket.clear();
	tempPacket<<myIdentifier<<message;
	socket.send(tempPacket, sf::IpAddress::Broadcast, port);
}

//receives a message from somewhere on some port
void NetworkUDP::receiveMessages()
{
	if(socket.isBlocking() == false)
	{
		while(true)
		{
			if(socket.receive(tempPacket, lastIP, lastPort) == sf::Socket::Done)
			{
				tempPacket>>tempShort>>tempStr;
				if(tempShort != myIdentifier)
				{
					receivedMessages.push_back(std::pair<short, std::string>(tempShort, tempStr));
					//adds the IP to list
					if(connectedIP.size() == 0)
					{
						connectedIP.push_back(lastIP);
					}
					else if(connectedIP.size() > 0)
					{
						bool isNew = true;
						for(int i = 0; i < connectedIP.size(); ++i)
						{
							if(connectedIP[i] == lastIP)
							{
								isNew = false;
								break;
							}
						}
						if(isNew == true)
						{
							connectedIP.push_back(lastIP);
						}
					}
				}
			}
			else
			{
				break;
			}
		}
	}
	else
	{
		for(int i = 0; i < 1; ++i)
		{
			if(socket.receive(tempPacket, lastIP, lastPort) == sf::Socket::Done)
			{
				tempPacket>>tempShort>>tempStr;
				if(tempShort != myIdentifier)
				{
					receivedMessages.push_back(std::pair<short, std::string>(tempShort, tempStr));
					if(connectedIP.size() == 0)
					{
						connectedIP.push_back(lastIP);
					}
					else if(connectedIP.size() > 0)
					{
						bool isNew = true;
						for(int i = 0; i < connectedIP.size(); ++i)
						{
							if(connectedIP[i] == lastIP)
							{
								isNew == false;
								return;
							}
						}
						if(isNew == true)
						{
							connectedIP.push_back(lastIP);
						}
					}
				}
				else
				{
					--i;
				}
			}
			else
			{
				return;
			}
		}
	}
}

//returns a message from the message que
std::string NetworkUDP::getPacketMessage(int index)
{
	return receivedMessages[index].second;
}

//returns the identifier from the message que
short NetworkUDP::getPacketIdentifier(int index)
{
	return receivedMessages[index].first;
}

//returns the number of messages in que
int NetworkUDP::getNumberOfMessages()
{
	return receivedMessages.size();
}

//sets if the socket is blocking or not
void NetworkUDP::setBlocking(bool block)
{
	socket.setBlocking(block);
}

//returns your random identifier
short NetworkUDP::getMyIdentifier()
{
	return myIdentifier;
}

//returns the broadcast IP
std::string NetworkUDP::getBroadcastIP()
{
	return sf::IpAddress::Broadcast.toString();
}

//returns your local IP
std::string NetworkUDP::getLocalIP()
{
	return sf::IpAddress::getLocalAddress().toString();
}

//clears the message que
void NetworkUDP::clearMessages()
{
	receivedMessages.clear();
}

//sets the port binding
void NetworkUDP::setBoundPort(unsigned short port)
{
	socket.unbind();
	socket.bind(port);
}

//returns the local host address
std::string NetworkUDP::getLocalHost()
{
	return sf::IpAddress::LocalHost.toString();
}

//changes a message in que
void NetworkUDP::setMessage(int index, std::string const& newMessage)
{
	receivedMessages[index].second = newMessage;
}

//get the amount of people connected
int NetworkUDP::getNumberConnected()
{
	return connectedIP.size();
}

//returns a IP address that is connected to the host
std::string NetworkUDP::getIPAdress(int address)
{
	return connectedIP[address].toString();
}



// - - - - - - - - - - - - - //
//			TCP				 //
// - - - - - - - - - - - - - //

NetworkTCP::NetworkTCP()
{
	mySocket.setBlocking(false);
	listener.setBlocking(false);
	connectedSockets.push_back(new sf::TcpSocket());
	listeningPort = 0;
}

NetworkTCP::~NetworkTCP()
{
	for(int i = 0; i < connectedSockets.size(); ++i)
	{
		delete connectedSockets[i];
	}
}

//connects to a computer, returns true if a connection is established
bool NetworkTCP::connect(sf::IpAddress address, unsigned short firstPort)
{
	if(mySocket.connect(address, firstPort) == sf::TcpSocket::Status::Done)
	{
		return true;
	}
	return false;
}

//gets any incoming connections, and increments the listening port
bool NetworkTCP::listenForConnections()
{
	if(listener.accept(*(connectedSockets[connectedSockets.size() - 1])) == sf::TcpSocket::Status::Done)
	{
		connectedSockets[connectedSockets.size() - 1]->setBlocking(false);
		connectedSockets.push_back(new sf::TcpSocket());
		return true;
	}
	return false;
}

//disconnects from a computer
void NetworkTCP::disconnect()
{
	if(connectedSockets.size() == 0)
	{
		mySocket.disconnect();
	}
	else
	{
		for(int i = 0; i < connectedSockets.size(); ++i)
		{
			delete connectedSockets[i];
		}
		connectedSockets.clear();
	}
}

//sends a message over a TCP stream
void NetworkTCP::sendMessage(std::string message)
{
	tempPacket.clear();
	tempPacket<<message;
	if(connectedSockets.size() > 1)
	{
		for(int i = 0; i < connectedSockets.size() - 1; ++i)
		{
			connectedSockets[i]->send(tempPacket);
		}
	}
	else
	{
		mySocket.send(tempPacket);
	}
}

//receives a message over a TCP stream
void NetworkTCP::receiveMessages()
{
	tempPacket.clear();
	tempStr.clear();
	if(connectedSockets.size() > 1)
	{
		bool loopSent = false;
		do
		{
			loopSent = false;
			for(int i = 0; i < connectedSockets.size() - 1; ++i)
			{
				if(connectedSockets[i]->receive(tempPacket) == sf::TcpSocket::Status::Done)
				{
					loopSent = true;
					tempPacket>>tempStr;
					messageQue.push_back(tempStr);
				}
			}
		}
		while(loopSent == true);
	}
	else
	{
		while(true)
		{
			if(mySocket.receive(tempPacket) == sf::TcpSocket::Status::Done)
			{
				tempPacket>>tempStr;
				messageQue.push_back(tempStr);
			}
			else
			{
				break;
			}
		}
	}
}

//sets if your socket is blocking
void NetworkTCP::setMySocketBlocking(bool block)
{
	mySocket.setBlocking(block);
}

//sets if the listen socket is blocking
void NetworkTCP::setListenBlocking(bool block)
{
	listener.setBlocking(block);
}

//gets a message in que
std::string NetworkTCP::getMessage(int index)
{
	return messageQue[index];
}

//gets the number of messages
int NetworkTCP::getNumberOfMessages()
{
	return messageQue.size();
}

//returns the number of computers connected to this one
int NetworkTCP::getNumberConnected()
{
	return connectedSockets.size();
}

//clears the message buffer
void NetworkTCP::clearMessages()
{
	messageQue.clear();
}

//sets the port that is listening for connections
void NetworkTCP::setListeningPort(unsigned short port)
{
	listeningPort = port;
	listener.close();
	listener.listen(listeningPort);
}

//sets if a connected socket is blocking or not
void NetworkTCP::setConnectedSocketBlocking(int index, bool block)
{
	connectedSockets[index]->setBlocking(block);
}
#include <SFML/Network.hpp>
#include <iostream>
#include <string>

#define BIND_PORT 55000

void main()
{
	sf::UdpSocket socket;

	if (socket.bind(BIND_PORT) == sf::Socket::Status::Done) {
		std::cout << "Puerto bineado correctamente" << std::endl;
	}
	else{
		std::cerr << "Hizo pum" << std::endl;
	}

	char buffer[1024];

	std::size_t receivedData;
	std::optional<sf::IpAddress> senderIP;
	unsigned short senderPort;

	while (true) {
		if (socket.receive(buffer, sizeof(buffer), receivedData, senderIP, senderPort) == sf::Socket::Status::Done) {
			std::cout << "Mensaje recibido de " << senderIP.value() << " : " << senderPort << std::endl;

			std::size_t byteRead = 0;

			int messageSize = 0;
			std::memcpy(&messageSize, buffer, sizeof(messageSize));
			byteRead += sizeof(messageSize);

			std::string receivedString(buffer + byteRead, messageSize);
			byteRead += messageSize;

			int receivedData;
			std::memcpy(&receivedData, buffer + byteRead, sizeof(receivedData));
			
			std::cout << receivedString << ": " << receivedData << std::endl;
		}
	}


}
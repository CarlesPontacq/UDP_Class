#include <SFML/Network.hpp>
#include <iostream>
#include <cstring>
#include <string>

#define SERVER_PORT 55000
const sf::IpAddress SERVER_IP = sf::IpAddress(127, 0, 0, 1);

void main()
{

	sf::UdpSocket serverSocket;

	char buffer[1024];
	std::size_t bufferDataSize = 0;

	std::string message = "Numero enviado";

	for (int i = 0; i < 100000; i++) {
		int data = i;

		int messageSize = message.size();
		std::memcpy(buffer + bufferDataSize, &messageSize, sizeof(messageSize));
		bufferDataSize = sizeof(messageSize);

		std::memcpy(buffer + bufferDataSize, message.c_str(), messageSize);
		bufferDataSize += messageSize;

		std::memcpy(buffer + bufferDataSize, &data, sizeof(data));
		bufferDataSize += sizeof(data);
		

		if (serverSocket.send(buffer, bufferDataSize, SERVER_IP, SERVER_PORT) == sf::Socket::Status::Done) {
			std::cout << "Mensaje " << i <<" entregado al sistema operatico" << std::endl;
		}
	}
}
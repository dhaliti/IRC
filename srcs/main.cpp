/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhaliti <dhaliti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:22:25 by dhaliti           #+#    #+#             */
/*   Updated: 2022/07/04 11:58:41 by dhaliti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/IRC.hpp"

fd_set active;

void force_quit(int)
{
	cout << endl << "Force quiting.." << endl;
	for (size_t i = 0; i < 1024; i++) {
		FD_CLR(i, &active);
		close(i);
	}
	exit (0);

}

static void Socketting(int &serverSock, int &_max)
{
	serverSock = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSock < 0)
		throw out_of_range("Socket failed");
	if (fcntl(serverSock, F_SETFL, O_NONBLOCK) == -1)
		throw out_of_range("Non-blocking Socket failed");
	_max = serverSock;
	FD_SET(serverSock, &active);
}

static void Binding(int &serverSock, sockaddr_in &addr, int &port)
{
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(2130706433);
	addr.sin_port = htons(port);
	fcntl(serverSock, F_SETFL, O_NONBLOCK);
	if ((bind(serverSock, (const struct sockaddr *)&addr, sizeof(addr))) < 0)
	   throw out_of_range("[Error] Binding failed");
	if (listen(serverSock, 128) < 0)
	   throw out_of_range("[Error] Listening failed");
}

static void checkArgs(Client *clients, fd_set &active, int &ac, char **av, int &port, string &password)
{
	if (ac != 3)
        throw invalid_argument("[Error] Wrong number of arguments\nUsage: ./ircserv port password");
	password = string(av[2]);
	port = atoi(av[1]);
	if (port <= 0 || port > 65535)
		throw out_of_range("[Error] Port out of range!");
	if (password.size() > 8)
		throw out_of_range("[Error] password too long!");
	bzero(&clients, sizeof(clients));
	FD_ZERO(&active);
}

int main(int ac, char **av)
{
	Client clients[1024];
	int _max = 0;
	int port;
	int serverSock;
	string password;
	struct sockaddr_in addr;

	try
	{
		checkArgs(clients, active, ac, av, port, password);
		Socketting(serverSock, _max);
		Binding(serverSock, addr, port);
		signal(SIGINT, force_quit);
		IRCLoop(clients, active, serverSock, password, addr, _max);
	}

	catch(exception &e)
	{
		cout << e.what() << endl;
		exit(1);
	}
}

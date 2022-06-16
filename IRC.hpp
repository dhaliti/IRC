/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cciobanu <cciobanu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:28:25 by dhaliti           #+#    #+#             */
/*   Updated: 2022/06/16 14:44:41 by cciobanu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include "Client.hpp"
#include "Bot.hpp"
#include "Files.hpp"
#include <signal.h>

#define NICK 1;
#define USER 2;
#define PRIVMSG 3;
#define PASS 4;
#define JOIN 5;
#define OPER 6;
#define PART 7;
#define KICK 8;
#define PING 9;
#define CLIENTS 10;


using namespace std;

char	**ft_split2(const char *str, const char *charset);
void 	ft_commands(Client *clients, int &s, const char *bufRead, string &password);
void 	newClient(Client *clients, int &s, char *bufRead);

/*utils.cpp*/
bool 	isUpper(string &str);
void 	isConnected(Client &client, int &index);
void 	ft_clients(Client *clients, int&, char **, int&);
bool 	notEmpty(char *str, int index);
bool 	newNick(char *str, Client *clients);
int 	searchNick(Client *clients, string &nick);
void 	newClient(Client *clients, int &index);
void 	botWelcome(Client &clients, int &index);
void 	botCommand(Client *clients, int &index, char **ident2, int &j);
int 	searchUser(Client *clients, string &user);
void	sendAll(int &dest, string message);
int		getCmd(string &cmd);
void 	IRCLoop(Client *clients, fd_set &readyRead, fd_set &readyWrite, fd_set &active, int &_max, int &serverSock, int &next_id, char *bufRead, string &password, socklen_t &addr_len, sockaddr_in &addr);

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhaliti <dhaliti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:31:27 by dhaliti           #+#    #+#             */
/*   Updated: 2022/06/20 11:49:28 by dhaliti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/IRC.hpp"

int getCmd(string &cmd)
{
	string elems[] = {"NICK", "USER", "PRIVMSG", "PASS", "JOIN", "OPER", "PART", "KICK", "PING", "CLIENTS", "SENDFILE", "GETFILE"};
	for (int i = 0; i < 10; i++)
	{
		if (cmd == elems[i])
			return (i);
	}
	return (-1);
}

void sendAll(int &dest, string message)
{
	size_t total = 0;
	int bytesleft = message.length();
	int b;

	while (total < message.length())
	{
		b = send(dest, message.c_str() + total, bytesleft, 0);
		if (b == -1)
			break;
		total += b;
		bytesleft -= b;
	}
	if (b == -1)
		cout << "Error: Data could not be sent" << endl;
}

int searchUser(Client *clients, string &user)
{
	for (int i = 1; i < 1024; i++)
	{
		if (clients[i].getUserName() == user || clients[i].getNickName() == user)
			return (i);
	}
	return (-1);
}

bool isUpper(string &str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		if (isupper(str[i] != 0))
			return true;
	}
	return false;
}

void isConnected(Client &client, int &index)
{
	if (client.getUserName() != "" && client.getNickName() != "" && client.password == true && client.isConnected() == false)
	{
		client.setConnected(true);
		string message = ":irc.serv 001 " + client.getNickName() + " :Welcome to the Internet Relay Network " + client.getNickName() + "!" + client.getUserName() +"@irc.serv\n";
		send(index, message.c_str(), message.size(), 0);
		botWelcome(client, index);
	}
}

void ft_clients(Client *clients, int &, char **, int &)
{
	for (int i = 0; i < 10; i++)
		cout << i << ": " << "ID: " << clients[i].getId() << endl << "username: " << clients[i].getUserName() << endl << "nickname: " << clients[i].getNickName() << endl;
}

bool notEmpty(char *str, int index)
{
	int i = -1;
	if (index == 1)
	{
		if (string(str) == "anonymous")
			return false;
	}

	while (str[++i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return true;
	}
	return false;
}

bool newNick(char *str, Client *clients)
{
	string nick = string(str);
	for (int i = 0; i < 1024; i++)
	{
		if (clients[i].getNickName() == nick)
			return false;
	}
	return true;
}

int searchNick(Client *clients, string &nick)
{
	for (int i = 1; i < 1024; i++)
	{
		if (clients[i].getNickName() == nick || clients[i].getUserName() == nick)
			return (i);
	}
	return (-1);
}

static int	ft_is_separator(const char *str, const char *charset)
{
	while (*charset)
		if (*str == *charset++)
			return (1);
	return (0);
}

static int	ft_wordlen(const char *str, const char *charset)
{
	int	i;

	i = 0;
	while (str[i] && !ft_is_separator(str + i, charset))
		i++;
	return (i);
}

static int	ft_wordcount(const char *str, const char *charset)
{
	int	i;
	int	w;

	w = 0;
	while (*str)
	{
		while (*str && ft_is_separator(str, charset))
			str++;
		i = ft_wordlen(str, charset);
		str += i;
		if (i)
			w++;
	}
	return (w);
}

static char	*ft_wordcpy(const char *src, int n)
{
	char	*dest;

	dest = (char *)malloc((n + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	dest[n] = '\0';
	while (n--)
		dest[n] = src[n];
	return (dest);
}

char	**ft_split2(const char *str, const char *charset)
{
	char	**t;
	int		size;
	int		i;
	int		n;

	size = ft_wordcount(str, charset);
	t = (char **)malloc((size + 1) * sizeof(char *));
	if (t == NULL)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		while (*str && ft_is_separator(str, charset))
			str++;
		n = ft_wordlen(str, charset);
		t[i] = ft_wordcpy(str, n);
		if (t[i] == NULL)
			return (NULL);
		str += n;
	}
	t[size] = 0;
	return (t);
}

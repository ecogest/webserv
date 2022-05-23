/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:18:20 by jchemoun          #+#    #+#             */
/*   Updated: 2022/05/21 12:58:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Request.hpp"
# include "Config.hpp"
# include "Response.hpp"

/*
get time for session if bonus
data in client ?
class is useless for now
*/

class Client
{
public:
	Config::Connection			accept_info;
	Config::Connection const	*listen_info;
	Request						request;
	Response					*response;

	Client(Config::Connection const *listen_info = NULL);
	~Client();

	bool	accept_connection();
	void	_print_connection_info();
	void	close_connection();
};

#endif

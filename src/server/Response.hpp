/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:02:03 by jchemoun          #+#    #+#             */
/*   Updated: 2022/05/04 13:40:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include <cstddef>
# include <string>
# include <iostream>
# include <fstream>
# include <sstream>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include "Config.hpp"
# include "Request.hpp"

class Response
{
private:
	std::string	header;
	std::string	body;
	std::string	full_response;
	std::string	content_type;
	int			code;
	std::map<int, std::string>	status_header;
	Config::Server const	&_serv;
	// Request const			&_req;
	bool	_autoindex;
public:
	Response(Config::Server const &serv, Request const &req);
	~Response();
	const char *c_str() const;
	size_t		size() const;

private:
	enum	e_filetype { FT_UNKOWN, FT_DIR, FT_FILE };
	e_filetype	check_path(std::string const &path) const;
	bool		check_read_perm(std::string const &path) const;
	std::string	create_auto_index_page(std::string const &location);
	size_t		read_file(std::string const &location);

	void		init_status_header();

	void		set_header();
	void		set_full_response();
};

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 17:59:25 by mjacq             #+#    #+#             */
/*   Updated: 2022/04/25 18:01:10 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP
# include <vector>
# include <string>

struct Config {

	struct	Location {
		std::string	location_path;
		std::string	root;
		void print() const;
	};

	struct	Server {
		std::vector<std::string>	server_names;
		int							listen;
		std::vector<Location>		locations;
		std::vector<std::string>	index;
		std::string					root;
		void print() const;
	};

	std::vector<Server>	servers;
	void print() const;
};

#endif

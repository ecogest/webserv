/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 13:17:12 by jchemoun          #+#    #+#             */
/*   Updated: 2022/05/09 15:25:17 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include <cstring>

Request::Request(): _is_complete(false), _ongoing(false), _index(0)
{
}

/*
** Syntax:
** Request-Line   = Method SP Request-URI SP HTTP-Version CRLF
**
** Note:
** - uri should not contain literal space
** - a good client will end each line by \r\n, but nginx also works with single '\n'
** Resources:
** - https://www.tutorialspoint.com/http/http_requests.htm
** - https://www.w3.org/Protocols/rfc2616/rfc2616-sec5.html
*/
void	Request::parse_request()
{
	std::cout << "\e[32m" << _raw_str << "\e[0m✋\n";

	if (!_ongoing) {
		_skip_empty_lines();
		if (!_raw_str[_index] || _raw_str.find("\n", _index) == std::string::npos)
			return ;
		_eat_word(method);		std::cout << "> method: " << method << "\n";
		_eat_spaces();
		_eat_word(location);	std::cout << "> location: " << location << "\n";
		_eat_spaces();
		_eat_word(protocol);	std::cout << "> protocol: " << protocol << "\n";
		_eat_eol();
		_ongoing = true;
	}
	while (_raw_str.find("\n", _index) != std::string::npos) {
		if (_raw_str[_index] == '\n' || _raw_str.substr(_index, 2) == "\r\n") {
			_ongoing = false;
			_is_complete = true;
			break ;
		}
		_eat_key();
		_eat_value();
	}
	_raw_str.erase(0, _index);
	_index = 0;
}

void	Request::append_unparsed_request(char *buffer, ssize_t len)
{
	_raw_str.append(buffer, len);
}

bool	Request::is_complete() const { return (_is_complete); }

std::string const	&Request::get_location() const {
	return (location);
}

void	Request::reset() {
	_is_complete = false;
}

Request::~Request() { }

/*
** ============================= Parsing Utils ============================== **
*/

/*
** remark: Using const char * instead of std::string is a bit more efficient
** and parsing request efficiency is critical (way more than parsing config)
*/
void	Request::_eat(const char *s) {
	size_t	size = std::strlen(s);
	if (_raw_str.substr(_index, size) != s)
		throw std::runtime_error("parse_request error");
	_index += size;
}

void	Request::_eat_word(std::string &s, const char *delimiter) {
	size_t	count = 0;
	char c;
	while ((c = _raw_str[_index + count]) && !strchr(delimiter, c))
		++count;
	if (count == 0)
		throw std::runtime_error("parse_request error");;
	s = _raw_str.substr(_index, count);
	_index += s.size();
}

void	Request::_eat_word(std::string &s) {
	static const char* word_delimiter = " \r\n";
	_eat_word(s, word_delimiter);
}

void	Request::_eat_eol() {
	if (_raw_str[_index] == '\r')
		++_index;
	_eat("\n");
}

void	Request::_eat_spaces() {
	_eat(" ");
	while (_raw_str[_index] == ' ')
		++_index;
}

/*
** syntax: "key: value"
** - more precisely: `message-header = field-name ":" [ field-value ]`
** remarks:
** - space is not mandatory (so no _eat_spaces())
** - multiple spaces allowed
** - https://www.w3.org/Protocols/rfc2616/rfc2616-sec4.html
*/
void	Request::_eat_key() {
	_eat_word(_tmp_key, ":");
	_eat(":");
	while (_raw_str[_index] == ' ')
		++_index;
	std::cout << "\e[36m> " << _tmp_key << ": \e[0m";
}

void	Request::_eat_value() {
	std::string	value;
	_eat_word(value, "\r\n");
	_eat_eol();
	header[_tmp_key] = value;
	std::cout << "\e[36m"<< value << "\e[0m\n";
}

void	Request::_skip_empty_lines() {
	while (true) {
		if (_raw_str[_index] == '\r' && _raw_str[_index + 1] == '\n')
			_index += 2;
		else if (_raw_str[_index] == '\n')
			++_index;
		else
			break;
	}
}

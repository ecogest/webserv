/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacq <mjacq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 18:01:10 by mjacq             #+#    #+#             */
/*   Updated: 2022/04/22 19:32:29 by mjacq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"
#include <stdexcept>
#include <iostream>

Lexer::Lexer(std::string filename): _line(), _pos(0), _vect(), _stream() {
	_open(filename);
	_tokenize_file();
}

Lexer::~Lexer(void) {
	_stream.close();
}

void	Lexer::_open(std::string &filename) {
	_stream.open(filename); // Calls setstate(failbit) on failure.
	if (!_stream)
		throw std::runtime_error("Fails to open file.");
}

void	Lexer::_tokenize_file() {
	while (std::getline(_stream, _line)) {
		_tokenize_line();
	}
}

void	Lexer::_tokenize_line() {
	_pos = 0;
	char	c;
	while ((c = _line[_pos])) {
		if (_is_skipped_char(c))
			++_pos;
		else if (_is_comment_char(c))
			_skip_comment();
		else if (_is_special_char(c))
			_tokenize_special_char();
		else
			_tokenize_word();
	}
}

void	Lexer::_tokenize_special_char() {
	std::string	value;
	value =_line[_pos];
	_vect.push_back(Token(Token::type_special_char, value));
	++_pos;
}

void	Lexer::_tokenize_word() {
	size_t	start = _pos;
	char	c;
	while ((c = _line[_pos])) {
		if (_is_skipped_char(c) || _is_special_char(c))
			break;
		++_pos;
	}
	_vect.push_back(Token(Token::type_word, _line.substr(start, _pos - start)));
}

void	Lexer::print() const{
	for (size_t i = 0; i < _vect.size(); i++)
		std::cout << _vect.at(i).get_value() << std::endl;
}

const char *Lexer::_special_chars = ";{}";

bool	Lexer::_is_special_char(char c) {
	return (std::strchr(_special_chars, c));
}

bool	Lexer::_is_skipped_char(char c) {
	return (std::strchr("\t ", c));
}

bool	Lexer::_is_comment_char(char c) {
	return (c == '#');
}

void	Lexer::_skip_comment() {
	_pos = _line.size();
}

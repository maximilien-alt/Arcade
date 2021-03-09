/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Errors
*/

#include "Errors.hpp"

Arcade::Errors::Errors(const std::string &message) noexcept : _what(message)
{
}

Arcade::Errors::~Errors() noexcept
{
}

const char *Arcade::Errors::what(void) const noexcept
{
	return _what.c_str();
}
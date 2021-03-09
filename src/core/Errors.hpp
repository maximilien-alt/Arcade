/*
** EPITECH PROJECT, 2021
** arcade
** File description:
** Errors
*/

#ifndef ERRORS_HPP_
#define ERRORS_HPP_

#include <string>
#include <exception>

namespace Arcade
{
    class Errors : public std::exception
    {
    public:
        explicit Errors(std::string const &message = "") noexcept;
        virtual ~Errors() noexcept;

        const char *what() const noexcept;

    private:
        std::string _what;
    };
} // namespace Arcade

#endif /* !ERRORS_HPP_ */

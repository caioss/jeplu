#ifndef FAKELIBFINDER_HPP
#define FAKELIBFINDER_HPP

#include "ILibFinder.hpp"

class FakeLibFinder : public ILibFinder
{
public:
    /**
     *  \brief Default constructor.
     */
    FakeLibFinder(const std::string &path = std::string()) {}

    std::vector<std::string> libsPath() const override
    {
        return std::vector<std::string>();
    }
};

#endif

#ifndef FAKELIBFINDER_HPP

#include "core/ILibFinder.hpp"

class FakeLibFinder : public ILibFinder
{
public:
    /**
     *  \brief Default constructor.
     */
    FakeLibFinder(const std::string &path) {}

    std::vector<std::string> libsPath() const override
    {
        return std::vector<std::string>();
    }
};

#endif

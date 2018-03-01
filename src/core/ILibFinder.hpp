#ifndef ILIBFINDER_HPP
#define ILIBFINDER_HPP

#include <vector>
#include <string>

/**
 *  \brief The interface ILibFinder should be implemented to find dynamic library files.
 *
 *  Its implementation should looks for any dynamic library that is inside a given path by its own rules and provide
 *  the libraries paths not depending of any plataform (If linux, find .so. If windows, find dll. If OSx, find dylib).
 */
class ILibFinder
{
public:
    /**
     *  \brief Gets the libraries found inside the initialized path.
     *
     *  This method should works providing only the dynamic libraries that is compatible with the running
     *  operational system.
     *
     *  \return A vector containing the path of all libraries found.
     */
    virtual std::vector<std::string> libsPath() const = 0;
};

#endif // ILIBFINDER_HPP

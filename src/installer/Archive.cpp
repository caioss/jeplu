#include "Archive.hpp"
#include "Zip.hpp"

Archive::Archive(void)
{
}

std::unique_ptr<Archive> Archive::make_archive(void)
{
    std::unique_ptr<Archive> archive;

    archive.reset(new Zip());

    //artifact = std::unique_ptr<Zip>();

    return archive;
}

Archive::~Archive(void)
{
}


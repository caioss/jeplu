#ifndef DLPLUGINCREATOR_HPP
#define DLPLUGINCREATOR_HPP

#include "iplugin.hpp"

#include <memory>

// DlPlugin creator.
typedef std::shared_ptr<IPlugin> create_t();

#endif

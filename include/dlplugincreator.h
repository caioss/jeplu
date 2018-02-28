#ifndef DLPLUGINCREATOR_HPP
#define DLPLUGINCREATOR_HPP

#include "IPlugin.hpp"

#include <memory>

// DlPlugin creator.
typedef std::shared_ptr<IPlugin> create_t();

#endif

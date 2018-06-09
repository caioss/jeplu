#ifndef DLPLUGINCREATOR_HPP
#define DLPLUGINCREATOR_HPP

#include <memory>

class IPlugin;

/**
 *  This is necessary for those plugins that will be loaded by the default loader `DlLoader` available
 *  for unix system.
 *  In case that the user (developer) wants to develops a new solution for the loader, this is no longer
 *  necessary and should be created a new solution for loading the \c IPlugin object from a dynamic
 *  library.
 *
 *  \sa IPlugin \sa Jeplu \sa DlLoader
 */
typedef std::shared_ptr<IPlugin> create_t();

#endif

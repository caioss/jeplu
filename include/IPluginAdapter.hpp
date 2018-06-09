#ifndef IPLUGINADAPTER_HPP
#define IPLUGINADAPTER_HPP

#include "IPlugin.hpp"

#include <memory>
#include <vector>
#include <string>

/**
 *  The \c IPluginAdapter interface must be used for converting \c IPlugin objects to an especific type that the only the
 *  adapter and the plugin knows.
 *
 *  It's used for extending any functionality for any kind of application. Each implementation of this interface may
 *  provide an interface so any \c IPlugin object can inherit. That way, after the plugin registration, each \c IPlugin
 *  object will be linked to its \c IPluginAdapter, becoming easy to find and cast to the custom type.
 *
 *  As an example, an Adapter could be the responsable for registering a set of custom widgets into the application. By
 *  doing that, we would need an interface that represents or that creates these widgets and the implementation of this
 *  \c IPluginAdapter to receive these objects like \c IPlugin and than try to cast and register these objects as the
 *  new interface provided by your application.
 *
 *  \code
 *  class CustomAdapter : public IPluginAdapter
 *  {
 *      // overrided methods of IPluginAdapter...
 *
 *      std::string adapterId() const { return "customadapter.adapter.jeplu"; }
 *
 *      // A custom function to retrieve all \c IPlugin registered to this proxy, casted to
 *      // a custom interface called ICustomInterface.
 *      std::vector<std::weak_ptr<ICustomInterface>> interfaces() const;
 *  }
 *  \endcode
 *
 *  This ICustomInterface could be defined as the follow:
 *  \code
 *  #include "IQtPlugin.hpp"
 *
 *  class ICustomInterface : public virtual IPlugin
 *  {
 *      // Overrides all IPlugin methods keeping it virtual and without implementation.
 *      std::string adapterId() const override { return "customadapter.adapter.jeplu"; }
 *
 *      // The custom widget created by the plugin and now can be access by the application.
 *      virtual QWidget* customWidget() = 0;
 *  }
 *  \endcode
 *
 */
class IPluginAdapter {
public:
    /**
     *  \brief Initializes this adapter with the given \c IPlugin objects.
     *
     *  \param plugins A vector containing all compatible \c IPlugin references.
     *  \return Returns \c true if initialized. Otherwise, returns \c false.
     */
    virtual bool init(std::vector<std::weak_ptr<IPlugin>> plugins = std::vector<std::weak_ptr<IPlugin>>()) = 0;

    /**
     *  \brief Gets the unique adapter ID.
     *
     *  \return Returns a unique ID representing this \c IPluginAdapter.
     */
    virtual std::string adapterId() const = 0;

    /**
     *  \brief Indicates if this adapter is initialized.
     *
     *  \return Returns \c true if this adapter is initialized. \c False otherwise.
     */
    virtual bool initialized() const = 0;

    /**
     *  \brief Indicates if has any \c IPlugin loaded into this adapter.
     */
    virtual bool hasPluginsLoaded() const = 0;

    /**
     *  \brief Gets all \c IPlugin references compatible with this adapter.
     *
     *  \return Returns a vector containing weak references of \c IPlugin objects.
     */
    virtual std::vector<std::weak_ptr<IPlugin>> plugins() const = 0;

    /**
     *  \brief Adds the \c plugin reference to this adapter.
     *
     *  If the \c plugin is not compatible with this \c IPluginAdapter, the plugin is not added.
     *
     *  \param plugin A weak reference to the \c IPlugin object.
     *  \return Returns \c true if the plugin is compatible and could be added to this adapter. Otherwise, returns
     *  \c false.
     */
    virtual bool addPlugin(std::weak_ptr<IPlugin> plugin) = 0;
};

#endif

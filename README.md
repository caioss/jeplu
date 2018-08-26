# Jeplu
The Jeplu is a lightweight and modular framework for plugin management. It works by finding the available shared libraries (with `ILibFinder`), loading them (with `IPluginLoader`) and retrieving it's casted object using a registered `IPluginAdapter`.

To do so, the main basic usage is to create an `IPluginAdapter` for object casting and creates a shared library using an `IPlugin` interface that matches with its `IPluginAdapter`. The default `ILibFinder` searches in the given path for any plugins that matches with its folder name (if you want to load a lib "libexample.so", put it inside a folder called "example"), then the Jeplu tries to load the library and, if succeeds, it registers the `IPlugin` object to it's `IPluginAdapter`, becoming available for usage inside your own application.

### Creating the Adapter

Before the creation of the library (plugin) itself, an Adapter must be created and registered into the `Jeplu` framework. To do so, it's a simple step:
 * Creates an subclass of `IPluginAdapter`;
 * Creates a method for cast of the `IPlugin` to your own interface;
 * Register the created adapter into `Jeplu` (`Jeplu::registerAdapter()`).
 
 Here is a simple example:
 
 ```
 class MyInterface : public IPlugin
 {
     // overrided methods
     ...
 }
 
 class MyAdapter : public IPluginAdapter
 {
     // overrided methods
     
     std::vector<std::weak_ptr<MyInterface>> pluginsToMyInterfaces() const
     {
         std::vector<std::weak_ptr<MyInterface>> interfaces;
         for (std::weak_ptr<IPlugin> plugin : _registeredPlugins) {
             std::shared_ptr<IPlugin> sPlugin = plugin.lock();
             if (sPlugin)
                 interfaces.push_back(std::dynamic_pointer_cast<MyInterface>(sPlugin));
         }
     }
 }
 
 // Inside your application
 
 ...
     auto myAdapter = std::make_shared<MyAdapter>();
     jeplu.registerAdapter(myAdapter);
     jeplu.init("plugins/");
     
     if (myAdapter.hasPluginsLoaded()) {
         //retrieve your interfaces
         std::vector<std::weak_ptr<MyInterface>> myPlugins = myAdapter.pluginsToMyInterfaces();
     }
 ...
 ```
 
 ### Creating the library
 
Creating the shared library is still a dull job. First the developer must decide which loader your plugin will be compatible with. That's because the way that the loader creates the plugin's object differs. The `QtLoader` (one of the Jeplu's default loader) for instance, needs to register your interface into `Qt` metasystem and the `IPlugin` interface must also have the `Q_OBJECT` macro. (I didn't like it either)
 
In pratical terms, that's what we'll need:
 * Include the `header` file provided by your loader;
 * Do whatever the loader asks to. That will it will be able to find the `IPlugin` creator;
 * Creates an `IPlugin` subclass;
 * Build the `IPlugin` subclas as a shared library;

See `test/example/qt-custom-plugin` for details.

### Customizing Jeplu

There is two ways to change the behavior of the `Jeplu` framework: changing the `ILibFinder` and/or creating a new `IPluginLoader`.
The `ILibFinder` is responsible for finding the libraries files. The default `ILibFinder` is a `Qt` dependent module which, as described above, searches in the given path for any plugins that matches with its folder name (valid: "example/libexample.so", invalid: "test/libtest2.so"). This is because the plugin may want to save any files, or provide some resources with anothers libs inside the folder. So matching the name with the name folder was the easier way to find the right library to load, whithout checking all of them.
The `IPluginLoader` is responsible for loading a single library and providing it's `IPlugin` object. The `Jeplu` provides two loaders, one based on `Qt` framework, using the [`QPluginLoader`](http://doc.qt.io/qt-5/qpluginloader.html); and another based on [Dlopen](https://linux.die.net/man/3/dlopen), a unix only library.

Knowing that, if the developer don't want `Qt` into its own application, for instance, he/she may be able to remove the usage of these default modules using some cmake flags and register his/her own modules, using `Jeplu::init()` to register the `ILibFinder` and `Jeplu::registerLoader()` to register any loader.

The CMake flags supported:
* `-Dno-qt-loader`: removes the `QtLoader` module, it won't be built;
* `-Dno-qt-loader`: removes the `DlLoader` module, it won't be built;
* `-Dno-default-libfinder`: removes the `JepluLibFinder` module, it won't be built;

 # Installing on windows #

 * Download CMake >= 3.10;
 * Download MSVC 2015;
 * Download Qt v5.10;
 * Download debugger from windows sdk (optional);
 * Install everything. Make sure to install Qt for MSVC 2015.

 ## Configuring ##

 * Run `vcvarsall.bat`;

## Building ##

 * Build using cmake and make (or MSBuild for windows).

```
mkdir build
cd build
cmake ..
make
```

or for windows:
```
MSBuild ALL_BUILD.vcxproj
```


# Developers

Eric Menezes (eirc.m@protonmail.com)

#ifndef _ARTIFACT_HPP
#define _ARTIFACT_HPP

#include <memory>
#include <cstdint>
#include <string>

// enum ARTIFACT_TYPE
//     {
//         AT_ZIP = 0,
//         AT_RAR,
//     };

class Artifact
{
public:

    /**
     * \brief Artifact
     *
     * \param  Description of
     * \return Artifact
     */
    Artifact(void);

    /**
     * \brief make_artifact
     *
     * \param at Description of at
     * \return Artifact
     */
    static std::unique_ptr<Artifact> make_artifact(void);

    /**
     * \brief setFilePath
     *
     * \param filePath Description of filePath
     */
    virtual void setFilePath(std::string filePath) = 0;

    /**
     * \brief setPluginPath
     *
     * \param pluginPath Description of pluginPath
     */
    virtual void setPluginPath(std::string pluginPath) = 0;

    /**
     * \brief compress
     *
     * \param  Description of
     */
    virtual bool compress(void) = 0;

    /**
     * \brief decompress
     *
     * \param  Description of
     */
    virtual bool decompress(void) = 0;

    virtual ~Artifact(void);

protected:
    std::string _filePath;

    std::string _pluginPath;
};

#endif // _ARTIFACT_HPP


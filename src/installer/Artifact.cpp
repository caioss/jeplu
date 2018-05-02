#include "Zip.hpp"
#include "Artifact.hpp"

Artifact::Artifact(void)
{
}

std::unique_ptr<Artifact> Artifact::make_artifact(void)
{
    std::unique_ptr<Artifact> artifact;

    artifact.reset(new Zip());

    //artifact = std::unique_ptr<Zip>();

    return artifact;
}

Artifact::~Artifact(void)
{
}


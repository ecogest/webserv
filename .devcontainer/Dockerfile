# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.231.6/containers/cpp/.devcontainer/base.Dockerfile

# [Choice] Debian / Ubuntu version (use Debian 11, Ubuntu 18.04/21.04 on local arm64/Apple Silicon): debian-11, debian-10, ubuntu-21.04, ubuntu-20.04, ubuntu-18.04
ARG VARIANT="bullseye"
FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-${VARIANT}

# [Optional] Install CMake version different from what base image has already installed. 
# CMake reinstall choices: none, 3.21.5, 3.22.2, or versions from https://cmake.org/download/
ARG REINSTALL_CMAKE_VERSION_FROM_SOURCE="none"

# Optionally install the cmake for vcpkg
# COPY ./reinstall-cmake.sh /tmp/
# RUN if [ "${REINSTALL_CMAKE_VERSION_FROM_SOURCE}" != "none" ]; then \
#         chmod +x /tmp/reinstall-cmake.sh && /tmp/reinstall-cmake.sh ${REINSTALL_CMAKE_VERSION_FROM_SOURCE}; \
#     fi \
#     && rm -f /tmp/reinstall-cmake.sh

# [Optional] Uncomment this section to install additional vcpkg ports.
# RUN su vscode -c "${VCPKG_ROOT}/vcpkg install <your-port-name-here>"

# [Optional] Uncomment this section to install additional packages.
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends clangd tree

RUN apt install -y --no-install-recommends fzf
RUN echo "source /usr/share/doc/fzf/examples/key-bindings.zsh" >> /home/vscode/.zshrc

RUN apt install -y --no-install-recommends fd-find ripgrep

RUN apt install -y --no-install-recommends bat
USER vscode
RUN mkdir -p /home/vscode/.local/bin && ln -s /usr/bin/batcat /home/vscode/.local/bin/bat && echo 'export PATH="$PATH:$HOME/.local/bin"' >> /home/vscode/.zshrc
USER root

RUN sudo apt install -y --no-install-recommends telnet
RUN sudo apt install -y --no-install-recommends siege
RUN sudo apt install -y --no-install-recommends valgrind

RUN apt install -y python3-pip
RUN pip install compiledb
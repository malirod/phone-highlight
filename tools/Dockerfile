FROM ubuntu:18.10

ENV HOME /root

WORKDIR $HOME

RUN apt install -y g++ ninja make cmake clang-7 clang-format-7 clang-tidy-7

# Install Conan
RUN apt install -y python-pip
RUN pip install conan
RUN conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
RUN conan remote add catchorg https://api.bintray.com/conan/catchorg/Catch2
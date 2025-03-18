FROM gcc:latest

ENV LC_ALL=C.UTF-8
ENV LANG=C.UTF-8

COPY ./includes /usr/src/chess/includes
COPY ./src /usr/src/chess/src
COPY ./tests /usr/src/chess/tests
COPY ./CMakeLists.txt /usr/src/chess/CMakeLists.txt
COPY Main.cpp /usr/src/chess/Main.cpp
WORKDIR /usr/src/chess/

RUN  set -ex;\
  apt-get update;\
  apt-get install -y cmake;\
  cmake .; make
CMD ["/usr/src/chess/chess"]
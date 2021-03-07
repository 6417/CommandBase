FROM ubuntu:18.04

RUN apt-get update
RUN apt-get install -y ssh
RUN apt-get install -y build-essential
RUN apt-get install -y gcc
RUN apt-get install -y g++
RUN apt-get install -y gdb
RUN apt-get install -y cmake
RUN apt-get install -y clang
RUN apt-get install -y rsync
RUN apt-get install -y tar
RUN apt-get install -y python
RUN apt-get install -y git
RUN apt-get clean

RUN ( \
    echo 'LogLevel DEBUG2'; \
    echo 'PermitRootLogin yes'; \
    echo 'PasswordAuthentication yes'; \
    echo 'Subsystem sftp /usr/lib/openssh/sftp-server'; \
  ) > /etc/ssh/sshd_config_test_clion \
  && mkdir /run/sshd

RUN useradd -m admin\
  && yes password | passwd admin
RUN usermod -aG sudo admin

WORKDIR /usr/local/lib
RUN git clone https://github.com/google/googletest
WORKDIR /usr/local/lib/googletest
RUN mkdir build
WORKDIR /usr/local/lib/googletest/build
RUN cmake .. -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_C_COMPILER=/usr/bin/clang -DBUILD_SHARED_LIBS=ON
RUN make

CMD ["/usr/sbin/sshd", "-D", "-e", "-f", "/etc/ssh/sshd_config_test_clion"]
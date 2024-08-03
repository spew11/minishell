FROM ubuntu:latest

RUN apt update && apt install -y make && \
apt install -y libreadline-dev && \
apt install -y build-essential && \
apt install -y tini

COPY minishell /root/minishell

WORKDIR /root/minishell

RUN make

ENTRYPOINT ["/usr/bin/tini", "--"]
CMD ["/root/minishell/minishell"]

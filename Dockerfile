FROM ubuntu:latest

RUN apt update && apt install -y make && \
apt install -y libreadline-dev && \
apt install -y build-essential

COPY minishell /root/minishell

WORKDIR /root/minishell

RUN make

ENTRYPOINT ["bash", "tool/script.sh"]

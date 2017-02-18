FROM debian:latest

RUN set -x && \
    apt-get update && \
    apt-get install -y build-essential sudo \
    python3 python2.7 python-dev libzip-dev \
    automake libncurses5-dev gperf bison flex gawk \
    libtool libexpat-dev expat wget texinfo libtool-bin

RUN groupadd -g 1000 raspi && \
    useradd -g raspi -G sudo -m -s /bin/bash raspi && \
    echo 'raspi:raspi' | chpasswd

RUN mkdir -p /home/raspi/cross/src/cross/rpi \
    && mkdir /home/raspi/cross/src/cross/src \
    && mkdir /home/raspi/cross/src/ct-ng_rpi

COPY config/.config /home/raspi/cross/src/ct-ng_rpi/
COPY config/config.gen /home/raspi/cross/src/ct-ng_rpi/

RUN chown -R raspi /home/raspi/cross

USER raspi

WORKDIR /home/raspi/cross/src
RUN wget http://crosstool-ng.org/download/crosstool-ng/crosstool-ng-1.19.0.tar.bz2 \
    && tar jxvf crosstool-ng-1.19.0.tar.bz2 \
    && cd crosstool-ng-1.19.0/ \
    && ./configure --prefix=/home/raspi/cross/ \
    && make \
    && make install \
    && ln -s /home/raspi/cross/src/ct-ng_rpi/config /home/raspi/cross/lib/ct-ng.1.19.0/config

WORKDIR /home/raspi/cross/src/ct-ng_rpi

RUN /home/raspi/cross/bin/ct-ng build

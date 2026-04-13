FROM ubuntu:24.04

WORKDIR /proxy

RUN apt-get update \
    && apt-get install -y --no-install-recommends ca-certificates curl tar gzip \
    && rm -rf /var/lib/apt/lists/*

RUN curl -fL --retry 10 --retry-all-errors --connect-timeout 20 "https://github.com/graalvm/graalvm-ce-builds/releases/download/jdk-21.0.2/graalvm-community-jdk-21.0.2_linux-x64_bin.tar.gz" -o /tmp/graalvm.tar.gz \
    && mkdir -p /opt/graalvm \
    && tar -xzf /tmp/graalvm.tar.gz -C /opt/graalvm --strip-components=1 \
    && ln -sf /opt/graalvm/bin/java /usr/local/bin/java \
    && rm -f /tmp/graalvm.tar.gz

RUN curl -fL --retry 10 --retry-all-errors --connect-timeout 20 "https://fill-data.papermc.io/v1/objects/728d8408102fd5fc7477d8b21c0dc60efc713404167cc24a95665cf72111d070/velocity-3.5.0-SNAPSHOT-574.jar" -o velocity.jar

COPY velocity.toml /proxy/velocity.toml

EXPOSE 25565

CMD ["java", "-Xms256M", "-Xmx512M", "-jar", "velocity.jar"]

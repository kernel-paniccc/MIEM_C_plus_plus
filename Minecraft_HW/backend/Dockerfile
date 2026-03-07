FROM ubuntu:latest

WORKDIR /backend

RUN apt-get update \
    && apt-get install -y --no-install-recommends ca-certificates curl tar gzip

RUN curl -fL --retry 10 --retry-all-errors --connect-timeout 20 "https://github.com/graalvm/graalvm-ce-builds/releases/download/vm-21.2.0/graalvm-ce-java16-linux-amd64-21.2.0.tar.gz" -o /tmp/graalvm.tar.gz \
    && mkdir -p /opt/graalvm \
    && tar -xzf /tmp/graalvm.tar.gz -C /opt/graalvm --strip-components=1 \
    && ln -sf /opt/graalvm/bin/java /usr/local/bin/java \
    && rm -f /tmp/graalvm.tar.gz

RUN curl -fL --retry 10 --retry-all-errors --connect-timeout 20 "https://fill-data.papermc.io/v1/objects/e67da4851d08cde378ab2b89be58849238c303351ed2482181a99c2c2b489276/paper-1.16.5-794.jar" -o paper.jar

RUN echo "eula=true" > eula.txt

COPY server.properties /backend/server.properties

EXPOSE 25570

CMD ["java", "-Xms512M", "-Xmx1536M", "-jar", "paper.jar", "--nogui"]

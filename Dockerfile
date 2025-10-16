FROM debian:bookworm-slim

RUN apt-get update && apt-get install -y --no-install-recommends \
    g++ make ca-certificates && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . /app

RUN make build

VOLUME ["/data"]

ENV CSV_PATH=/data/input.csv \
    DATA_DIR=/data/db \
    LOG_LEVEL=info

CMD ["bash", "-lc", "echo \"Use: docker run --rm -v $(pwd)/data:/data tp2 ./bin/upload /data/input.csv\"; ls -l bin/"]

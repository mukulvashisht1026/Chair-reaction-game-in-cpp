FROM gcc:14 AS build
WORKDIR /src
COPY ChainReactionGame.cpp ./
RUN g++ -std=c++17 -O2 -static ChainReactionGame.cpp -o /game
FROM debian:bookworm-slim
COPY --from=build /game /game
USER 65534:65534
ENTRYPOINT ["/game"]

# Chain Reaction terminal game

Native C++ terminal game with a 10×10 board and two players. Enter zero-based row and column coordinates (`0 0` through `9 9`) when prompted. This is an interactive console program, not a web service. Invalid coordinates are rejected and EOF exits cleanly.

Requires a C++17 compiler and Make:

```sh
make build
make demo
make check
make clean
```

`make check` exercises rejection of an out-of-range coordinate, two valid moves and clean EOF. It is a smoke check, not validation of all chain-reaction rules.

Docker Engine alternative: `make docker-build && make run`. The run requires an interactive terminal; no HTTP ports are exposed. First build downloads compiler/runtime images. Docker runtime has not been verified. See [TODO.md](TODO.md) for remaining game-rule work.

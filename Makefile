CXX ?= c++
CXXFLAGS ?= -std=c++17 -Wall -Wextra
IMAGE ?= chain-reaction-game
.PHONY: build demo check docker-build run clean
build:
	$(CXX) $(CXXFLAGS) ChainReactionGame.cpp -o chain-reaction
demo: build
	./chain-reaction
check: build
	printf "%s\n" "-1 0" "0 0" "9 9" | ./chain-reaction > /dev/null
docker-build:
	docker build -t $(IMAGE) .
run:
	docker run --rm -it $(IMAGE)
clean:
	rm -f chain-reaction

CC = aarch64-linux-gnu-gcc
CFLAGS = -static
APP=temp
APP_BIN=temp-aarch64
all: $(APP)

$(APP): temp.c
	$(CC) $(CFLAGS) -o $(APP_BIN) $(APP).c

.PHONY: clean install

install:
	scp $(APP_BIN) root@192.168.0.213:/usr/bin/$(APP_BIN)

clean:
	rm -f $(APP_BIN)

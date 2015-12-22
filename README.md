#VPNPoll
Simple command line tool that shows you if you are connected
to the `ovpn.to` network or not. Also contains a small lib so
that you can use `int is_connected(void)` outside if you like.

## Building
Run `make cli`. Run `./vpn-poll` to start the program. Default
polling time is `30s` between each refresh. If you want to
modify this behavior, edit line `19` in `main.c` and change
the number `30` to an arbitrary second value.

## LICENSE
See `LICENSE`.

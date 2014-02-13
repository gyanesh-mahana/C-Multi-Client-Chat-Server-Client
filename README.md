# Command-Line Multi-user Chat Server & Client
Beginning stages of development. Goal of this project is to become aquainted with TCP/IP, pThreads, C NCurses Library, and Mutex's & Semaphores.

## Requirements
Any Linux OS will do. No support for Windows at this time.

## Dependencies
Libraries: 
* libpthread
* libcurses5-dev

## How To Build
```bash
git clone https://github.com/EmilMaric/C-Multi-Client-Chat-Server-Client.git
```
`cd` to the project root directory. Run `make` to build object files and binaries. Run `make clean` if you want to remove the object files and binaries.

On success, you will get a `cserver` or `cclient` binary file in `./server/` or `./client/` respectively.

Alternatively, if you only want to test either the client or server, a Makefile is available in either `./server/` or `./client/` with the same options as listed above. The difference is, only the object files and binaries for either the client or server will be built.

## Executing Binaries
Running the server is as simple as `./cserver`.

For the client, `./cclient <server_ip_address>`. 

## Developer Workflow
```bash
cd <project_root_dir>
make clean
make
./server/cserver

// In a new terminal
netstat -na | grep 3490   /* Port 3490 should be listening */

./client/cclient 127.0.0.1

netstat -na | grep <Port number shown on server>
```
On the server terminal, you should see text come out showing information about the client connection. You can grep for that port number to check that the server is getting the right information. 

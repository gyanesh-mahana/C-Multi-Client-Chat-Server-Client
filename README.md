# Command-Line Multi-user Chat Server & Client
Beginning stages of development. Goal of this project is to become aquainted with TCP/IP, pThreads, C NCurses Library, and Mutex's & Semaphores.

## Requirements
Any Linux OS will do. No support for Windows at this time.

## Dependencies
Libraries: 
* libpthread
* libcurses5-dev

## How To Build
```
git clone [url]
```
`cd` to either `server/` or `client/`, depending on what you want to build. 

Once inside, just run `make`, you will get a binary of either `cserver` or `cclient`.

To clean the build, run `make clean`.

## Executing Binaries
Running the server is as simple as `./cserver`.

For the client, `./cclient <server_ip_address>`. 




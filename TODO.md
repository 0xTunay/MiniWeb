# miniweb TODO

# FIRST PROJECT WITH SMART TECHNOLOGY

## 30.01.2025 First day — open the socket and launch the server 

- [ ] create `server.c/h` with init and loop functions
- [ ] open the socket (`socket()`)
- [ ] Bind the socket to a port (`bind()`)
- [ ] Listen for connection (`listen()`)
- [ ] Accept clients connections  (`accept()`)

## N Second day — develop requits

- [ ] create `request.c/h`
- [ ] read data from the socket (`recv()`)
- [ ] parse method , path, version
- [ ] separate headers from  implementation

## N third day — build answer

- [ ] create `response.c/h`
- [ ] check if the file exists, open it
- [ ] read the file and send `HTTP/1.1 200 OK`
- [ ] return 404 if the file not is found 

## N fourth day — MIME-type

- [ ] create `mime.c/h`
- [ ] Determine by extension `Content-Type`
- [ ] paste to answer


## N fifth day — log 
- [ ] create folder 'logs'
- [ ] login IP client, path, status
- [ ] log write to 'logs/access.log'


## N sixth day — build, docs, test
- [ ] realization 'CMakeLists.txt'
- [ ] write the README.md file with information:
  - how build the program
  - how start the program
- [ ] testing 'curl', 'browser', '404' , png ,html


## FUTURE ?
- [ ] 'POST' support
- [ ] configuration (port, directory)
- [ ] HTTPS (OpenSSL)
- [ ] CI/CD gitlab
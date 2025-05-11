# Minimal Web Server in C

HTTP/1.0 RELEASE



# miniweb

**miniweb** — this simple HTTP server, write on C lang.

## Сборка

for build program you need install ```cmake``` and ```gcc```


After than clone repositpry:

```bash
git clone https://gitlab.com/0xTunay/miniweb.git
cd miniweb
chmod 755 install.sh
./install.sh
```

---


## Testing

You can test any ways:

### 1. `curl`
### 2. `png`
### 3. `img`
```bash
curl http://localhost:8080/index.html
```

### Browser

Open your brower and go to:

```
http://localhost:8080/
```

### MIME-type

Check work any ways: `.html`, `.png`, `.txt` and etc.

---

## Struct project
```
miniweb/
├── CMakeLists.txt
├── include/
│   ├── mime.h
│   ├── request.h
│   ├── response.h
│   ├── server.h
├── install.sh
├── main.c
├── miniweb
├── README.md
├── src/
│   ├── mime.c
│   ├── request.c
│   ├── response.c
│   ├── server.c
├── static/
│   ├── index.html
```

## Future

- [ ] support method  `POST`
- [ ] cfg porn and directory through file
- [ ] HTTPS through OpenSSL
- [ ] CI/CD in GitLab

---
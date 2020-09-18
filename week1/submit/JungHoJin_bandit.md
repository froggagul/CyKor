# over the wire bandit 0~5
## 0~1
### 문제상황
readme에 pw 존재
### 풀이
```bash
ssh bandit0@bandit.labs.overthewire.org -p 2220
cat readme
```
### pw
boJ9jbbUNNfktd78OOpsqOltutMc3MY1

## 1~2
### 문제상황
-라는 이름의 파일 존재
### 풀이
```bash
bandit1@bandit:~$ cat ./-
CV1DtqXWVFXTvM2F0k09SHz0YwRINYA9
```
### pw
CV1DtqXWVFXTvM2F0k09SHz0YwRINYA9

## 2~3
### 문제상황
space가 들어있는 파일 이름에 pw 존재
### 풀이
```bash
bandit2@bandit:~$ ls
spaces in this filename
bandit2@bandit:~$ cat "spaces in this filename"
UmHadQclWmgdLOKQ3YNgjWxGoRMb5luK
```
### pw
UmHadQclWmgdLOKQ3YNgjWxGoRMb5luK

## 3~4
### 문제상황
inhere라는 폴더에 숨겨진 파일이 있다.

### 풀이
```bash
bandit3@bandit:~$ ls
inhere
bandit3@bandit:~$ cd inhere
bandit3@bandit:~/inhere$ ls -a
.  ..  .hidden
bandit3@bandit:~/inhere$ cat .hidden
pIwrPrtPN36QITSp3EQaw936yaFoFgAB
```
### pw
pIwrPrtPN36QITSp3EQaw936yaFoFgAB

## 4~5
### 문제상황
inhere에 있는 파일 중 사람이 읽을 수 있는 파일(ascii로 구성)에 pw가 들어있다.

### 풀이
* [참고](https://unix.stackexchange.com/questions/292253/how-to-use-cat-command-on-find-commands-output)
```
cd inhere
cat $(find . -name "-file*")
```
### pw
koReBOKuIDDepwhWk7jZC0RTdopnAYKh

# over the wire bandit 6~10
## 5~6
### 문제상황
The password for the next level is stored in a file somewhere under the inhere directory and has all of the following properties:
* human-readable
* 1033 bytes in size
* not executable

### 풀이
```bash
bandit5@bandit:~$ cd inhere
bandit5@bandit:~/inhere$ find . -size 1033c
./maybehere07/.file2
bandit5@bandit:~/inhere$ cat ./maybehere07/.file2
DXjZPULLxYr17uwoI01bNLQbtFemEgo7
```
### pw
DXjZPULLxYr17uwoI01bNLQbtFemEgo7

## 6~7
### 문제상황
The password for the next level is stored somewhere on the server and has all of the following properties:
* owned by user bandit7
* owned by group bandit6
* 33 bytes in size
### 풀이
* [find manual](https://recipes4dev.tistory.com/156)
```bash
bandit6@bandit:~$ find / -user bandit7 -group bandit6 -size 33c 2>/dev/null
/var/lib/dpkg/info/bandit7.password
bandit6@bandit:~$ find / -user bandit7 -group bandit6 -size 33c 2>/dev/null -exec cat {} \;
HKBPTKQnIay4Fw76bEy8PVxKEDQRKTzs
```
### pw
HKBPTKQnIay4Fw76bEy8PVxKEDQRKTzs

## 7~8
### 문제상황
The password for the next level is stored in the file data.txt next to the word millionth
### 풀이
```bash
bandit7@bandit:~$ grep "millionth" ./data.txt
millionth	cvX2JJa4CFALtqS87jk27qwqGhBM9plV
```
### pw
cvX2JJa4CFALtqS87jk27qwqGhBM9plV

## 8~9
### 문제상황
The password for the next level is stored in the file data.txt and is the only line of text that occurs only once
### 풀이
* [link](https://stackoverflow.com/questions/13778273/find-unique-lines)
* when using uniq, make sure lines ar sorted
```bash
bandit8@bandit:~$ cat data.txt | sort | uniq -u
UsvVyFSfZZWbi6wgC7dAFyFuR6jQQUhR

```
### pw
## 9~10
### 문제상황
The password for the next level is stored in the file data.txt in one of the few human-readable strings, preceded by several ‘=’ characters.
### 풀이
* [link](https://junho85.pe.kr/434)
    > 특정 바이너리 파일에서 문자열만 추출하고 싶을 때가 있다. 그럴 때 유용한 명령어가 strings 이다.
    > 다음과 같이 하면 문자열만 추출해준다.
    `$ strings binaryfilename`

```bash
bandit9@bandit:~$ strings data.txt | grep "===="
========== the*2i"4
========== password
Z)========== is
&========== truKLdjsbJ5g7yyJ2X2R0o3a5HQJFuLk
```
### pw
truKLdjsbJ5g7yyJ2X2R0o3a5HQJFuLk

# over the wire bandit 10~15
## 10~11
### 문제상황
The password for the next level is stored in the file data.txt, which contains base64 encoded data
### 풀이
* [base64 command](https://linuxhint.com/bash_base64_encode_decode/)
```bash
bandit10@bandit:~$ base64 -d data.txt
The password is IFukwKGsFW8MOq3IRFqrxE1hxTNEbUPR
```
### pw
IFukwKGsFW8MOq3IRFqrxE1hxTNEbUPR

## 11~12
### 문제상황
The password for the next level is stored in the file data.txt, where all lowercase (a-z) and uppercase (A-Z) letters have been rotated by 13 positions
### 풀이
* [stackoverflow](https://stackoverflow.com/questions/5442436/using-rot13-and-tr-command-for-having-an-encrypted-email-address)
* [tr command](https://www.geeksforgeeks.org/tr-command-in-unix-linux-with-examples/)
```bash
bandit11@bandit:~$ cat data.txt
Gur cnffjbeq vf 5Gr8L4qetPEsPk8htqjhRK8XSP6x2RHh
bandit11@bandit:~$ cat data.txt | tr 'A-Za-z' 'N-ZA-Mn-za-m'
The password is 5Te8Y4drgCRfCx8ugdwuEX8KFC6k2EUu
```
### pw
5Te8Y4drgCRfCx8ugdwuEX8KFC6k2EUu

## 12~13
### 문제상황
The password for the next level is stored in the file data.txt, which is a **hexdump** of a file that has been repeatedly compressed. For this level it may be useful to create a directory under /tmp in which you can work using mkdir. For example: mkdir /tmp/myname123. Then copy the datafile using cp, and rename it using mv (read the manpages!)
### 풀이
* lets change txt file to binary file, then `file <filename>` for get information of file name
```bash
bandit12@bandit:/tmp/froggagul$ xxd -r data.txt data2.bin
bandit12@bandit:/tmp/froggagul$ cat data2.bin
bandit12@bandit:/tmp/froggagul$ file data2.bin
data2.bin: gzip compressed data, was "data2.bin", last modified: Thu May  7 18:14:30 2020, max compression, from Unix
bandit12@bandit:/tmp/froggagul$ gzip -d data3.gz
bandit12@bandit:/tmp/froggagul$ ls
data3  data.txt
bandit12@bandit:/tmp/froggagul$ file data3
data3: bzip2 compressed data, block size = 900k
bandit12@bandit:/tmp/froggagul$ mv data3 data2.bz2
bandit12@bandit:/tmp/froggagul$ bunzip2 data2.bz2
bandit12@bandit:/tmp/froggagul$ file data2
data2: gzip compressed data, was "data4.bin", last modified: Thu May  7 18:14:30 2020, max compression, from Unix
bandit12@bandit:/tmp/froggagul$ mv data2 data4.bin.gz
bandit12@bandit:/tmp/froggagul$ gunzip data4.bin.gz
bandit12@bandit:/tmp/froggagul$ ls
data4.bin  data.txt
bandit12@bandit:/tmp/froggagul$ file data4.bin
data4.bin: POSIX tar archive (GNU)
(...)
bandit12@bandit:/tmp/froggagul$ file data9.bin.gz
data9.bin.gz: gzip compressed data, was "data9.bin", last modified: Thu May  7 18:14:30 2020, max compression, from Unix
bandit12@bandit:/tmp/froggagul$ gunzip data9.bin.gz
bandit12@bandit:/tmp/froggagul$ ls
data5.tar  data6.bin.tar  data7.bin.gz  data9.bin  data.txt
bandit12@bandit:/tmp/froggagul$ file data9.bin
data9.bin: ASCII text
bandit12@bandit:/tmp/froggagul$ cat data9.bin
The password is 8ZjyCRiBWFYkneahHwxCv3wb2a1ORpYL
```
### pw
8ZjyCRiBWFYkneahHwxCv3wb2a1ORpYL

## 13~14
### 문제상황
The password for the next level is stored in /etc/bandit_pass/bandit14 and can only be read by user bandit14. For this level, you don’t get the next password, but you get a private SSH key that can be used to log into the next level. Note: localhost is a hostname that refers to the machine you are working on
### 풀이
* [connecting ssh with private key](https://docs.rackspace.com/support/how-to/logging-in-with-an-ssh-private-key-on-linuxmac/)
```bash
bandit13@bandit:~$ ssh -i sshkey.private
bandit14@bandit:~$ cat /etc/bandit_pass/bandit14
4wcYUJFw0k0XLShlDzztnTBHiqxU3b3e
```
### pw
4wcYUJFw0k0XLShlDzztnTBHiqxU3b3e

## 14~15
### 문제상황
The password for the next level can be retrieved by submitting the password of the current level to port 30000 on localhost.
### 풀이
* [nc command](https://htst.tistory.com/61)
```bash
bandit14@bandit:~$ cat /etc/bandit_pass/bandit14 | nc localhost 30000
Correct!
BfMYroe26WYalil77FoDi9qh59eK5xNr
```
### pw
BfMYroe26WYalil77FoDi9qh59eK5xNr

# over the wire bandit 15~20
## 15~16
### 문제상황
The password for the next level can be retrieved by submitting the password of the current level to port **30001** on localhost using **SSL** encryption.
### 풀이
* [openssl command](https://m.blog.naver.com/jihye2340/220659855526)
* simple openssl problem
```bash
bandit15@bandit:~$ openssl s_client -connect localhost:30001
BfMYroe26WYalil77FoDi9qh59eK5xNr
Correct!
cluFn7wTiGryunymYOu4RcffSxQluehd
```
### pw
cluFn7wTiGryunymYOu4RcffSxQluehd

## 16~17
### 문제상황
The credentials for the next level can be retrieved by submitting the password of the current level to a port on localhost in the range 31000 to 32000. First find out which of these ports have a server listening on them. Then find out which of those speak SSL and which don’t. There is only 1 server that will give the next credentials, the others will simply send back to you whatever you send to it.
### 풀이
* lets search which port is open
```bash
bandit16@bandit:~$ nmap -p 31000-32000 localhost

Starting Nmap 7.40 ( https://nmap.org ) at 2020-09-18 14:10 CEST
Nmap scan report for localhost (127.0.0.1)
Host is up (0.00031s latency).
Not shown: 996 closed ports
PORT      STATE SERVICE
31046/tcp open  unknown
31518/tcp open  unknown
31691/tcp open  unknown
31790/tcp open  unknown
31960/tcp open  unknown

Nmap done: 1 IP address (1 host up) scanned in 0.11 seconds
```
* lets open every port :)
```bash
bandit16@bandit:~$ openssl s_client -connect localhost:31790

cluFn7wTiGryunymYOu4RcffSxQluehd
Correct!
-----BEGIN RSA PRIVATE KEY-----
MIIEogIBAAKCAQEAvmOkuifmMg6HL2YPIOjon6iWfbp7c3jx34YkYWqUH57SUdyJ
imZzeyGC0gtZPGujUSxiJSWI/oTqexh+cAMTSMlOJf7+BrJObArnxd9Y7YT2bRPQ
Ja6Lzb558YW3FZl87ORiO+rW4LCDCNd2lUvLE/GL2GWyuKN0K5iCd5TbtJzEkQTu
DSt2mcNn4rhAL+JFr56o4T6z8WWAW18BR6yGrMq7Q/kALHYW3OekePQAzL0VUYbW
JGTi65CxbCnzc/w4+mqQyvmzpWtMAzJTzAzQxNbkR2MBGySxDLrjg0LWN6sK7wNX
x0YVztz/zbIkPjfkU1jHS+9EbVNj+D1XFOJuaQIDAQABAoIBABagpxpM1aoLWfvD
KHcj10nqcoBc4oE11aFYQwik7xfW+24pRNuDE6SFthOar69jp5RlLwD1NhPx3iBl
J9nOM8OJ0VToum43UOS8YxF8WwhXriYGnc1sskbwpXOUDc9uX4+UESzH22P29ovd
d8WErY0gPxun8pbJLmxkAtWNhpMvfe0050vk9TL5wqbu9AlbssgTcCXkMQnPw9nC
YNN6DDP2lbcBrvgT9YCNL6C+ZKufD52yOQ9qOkwFTEQpjtF4uNtJom+asvlpmS8A
vLY9r60wYSvmZhNqBUrj7lyCtXMIu1kkd4w7F77k+DjHoAXyxcUp1DGL51sOmama
+TOWWgECgYEA8JtPxP0GRJ+IQkX262jM3dEIkza8ky5moIwUqYdsx0NxHgRRhORT
8c8hAuRBb2G82so8vUHk/fur85OEfc9TncnCY2crpoqsghifKLxrLgtT+qDpfZnx
SatLdt8GfQ85yA7hnWWJ2MxF3NaeSDm75Lsm+tBbAiyc9P2jGRNtMSkCgYEAypHd
HCctNi/FwjulhttFx/rHYKhLidZDFYeiE/v45bN4yFm8x7R/b0iE7KaszX+Exdvt
SghaTdcG0Knyw1bpJVyusavPzpaJMjdJ6tcFhVAbAjm7enCIvGCSx+X3l5SiWg0A
R57hJglezIiVjv3aGwHwvlZvtszK6zV6oXFAu0ECgYAbjo46T4hyP5tJi93V5HDi
Ttiek7xRVxUl+iU7rWkGAXFpMLFteQEsRr7PJ/lemmEY5eTDAFMLy9FL2m9oQWCg
R8VdwSk8r9FGLS+9aKcV5PI/WEKlwgXinB3OhYimtiG2Cg5JCqIZFHxD6MjEGOiu
L8ktHMPvodBwNsSBULpG0QKBgBAplTfC1HOnWiMGOU3KPwYWt0O6CdTkmJOmL8Ni
blh9elyZ9FsGxsgtRBXRsqXuz7wtsQAgLHxbdLq/ZJQ7YfzOKU4ZxEnabvXnvWkU
YOdjHdSOoKvDQNWu6ucyLRAWFuISeXw9a/9p7ftpxm0TSgyvmfLF2MIAEwyzRqaM
77pBAoGAMmjmIJdjp+Ez8duyn3ieo36yrttF5NSsJLAbxFpdlc1gvtGCWW+9Cq0b
dxviW8+TFVEBl1O4f7HVm6EpTscdDxU+bCXWkfjuRb7Dy9GOtt9JPsX8MBTakzh3
vBgsyi/sN3RqRBcGU40fOoZyfAMT8s1m/uYv52O6IgeuZ/ujbjY=
-----END RSA PRIVATE KEY-----
```
* connect by ssh
```bash
bandit16@bandit:~$ mkdir /tmp/frog
bandit16@bandit:~$ cd /tmp/frog
bandit16@bandit:/tmp/frog$ vim kkk.txt
bandit16@bandit:/tmp/frog$ mv kkk.txt kkk.private
bandit16@bandit:/tmp/frog$ chmod 400 kkk.private
bandit16@bandit:/tmp/frog$ ssh -i kkk.private bandit17@localhost
bandit17@bandit:~$ cat /etc/bandit_pass/bandit17
xLYVMN9WE5zQ5vHacb0sZEVqbrp7nBTn
```
### pw
xLYVMN9WE5zQ5vHacb0sZEVqbrp7nBTn

## 17~18
### 문제상황
There are 2 files in the homedirectory: passwords.old and passwords.new. The password for the next level is in passwords.new and is the only line that has been changed between passwords.old and passwords.new

NOTE: if you have solved this level and see ‘Byebye!’ when trying to log into bandit18, this is related to the next level, bandit19
### 풀이
* [diff command](http://www.incodom.kr/Linux/%EA%B8%B0%EB%B3%B8%EB%AA%85%EB%A0%B9%EC%96%B4/diff)
```bash
bandit17@bandit:~$ diff passwords.old passwords.new
42c42
< w0Yfolrc5bwjS4qw5mq1nnQi6mF03bii
---
> kfBf3eYk5BPBRzwjqutbbfE887SVc5Yd
```
### pw
kfBf3eYk5BPBRzwjqutbbfE887SVc5Yd

## 18~19
### 문제상황
The password for the next level is stored in a file readme in the homedirectory. Unfortunately, someone has modified .bashrc to log you out when you log in with SSH.
### 풀이
* [ssh and command](https://www.unix.com/shell-programming-and-scripting/257558-ssh-cat-file-output-into-file-local-computer.html)
```bash
froggagul@ubuntu:~/Desktop$ ssh bandit18@bandit.labs.overthewire.org -p 2220 "cat readme"
This is a OverTheWire game server. More information on http://www.overthewire.org/wargames

bandit18@bandit.labs.overthewire.org's password: 
IueksS7Ubh8G3DCwVzrTd8rAVOwq3M5x

```
### pw
IueksS7Ubh8G3DCwVzrTd8rAVOwq3M5x

## 19~20
### 문제상황
To gain access to the next level, you should use the setuid binary in the homedirectory. Execute it without arguments to find out how to use it. The password for this level can be found in the usual place (/etc/bandit_pass), after you have used the setuid binary.
### 풀이
```bash
bandit19@bandit:~$ ls
bandit20-do
bandit19@bandit:~$ ./bandit20-do
Run a command as another user.
  Example: ./bandit20-do id
bandit19@bandit:~$ ./bandit20-do cat /etc/bandit_pass/bandit20
GbKksEFF4yrVs6il55v6gwY5aVje5f0j
```
### pw
GbKksEFF4yrVs6il55v6gwY5aVje5f0j

# over the wire bandit 20~25
## 20~21
### 문제상황
There is a setuid binary in the homedirectory that does the following: it makes a connection to localhost on the port you specify as a commandline argument.
1. It then reads a line of text from the connection and
2. compares it to the password in the previous level (bandit20)
3. If the password is correct, it will transmit the password for the next level (bandit21).
### 풀이
* [simple server](https://devanix.tistory.com/307)
```bash
bandit20@bandit:~$ ./suconnect
Usage: ./suconnect <portnumber>
This program will connect to the given port on localhost using TCP. If it receives the correct password from the other side, the next password is transmitted back.
bandit20@bandit:~$ ./suconnect 22
Read: SSH-2.0-OpenSSH_7.4p1
ERROR: This doesn't match the current password!
```
* lets make simple chat service(?) by nc.
* login by bandit20 in two terminals. I will call it terminal 1 and terminal 2 from now
**termina1**
```bash
bandit20@bandit:~$ nc -l -p 1234
```
**terminal2**
```bash
bandit20@bandit:~$ ./suconnect 1234
```
**termina1**
```bash
GbKksEFF4yrVs6il55v6gwY5aVje5f0j
```
* send password of bandit20
**terminal2**
```bash
bandit20@bandit:~$ ./suconnect 1234
Read: GbKksEFF4yrVs6il55v6gwY5aVje5f0j
Password matches, sending next password
```
* checkout terminal1 and there is password.

### pw
gE269g2h3mw3pwgrj0Ha9Uoqen1c9DGr

## 21~22
### 문제상황
A program is running automatically at regular intervals from cron, the time-based job scheduler. Look in /etc/cron.d/ for the configuration and see what command is being executed.
### 풀이
```bash
bandit21@bandit:~$ cd /etc/cron.d
bandit21@bandit:/etc/cron.d$ ls -al
total 36
drwxr-xr-x  2 root root 4096 Jul 11 15:56 .
drwxr-xr-x 87 root root 4096 May 14 09:41 ..
-rw-r--r--  1 root root   62 May 14 13:40 cronjob_bandit15_root
-rw-r--r--  1 root root   62 Jul 11 15:56 cronjob_bandit17_root
-rw-r--r--  1 root root  120 May  7 20:14 cronjob_bandit22
-rw-r--r--  1 root root  122 May  7 20:14 cronjob_bandit23
-rw-r--r--  1 root root  120 May 14 09:41 cronjob_bandit24
-rw-r--r--  1 root root   62 May 14 14:04 cronjob_bandit25_root
-rw-r--r--  1 root root  102 Oct  7  2017 .placeholder
bandit21@bandit:/etc/cron.d$ cat cronjob_bandit22
@reboot bandit22 /usr/bin/cronjob_bandit22.sh &> /dev/null
* * * * * bandit22 /usr/bin/cronjob_bandit22.sh &> /dev/null
bandit21@bandit:/etc/cron.d$ cat /usr/bin/cronjob_bandit22.sh
#!/bin/bash
chmod 644 /tmp/t7O6lds9S0RqQh9aMcz6ShpAoZKF7fgv
cat /etc/bandit_pass/bandit22 > /tmp/t7O6lds9S0RqQh9aMcz6ShpAoZKF7fgv
```
* so, they are sending password of bandit22 to file in /tmp directory
* lets checkout :)
```bash
bandit21@bandit:/etc/cron.d$ cat /tmp/t7O6lds9S0RqQh9aMcz6ShpAoZKF7fgv
Yk7owGAcWjwMVRwrTesJEwB7WVOiILLI
```
### pw
Yk7owGAcWjwMVRwrTesJEwB7WVOiILLI

## 22~23
### 문제상황
A program is running automatically at regular intervals from cron, the time-based job scheduler. Look in /etc/cron.d/ for the configuration and see what command is being executed.
### 풀이
```bash
bandit22@bandit:~$ cd /etc/cron.d
bandit22@bandit:/etc/cron.d$ ls -a
.                      cronjob_bandit17_root  cronjob_bandit24
..                     cronjob_bandit22       cronjob_bandit25_root
cronjob_bandit15_root  cronjob_bandit23       .placeholder
bandit22@bandit:/etc/cron.d$ cat cronjob_bandit23
@reboot bandit23 /usr/bin/cronjob_bandit23.sh  &> /dev/null
* * * * * bandit23 /usr/bin/cronjob_bandit23.sh  &> /dev/null
bandit22@bandit:/etc/cron.d$ cat /usr/bin/cronjob_bandit23.sh
bandit22@bandit:/etc/cron.d$ cat /usr/bin/cronjob_bandit23.sh
#!/bin/bash

myname=$(whoami)
mytarget=$(echo I am user $myname | md5sum | cut -d ' ' -f 1)

echo "Copying passwordfile /etc/bandit_pass/$myname to /tmp/$mytarget"

cat /etc/bandit_pass/$myname > /tmp/$mytarget
```
* they are passing password to /tmp/$mytarget
* and my we can get $mytarget by executing in shell
```bash
bandit22@bandit:/etc/cron.d$ echo I am user bandit23 | md5sum | cut -d ' ' -f 1 | cat
8ca319486bfbbc3663ea0fbe81326349
bandit22@bandit:/etc/cron.d$ cat /tmp/8ca319486bfbbc3663ea0fbe81326349
jc1udXuA1tiHqjIsL8yaapX5XIAI6i0n
```

### pw
jc1udXuA1tiHqjIsL8yaapX5XIAI6i0n

## 23~24
### 문제상황
A program is running automatically at regular intervals from cron, the time-based job scheduler. Look in /etc/cron.d/ for the configuration and see what command is being executed.

NOTE: This level requires you to create your own first shell-script. This is a very big step and you should be proud of yourself when you beat this level!

NOTE 2: Keep in mind that your shell script is removed once executed, so you may want to keep a copy around…
### 풀이
```bash
bandit23@bandit:~$ cd /etc/cron.d
bandit23@bandit:/etc/cron.d$ ls
cronjob_bandit15_root  cronjob_bandit22  cronjob_bandit24
cronjob_bandit17_root  cronjob_bandit23  cronjob_bandit25_root
bandit23@bandit:/etc/cron.d$ cat cronjob_bandit24
@reboot bandit24 /usr/bin/cronjob_bandit24.sh &> /dev/null
* * * * * bandit24 /usr/bin/cronjob_bandit24.sh &> /dev/null
bandit23@bandit:/etc/cron.d$ cat /usr/bin/cronjob_bandit24/sh
cat: /usr/bin/cronjob_bandit24/sh: No such file or directory
bandit23@bandit:/etc/cron.d$ cat /usr/bin/cronjob_bandit24.sh
#!/bin/bash

myname=$(whoami)

cd /var/spool/$myname
echo "Executing and deleting all scripts in /var/spool/$myname:"
for i in * .*;
do
    if [ "$i" != "." -a "$i" != ".." ];
    then
        echo "Handling $i"
        owner="$(stat --format "%U" ./$i)"
        if [ "${owner}" = "bandit23" ]; then
            timeout -s 9 60 ./$i
        fi
        rm -f ./$i
    fi
done

```
* cron executes every 1minute
```bash
bandit23@bandit:/var/spool/bandit24$ cat lol.sh
#!/bin/sh

cat /etc/bandit_pass/bandit24 > ./pass
bandit23@bandit:/var/spool/bandit24$ cat ./pass
UoMYTrfrBFHyQXmg6gzctqAwOmw1IohZ
```

### pw
UoMYTrfrBFHyQXmg6gzctqAwOmw1IohZ

## 24~25
### 문제상황
A daemon is listening on port 30002 and will give you the password for bandit25 if given the password for bandit24 and a secret numeric 4-digit pincode. There is no way to retrieve the pincode except by going through all of the 10000 combinations, called brute-forcing.
### 풀이
```bash
bandit24@bandit:~$ nc localhost 30002
I am the pincode checker for user bandit25. Please enter the password for user bandit24 and the secret pincode on a single line, separated by a space.
```
```python
import socket
import sys

password = "UoMYTrfrBFHyQXmg6gzctqAwOmw1IohZ"
try:
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = ('127.0.0.1', 30002)
    sock.connect(server_address)
    msg = sock.recv(2048)
    print(msg)
    for i in range(10000):
        pin = str(i).zfill(4)
        message = password + " " + pin + "\n"
        sock.sendall(message.encode())
        msg = sock.recv(1024)
        if "Wrong" in msg:
            print("wrong", pin)
        else:
            print(pin, msg)
            break
    sock.close()
finally:
    sys.exit(1)
```
```bash
('2588', 'Correct!\nThe password of user bandit25 is uNG9O58gUE7snukf3bvZ0rxhtnjzSGzG\n\nExiting.\n')
```
### pw
uNG9O58gUE7snukf3bvZ0rxhtnjzSGzG
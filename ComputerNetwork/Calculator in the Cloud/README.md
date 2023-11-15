# [Computer Network] Calculator in the Cloud
Create network application that calculator program using Java socket API.

## Requirements

- 클라이언트가 계산을 요청하면 서버가 계산해서 클라이언트로 결과 보내줌
- 사칙연산이 가능
- 서버 thread 처리
- 프로토콜 기반 메시지 전송/수신/해석
- 서버의 ip address와 port number는 외부 파일로 만들어 사용 (serverinfo.dat)

## Protocol

### Server to Client

**[ERROR]**

- [400] format error

- [401] not number

- [402] not operator

- [403] divided by ZERO



### Client to Server
**[CALCULATE]**

`[operator] [first number] [second number]`

- operator : add, sub, mul, div (not case-sensitive)
- 각 요소는 스페이스로 구분한다.

**[EXIT]**

if you want exit program, enter `q` (not case-sensitive)

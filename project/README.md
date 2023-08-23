# Project Template

### 개요

본 레포지토리는 아주대학교 소프트웨어학과 소학회 한터의 2023학년도 하계 시스템 프로그래밍 스터디 프로젝트의 탬플릿 입니다.

<br>

### 프로젝트 상세

본 레포지토리는 시스템 프로그래밍 관련 프로젝트를 더욱 손쉽게 진행할 수 있도록 `GPIO`, `PWM`, `SPI` 등의 여러 라이브러리를 구성해 두었습니다.

또한 이러한 전체 라이브러리 및 메인 함수를 Cmake를 활용하여 빌드 자동화 환경을 구축하여 간편하게 빌드 및 테스트가 가능합니다.

라이브러리에 대한 개별 설명은 다음과 같습니다.
- `GPIO` : GPIO 제어 라이브러리
- `PWM` : PWM 제어 라이브러리
- `SPI` : SPI 제어 라이브러리
- `LCD` : WIRINGPI 활용 LCD 제어 라이브러리
- `SOCKET` : SOCKET 생성 및 제어 라이브러리
- `UTILS` : THREAD 등 유틸리티 라이브러리
- `PARSON` : JSON 파싱 라이브러리

<br>

### 프로젝트 실행

``` bash
user@raspberrypi:~/project $ sudo apt-get install cmake
user@raspberrypi:~/project $ sudo apt-get install libcurl4-openssl-dev
user@raspberrypi:~/project $ sudo apt-get install wiringpi
user@raspberrypi:~/project $ mkdir build
user@raspberrypi:~/project $ cd build
user@raspberrypi:~/project/build $ cmake ..
user@raspberrypi:~/project/build $ make
user@raspberrypi:~/project/build $ ./main.out
```

<br>

### 프로젝트 구조

``` text
├── README.md
└── project
    ├── CMakeLists.txt  // CMake 설정 
    ├── build           // 빌드 디렉토리
    ├── include         // 내부 라이브러리 디렉토리
    │   ├── gpio.c
    │   ├── gpio.h
    │   ├── lcd.c
    │   ├── lcd.h
    │   ├── pwm.c
    │   ├── pwm.h
    │   ├── socket.c
    │   ├── socket.h
    │   ├── spi.c
    │   ├── spi.h
    │   ├── utils.c
    │   └── utils.h
    ├── lib             // 외부 라이브러리 디렉토리
    │   ├── parson.c
    │   └── parson.h
    └── src             // 소스 디렉토리
        └── main.c
```

<br>

### 참고 문헌
- [CMake 로 빌드시스템 생성하기](https://velog.io/@soopsaram/CMake-로-빌드시스템-생성하기)
- [CMake 할때 쪼오오금 도움이 되는 문서](https://gist.github.com/luncliff/6e2d4eb7ca29a0afd5b592f72b80cb5c)
- [C++ Project Structure and Cross-Platform Build With CMake](https://medium.com/swlh/c-project-structure-for-cmake-67d60135f6f5)
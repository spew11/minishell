## 소개
Linux BashShell의 핵심기능을 구현한 프로젝트 입니다.

## 프로젝트 진행 기간
설계 및 주요 기능 구현: 2022.11.12 ~ 2023.12.22

## 제공하는 기능
- 절대 경로/상대 경로를 기준으로 excutable 파일을 실행합니다.
- 워킹 히스토리를 제공합니다.
- 파이프를 통해 프로세스 간 통신(IPC)이 가능합니다.
- redirection, heredoc, pipe 를 동시에 사용하는 명령어들 처리를 제공합니다.
- PATH 변수를 포함한 환경 변수를 관리할 수 있습니다.
- '$'를 통해서 execute status를 확인할 수 있습니다.
- ectrl-C, ctrl-D 및 ctrl-\의 기능은 Bash와 동일합니다.
- 다음과 같은 내장 기능이 포함되어 있습니다.
    -  echo (옵션 n 제공)
    -  cd (절대변수/상대변수)
    -  pwd
    -  export
    -  unset
    -  env
    -  exit

## 팀원 소개

<section >
  <table>
      <tr>
          <td align=center><a href="https://github.com/spew11">이은지</a></td> 
          <td align=center><a href="https://github.com/izone00">정우진</a></td>
      </tr>
      <tr>
          <td>
            - IPC 구현 </br>
          - 내장함수 구현 </br>
          - 환경변수 자료구조 구현 </br>
          - Signal 구현 </br>
          - docker 격리 </br>
          </td>
          <td>
            - 명령어 구조 설계</br>
          - 명령어 자료 구조 구현 </br>
          - 파서 구현</br>
          - heredoc 구현</td>
      </tr>
      </tr>
  </table>
</section>
<br/>

<section>

## 서비스 화면


## 실행 방법
Docker 설치가 필요합니다.
```bash
git clone https://github.com/spew11/minishell.git && \
  cd minishell && make
``` 
--------------------

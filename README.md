# 🐚 MiniShell

## 🚀 소개  
🔹 **Linux BashShell의 핵심 기능을 C 언어로 구현한 프로젝트입니다.**  


## 🗓️ 프로젝트 진행 기간  
📅 **설계 및 주요 기능 구현:** `2022.11.12 ~ 2023.12.22`


## ⚡ 제공하는 기능  
✅ **Excutable 실행**: 절대 경로/상대 경로 기반 실행 가능  
✅ **히스토리 기능**: 실행 명령어 워킹 히스토리 제공  
✅ **프로세스 간 통신(IPC)**: pipe를 통한 데이터 전달 가능  
✅ **입출력 리디렉션 지원**: `redirection`, `heredoc`, `pipe` 동시에 사용 가능  
✅ **환경 변수 관리**: `PATH` 변수 포함, `$`로 실행 상태 확인 가능  
✅ **시그널 핸들링 지원**: `ctrl-C`, `ctrl-D`, `ctrl-\`의 Bash와 동일한 동작  
✅ **내장 명령어(Built-in Commands) 지원**  
   - `echo` (옵션 `-n` 지원)  
   - `cd` (절대/상대 경로 이동)  
   - `pwd`  
   - `export`  
   - `unset`  
   - `env`  
   - `exit`  


## 👥 팀원

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/spew11">
        <img src="https://github.com/spew11.png" width="100" height="100"><br>
        <b>spew11</b>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/izone00">
        <img src="https://github.com/izone00.png" width="100" height="100"><br>
        <b>izone</b>
      </a>
    </td>
  </tr>
  <tr>
    <td valign="top">
      🔹 <b>IPC 구현</b> <br>
      🔹 <b>내장함수 구현</b> <br>
      🔹 <b>환경변수 자료구조 구현</b> <br>
      🔹 <b>Signal 구현</b> <br>
      🔹 <b>Docker 이미지 구축</b> <br>
    </td>
    <td valign="top">
      🔹 <b>명령어 구조 설계</b> <br>
      🔹 <b>명령어 자료 구조 구현</b> <br>
      🔹 <b>파서 구현</b> <br>
      🔹 <b>heredoc 구현</b> <br>
    </td>
  </tr>
</table>

---

## 🖥️ 실행 화면  
![MINISHELL](https://github.com/spew11/minishell/assets/95565246/ce020cbc-7d1a-440d-82e7-aea5304a81f7)

---

## 🚀 실행 방법  
**🛠️ Docker 설치가 필요합니다.**  
```bash
git clone https://github.com/spew11/minishell.git && \
  cd minishell && make

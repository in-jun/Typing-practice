# C++ 코드 실행 방법

이 코드는 C++ 언어로 작성된 콘솔 애플리케이션입니다. 코드를 실행하기 위해서는 다음 단계를 따르세요.

1. C++ 컴파일러를 설치하세요. 대표적인 C++ 컴파일러로는 gcc 이 있습니다.
2. 텍스트 에디터를 열고 `main.cpp` 파일을 생성하세요.
3. 코드를 복사하여 `main.cpp` 파일에 붙여넣으세요.
4. 컴파일러를 사용하여 코드를 컴파일하세요. 예를 들어, gcc를 사용하여 컴파일하려면 터미널에서 다음 명령어를 실행하세요.

```
g++ -o main main.cpp
```

5. 컴파일이 완료되면, 실행 파일을 실행하세요. 예를 들어, 터미널에서 다음 명령어를 실행하여 실행 파일을 실행할 수 있습니다.

```
./main
```

6. 코드가 실행되면, 타이핑 게임이 시작됩니다. 단어를 올바르게 입력하면 다음 단어가 나타나고, 타이핑 오류가 있으면 `typo` 수가 증가합니다.

# 코드 목적

이 코드는 타이핑 게임을 구현한 예제입니다. 코드는 `words` 배열에 저장된 단어들을 사용하여 게임을 시작합니다. 각 단어를 정확하게 타이핑하는 것이 목적입니다. 게임은 무한 반복되며, 타이핑 오류가 발생할 때마다 `typo` 수가 증가합니다.
# Grundlagen der Programmierung Exam Wintersemester 20/21

Compile command:

```shell
g++ -Wall -std=c++17 -I . -o bin/main \
    apps/main.cpp \
    src/Bank.cpp \
    src/Database.cpp \
    src/Filesystem.cpp \
    src/PriceCalculator.cpp \
    src/Stop.cpp \
    src/StopCollection.cpp \
    src/UserInterface.cpp
```

Execute the generated binary:

```shell
bin/main
```

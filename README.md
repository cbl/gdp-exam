# Grundlagen der Programmierung Exam Wintersemester 20/21

## Setup

Compile command:

```shell
g++ -Wall -std=c++17 -I . -Os -o main \
    main.cpp \
    Bank.cpp \
    Database.cpp \
    Filesystem.cpp \
    PriceCalculator.cpp \
    Stop.cpp \
    StopCollection.cpp \
    TerminalUserInterface.cpp
```

Execute the generated binary:

```shell
./main
```

## Testing

### Run Tests

To run the unit tests the tests have to be compiled first:

```shell
g++ -Wall -std=c++17 -I . -o bin/test_database test/test_database.cpp && \
g++ -Wall -std=c++17 -I . -o bin/test_price_calculator test/test_price_calculator.cpp && \
g++ -Wall -std=c++17 -I . -o bin/test_stop_collection test/test_stop_collection.cpp && \
g++ -Wall -std=c++17 -I . -o bin/test test/test.cpp
```

These can then be executed:

```shell
bin/test_database && \
bin/test_price_calculator && \
bin/test_stop_collection && \
bin/test
```

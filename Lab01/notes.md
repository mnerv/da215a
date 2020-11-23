# L01:  Avläsning av tangentbord

## Table of content

- [L01:  Avläsning av tangentbord](#l01--avläsning-av-tangentbord)
  - [Table of content](#table-of-content)
  - [Grundläggande programkod](#grundläggande-programkod)
    - [3.2.1](#321)
    - [3.2.2](#322)
    - [3.2.3](#323)
    - [3.2.4](#324)
    - [3.2.5](#325)
    - [3.2.6](#326)
    - [3.2.7](#327)
  - [Avläsning av ett fåtal knappar](#avläsning-av-ett-fåtal-knappar)
    - [5.2.2](#522)
    - [5.2.3](#523)
    - [5.3.2](#532)
    - [5.3.3](#533)
  - [Inkoppling av avkodare och multiplexer](#inkoppling-av-avkodare-och-multiplexer)
    - [6.4.1](#641)
    - [6.4.2](#642)
    - [6.4.3](#643)
    - [6.4.4](#644)
  - [Komplett tangentbordsdrivrutin](#komplett-tangentbordsdrivrutin)
    - [7.2.1](#721)
    - [7.2.3](#723)
    - [7.2.4](#724)
    - [7.2.5](#725)
    - [7.2.6](#726)
    - [7.2.7](#727)
    - [7.2.8](#728)
    - [7.2.8](#728-1)
    - [7.2.9](#729)
    - [7.2.10](#7210)

## Grundläggande programkod

### 3.2.1

`.CSEG`: lets the compiler switch to the code section

`.ORG RESET`: The start of the instruction in EERPOM

These two make sure that the compiler put the program in the correct memory space.

`RJMP init`: Jumps to where the init subroutine is.

`.ORG PM_START`: This address to a program memory

### 3.2.2

TODO

### 3.2.3

TODO

### 3.2.4

```
0b10000000 --> 0x80
```

### 3.2.5

Set bit

```
SBI PORTC, 0x07 ; Set PORTC
```

### 3.2.6

Clear bit

```
CBI PORTC, 0x07
```

### 3.2.7

No operation

```
NOP
```

## Avläsning av ett fåtal knappar

### 5.2.2

### 5.2.3

### 5.3.2

### 5.3.3

## Inkoppling av avkodare och multiplexer

### 6.4.1

### 6.4.2

### 6.4.3

### 6.4.4

## Komplett tangentbordsdrivrutin

### 7.2.1

### 7.2.3

### 7.2.4

### 7.2.5

### 7.2.6

### 7.2.7

### 7.2.8

### 7.2.8

### 7.2.9

### 7.2.10
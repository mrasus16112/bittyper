# BitTyper: The best way to decrease your typing speed.

## How it works

```
7 6 5 4  3 2 1 0
a s d f  j k l ;
```

In BitTyper, you press individual keys that will flip bits of a byte (the "current byte") that will then be written to a file. As you can see on the chart, pressing the A key will flip bit at position 7, and pressing ; will flip bit at position 0.
Once you have finished writing the current byte, press SPACE to write it to the file.

## Registers

By default, you will have 8 registers that can store one byte each. You can set the current byte to a register's value, and you can set a register to the current byte. This allows you to use registers like shortcuts. You can also increase the amount of registers you can have (up to 255). Then again, if you're using this program, you probably don't want shortcuts to aid your esoteric typing mission.

## Commands

h: toggle <ins>h</ins>exadecimal representation<br>
b: <ins>b</ins>reak the binary representation up (for example, `1011010` becomes `1011  1010`. it makes it easier to type with in my opinion)<br>
c: toggle <ins>c</ins>learing the current byte after writing it to the file


# BitTyper: The best way to decrease your typing speed.

## How it works

```
7 6 5 4  3 2 1 0
a s d f  j k l ;
```

In BitTyper, you press individual keys that will flip bits of a byte (the "current byte") that will then be written to a file. As you can see on the chart, pressing the A key will flip bit at position 7, and pressing ; will flip bit at position 0.
Once you have finished writing the current byte, press SPACE to write it to the file.

## Commands

h: toggle <u>h</u>exadecimal representation<br>
b: <u>b</u>reak the binary representation up (for example, `1011010` becomes `1011  1010`. it makes it easier to type with in my opinion)<br>
c: toggle <u>c</u>learing the current byte after writing it to the file

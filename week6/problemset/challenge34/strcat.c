/* This file was generated by the Hex-Rays decompiler.
   Copyright (c) 2007-2019 Hex-Rays <info@hex-rays.com>

   Detected compiler: GNU C++
*/

#include <defs.h>


//-------------------------------------------------------------------------
// Function declarations

__int64 (**init_proc())(void);
__int64 sub_400710();
// void free(void *ptr);
// int putchar(int c);
// int puts(const char *s);
// size_t strlen(const char *s);
// int system(const char *command);
// int printf(const char *format, ...);
// unsigned int alarm(unsigned int seconds);
// ssize_t read(int fd, void *buf, size_t nbytes);
// __sighandler_t signal(int sig, __sighandler_t handler);
// void *malloc(size_t size);
// int setvbuf(FILE *stream, char *buf, int modes, size_t n);
// int atoi(const char *nptr);
// void __noreturn exit(int status);
// void __usercall __noreturn start(__int64 a1@<rax>, void (*a2)(void)@<rdx>);
signed __int64 deregister_tm_clones();
__int64 register_tm_clones();
signed __int64 _do_global_dtors_aux();
__int64 frame_dummy();
void __noreturn handler();
unsigned int setup();
int win();
int print_menu();
__int64 __fastcall readline(void *a1, int a2);
__int64 read_int32();
int __cdecl main(int argc, const char **argv, const char **envp);
void _libc_csu_init(void); // idb
void _libc_csu_fini(void); // idb
void term_proc();
// int __fastcall _libc_start_main(int (__fastcall *main)(int, char **, char **), int argc, char **ubp_av, void (*init)(void), void (*fini)(void), void (*rtld_fini)(void), void *stack_end);
// __int64 _gmon_start__(void); weak

//-------------------------------------------------------------------------
// Data declarations

__int64 (__fastcall *_frame_dummy_init_array_entry[2])() = { &frame_dummy, &_do_global_dtors_aux }; // weak
__int64 (__fastcall *_do_global_dtors_aux_fini_array_entry)() = &_do_global_dtors_aux; // weak
__int64 (*qword_602010)(void) = NULL; // weak
_UNKNOWN _bss_start; // weak
_UNKNOWN unk_602097; // weak
FILE IO_2_1_stdout_; // idb
FILE IO_2_1_stdin_; // idb
char completed_7561; // weak
int maxlen; // weak
char name[128]; // idb
char *desc; // idb


//----- (00000000004006F8) ----------------------------------------------------
__int64 (**init_proc())(void)
{
  __int64 (**result)(void); // rax

  result = &_gmon_start__;
  if ( &_gmon_start__ )
    result = (__int64 (**)(void))_gmon_start__();
  return result;
}
// 6023A0: using guessed type __int64 _gmon_start__(void);

//----- (0000000000400710) ----------------------------------------------------
__int64 sub_400710()
{
  return qword_602010();
}
// 602010: using guessed type __int64 (*qword_602010)(void);

//----- (00000000004007F0) ----------------------------------------------------
// positive sp value has been detected, the output may be wrong!
void __usercall __noreturn start(__int64 a1@<rax>, void (*a2)(void)@<rdx>)
{
  int v2; // esi
  __int64 v3; // [rsp-8h] [rbp-8h]
  char *retaddr; // [rsp+0h] [rbp+0h]

  v2 = v3;
  v3 = a1;
  _libc_start_main(
    (int (__fastcall *)(int, char **, char **))main,
    v2,
    &retaddr,
    _libc_csu_init,
    _libc_csu_fini,
    a2,
    &v3);
  __halt();
}
// 4007F6: positive sp value 8 has been found

//----- (0000000000400820) ----------------------------------------------------
signed __int64 deregister_tm_clones()
{
  signed __int64 result; // rax

  result = &unk_602097 - &_bss_start;
  if ( (unsigned __int64)(&unk_602097 - &_bss_start) > 0xE )
    result = 0LL;
  return result;
}

//----- (0000000000400860) ----------------------------------------------------
__int64 register_tm_clones()
{
  return 0LL;
}

//----- (00000000004008A0) ----------------------------------------------------
signed __int64 _do_global_dtors_aux()
{
  signed __int64 result; // rax

  if ( !completed_7561 )
  {
    result = deregister_tm_clones();
    completed_7561 = 1;
  }
  return result;
}
// 602260: using guessed type char completed_7561;

//----- (00000000004008C0) ----------------------------------------------------
__int64 frame_dummy()
{
  return register_tm_clones();
}
// 4008C0: could not find valid save-restore pair for rbp

//----- (00000000004008E6) ----------------------------------------------------
void __noreturn handler()
{
  exit(1);
}

//----- (00000000004008F4) ----------------------------------------------------
unsigned int setup()
{
  setvbuf(&IO_2_1_stdout_, 0LL, 2, 0LL);
  setvbuf(&IO_2_1_stdin_, 0LL, 2, 0LL);
  signal(14, (__sighandler_t)handler);
  return alarm(0x3Cu);
}

//----- (000000000040094C) ----------------------------------------------------
int win()
{
  return system("cat flag");
}

//----- (000000000040095F) ----------------------------------------------------
int print_menu()
{
  return puts("Menu:\n1. Concat to name.\n2. Edit description.\n3. Print it all.");
}

//----- (0000000000400972) ----------------------------------------------------
__int64 __fastcall readline(void *a1, int a2)
{
  int v2; // eax

  read(0, a1, a2);
  v2 = strlen(name);
  *((_BYTE *)a1 + v2 - 1) = 0;
  return (unsigned int)(v2 - 1);
}

//----- (00000000004009BF) ----------------------------------------------------
__int64 read_int32()
{
  unsigned int v1; // [rsp+4h] [rbp-Ch]
  char *nptr; // [rsp+8h] [rbp-8h]

  nptr = (char *)malloc(0x20uLL);
  readline(nptr, 32);
  v1 = atoi(nptr);
  free(nptr);
  return v1;
}

//----- (0000000000400A06) ----------------------------------------------------
int __cdecl __noreturn main(int argc, const char **argv, const char **envp)
{
  int v3; // eax
  int v4; // ebx
  int v5; // ebx
  size_t v6; // rax

  setup();
  puts("My strcat");
  maxlen = 128;
  printf("Name: ", argv);
  maxlen -= readline(name, 128);
  desc = (char *)malloc(0x20uLL);
  printf("Desc: ");
  readline(desc, 32);
  while ( 1 )
  {
    print_menu();
    printf("> ");
    v3 = read_int32();
    switch ( v3 )
    {
      case 2:
        printf("Desc: ");
        readline(desc, 32);
        break;
      case 3:
        printf(name);
        printf(desc);
        putchar(10);
        break;
      case 1:
        printf("Name: ");
        v4 = maxlen;
        v5 = v4 - strlen(name);
        v6 = strlen(name);
        maxlen -= readline(&name[v6], v5);
        break;
      default:
        puts("Invalid");
        break;
    }
  }
}
// 602280: using guessed type int maxlen;

//----- (0000000000400B90) ----------------------------------------------------
void _libc_csu_init(void)
{
  signed __int64 v0; // rbp
  __int64 i; // rbx

  v0 = &_do_global_dtors_aux_fini_array_entry - _frame_dummy_init_array_entry;
  init_proc();
  if ( v0 )
  {
    for ( i = 0LL; i != v0; ++i )
      _frame_dummy_init_array_entry[i]();
  }
}
// 601E08: using guessed type __int64 (__fastcall *_frame_dummy_init_array_entry[2])();
// 601E10: using guessed type __int64 (__fastcall *_do_global_dtors_aux_fini_array_entry)();

//----- (0000000000400C04) ----------------------------------------------------
void term_proc()
{
  ;
}

// nfuncs=45 queued=16 decompiled=16 lumina nreq=0 worse=0 better=0
// ALL OK, 16 function(s) have been successfully decompiled
